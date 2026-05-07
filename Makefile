NAME			:= anim
BUILD_DIR		:= .build

SRC_DIR			:= src
SRCS			:= 								\
	file_op/read_file.c							\
												\
	gnl/gnl.c									\
	gnl/gnl_utils.c								\
												\
	loops/game_loop.c							\
	loops/lobby_loop.c							\
												\
	game/check_win.c							\
	game/nb_question.c							\
	game/question.c								\
	game/shuf_str_question.c					\
	game/str_question.c							\
												\
												\
	net/actions/send.c							\
	net/actions/listen.c						\
												\
	net/change_state/handle_conflicts.c			\
	net/change_state/set_initial_state.c		\
												\
	net/process_msg/process_msg_host.c			\
	net/process_msg/process_msg_client.c		\
												\
	net/get_addr.c								\
	net/network.c								\
	net/setup_sock_addr.c						\
												\
												\
	ui/render_ui/render_anim_text.c				\
	ui/render_ui/render_corners.c				\
	ui/render_ui/render_input.c					\
	ui/render_ui/render_ui.c					\
												\
	ui/update_ui/floating_corners.c				\
	ui/update_ui/pid_controller.c				\
	ui/update_ui/update_ui.c					\
												\
	ui/init_ui.c								\
												\
												\
	utils/utf8.c								\
	utils/utils.c								\
	utils/utils_n.c								\
	utils/utils_str.c							\
	utils/utils_uchar.c							\
												\
	window/init_window.c						\
	window/input.c								\
												\
	init.c										\
	main.c										\
												\
	vector.c									\

INCLUDES		:= 								\
	include										\

LIB_DIR			:= lib
LIBS			:=								\
	raylib

RAYLIB_GIT      := https://github.com/raysan5/raylib.git
RAYLIB_VERSION	:= 6.0
RAYLIB_DIR		:= external/raylib
RAYLIB_A        := $(LIB_DIR)/libraylib.a


SRCS			:= $(SRCS:%=$(SRC_DIR)/%)
OBJS			:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS			:= $(OBJS:.o=.d)

CC				:= cc
CFLAGS			:= -Wall -Wextra -g3
CPPFLAGS		:= $(addprefix -I,$(INCLUDES)) -MMD -MP
LDFLAGS 		:= -L$(LIB_DIR) $(addprefix -l,$(LIBS))	\
				   -lm -ldl -lpthread -lGL -lX11		\

all: $(NAME)

$(NAME): $(OBJS) $(RAYLIB_A)
	$(CC) $^ $(LDFLAGS) -o $@

$(RAYLIB_A):
	@echo "Building Raylib $(RAYLIB_VERSION)..."
	@mkdir -p external $(LIB_DIR)
	@git clone --depth 1 --branch $(RAYLIB_VERSION) $(RAYLIB_GIT) $(RAYLIB_DIR)	--quiet -c advice.detachedHead=false
	@cd $(RAYLIB_DIR)/src
	@$(MAKE) -C $(RAYLIB_DIR)/src PLATFORM=PLATFORM_DESKTOP --silent 2>/dev/null
	@cp $(RAYLIB_DIR)/src/libraylib.a $(LIB_DIR)
	@rm -rf external/

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME)

val: all
	valgrind --leak-check=full --suppressions=val.supp ./anim

.PHONY: all clean fclean re
