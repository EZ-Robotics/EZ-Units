// Built by the default (non-okapi) test target, where tests/fixtures is NOT
// on the include path. Confirms the header compiles cleanly with no okapi
// present, and that the bridge correctly disables itself via __has_include.
#include "EZ-Units/units.hpp"
#include "framework.hpp"

#ifdef EZ_UNITS_HAS_OKAPI_BRIDGE
#error "EZ_UNITS_HAS_OKAPI_BRIDGE should not be defined without okapi headers on the include path"
#endif

EZTEST(header_is_usable_without_okapi_present) {
  const ez::QLength d(1.0);
  EZ_ASSERT_NEAR(d.getValue(), 1.0, 1e-12);
}
