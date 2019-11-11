FROM        ubuntu:bionic
MAINTAINER  christian


########################################################
# Essential packages for remote debugging and login in
########################################################

RUN apt-get update && apt-get upgrade -y && apt-get install -y \
    openssh-server \
    gdb \
    gdbserver \
    rsync && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir /var/run/sshd
RUN echo 'root:root' | chpasswd
RUN sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

# SSH login fix. Otherwise user is kicked off after login
RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd

ENV NOTVISIBLE "in users profile"
RUN echo "export VISIBLE=now" >> /etc/profile

# 22 for ssh server. 7777 for gdb server.
EXPOSE 22 7777

RUN useradd -ms /bin/bash debugger
RUN echo 'debugger:pwd' | chpasswd

########################################################
# Add custom packages and development environment here
########################################################

# update and install dependencies
RUN apt-get update && \
    apt-get install -y \ 
    	    build-essential \
	    cmake \
	    cppcheck \
	    dia \
	    doxygen \
	    emacs \
	    gcc-8 \
	    g++-8 \
	    git \
	    graphviz \
	    libgtk2.0-0 \
	    libxslt1.1 \
	    mscgen \
	    python-pip \
	    sudo \
	    valgrind \
	    wget && \
	    apt-get clean && \
	    rm -rf /var/lib/apt/lists/*

# Make gcc / g++ 8 the default
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 700 --slave /usr/bin/g++ g++ /usr/bin/g++-7 && \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 800 --slave /usr/bin/g++ g++ /usr/bin/g++-8

