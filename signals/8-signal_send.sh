#!/usr/bin/bash

if [ $# -eq 0 ]; then
	echo "Usage: $0 <pid>"
	exit 1
fi

pid=$1

kill -3 $pid
