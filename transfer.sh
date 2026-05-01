rsync -av --delete \
    --exclude='.git' \
    --exclude='.build' \
    --exclude='anim' \
    --exclude='lib/' \
    . anim@192.168.1.89:~/anim/
