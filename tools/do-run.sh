if [ $# -eq 0 ]
  then
    echo "usage: do-run.sh path-to-rapidoson"
    exit
fi

docker run -it \
    --entrypoint /bin/bash \
    --name rapidoson-dev-container \
    -v $1:/home/dev \
    rapidoson-dev-image