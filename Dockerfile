FROM ubuntu:24.04
# FROM docker.m.daocloud.io/library/ubuntu:24.04

# install dependencies
ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get -y install git vim wget build-essential cmake bear tmux libomp-dev \
    python3.12 python3.12-dev python3-setuptools python3-pip \
    clang llvm libclang-dev clang-format

# set work directory
COPY . /promefuzz
WORKDIR /promefuzz
ENTRYPOINT []

# install Python dependencies
RUN rm /usr/lib/python*/EXTERNALLY-MANAGED
RUN python3 -m pip install -r requirements.txt --ignore-installed pyyaml
# RUN python3 -m pip install -i https://pypi.tuna.tsinghua.edu.cn/simple/ -r requirements.txt --ignore-installed pyyaml


# install AFL++
RUN wget -O /root/aflpp.tar.gz https://github.com/AFLplusplus/AFLplusplus/archive/refs/tags/v4.33c.tar.gz
# RUN wget -O /root/aflpp.tar.gz https://ghfast.top/https://github.com/AFLplusplus/AFLplusplus/archive/refs/tags/v4.33c.tar.gz
RUN cd /root && tar -xzf aflpp.tar.gz --transform 's,^AFLplusplus-[^/]*,AFLplusplus,' && \
    cd /root/AFLplusplus && make source-only && make install
ENV AFLPP_PATH=/root/AFLplusplus

# build
RUN chmod +x ./setup.sh && ./setup.sh
