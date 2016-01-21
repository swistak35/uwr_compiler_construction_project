#!/bin/sh

# set -x
echo -n "Running '$1'... "

cat "tests/$1.input" | ./calculator > tmp/test_output
result=$?

if [ -f "tests/$1.output" ]
then
  diff tmp/test_output "tests/$1.output" > tmp/diff_output

  if [ $? -ne 0 ]
  then
    echo "FAILED"
    cat tmp/diff_output
  else
    echo "OK"
  fi
else
  if [ $result -ne 0 ]
  then
    echo "FAILED"
  else
    echo "OK"
  fi
fi

