#!/bin/bash


exec 3>pipe 

for i in {1..10}
do
    echo 'write2' > pipe;
    sleep 1
done

exec 3>&- 
