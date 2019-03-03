FROM ubuntu:16.04

ENV csapp3e /opt/csapp3e
WORKDIR ${csapp3e}

# the following instruction makes it possible to install softwares
RUN apt-get update && apt-get install apt-file -y && apt-file update

# install the packages we need to do the labs
RUN apt-get install -y vim make gcc libc6-dev-i386
