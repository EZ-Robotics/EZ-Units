// Dimension mismatch: QForce (M^1 L^1 T^-2) has no converting constructor
// into QTorque (M^1 L^2 T^-2). This must fail to compile.
// EXPECT: error:.*conversion.*QTorque
#include "EZ-Units/units.hpp"

using namespace ez::literals;

int main() {
  ez::QTorque t = 1_n;
  (void)t;
  return 0;
}
