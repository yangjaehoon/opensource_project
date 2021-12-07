FROM ubuntu:20.04

ENV TZ=Asia/Seoul
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN sed -ie 's/archive.ubuntu.com/mirror.kakao.com/g' /etc/apt/sources.list

RUN apt-get update && apt-get -y upgrade && apt-get -y autoremove

RUN apt-get install -y python3 \
                    python3-pip \
                    vim

COPY ./ /chang-web 
WORKDIR /chang-web

RUN pip3 install flask

EXPOSE 3000
CMD python3 runserver.py