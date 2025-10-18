#!/bin/bash

set -o allexport
source .env
set +o allexport

WORKDIR=$(pwd)

cd $WORKDIR/build/nginx-$NGINX_VERSION
make
