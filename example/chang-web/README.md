# chang-web

## Install
Search Google

## Build
```
$ docker build -t chang-web .
```

## Run
```
$ docker run -d -p 3000:3000 chang-web /bin/bash
```

## Stop
```
$ docker stop {CONTAINER ID}
```


## Check
브라우저 http://localhost:3000


## Dockerfile 구조 설명
```
// Ubuntu 20.04 버전을 베이스 이미지 지정
FROM ubuntu:20.04

// Time zone을 서울로 수정
ENV TZ=Asia/Seoul
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

// apt 패키지 다운로드 서버를 카카오로 바꾸기
RUN sed -ie 's/archive.ubuntu.com/mirror.kakao.com/g' /etc/apt/sources.list

// apt 업데이트 및 업그레이드
RUN apt-get update && apt-get -y upgrade && apt-get -y autoremove

// 필요한 프로그램 설치
RUN apt-get install -y python3 \
                    python3-pip \
                    vim

// 현재 디렉토리를 도커 이미지 환경에 복사
COPY ./ /chang-web 

// 현재 작업 디렉토리를 /chang-web으로 변경
WORKDIR /chang-web

// flask 파이썬 라이브러리 설치
RUN pip3 install flask

// 3000 포트를 개방하겠다 명시
EXPOSE 3000

// runserver.py을 실행 -> 웹서버 실행
CMD python3 runserver.py
```
