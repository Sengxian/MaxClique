while true
do
../testcase/gen 25 > ../testcase/val.clq
./main val < test.in > test1.out 2> /dev/null
./main val maxclq < test.in > test0.out 2> /dev/null
cat test0.out
if diff test0.out test1.out
then echo "Accepted"
else break
fi
done
