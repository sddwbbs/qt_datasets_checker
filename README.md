# Qt application

An application written in C++ using the Qt library, built with the CMake build system, and utilizing a PostgreSQL database to store user account data. The application and database run within Docker containers. 
Its primary function is to download and display datasets from https://www.kaggle.com/.

## Installation (Linux, WSL)

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

## Launch

To run the application correctly, you will need:
```
xhost +local:docker

sudo docker-compose up
```

## Possible problems

If any of the windows appear blank/black try this:
https://stackoverflow.com/questions/52501594/qt-app-ui-elements-randomly-rendered-as-blank-black-in-docker
