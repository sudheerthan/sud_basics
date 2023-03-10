#include <stdio.h>
#include <math.h>

#define num_samples     100
#define PI 3.14159265358979323846

double mul_out_i[num_samples];
double filtered_signal_i[num_samples]; // Filtered signal

long m_b[3] = { 9.825916820482009e-06, 1.965183364096402e-05, 9.825916820482009e-06};
long m_a[3] = { 1.000000000000000, -1.991114292201654, 0.991153595868935 };

double fs = 100000; //100khz
double cos_freq = 6000; //cutoff frequemcy

void butt_filter(double* input, double* output)
{
    // Iterate over all input samples
    for (int i = 0; i < num_samples; i++) {
        // Calculate the current output sample using the difference equation
        double y = 20 * input[i] + 30 * input[i-1] + 40 * input[i-2] - 50* output[i-1] - 60 * output[i-2];

        // Store the output sample in the output buffer
        output[i] = y;
    }
}

int main()
{

    /* cosine wave generation */
    for (int j = 0; j < num_samples ; j++)
    {
        mul_out_i[j]= 2 * cos(2* PI* cos_freq /fs * j);
        printf("cos %lf\n",mul_out_i[j]);
    }

        butt_filter(mul_out_i,filtered_signal_i);

    for(int m = 0; m < num_samples ; m++)
    {
        //filtered_signal_i[m]= filter(mul_out_i[m], x,y);

        printf("%lf\n",filtered_signal_i[m]);
    }
    
    return 0;
}