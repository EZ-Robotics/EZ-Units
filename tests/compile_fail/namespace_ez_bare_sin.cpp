// Gotcha documented in the README: units.hpp declares sin, cos, abs, sqrt, etc.
// as free functions inside namespace ez. Inside namespace ez, unqualified name
// lookup stops at ez::sin and never reaches ::sin, so a bare sin(1.0f) only
// sees the RQuantity overloads and fails. Qualify as std::sin. One expression
// per file so each of these is pinned on its own.
#include "EZ-Units/units.hpp"

namespace ez {
void f() {
  auto v = sin(1.0f); // must not compile: ::sin is hidden by ez::sin
  (void)v;
}
} // namespace ez

int main() {
  return 0;
}
