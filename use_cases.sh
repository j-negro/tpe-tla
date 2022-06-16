#!/bin/bash
# for each file in use_cases directory pipe it to ./bin/Compiler
# and save errors in array

errors=( )
cd use_cases
for file in *
do
  cd ..
  cat use_cases/"$file" | bin/Compiler &> logs/"$file".log
  if [ $? -ne 0 ]; then
    errors[${#errors[@]}]=$file
  fi
  cd use_cases
done

for error in "${errors[@]}"
do
  echo "Error in $error"
done
