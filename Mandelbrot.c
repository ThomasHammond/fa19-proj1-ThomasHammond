/*********************
**  Mandelbrot fractal
** clang -Xpreprocessor -fopenmp -lomp -o Mandelbrot Mandelbrot.c
** by Dan Garcia <ddgarcia@cs.berkeley.edu>
** Modified for this class by Justin Yokota and Chenyu Shi
**********************/

#include <stdio.h>
#include <stdlib.h>
#include "ComplexNumber.h"
#include "Mandelbrot.h"
#include <sys/types.h>


/*
This function returns the number of iterations before the initial point >= the threshold.
If the threshold is not exceeded after maxiters, the function returns 0.
*/
u_int64_t MandelbrotIterations(u_int64_t maxiters, ComplexNumber * point, double threshold)
{
    //YOUR CODE HERE
    u_int64_t iterations = 0; 
    ComplexNumber *Z = newComplexNumber(0, 0);
    while(ComplexAbs(Z) < threshold) {
      if (iterations > maxiters) {
        freeComplexNumber(Z);
        return 0;
      }
      else {
        ComplexNumber *tempZProduct = ComplexProduct(Z, Z);
        freeComplexNumber(Z);
        ComplexNumber *tempZSum = ComplexSum(tempZProduct, point);
        freeComplexNumber(tempZProduct);
        Z = tempZSum;
        iterations++;
      }
    }
    freeComplexNumber(Z);
    return iterations;


}

/*
This function calculates the Mandelbrot plot and stores the result in output.
The number of pixels in the image is resolution * 2 + 1 in one row/column. It's a square image.
Scale is the the distance between center and the top pixel in one dimension.
*/
void Mandelbrot(double threshold, u_int64_t max_iterations, ComplexNumber* center, double scale, u_int64_t resolution, u_int64_t * output){
    //YOUR CODE HERE
    double step = (double) scale/resolution;

    double *reArr;
    reArr = malloc((2 * resolution + 1) * sizeof(double));

    double *imArr;
    imArr = malloc((2 * resolution + 1) * sizeof(double));

    if (reArr == NULL || imArr == NULL) {
      printf("Memory error.");
      exit(1);
    }

    double real = Re(center);
    double im = Im(center);

    int indexLeft = (int) resolution - 1;
    int indexRight = (int) resolution + 1;

    reArr[resolution] = real;
    imArr[resolution] = im;

    for (int i = 1; i <= resolution; i++) {
      double thisStep = (double) i * step;
      reArr[indexLeft] = real - thisStep;
      imArr[indexLeft] = im + thisStep;
      indexLeft--;
      reArr[indexRight] = real + thisStep;
      imArr[indexRight] = im - thisStep;
      indexRight++;
    }

    int outputIndex = 0;

    int len = (int) 2 * resolution + 1;

    for (int i = 0; i < len; i++) {
      for (int r = 0; r < len; r++) {
        ComplexNumber *c = newComplexNumber(reArr[r], imArr[i]);
        output[outputIndex] = MandelbrotIterations(max_iterations, c, threshold);
        freeComplexNumber(c);
        outputIndex++;
      }
    }
    free(reArr);
    free(imArr);
}


