// See namespace_ez_bare_sin.cpp: ez::abs hides ::abs inside namespace ez.
// Qualify as std::abs.
#include "EZ-Units/units.hpp"

namespace ez {
void f() {
  auto v = abs(-3); // must not compile: ::abs is hidden by ez::abs
  (void)v;
}
} // namespace ez

int main() {
  return 0;
}
