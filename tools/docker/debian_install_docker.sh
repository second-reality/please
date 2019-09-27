#!/usr/bin/env bash

debian_version=$(cat /etc/os-release | grep VERSION_CODENAME | cut  -d '=' -f 2)

apt update && apt install -y apt-transport-https ca-certificates \
              curl gnupg2 software-properties-common &&\
 curl -fsSL https://download.docker.com/linux/debian/gpg | apt-key add - &&\
 apt-key fingerprint 0EBFCD88 &&\
 add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/debian $debian_version stable" &&\
 apt update && apt install -y docker-ce docker-compose
