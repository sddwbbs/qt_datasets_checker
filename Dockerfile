FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y && \
    apt-get install -y libxcb-xinerama0 \
    libxcb-xinerama0-dev \
    g++ \
    qtcreator \
    qtbase5-dev \
    qtwayland5-dev-tools \
    qtwayland5 \
    cmake \
    plasma-widgets-addons \
    plasma-desktop \
    make \
    git -y

COPY . /app
WORKDIR /app

RUN rm -rf build && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make

ENTRYPOINT ["/app/build/qt_http_service"]