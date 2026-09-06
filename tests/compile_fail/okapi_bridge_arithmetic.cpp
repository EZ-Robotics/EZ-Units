// Documented in the README: the okapi bridge covers implicit conversion into
// an ez-typed function parameter, but not arithmetic between an ez type and
// an okapi type directly, since template deduction won't go through a
// converting constructor. Only compiled by the okapi-fixture test target.
#include "EZ-Units/units.hpp"
#include "okapi/api/units/QLength.hpp"

int main() {
  ez::QLength a(1.0);
  okapi::QLength b(1.0);
  auto c = a + b; // no operator+ for (ez::RQuantity, okapi::RQuantity)
  (void)c;
  return 0;
}
