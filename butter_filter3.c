#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846
#define sine_amplitude  10
#define cos_amplitude   10
#define num_samples     100
#define order           2 // filter order

double fs = 100000; //100khz
double cutoff_freq = 100; //cutoff frequemcy
double sine_freq = 6000; //6khz
double cos_freq = 6000; //6khz
double gen_freq = 6000; //6khz
long double a[3], b[3];

/* filter coefficients */
double f_b[order +1];
double f_a[order +1];

/* private variables*/
double sine_wave[num_samples];
double cos_wave[num_samples];
double mul_out_i[num_samples];
double mul_out_q[num_samples];
double gen_wave[num_samples];
double amplitude[num_samples];
double filtered_signal_i[num_samples]; // Filtered signal
double filtered_signal_q[num_samples]; // Filtered signal
double x[order+1] = {0}; // Input samples
double y[order+1] = {0}; // Output samples

double previous_inputs[2] = {0, 0};
double previous_outputs[2] = {0, 0};

long m_b[3] = { 9.825916820482009e-06, 1.965183364096402e-05, 9.825916820482009e-06};
long m_a[3] = { 1.000000000000000, -1.991114292201654, 0.991153595868935 };

/*double gen_wave[num_samples] = {32768,34846,36916,38969,40997,42992,44946,46851,48699,50483,52196,53830,55380,56838,58200,59459,
    60611,61651,62574,63377,64057,64611,65037,65333,65498,65531,65432,65201,64840,64350,63733,62991,
    62127,61145,60049,58843,57532,56121,54616,53023,51349,49599,47782,45905,43975,41999,39987,37945,
    35882,33807,31728,29653,27590,25548,23536,21560,19630,17753,15936,14186,12512,10919,9414,8003,
    6692,5486,4390,3408,2544,1802,1185,695,334,103,4,37,202,498,924,1478,2158,2961,3884,4924,6076,7335,8697,10155,
    11705,13339,15052,16836,18684,20589,22543,24538,26566,28619,30689,32768};*/

/* calculate butterworth filter coeffients*/
void filter_coeffients(){
   long double wc = 2.0 * PI * cutoff_freq / fs;
   long double c1 = cos(wc);
   long double s1 = sin(wc);
   long  double alpha = s1 / (2.0 * sqrt(pow(2.0, 1.0/order) - 1.0));
   long double a0 = 1.0 + alpha;
   long double a1 = -2.0 * c1;
   long double a2 = 1.0 - alpha;
   long  double b0 = (1.0 - c1) / 2.0 / a0;
   long  double b1 = (1.0 - c1) / a0;
   long  double b2 = (1.0 - c1) / 2.0 / a0;

    a[0] = a0;
    a[1] = a1;
    a[2] = a2;
    b[0] = b0;
    b[1] = b1;
    b[2] = b2;
}

/* butterworth lowpass filter implementaion */
double filter(double input, double* x, double* y)
{
   // printf("%lf %lf %lf \n", input,x,y);
     double output = 0;

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
    printf("output %lf\n",output);
    return output;
    // int i;
    // // Shift input and output samples
    // for(i = order; i >= 1; i--)
    // {
    //     x[i] = x[i-1];
    //     y[i] = y[i-1];
    // }
    // x[0] = input;
    
    // // Calculate output
    // y[0] = f_b[0]*x[0];
    // for(i = 1; i <= order; i++)
    // {
    //     y[0] += f_b[i]*x[i] - f_a[i]*y[i];
    // }
    
    // *output = y[0];

}

void butt_filter(double* input, double* output)
{
    // Iterate over all input samples
    for (int i = 0; i < num_samples; i++) {
        // Calculate the current output sample using the difference equation
        double y = m_b[0] * input[i] + m_b[1] * input[i-1] + m_b[2] * input[i-2] - m_a[1] * output[i-1] - m_a[2] * output[i-2];

        // Store the output sample in the output buffer
        output[i] = y;
    }
}

int main()
{
    /* sine wave generation */
    for (int i = 0; i < num_samples ; i++)
    {
        sine_wave[i]= sine_amplitude * sin(2.0* PI * sine_freq/fs * i);
    }

    /* cosine wave generation */
    for (int j = 0; j < num_samples ; j++)
    {
        cos_wave[j]= cos_amplitude * cos(2* PI* cos_freq /fs * j);
    }

    /* cosine wave generation */
    for (int j = 0; j < num_samples ; j++)
    {
        gen_wave[j]= sine_amplitude * sin(2* PI* sine_freq /fs * j);
    }

    /* multiply sine wave with gen wave */
    for (int k = 0; k < num_samples ; k++)
    {
        mul_out_i[k] = gen_wave[k] * sine_wave[k];
    }

    /* multiply cosine wave with gen wave */
    for (int l = 0; l < num_samples ; l++)
    {
        mul_out_q[l] = gen_wave[l] * cos_wave[l];
    }
    
    /* i phase butterworth filter function */
    for(int m = 0; m < num_samples ; m++)
    {
        //filtered_signal_i[m]= filter(mul_out_i[m], x,y);
        butt_filter(mul_out_i[m],filtered_signal_i[m]);
        //printf("%lf\n",filtered_signal_i[m]);
    }
    
    /* q phase butterworth filter function */
    for(int n = 0; n < num_samples ; n++)
    {
        filtered_signal_q[n]= filter(mul_out_i[n], x,y);
    }

    
    for(int n = 0; n < num_samples ; n++)
    {
        //printf("filtered signal i [%d ] = %lf\n",n,filtered_signal_i[n]);
    }
    for(int n = 0; n < num_samples ; n++)
    {
       // printf("filtered signal q [%d ] = %lf\n",n,filtered_signal_q[n]);
    }
    /* amplitude */
    for(int p = 0; p < num_samples ; p++)
    {
        amplitude[p] = sqrt((filtered_signal_i[p] * filtered_signal_i[p]) + (filtered_signal_q[p] * filtered_signal_q[p]));
    };
        printf("amplitude of %d point = %lf",1,amplitude[0]);
  
    return 0;
}