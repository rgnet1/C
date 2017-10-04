#include<stdio.h>
#include<stdlib.h>

int hamming_distance(unsigned int num1, unsigned int num2);
int main(int argc, char const *argv[])
{
	unsigned int num1 = 5;
	unsigned int num2 = 4;

	printf("Hamming result: %d\n", hamming_distance(num1,num2));
	return 0;
}

int hamming_distance(unsigned int num1, unsigned int num2){
	//returns 1 if num1 and num2 have a hamming distance <=1
	// 0 otherwise
	//There is no difference in bits if nums are the same
	if(num1 == num2){ 
		return 1;
	}
	//the xor of two nums will tell us the different bits
		unsigned int temp = num1^num2;
	//now if the xor result is a power of 2, we know only
	//one bit is different. 

//This is how I determine how a number is a power of 2:

	//subtracting 1 from xor and ANDing this result
	// with the xor result should be 0 if
	// only one bit is changed (Power of 2)
		
	unsigned int tempTwo=temp-1; //subtract one
	if((temp&tempTwo) == 0 ){ //AND new result with xor result
		return 1;
	}
	else
		return 0;
}