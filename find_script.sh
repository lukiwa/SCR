#!/bin/bash

#"$(cd ~; pwd)" - znajdz wszystko od katalogu home
#-mtime -$2  - znajdz co zostalo zmodyfikowane $2 dni temu do teraz
#-name - o rozszerzeniu $1


files=$(find $(cd ~/Desktop; pwd) -name "*.$1" -mtime -$2);


#stworz puste archiwum o nazwie $3.tar
tar -cf $3.tar --files-from /dev/null

for path in $files; do
    tar -rf $3.tar $path -P
done
