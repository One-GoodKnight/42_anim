REMOTE_IP=$(cat vm_ip.txt)

if [ -z "$REMOTE_IP" ]; then
    echo "Error: ip.txt is empty or not found."
    exit 1
fi

rsync -av --delete \
    --exclude='.git' \
    --exclude='.build' \
    --exclude='anim' \
    --exclude='lib/' \
    . anim@${REMOTE_IP}:~/anim/
