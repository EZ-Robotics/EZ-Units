// Dimension mismatch that matters: QFrequency is T^-1 A^0 and QAngularSpeed
// is T^-1 A^1 - same time exponent, different angle exponent, so they must
// not be addable. This is the one place a sloppy dims table would silently
// let rad/s and 1/s mix. This must fail to compile.
// EXPECT: error:.*QFrequency.*QAngularSpeed
#include "EZ-Units/units.hpp"

using namespace ez::literals;

int main() {
  auto x = 1_Hz + 1_rpm;
  (void)x;
  return 0;
}
