#include <stdio.h>
#include <math.h>
#include <complex.h>

#define PI 3.14159265358979323846

/*matlab created butter worth coeffeints */
long m_b[3] = { 9.825916820482009e-06, 1.965183364096402e-05, 9.825916820482009e-06};
long m_a[3] = { 1.000000000000000, -1.991114292201654, 0.991153595868935 };

// Function to generate Butterworth lowpass filter coefficients
void butterworth_lpf_coeffs(int order, double cutoff_freq, double sample_rate, double* b_coeffs, double* a_coeffs)
{
    // Compute normalized cutoff frequency
    double wc = 2 * PI * cutoff_freq / sample_rate;
    
    // Compute poles of analog Butterworth lowpass filter
    double complex s[order];
    for (int k = 0; k < order; k++) {
        double real_part = - sin(PI * (2*k + 1)/(2*order));
        double imag_part = cos(PI * (2*k + 1)/(2*order));
        s[k] = wc * (real_part + k*imag_part);
    }
    
    // Compute transfer function coefficients using pole-zero cancellation method
    double complex H_num[order+1], H_den[order+1];
    H_num[0] = 1;
    H_den[0] = 1;
    for (int i = 1; i <= order; i++) {
        H_num[i] = 0;
        H_den[i] = 0;
        for (int j = 0; j < i; j++) {
            H_num[i] += H_num[j] * s[i-j-1];
            H_den[i] += H_den[j] * s[i-j-1];
        }
        H_num[0] = creal(H_num[i]);
        H_den[0] = creal(H_den[i]);
    }
    
    // Scale coefficients so that H_den[0] is 1
    for (int i = 0; i <= order; i++) {
        H_num[i] /= H_den[0];
        H_den[i] /= H_den[0];
    }
    
    // Copy coefficients to output arrays
    for (int i = 0; i <= order; i++) {
        b_coeffs[i] = creal(H_num[order-i]);
        a_coeffs[i] = creal(H_den[order-i]);
    }
}

int main()
{
    // Set filter parameters
    int order = 4;
    double cutoff_freq = 1000;
    double sample_rate = 44100;
    
    // Allocate memory for filter coefficients
    double b_coeffs[order+1];
    double a_coeffs[order+1];
    
    // Generate filter coefficients
    butterworth_lpf_coeffs(order, cutoff_freq, sample_rate, b_coeffs, a_coeffs);
    
    // Print coefficients to console
    printf("b_coeffs = [ ");
    for (int i = 0; i <= order; i++) {
        printf("%f ", b_coeffs[i]);
    }
    printf("]\n");
    
    printf("a_coeffs = [ ");
    for (int i = 0; i <= order; i++) {
        printf("%f ", a_coeffs[i]);
    }
    printf("]\n");
    
    return 0;
}
