FROM        ubuntu:bionic
MAINTAINER  christian

# update and install dependencies
RUN         apt-get update \
                && apt-get install -y \ 
		build-essential \
		cmake \
		emacs \
		git \
		sudo \
		&& apt-get clean \
		&& rm -rf /var/lib/apt/lists/*

ENTRYPOINT [ "sh", "-c", "echo $HOME" ]

RUN useradd -d /home/dev -ms /bin/bash -g root -G sudo -p dev dev
RUN adduser dev sudo
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers
ENV HOME /home/dev
USER dev
WORKDIR /home/dev