// See namespace_ez_bare_sin.cpp: ez::sqrt hides ::sqrt inside namespace ez.
// Qualify as std::sqrt.
#include "EZ-Units/units.hpp"

namespace ez {
void f() {
  auto v = sqrt(2.0); // must not compile: ::sqrt is hidden by ez::sqrt
  (void)v;
}
} // namespace ez

int main() {
  return 0;
}
