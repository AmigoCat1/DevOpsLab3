FROM alpine AS build
RUN apk add --no-cache build-base automake autoconf

WORKDIR /home/DevOpsLab3

COPY . .
RUN autoreconf --install
RUN ./configure
RUN make

FROM alpine
COPY --from=build /home/DevOpsLab3/FuncCosh /usr/local/bin/FuncCosh
ENTRYPOINT ["/usr/local/bin/FuncCosh"]
