#!/bin/bash

set -o allexport
source .env
set +o allexport

WORKDIR=$(pwd)

if [ ! -d $WORKDIR/build ]; then
	mkdir $WORKDIR/build
fi

if [[ ! -f $WORKDIR/build/nginx-$NGINX_VERSION.tar.gz ]]; then
    wget https://nginx.org/download/nginx-$NGINX_VERSION.tar.gz -P $WORKDIR/build
fi

if [ ! -d $WORKDIR/build/nginx-$NGINX_VERSION ]; then
    tar xf $WORKDIR/build/nginx-$NGINX_VERSION.tar.gz -C $WORKDIR/build
fi

rm -rf $WORKDIR/build/nginx
mkdir $WORKDIR/build/nginx
cd $WORKDIR/build/nginx-$NGINX_VERSION
./configure --add-dynamic-module=$WORKDIR --prefix="$WORKDIR/build/nginx"

echo $NGINX_VERSION