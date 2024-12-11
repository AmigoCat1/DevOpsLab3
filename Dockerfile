FROM ubuntu:latest
RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    autoconf \
    automake \
    libtool \
    pkg-config

WORKDIR /optima
COPY . /optima

RUN autoreconf --install && ./configure && make

EXPOSE 8081

CMD ["./FuncCosh"]
