#!/bin/bash

number=2
while [ $number -le 9 ]
do
	n=1
	while [ $n -le 9 ]
	do
		printf "$(( $number * $n )) "
		((n++))
	done
	((number++))
	printf "\n"
done

exit 0
