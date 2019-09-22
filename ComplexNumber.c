/*********************
**  Complex Numbers
**  This file contains a few functions that will be useful when performing computations with complex numbers
**  It is advised that you work on this part first.
**********************/

#include "ComplexNumber.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct ComplexNumber
{
	double real;
	double imaginary;
}ComplexNumber;

//Returns a pointer to a new Complex Number with the given real and imaginary components
ComplexNumber* newComplexNumber(double real_component, double imaginary_component)
{	// Initialize
	ComplexNumber *complexNumber;
	// Allocate space
	complexNumber = malloc(sizeof(ComplexNumber));
	// Assign real and imaginary components
	complexNumber->real = real_component;
	complexNumber->imaginary = imaginary_component;
	// Return new complex number
	return complexNumber;
}

//Returns a pointer to a new Complex Number equal to a*b
ComplexNumber* ComplexProduct(ComplexNumber* a, ComplexNumber* b)
{
    //YOUR CODE HERE
	double a_real = Re(a);
	double a_imaginary = Im(a);

	double b_real = Re(b);
	double b_imaginary = Im(b);

	double realProduct = (a_real * b_real) - (a_imaginary * b_imaginary);
	double imaginaryProduct = (a_real * b_imaginary) + (b_real * a_imaginary);

	return newComplexNumber(realProduct, imaginaryProduct);
}

//Returns a pointer to a new Complex Number equal to a+b
ComplexNumber* ComplexSum(ComplexNumber* a, ComplexNumber* b)
{
    //YOUR CODE HERE
	double a_real = Re(a);
	double a_imaginary = Im(a);

	double b_real = Re(b);
	double b_imaginary = Im(b);

	double realSum = a_real + b_real;
	double imaginarySum = a_imaginary + b_imaginary;
	
	return newComplexNumber(realSum, imaginarySum);
}

//Returns the absolute value of Complex Number a
double ComplexAbs(ComplexNumber* a)
{
    //YOUR CODE HERE
	return sqrt((Re(a) * Re(a)) + (Im(a) * Im(a)));
}

void freeComplexNumber(ComplexNumber* a)
{
	//YOUR CODE HERE
	free(a);
}

double Re(ComplexNumber* a)
{
	//YOUR CODE HERE
	return a->real;
}
double Im(ComplexNumber* a)
{
	//YOUR CODE HERE
	return a->imaginary;
}


//Contains a few tests.
int test_complex_number()
{
	ComplexNumber* a = newComplexNumber(2.0, 1.0);
	if (a == NULL)
	{
		printf("Creation of complex numbers not implemented\n");
		return 0;
	}
	ComplexNumber* b = ComplexProduct(a, a);
	if (b == NULL)
	{
		printf("Multiplication of complex numbers not implemented\n");
		free(a);
		return 0;
	}
	ComplexNumber* c = ComplexSum(b, b);
	if (c == NULL)
	{
		printf("Addition of complex numbers not implemented\n");
		free(a);
		free(b);
		return 0;
	}
	float d = ComplexAbs(c);
	if (d == 0)
	{
		printf("Absolute Value of complex numbers not implemented\n");
		free(a);
		free(b);
		free(c);
		return 0;
	}
	else if (fabsf(d - 10) < 0.0001)
	{
		printf("Sample tests for complex numbers all passed\n");
	}
	else
	{
		printf("At least one of your functions is incorrect\n");
	}
	free(a);
	free(b);
	free(c);
	return 0;
}

// int main(int argc, char const *argv[])
// {
// 	test_complex_number();
// 	return 0;
// }

