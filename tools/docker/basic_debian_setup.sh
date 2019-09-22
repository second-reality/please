#!/bin/bash

# create user
# to get sound, we must have pulse audio installed
# to get vulkan, we must have mesa drivers installed
# allows to get autocomplete for package install inside container

dpkg --add-architecture i386 &&
mkdir /etc/sudoers.d/ &&
echo "user ALL=(root) NOPASSWD:ALL" >> /etc/sudoers.d/user &&
chmod 0440 /etc/sudoers.d/user &&
adduser user&&
apt update &&
apt install -y\
    alsa-utils\
    apt-utils \
    bash-completion \
    coreutils \
    elinks \
    ffmpeg \
    git \
    htop \
    imagemagick \
    iptables \
    locales-all \
    lsof \
    mesa*drivers\
    mesa-utils\
    net-tools \
    pulseaudio\
    ncdu \
    software-properties-common \
    rsync \
    strace \
    sudo \
    tig \
    time \
    tree \
    tmux \
    vim-gtk \
    vulkan-utils \
    x11-apps \
    xclip \
    xz-utils \
    zip \
    wget &&
apt upgrade -y &&
rm /etc/apt/apt.conf.d/docker-clean && apt update
