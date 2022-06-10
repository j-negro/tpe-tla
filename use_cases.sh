#!/bin/bash
# for each file in use_cases directory pipe it to ./bin/Compiler
# and save errors in array

errors=( )
for file in ./use_cases/*
do
  echo "Compiling $file"
  cat "$file" | ./bin/Compiler
  if [ $? -ne 0 ]; then
    errors[${#errors[@]}]=$file
  fi
done

for error in "${errors[@]}"
do
  echo "Error in $error"
done
