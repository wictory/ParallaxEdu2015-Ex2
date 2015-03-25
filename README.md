
# ParallaxEdu2015-Ex2
This repository contains second exercise and its solution for Parallax Education Day 2015. In addition, it also consists of a test program to test your environment setup. The details are given below.

## Requirements

1. An x86_64 CPU
2. Preferably a Linux OS 
3. [Docker](https://docs.docker.com/installation/)
4. An programming editor

## Environment Setup

The exercise uses

1. [OpenCV](http://opencv.org)
2. [Git](http://git-scm.com/), and
3. C++11

### Setup without docker (on Ubuntu)

If this works for you, you can also run the exercise without docker :) 

```bash
$ sudo apt-get install build-essential pocl-opencl-icd clinfo cmake git opencl-headers ocl-icd-opencl-dev libopencv*-dev
```

### Setup using docker


You can install these components independently on your own, or use a docker image which has all the necessary components included. The following steps assumes that you are using the docker image.

* To use the docker image, [Docker](https://docs.docker.com/installation/) needs to be installed. Start docker using terminal in linux based systems or boot2docker in non-linux based systems. When running boot2docker, a terminal window pops up.
* To clone this repository in your workspace run the following command. Here it is assumed to be your home directory.
```bash
$ git clone https://github.com/wictory/ParallaxEdu2015-Ex2.git
```
* To test the docker image, run to see gcc installed in the docker image. Type the following window in the terminal (In Linux systems, docker runs as priviledged user. So you might need to use `sudo`) 
```bash
$ docker run -ti --rm wictory/parallax_edu g++ --version
```

* To run the exercise you need to bind a directory to your docker container. You should preferably make a new directory, enter it and start your docker container.
```bash
$ cd $HOME
$ mkdir parallax_education_day
$ cd parallax_education_day
$ docker run -ti --rm -v $PWD:/src wictory/parallax_edu git clone https://github.com/wictory/ParallaxEdu2015-Ex2.git
$ cd ParallaxEdu2015-Ex2
$ ./compile_capture_show.sh # Compile capture_show.cpp
$ ./run_capture_show_webcam.sh # Run the program using the webcam (only works on Linux)
```
