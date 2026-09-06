// Dimension mismatch: length * time has dims (length^1, time^1), which does
// not match QLength's dims (length^1). No converting constructor exists for
// this, so the assignment must fail to compile.
#include "EZ-Units/units.hpp"

using namespace ez::literals;

int main() {
  ez::QLength x = 1_m * 1_s;
  (void)x;
  return 0;
}
