double compute_p(double A[], int len, double x) {
  double sum = 0;
  double x_prime = 1;
  for (int i = 0; i < len; i++) {
    sum += x_prime * A[i];
    x_prime *= x;
  }
  return sum;
}
