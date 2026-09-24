// Dimension mismatch: QLength (L^1) has no converting constructor into
// QSpeed (L^1 T^-1). This must fail to compile.
// EXPECT: error:.*conversion.*QSpeed
#include "EZ-Units/units.hpp"

using namespace ez::literals;

int main() {
  ez::QSpeed s = 1_m;
  (void)s;
  return 0;
}
