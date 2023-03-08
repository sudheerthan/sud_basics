#include <math.h>

#define M_PI 3.14159265358979323846
/*
 * y[n] = b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] - a1 * y[n-1] - a2 * y[n-2]
 *  
 */


void butterworth_lowpass_filter(double *input, double *output, int n_samples, double sample_rate, double cutoff_freq, int filter_order)
{
    double w0 = 2 * M_PI * cutoff_freq / sample_rate;
    double alpha = sin(w0) / (2 * pow(cos(w0), filter_order));
    double b0 = pow(1 + sqrt(2) * alpha + pow(alpha, 2), filter_order);
    double b1 = 2 * pow(1 - pow(cos(w0), 2), filter_order) / b0;
    double b2 = pow(1 - sqrt(2) * alpha + pow(alpha, 2), filter_order) / b0;
    double a1 = 2 * (pow(alpha, 2) - 1) / b0;
    double a2 = (1 - sqrt(2) * alpha + pow(alpha, 2)) / b0;
    
    double x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    
    for (int i = 0; i < n_samples; i++) {
        double x0 = input[i];
        double y0 = b0 * x0 + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2;
        x2 = x1;
        x1 = x0;
        y2 = y1;
        y1 = y0;
        output[i] = y0;
    }
}


/*************another example***********/

#define ORDER 4 // Filter order
#define SAMPLE_RATE 1000 // Sampling rate in Hz
#define CUTOFF_FREQ 100 // Cutoff frequency in Hz

// Coefficients for a Butterworth lowpass filter of order 4 with a cutoff frequency of 100 Hz and a sampling rate of 1000 Hz
const float b[ORDER+1] = {0.0003851645, 0.001540658, 0.002311987, 0.001540658, 0.0003851645};
const float a[ORDER+1] = {1, -2.365174, 2.313988, -1.05416, 0.178557};

float x[ORDER+1] = {0}; // Input samples
float y[ORDER+1] = {0}; // Output samples

void filter(float input, float* output)
{
    int i;
    // Shift input and output samples
    for(i = ORDER; i >= 1; i--)
    {
        x[i] = x[i-1];
        y[i] = y[i-1];
    }
    x[0] = input;
    
    // Calculate output
    y[0] = b[0]*x[0];
    for(i = 1; i <= ORDER; i++)
    {
        y[0] += b[i]*x[i] - a[i]*y[i];
    }
    
    *output = y[0];
}

int main()
{
    // Use the filter function in a loop to filter a signal
    float input_signal[1000]; // Example input signal
    float filtered_signal[1000]; // Filtered signal
    int i;
    for(i = 0; i < 1000; i++)
    {
        filter(input_signal[i], &filtered_signal[i]);
    }
    
    return 0;
}
