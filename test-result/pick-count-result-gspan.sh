#! /bin/bash

if [[ $# -lt 1 ]]; then
  echo 'Compuate the approximate number of generated motifs of gSpan (gBolt after my modification).'
  echo 'Usage: <log-file>';
  exit
fi

log_file=$1;

b=$(grep 'node(s)' $log_file | cut -d ' ' -f 7)

echo $b

