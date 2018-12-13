cd "$(dirname "$0")"

xhost +

# socat TCP-LISTEN:6000,reuseaddr,fork UNIX-CLIENT:\"$DISPLAY\" &

# open -a XQuartz &

IP=$(ifconfig en0 | grep inet | awk '$1=="inet" {print $2}')

docker rm rapidschema-dev-container

docker run -it \
    --entrypoint /bin/bash \
    -u root \
    -e DISPLAY=$IP:0 \
    --name rapidschema-dev-container \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v `pwd`/.java:/root/.java:delegated \
    -v ${HOME}/.Xauthority:/home/dev/.Xauthority \
    -v `pwd`/.CLion2018.2:/root/.CLion2018.2:delegated \
    -v `pwd`/../../..:/home/dev/rapidschema:delegated \
    rapidschema-dev-image