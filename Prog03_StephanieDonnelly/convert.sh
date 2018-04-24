#!/bin/bash
copyFirst=$1'copy'
copySecond=$2'copy'

mkdir $copyFirst
for entry in "$1/"*; do
	newFile=$copyFirst/${entry##*/}
	cp $entry $newFile
	tr -d '\r' < $entry > $newFile
	rm $entry
	mv $newFile $1
	
done
rm -r $copyFirst

mkdir $copySecond
for entry in "$2/"*; do
	newFile=$copySecond/${entry##*/}
        cp $entry $newFile
        tr -d '\r' < $entry > $newFile
	rm $entry
	mv $newFile $2
done
rm -r $copySecond

