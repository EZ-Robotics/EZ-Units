// Only built by the okapi-fixture test target (tests/fixtures on the include
// path). Verifies the implicit converting constructor from okapi::RQuantity
// into ez::RQuantity (and the three named types) compiles and produces the
// correct converted value, and that EZ_UNITS_HAS_OKAPI_BRIDGE is defined.
#include "EZ-Units/units.hpp"
#include "framework.hpp"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QTime.hpp"

#ifndef EZ_UNITS_HAS_OKAPI_BRIDGE
#error "EZ_UNITS_HAS_OKAPI_BRIDGE should be defined when okapi headers are visible"
#endif

static void takes_ez_qlength(ez::QLength q, double *out) {
  *out = q.getValue();
}

static void takes_ez_qangle(ez::QAngle q, double *out) {
  *out = q.getValue();
}

static void takes_ez_qtime(ez::QTime q, double *out) {
  *out = q.getValue();
}

EZTEST(okapi_values_convert_implicitly_into_ez_parameters) {
  const okapi::QLength okLen = 5.0 * okapi::inch;
  const okapi::QAngle okAng = 45.0 * okapi::degree;
  const okapi::QTime okTime = 200.0 * okapi::millisecond;

  double lenOut = 0.0, angOut = 0.0, timeOut = 0.0;
  takes_ez_qlength(okLen, &lenOut);
  takes_ez_qangle(okAng, &angOut);
  takes_ez_qtime(okTime, &timeOut);

  EZ_ASSERT_NEAR(lenOut, 5.0 * 0.0254, 1e-9);
  EZ_ASSERT_NEAR(angOut, 45.0 * 3.1415926535897932384626433832795 / 180.0, 1e-9);
  EZ_ASSERT_NEAR(timeOut, 0.2, 1e-9);
}
