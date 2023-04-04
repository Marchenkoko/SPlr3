FROM ubuntu

RUN apt update && apt install -y gcc

COPY ./main.c .

RUN gcc ./main.c -o progC
