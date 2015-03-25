#!/usr/bin/env bash

docker run -ti --rm -e DISPLAY=$DISPLAY --device /dev/video0:/dev/video0 -v /tmp/.X11-unix:/tmp/.X11-unix -v $PWD:/source wictory/parallax_edu ./capture_show
