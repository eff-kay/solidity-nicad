FROM --platform=x86_64 python:3.10

COPY . /nicad6

WORKDIR /nicad6

RUN tar -xvzf docker/5699-txl10.8b.linux64.tar.gz && cd txl10.8b.linux64 && ./InstallTxl && cd .. && make

CMD ["bash", "docker/execute_cloning"]
