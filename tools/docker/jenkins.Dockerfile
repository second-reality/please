FROM jenkins/jenkins:lts

ENV DEBIAN_FRONTEND noninteractive

USER root
ADD debian_install_docker.sh /
RUN /debian_install_docker.sh && rm /debian_install_docker.sh

USER jenkins
