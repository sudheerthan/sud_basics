#define PI 3.14159265358979323846

typedef struct {
  double a0, a1, a2; // numerator coefficients
  double b1, b2; // denominator coefficients
  double x1, x2; // input delays
  double y1, y2; // output delays
} butterworth2;

void butterworth2_init(butterworth2 *filter, double fc, double fs) {
  double w0 = 2.0 * PI * fc / fs;
  double cw0 = cos(w0);
  double sw0 = sin(w0);
  double alpha = sw0 / (2.0 * 0.707106781186548); // 0.707106781186548 = sqrt(2)/2
  double a0 = 1.0 + alpha;
  filter->a0 = 1.0 / a0;
  filter->a1 = -2.0 * cw0 / a0;
  filter->a2 = (1.0 - alpha) / a0;
  filter->b1 = 2.0 * cw0 / a0;
  filter->b2 = -(1.0 - alpha) / a0;
  filter->x1 = 0.0;
  filter->x2 = 0.0;
  filter->y1 = 0.0;
  filter->y2 = 0.0;
}

double butterworth2_filter(butterworth2 *filter, double x) {
  double y = filter->a0 * x + filter->a1 * filter->x1 + filter->a2 * filter->x2
             - filter->b1 * filter->y1 - filter->b2 * filter->y2;
  filter->x2 = filter->x1;
  filter->x1 = x;
  filter->y2 = filter->y1;
  filter->y1 = y;
  return y;
}
