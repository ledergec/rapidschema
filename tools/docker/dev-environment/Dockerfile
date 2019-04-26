FROM        ubuntu:bionic
MAINTAINER  christian

# update and install dependencies
RUN apt-get update && \
    apt-get install -y \ 
    	    build-essential \
	    cmake \
	    emacs \
	    gcc-8 \
	    g++-8 \
	    git \
	    libgtk2.0-0 \
	    libxslt1.1 \
	    python-pip \
	    sudo \
	    valgrind \
	    wget && \
	    apt-get clean && \
	    rm -rf /var/lib/apt/lists/*

# Make gcc / g++ 8 the default
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 700 --slave /usr/bin/g++ g++ /usr/bin/g++-7 && \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 800 --slave /usr/bin/g++ g++ /usr/bin/g++-8

RUN mkdir /home/dev

ENV CLION_VERSION=2019.1.2

RUN wget https://download.jetbrains.com/cpp/CLion-$CLION_VERSION.tar.gz && \
    tar -C /home/dev -zxvf CLion-$CLION_VERSION.tar.gz && \
    rm CLion-$CLION_VERSION.tar.gz
    
RUN echo '' >> /home/dev/.bashrc && \
    echo 'alias clion=/home/dev/clion-$CLION_VERSION/bin/clion.sh' >> /home/dev/.bashrc

ENTRYPOINT [ "sh", "-c", "echo $HOME" ]

RUN useradd -d /home/dev -ms /bin/bash -g root -G sudo -p dev dev
RUN adduser dev sudo
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers
ENV HOME /home/dev
RUN mkdir /home/dev/rapidschema
USER dev
WORKDIR /home/dev