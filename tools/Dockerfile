FROM        ubuntu:bionic
MAINTAINER  christian

# update and install dependencies
RUN apt-get update && \
    apt-get install -y \ 
    	    build-essential \
	    cmake \
	    emacs \
	    git \
	    python-pip \
	    sudo \
	    valgrind \
	    wget && \
	    apt-get clean && \
	    rm -rf /var/lib/apt/lists/*

RUN pip install cpplint

RUN mkdir /home/dev

RUN wget https://download.jetbrains.com/cpp/CLion-2018.2.6.tar.gz && \
    tar -C /home/dev -zxvf CLion-2018.2.6.tar.gz && \
    rm CLion-2018.2.6.tar.gz
    
RUN echo '' >> /home/dev/.bashrc && \
    echo 'alias clion=/home/dev/clion-2018.2.6/bin/clion.sh' >> /home/dev/.bashrc

ENTRYPOINT [ "sh", "-c", "echo $HOME" ]

RUN useradd -d /home/dev -ms /bin/bash -g root -G sudo -p dev dev
RUN adduser dev sudo
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers
ENV HOME /home/dev
RUN mkdir /home/dev/rapidschema
USER dev
WORKDIR /home/dev