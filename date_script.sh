#!/bin/bash

LC_ALL=C

dayData=$(date | awk '{print $1;}');

if [ "$dayData" = "Sat" ] || [ "$dayData" = "Sun" ]; then
    echo "Nareszcie weekend!"
else
    echo "Czas do pracy!"
fi
