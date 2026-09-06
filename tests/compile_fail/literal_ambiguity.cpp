// Documented in the README: pulling in both okapi::literals and ez::literals
// makes every shared literal suffix ambiguous. This file is only compiled by
// the okapi-fixture test target, which puts tests/fixtures on the include path.
#include "EZ-Units/units.hpp"
#include "okapi/api/units/QLength.hpp"

using namespace ez::literals;
using namespace okapi::literals;

int main() {
  auto x = 24_in; // ambiguous between ez::literals and okapi::literals
  (void)x;
  return 0;
}
