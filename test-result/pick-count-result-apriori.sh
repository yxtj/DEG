#! /bin/bash

if [[ $# -lt 2 ]]; then
  echo 'Compuate the approximate number of generated motifs of apriori.'
  echo 'Usage: <res-file> <log-file>';
  exit
fi

res_file=$1;
log_file=$2;

a=$(wc -l $res_file | cut -d ' ' -f 1)
b=$(grep 'node(s)' $log_file | cut -d ' ' -f 5 | cut -b2-)

echo $((a+b))

