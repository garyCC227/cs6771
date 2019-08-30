#!/bin/bash

bin="./bazel-bin/assignments/wl/main"
if [[ "$OSTYPE" == "darwin"* ]]
then
    reference_bin="./assignments/wl/reference_solution_osx"
elif [[ "$OSTYPE" == "linux-gnu" ]]
then
    reference_bin="./assignments/wl/reference_solution"
fi
dict="./assignments/wl/words.txt"
time_bin="time"

mkdir -p temp/failed


bazel build //assignments/wl:main

if [[ $? -ne 0 ]]
then
    echo "Build failed"
    exit 1
fi

echo "Randomising dictionary..."
sort --random-sort assignments/wl/words.txt > temp/words.txt

line=1
while true
do
    if test $line -gt 120000
    then
        line=1
        sort --random-sort assignments/wl/words.txt > temp/words.txt
    fi

    start=`sed -n "$line""p" temp/words.txt`
    line=$((line + 1))

    # skip short or long words
    if test ${#start} -ge 6 || test ${#start} -le 3
    then
        continue
    fi

    # find next word with same length
    while ! test ${#start} -eq ${#end}
    do
        end=`sed -n "$line""p" temp/words.txt`
        line=$((line + 1))
    done

    echo "testing" $start "->" $end
    echo "testing" $start "->" $end >> temp/timing
    echo "Your time:" >> temp/timing
    echo -e "$start\n$end\n" | time $bin > temp/output 2>> temp/timing
    echo "Ref. solution's time:" >> temp/timing
    echo -e "$start\n$end\n" | time $reference_bin > temp/correct 2>> temp/timing
    grep "No ladder found" temp/correct > /dev/null
    if test $? -eq 0
    then
        n_ladders=0
        echo "No ladders"
    else
        n_ladders=`wc -l temp/correct | awk '{print $1}'`
        echo "$start -> $end $n_ladders ladders" >> temp/ladders
        echo "Found (approx.) $n_ladders ladders"
    fi

    diff temp/output temp/correct
    if test $? -ne 0
    then
        echo "[WRONG] $start -> $end failed, see output in ./temp/failed"
        mv temp/output "temp/failed/$start""_""$end""_""out"
        mv temp/correct "temp/failed/$start""_""$end""_""correct"
    fi

    echo
    echo "=============================="
    echo

done