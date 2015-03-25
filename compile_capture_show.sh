#!/usr/bin/env bash

docker run -ti --rm -v $PWD:/source wictory/parallax_edu g++ -std=c++11 -lopencv_core -lopencv_imgproc -lopencv_highgui -pthread -o capture_show ./capture_show.cpp
