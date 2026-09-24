// Dimension mismatch: operator+ requires both sides to share the same dims.
// QMass (M^1) and QForce (M^1 L^1 T^-2) don't. This must fail to compile.
// EXPECT: error:.*QMass.*QForce
#include "EZ-Units/units.hpp"

using namespace ez::literals;

int main() {
  auto x = 1_kg + 1_n;
  (void)x;
  return 0;
}
