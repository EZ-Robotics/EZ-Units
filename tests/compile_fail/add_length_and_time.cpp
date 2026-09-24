// Dimension mismatch: operator+ requires both sides to share the same dims.
// This must fail to compile.
// EXPECT: error:.*QLength.*QTime
#include "EZ-Units/units.hpp"

using namespace ez::literals;

int main() {
  auto x = 1_m + 1_s;
  (void)x;
  return 0;
}
