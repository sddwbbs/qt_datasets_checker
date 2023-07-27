# Qt application

An application written in C++ using the Qt library, built with the CMake build system, and utilizing a PostgreSQL database to store user account data. The application and database run within Docker containers. 
Its primary function is to download and display datasets from https://www.kaggle.com/.

## Installation 

### Linux, WSL

First, you need to install the Docker and Docker Compose packages from the official repositories.

using `pacman`:
```
sudo pacman -S docker docker-compose
```

using `apt`: 
```
sudo apt-get install docker docker-compose
```

After that, you will need to clone the repository:
```
git clone git@github.com:sddwbbs/qt_http_service.git
cd qt_http_service
```

### macOS

clone the repository:
```
git clone git@github.com:sddwbbs/qt_http_service.git
cd qt_http_service
```

- Go to the XQuartz website: Open your web browser and visit the XQuartz website at [https://www.xquartz.org/](https://www.xquartz.org/).
- Download the latest version: On the XQuartz website, you will find a link to download the latest version of XQuartz. Click on the download link to get the installation package.

Install `socat`: 
```
brew install socat
```

Start `socat`:
```
socat TCP-LISTEN:6000,reuseaddr,fork UNIX-CLIENT:\"$DISPLAY\"
```

## Launch 

### Linux, WSL

```
xhost +local:docker

sudo docker-compose up
```

### macOS

```
IP=$(ifconfig en0 | grep inet | awk '$1=="inet" {print $2}') xhost + $IP

docker-compose up
```


## Possible problems

If any of the windows appear blank/black try this:
https://stackoverflow.com/questions/52501594/qt-app-ui-elements-randomly-rendered-as-blank-black-in-docker
