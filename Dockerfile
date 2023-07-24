FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y && \
    apt-get install -y libxcb-xinerama0 \
    libxcb-xinerama0-dev \
    g++ \
    qtwebengine5-dev \
    libgl1-mesa-dev \
    qtbase5-dev \
    qtwayland5-dev-tools \
    qtwayland5 \
    cmake \
    plasma-widgets-addons \
#    plasma-desktop \
    make \
    git \
    build-essential \
    extra-cmake-modules \
    libsm-dev \
#    frei0r-plugins \
#    ffmpeg \
    libkf5archive-dev \
    libkf5bookmarks-dev \
    libkf5coreaddons-dev \
    libkf5config-dev \
    libkf5configwidgets-dev \
    libkf5dbusaddons-dev \
    libkf5kio-dev \
    libqt5sql5-psql \
    libkf5widgetsaddons-dev \
    libkf5notifyconfig-dev \
    libkf5newstuff-dev \
    libkf5xmlgui-dev \
    libkf5declarative-dev \
    libkf5notifications-dev \
    libkf5guiaddons-dev \
    libkf5textwidgets-dev \
    libkf5purpose-dev \
    libkf5iconthemes-dev \
    libkf5crash-dev \
    libkf5filemetadata-dev \
    libkf5codecs-dev \
#    kio \
#    kinit \
    qtdeclarative5-dev \
    libqt5svg5-dev \
    qml-module-qtquick-controls \
    libqt5networkauth5-dev \
    qtmultimedia5-dev \
    qtquickcontrols2-5-dev \
    qttools5-dev \
#    breeze-icon-theme \
#    breeze \
#    libxml++2.6-dev \
#    libavformat-dev \
#    libswscale-dev \
#    libavfilter-dev \
#    libavutil-dev \
#    libavdevice-dev \
#    libsdl1.2-dev \
#    librtaudio-dev \
#    libsox-dev \
#    libsamplerate0-dev \
#    librubberband-dev \
#    libebur128-dev \
#    ruby \
#    subversion \
#    gnupg2 \
    postgresql \
    postgresql-contrib \
    x11-xserver-utils \
    libpq-dev \
    gettext -y

COPY . /app
WORKDIR /app

#RUN apt-get update && apt-get install -y x11-xserver-utils

# Add xhost +local:docker command
#RUN xhost +local:docker

# Set the DISPLAY environment variable
#ENV DISPLAY=:0

# Mount the X11 Unix domain socket
#VOLUME /tmp/.X11-unix:/tmp/.X11-unix

# Set the environment variable for QT_X11_NO_MITSHM
ENV QT_X11_NO_MITSHM=1

RUN rm -rf build && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make

# Start PostgreSQL when the container is run
CMD /app/build/qt_http_service --no-sandbox