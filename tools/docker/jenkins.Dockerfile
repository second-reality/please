FROM jenkins/jenkins:lts

ENV DEBIAN_FRONTEND noninteractive

USER root
ADD debian_install_docker.sh /
RUN /debian_install_docker.sh && rm /debian_install_docker.sh

# fix jenkins shitty entry point
# Permission denied - /var/jenkins_home/copy_reference_file.log
RUN sed -i /usr/local/bin/jenkins.sh -e 's/touch.*$//g' /usr/local/bin/jenkins.sh
RUN sed -i /usr/local/bin/jenkins.sh -e 's/.*jenkins-support.*$//g' /usr/local/bin/jenkins.sh
RUN sed -i /usr/local/bin/jenkins.sh -e 's/.*COPY_REFERENCE_FILE_LOG.*$//g' /usr/local/bin/jenkins.sh
RUN cat /usr/local/bin/jenkins.sh
