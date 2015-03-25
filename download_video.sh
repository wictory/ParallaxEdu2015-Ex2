#!/usr/bin/env bash

url=http://clips.vorwaerts-gmbh.de/big_buck_bunny.ogv

docker run -ti --rm -v $PWD:/source wictory/parallax_edu wget $url
