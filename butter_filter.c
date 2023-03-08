#include <stdio.h>

#define PI 3.14159265358979323846

// Define parameters
const int fs = 48000;           // Sampling frequency
const int f = 6000;             // Frequency of the sine wave
const double A = 2.0;           // Amplitude

void lowpass_filter(int f_cutoff)
{
    // Define filter parameters
    double dt = 1.0 / fs;
    double RC = 1.0 / (2.0 * PI * f_cutoff);
    double alpha = dt / (RC + dt);
    double b[3] = {1 - alpha, 2 * (1 - alpha), 1 - alpha};
    double a[3] = {1, -2 * alpha, alpha - 1};
    for (int i = 0; i <= 2; i++)
    {
        /* code */
        printf("b[%d] = %lf\n",i,b[i]);
        printf("a[%d] = %lf\n",i,a[i]);
    }
    
}


int main()
{
   lowpass_filter(100); 
    
    return 0;
}