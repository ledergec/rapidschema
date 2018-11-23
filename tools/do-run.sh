cd "$(dirname "$0")"

IP=$(ifconfig en0 | grep inet | awk '$1=="inet" {print $2}')
xhost + $IP

socat TCP-LISTEN:6000,reuseaddr,fork UNIX-CLIENT:\"$DISPLAY\" &

open -a XQuartz &

docker rm rapidoson-dev-container

docker run -it \
    --entrypoint /bin/bash \
    -u root \
    -e DISPLAY=$(ifconfig en0 | grep inet | awk '$1=="inet" {print $2}'):0 \
    --name rapidoson-dev-container \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v `pwd`/.java:/root/.java \
    -v ${HOME}/.Xauthority:/home/dev/.Xauthority \
    -v `pwd`/.CLion2018.2:/root/.CLion2018.2 \
    -v `pwd`/..:/home/dev/rapidoson \
    rapidoson-dev-image