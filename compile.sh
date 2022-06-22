#!/bin/bash
set -e

#Compiles the program $1 and copies MVN project to directory $2
if [ $# -eq 0 ]; then
  echo "No arguments supplied";
  exit 1;
fi
if [ -z "$1" ]; then
  echo "No program supplied";
fi

cat "$1" | bin/Compiler &> compile.log;

if [ $# -lt 2 ]; then
  cp -r src/backend/generated-java/source_classes/ "$PWD";
  exit 0;
fi

if [ -z "$2" ]; then
  echo "No directory supplied";
  exit 1;
fi

cp -r src/backend/generated-java/source_classes/ "$2";
exit 0;