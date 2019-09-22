FROM debian:buster
ENV DEBIAN_FRONTEND noninteractive

RUN echo "deb-src http://deb.debian.org/debian buster main" >> /etc/apt/sources.list
ADD basic_debian_setup.sh /
RUN /basic_debian_setup.sh && rm /basic_debian_setup.sh

# docker
RUN apt update && apt install -y apt-transport-https ca-certificates \
                  curl gnupg2 software-properties-common &&\
    curl -fsSL https://download.docker.com/linux/debian/gpg | apt-key add - &&\
    apt-key fingerprint 0EBFCD88 &&\
    add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/debian buster stable" &&\
    apt update && apt install -y docker-ce

# for development
RUN apt update && apt install -y\
    bear \
    build-essential \
    cargo \
    ccache \
    cgdb \
    clang \
    clang-format \
    clang-tidy \
    cmake \
    cppcheck \
    cppreference-doc-en-html \
    doxygen \
    exuberant-ctags \
    g++ \
    gcc \
    gcc-multilib \
    g++-multilib \
    gdb \
    gdbserver \
    graphviz \
    lcov \
    libboost-all-dev \
    libpython-all-dev \
    linux-perf \
    man \
    make \
    ninja-build \
    pandoc \
    pyflakes \
    pylint \
    python2.7 \
    python3 \
    python3-pip \
    python-docutils \
    python-doc \
    python3-doc \
    python-pip \
    qemu \
    qemu-kvm \
    qemu-user \
    rst2pdf \
    rsync \
    rr \
    rtags \
    ssh \
    texinfo \
    tig \
    tmux \
    tree \
    unzip \
    valgrind \
    vim-gtk \
    xz-utils
# yapf
RUN pip3 install yapf

# vim coc autocomplete
RUN apt update && apt install -y yarnpkg
RUN echo "deb http://apt.llvm.org/buster/ llvm-toolchain-buster main" >> /etc/apt/sources.list &&\
    wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key| apt-key add - &&\
    apt update && apt install -y clang-10 lldb-10 lld-10 clangd-10
