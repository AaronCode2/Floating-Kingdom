FROM ubuntu:latest

RUN apt update && apt install -y \
    build-essential cmake git \
    libx11-dev libxcursor-dev libxrandr-dev libxinerama-dev \
    libgl1-mesa-dev libxi-dev

WORKDIR /app
COPY . .


RUN mkdir -p build && cd build && cmake .. && make


CMD ["./build/Floating_Kingdom"]