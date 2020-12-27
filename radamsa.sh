counter=1
while true
do
	radamsa "in/1.img" > fuzz.img
	echo "Processing test case: $counter"
	counter=$[$counter+1]
	./imgRead_radamsa fuzz.img > /dev/null
	test $? -eq 1 && echo "Crashed..." && cp fuzz.img fuzz_$counter.img #&& break
done
