#! /bin/bash

make clean;
make;
cp P2Tests/*.ss .; # copy all test cases
array=$(ls P2Tests/ | cut -d '.' -f1 | sort -u); # create list of files
#pwd;
#./P2.out 01P1.ss
for i in ${array[@]}
do
	./P2.out $i.ss;
	diff -qs $i.ss $i.p2.ss;
 pwd;
done
