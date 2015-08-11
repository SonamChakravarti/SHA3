********************READ ME*************************************
********************SHA-3 Hashing Algorithm*********************

1. The implementation of SHA-3 has been done in C++.
2. Makefile has been provided along with the main.cpp file to run the project.
3. To run the project, follow the below steps:
	a. Place the main.cpp input.txt and Makefile in SAME folder
	b. Run "make" command
	c. Enter the following command:	./sha3 input_filename.txt output_filename.txt
		eg.	./sha3 input.txt output.txt
	d. Run make clean before trying to run the program for second time with different input.
4. The output message digest is printed as well as written in given outputfile.
5. The pseudo-code for the programm is as follows:
		1. Convert strings in input file to bits (using bitset vectors of 8 bits)
		2. Pad the bitset vector(combine elements of vector) to form 1088 sized n message blocks
		3. XOR each message block to sponge function at a time and run 24 rounds of 5 functions namely, theta,rho,pi,chi and iota(toatl 24*5 steps)
		4. From the final sponge , extract first L(256) bits and convert to hex.
		5. write the  digest togiven output file
6. Example.txt has been attached to show SHA-3 hashing and AVALANCHE effect
