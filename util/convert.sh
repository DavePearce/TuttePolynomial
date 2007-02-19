#!/bin/sh

FILES=$@

CONVERT=$HOME/projects/tuttepoly/util/convert

for f in $FILES
do
 echo "CONVERTING $f ... "
 $CONVERT < $f > $f.dat
done

