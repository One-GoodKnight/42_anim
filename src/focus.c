#include "focus.h"
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

static const char *g_title;

static Window find_window_by_title(Display *d, Window root, const char *title)
{
    Window parent, *children;
    unsigned int nchildren;
    if (!XQueryTree(d, root, &root, &parent, &children, &nchildren))
        return 0;

    Window result = 0;
    for (unsigned int i = 0; i < nchildren && !result; i++)
    {
        char *name = NULL;
        if (XFetchName(d, children[i], &name) && name)
        {
            if (strstr(name, title))
                result = children[i];
            XFree(name);
        }
        if (!result)
            result = find_window_by_title(d, children[i], title);
    }
    if (children) XFree(children);
    return result;
}

static void activate_window(Display *d, Window w)
{
    Window root = DefaultRootWindow(d);
    Atom net_active = XInternAtom(d, "_NET_ACTIVE_WINDOW", False);

    XEvent e = {0};
    e.type                 = ClientMessage;
    e.xclient.display      = d;
    e.xclient.window       = w;
    e.xclient.message_type = net_active;
    e.xclient.format       = 32;
    e.xclient.data.l[0]    = 1;
    e.xclient.data.l[1]    = CurrentTime;
    e.xclient.data.l[2]    = 0;

    XSendEvent(d, root, False,
               SubstructureNotifyMask | SubstructureRedirectMask, &e);
    XFlush(d);
}

static void *focus_thread(void *arg)
{
    (void)arg;

    Display *d = XOpenDisplay(NULL);
    if (!d) return NULL;

    while (1)
    {
        sleep(3);
        Window w = find_window_by_title(d, DefaultRootWindow(d), g_title);
        if (w) activate_window(d, w);
    }

    XCloseDisplay(d);
    return NULL;
}

void start_focus_thread(const char *window_title)
{
    g_title = window_title;
    pthread_t tid;
    pthread_create(&tid, NULL, focus_thread, NULL);
    pthread_detach(tid);
}
