#! /bin/bash

> diff.res;
make clean;
make;
cp P2Tests/*.ss .; # copy all test cases

array=$(ls P2Tests/ | cut -d '.' -f1 | sort -u); # create list of files

for i in ${array[@]}
do
	./P2.out $i.ss;
	diff -qs P2Tests/$i.p2 $i.p2 >> diff.res;
done

rm -f *.ss; # remove all the test cases