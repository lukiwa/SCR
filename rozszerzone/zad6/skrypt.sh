#!/bin/bash

trap "echo trap" {1..15}


while :
do
    date +"%T"
    sleep 1
done
