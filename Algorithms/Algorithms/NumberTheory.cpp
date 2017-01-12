#include "NumberTheory.h"

namespace Algorithms {

  unsigned NumberTheory::GCD(unsigned a, unsigned b) {
    int x = a;
    int y = b;
    int r;
    while (y != 0) {
      r = x % y;
      x = y;
      y = r;
    }

    return x;
  }

  int NumberTheory::ModularInverse(unsigned a, unsigned m) {
    auto gcd = GCD(a, m);
    if (gcd != 1)
      return 0;

    int x0 = 0, x1 = 1;

    int remainder = m;
    if (remainder == 1)
      return 0;

    while (a > 1) {
      int quotient = a / remainder;
      int t = remainder;
      remainder = a % remainder;
      a = t;
      t = x0;
      x0 = x1 - quotient * x0;
      x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
      x1 += m;

    return x1;
  }

  int NumberTheory::SolveSystemOfCongruences(std::vector<IntegerPair> pairs) {
    
    // Calculate m, the sum of all remainders
    int m = pairs[0].first;

    for (int i = 1; i < pairs.size(); ++i) {
      int& di = pairs[i].first;
      int& ri = pairs[i].second;
      m *= di;
      int gcd = GCD(di, ri);
      if (gcd != 1) {
        //Trace(" - (" << di << "," << ri << ") are not relatively prime! Returning failure!");
      }
      else {
        //Trace(" - (" << di << "," << ri);
      }
      //Trace(" - (" << di << "," << ri << ") - Relatively prime");
    }

    int x = 0;
    for (int i = 0; i < pairs.size(); ++i) {
      int& di = pairs[i].first;
      int& ri = pairs[i].second;
      int mi = m / di;
      int si = ModularInverse(mi, di);
      //Trace(" - d" << i << " = " << di << ", r" << i << " = " << ri << ", m" << i << " = " << mi << ", s" << i << " = " << si);
      //Trace("x += (" << ri << ri << " * " << mi << " * " << si << ")");
      x += ri * mi * si;;
    }

    //Newline(1);
    x = x % m;
    //Trace("x = " << x);
    return x;
  }

}