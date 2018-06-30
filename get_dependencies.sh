#!/bin/bash

deps=$(g++ -MM $1)
deps_array=($deps)

sources=()

objname=${deps_array[0]}
objname_no_colon=$(echo $objname | sed "s/://g")
targetname=${deps_array[1]}

echo -n build/$objname
echo -n " "

for i in $deps; do
  if [ -f $i ]; then
    sources+=" $i"
    echo -n $i
    echo -n " "
  fi
done

for i in $sources; do
  cppname=$(basename $i .h).cpp
  if [ -f $cppname ] && [[ $cppname != $objname_no_colon.cpp ]]; then
    echo -n $cppname
    echo -n " "
  fi
done

echo
echo -e \\t g++ -Wall -c -o build/$objname_no_colon $targetname
