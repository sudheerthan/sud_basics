#include <stdio.h>
#include <math.h>
#define PI 3.14159265358979323846

#define FILTER_ORDER 2

double filter(double input, double* m_a, double* m_b, double* x, double* y) {
    int i;
    double output = 0;

    // Shift the input buffer
    for (i = FILTER_ORDER-1; i > 0; i--) {
        x[i] = x[i-1];
        y[i] = y[i-1];
    }

    // Add the new input to the input buffer
    x[0] = input;

    // Calculate the new output
    output += m_b[0] * x[0];
    output += m_b[1] * x[1];
    output += m_b[2] * x[2];
    output -= m_a[1] * y[1];
    output -= m_a[2] * y[2];

    // Add the new output to the output buffer
    y[0] = output;

    return output;
}

int main() {
    double m_a[3] = { 1.000000000000000, -1.991114292201654, 0.991153595868935 };
    double m_b[3] = { 9.825916820482009e-06, 1.965183364096402e-05, 9.825916820482009e-06 };
    double x[FILTER_ORDER] = { 0 };
    double y[FILTER_ORDER] = { 0 };

    // Generate test signal with 200Hz sampling rate and 1kHz frequency
    double frequency = 1000;
    double sampling_rate = 200;
    double amplitude = 1;
    int num_samples = 1000;
    double input_signal[num_samples];
    double t = 0;
    for (int i = 0; i < num_samples; i++) {
        input_signal[i] = amplitude * sin(2 * PI * frequency * t);
        t += 1.0 / sampling_rate;
    }

    // Filter the signal
    double output_signal[num_samples];
    for (int i = 0; i < num_samples; i++) {
        output_signal[i] = filter(input_signal[i], m_a, m_b, x, y);
    }

    // Print the output signal
    for (int i = 0; i < num_samples; i++) {
        printf("%f\n", output_signal[i]);
    }

    return 0;
}
