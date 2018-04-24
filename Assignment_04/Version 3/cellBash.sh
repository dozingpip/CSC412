#!/bin/bash


pipe=/tmp/testpipe

trap "rm -f $pipe" EXIT

if [[ ! -p $pipe ]]; then
    mkfifo $pipe
fi

exec 3<> $pipe

./cell $1 $2 $3 &

echo "input: "
while true
do
    if read line; then
        if echo $line >$pipe; then
            if [[ "$line" == 'end' ]]; then
                break
            fi
        fi
    fi
done
sleep .5
echo "Reader exiting"