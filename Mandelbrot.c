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

    ComplexNumber *Z = newComplexNumber(0.0, 0.0);
    while(ComplexAbs(Z) <= threshold) {
      if (iterations >= maxiters) {
        freeComplexNumber(Z);
        return 0;
      }
      else {
        Z = ComplexSum(ComplexProduct(Z, Z), point);
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
    double dRes = (double) resolution;
    double step = scale / dRes;
    
    double imC = Im(center);
    double reC = Re(center);

    int index = 0;

    for (double i = imC + scale; i >= imC - scale; i -= step) {
      for (double r = reC - scale; r <= reC + scale; r += step) {
        ComplexNumber *C = newComplexNumber(r, i);
        output[index] = MandelbrotIterations(max_iterations, C, threshold);
        freeComplexNumber(C);
        index++;
      }
    }
}


