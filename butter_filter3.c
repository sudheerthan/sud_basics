#include <stdio.h>

#define PI 3.14159265358979323846
#define sine_amplitude  2
#define cos_amplitude   2
#define num_samples     100
#define order           2 // filter order

double fs = 100000; //100khz
double cutoff_freq = 100; //cutoff frequemcy
double sine_freq = 6000; //6khz
double cos_freq = 6000; //6khz
double gen_freq = 6000; //6khz

/* filter coefficients */
double b[order +1];
double a[order +1];

/* private variables*/
double sine_wave[num_samples];
double cos_wave[num_samples];
double mul_out_i[num_samples];
double mul_out_q[num_samples];
double gen_wave[num_samples];

/*double gen_wave[num_samples] = {32768,34846,36916,38969,40997,42992,44946,46851,48699,50483,52196,53830,55380,56838,58200,59459,
    60611,61651,62574,63377,64057,64611,65037,65333,65498,65531,65432,65201,64840,64350,63733,62991,
    62127,61145,60049,58843,57532,56121,54616,53023,51349,49599,47782,45905,43975,41999,39987,37945,
    35882,33807,31728,29653,27590,25548,23536,21560,19630,17753,15936,14186,12512,10919,9414,8003,
    6692,5486,4390,3408,2544,1802,1185,695,334,103,4,37,202,498,924,1478,2158,2961,3884,4924,6076,7335,8697,10155,
    11705,13339,15052,16836,18684,20589,22543,24538,26566,28619,30689,32768};*/

double filter_coeffients(){

}

int main()
{
    /* sine wave generation */
    for (int i = 0; i < num_samples ; i++)
    {
        sine_wave[i]= sine_amplitude * sin(2* PI * sine_freq/fs);
    }

    /* cosine wave generation */
    for (int j = 0; j < num_samples ; j++)
    {
        cos_wave[j]= cos_amplitude * cos(2* PI* cos_freq /fs);
    }

    /* cosine wave generation */
    for (int j = 0; j < num_samples ; j++)
    {
        gen_wave[j]= sine_amplitude * sin(2* PI* sine_freq /fs);
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


    



       

    
    
    return 0;
}