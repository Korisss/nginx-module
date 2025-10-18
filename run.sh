#!/bin/bash

set -o allexport
source .env
set +o allexport

WORKDIR=$(pwd)

mkdir -p $WORKDIR/build/nginx/conf
cp $WORKDIR/nginx.conf $WORKDIR/build/nginx/conf/nginx.conf
mkdir -p $WORKDIR/build/nginx/logs

$WORKDIR/build/nginx-$NGINX_VERSION/objs/nginx
