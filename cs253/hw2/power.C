// Compute x^n in two different ways,
// where n is a non-negative integer.

#include <iostream.h>

// Linear time: roughly c*n, for some constant c.
double power(double x, int n)
{
  double ret=1.0;
  for (int i=0; i<n; i++)
    ret *= x;
  return ret;
}

// Logarithmic time: roughly c'*(log n), for some constant c'.
double power2(double x, int n)
{
  double ret=1.0;
  for (int i=1; i<=n; i += i, x *= x)
    if (i&n) ret *= x;
  return ret;
}

// Ok, do something pretty with them.

main()
{
  for (int i=0; i<4; i++)
    cout << "\tpower\tpower2";
  cout << endl;
  for (int n=1; n<= 16; n++) {
    cout << "x^" << n << ':';
    for (double x=1.1; x < 1.701; x += 0.2)
      cout << '\t' << power(x,n) << '\t' << power2(x,n);
    cout << endl;
  }
}

// Local Variables:
// compile-command: "CC -o power power.C"
// end:
