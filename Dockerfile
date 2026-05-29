FROM ubuntu:24.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y \
    git python3-pip python3-venv pipx \
    build-essential gcc unzip wget zip \
    gcc-avr binutils-avr avr-libc dfu-programmer dfu-util \
    gcc-arm-none-eabi binutils-arm-none-eabi libnewlib-arm-none-eabi \
    && rm -rf /var/lib/apt/lists/*
ENV PATH="/root/.local/bin:$PATH"
RUN pipx install qmk
RUN qmk setup -y
CMD qmk compile -kb gmmk/pro -km default
