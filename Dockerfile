FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential cmake \
    libgoogle-glog-dev libevent-dev \
    libboost-dev libconcurrentqueue-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN mkdir -p build && cd build && cmake .. && make -j$(nproc)

EXPOSE 3653
CMD ["./build/bin/mfc", "0.0.0.0", "3653", "4"]
