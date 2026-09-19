// Only built by the okapi-fixture test target (tests/fixtures on the include
// path). Pins the "stale line" compatibility EZ-Template projects rely on.
//
// Existing EZ-Template projects have `using namespace okapi::literals;` in
// main.h. That line only compiles because units.hpp, when it can see okapi,
// includes okapi's RQuantity.hpp, and RQuantity.hpp is what declares the
// okapi::literals namespace - it contains just `_pi`. Unit suffixes like _in,
// _deg and _ms live in okapi's QLength/QAngle/QTime.hpp, which this file
// deliberately does NOT include, so they stay unambiguous and resolve to ez's.
//
// This is the complement of compile_fail/literal_ambiguity.cpp, which includes
// okapi's QLength.hpp (bringing in okapi's _in) and therefore does fail.
//
// Only units.hpp may be included here (framework.hpp is std-only). Do not add
// any okapi/api/units/Q*.hpp include: it would turn this into the ambiguous case.
#include "EZ-Units/units.hpp"
#include "framework.hpp"
#include <type_traits>

#ifndef EZ_UNITS_HAS_OKAPI_BRIDGE
#error "EZ_UNITS_HAS_OKAPI_BRIDGE should be defined when okapi headers are visible"
#endif

using namespace okapi::literals;
using namespace ez::literals;

static_assert(std::is_same<decltype(24_in), ez::QLength>::value, "24_in should be an ez::QLength");
static_assert(std::is_same<decltype(90_deg), ez::QAngle>::value, "90_deg should be an ez::QAngle");
static_assert(std::is_same<decltype(100_ms), ez::QTime>::value, "100_ms should be an ez::QTime");

EZTEST(stale_okapi_literals_using_still_resolves_to_ez) {
  ez::QLength x = 24_in;
  ez::QAngle a = 90_deg;
  ez::QTime t = 100_ms;
  EZ_ASSERT_NEAR(x.getValue(), 24.0 * 0.0254, 1e-12);
  EZ_ASSERT_NEAR(a.getValue(), 3.1415926535897932384626433832795 / 2.0, 1e-12);
  EZ_ASSERT_NEAR(t.getValue(), 0.1, 1e-12);
}
