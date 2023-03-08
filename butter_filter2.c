#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

int main()
{
    double fs = 44100; // sample rate
    double t_step = 1/fs; // time step
    double t_max = 1; // maximum time
    int num_samples = (int)(t_max/t_step) + 1; // number of samples
    
    double f = 6000; // frequency
    double A = 3; // amplitude
    
    double x[num_samples]; // 6 kHz sine wave with amplitude of 3
    for(int i=0; i<num_samples; i++) {
        double t = i*t_step;
        x[i] = A*sin(2*PI*f*t);
    }
    
    double f2 = 6000; // frequency
    double A2 = 2; // amplitude
    
    double y[num_samples]; // 6 kHz sine wave with amplitude of 2
    double z[num_samples]; // 6 kHz cosine wave with amplitude of 2
    for(int i=0; i<num_samples; i++) {
        double t = i*t_step;
        y[i] = A2*sin(2*PI*f2*t);
        z[i] = A2*cos(2*PI*f2*t);
    }
    
    double xy[num_samples]; // result of multiplying x with y
    double xz[num_samples]; // result of multiplying x with z
    for(int i=0; i<num_samples; i++) {
        xy[i] = x[i]*y[i];
        xz[i] = x[i]*z[i];
    }
    
    double fc = 100; // cutoff frequency
    int order = 2; // filter order
    
    double b[order+1]; // filter coefficients
    double a[order+1];
    double w[order+1];
    double y_filt[num_samples]; // filtered signal
    
    // Compute filter coefficients
    double wc = 2*PI*fc/fs;
    double alpha = sin(wc)/(2*pow(cos(wc), 0.5));
    double a0 = 1 + 2*alpha + pow(alpha, 2);
    b[0] = pow(alpha, 2)/a0;
    b[1] = 2*b[0];
    b[2] = b[0];
    a[0] = 1;
    a[1] = -2*alpha*(1 - pow(alpha, 2))/a0;
    a[2] = (1 - 2*alpha + pow(alpha, 2))/a0;
    
    // Initialize filter state
    for(int i=0; i<=order; i++) {
        w[i] = 0;
    }
    
    // Filter the signals
    for(int i=0; i<num_samples; i++) {
        y_filt[i] = b[0]*xy[i] + b[1]*w[0] + b[2]*w[1] - a[1]*y_filt[i-1] - a[2]*y_filt[i-2];
        w[1] = w[0];
        w[0] = xy[i];
    }
    
    // Print the results
    for(int i=0; i<num_samples; i++) {
        printf("%f, %f, %f, %f, %f\n", x[i], y[i], z[i], xy[i], xz[i], y_filt[i]);
    }
    
    return 0;
}
