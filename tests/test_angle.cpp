#include "EZ-Units/units.hpp"
#include "framework.hpp"

#include <cmath>

using namespace ez::literals;

static constexpr double PI = 3.1415926535897932384626433832795;

EZTEST(angle_literals_produce_correct_base_values_in_radians) {
  EZ_ASSERT_NEAR((1_rad).getValue(), 1.0, 1e-12);
  EZ_ASSERT_NEAR((180_deg).getValue(), PI, 1e-9);
  EZ_ASSERT_NEAR((90_deg).getValue(), PI / 2.0, 1e-9);
  EZ_ASSERT_NEAR((360_deg).getValue(), 2.0 * PI, 1e-9);
}

EZTEST(angle_round_trip_conversion_every_unit) {
  const ez::QAngle a = 90_deg;
  EZ_ASSERT_NEAR(a.convert(1.0_deg), 90.0, 1e-9);
  EZ_ASSERT_NEAR(a.convert(1.0_rad), PI / 2.0, 1e-9);

  const ez::QAngle b = 1_rad;
  EZ_ASSERT_NEAR(b.convert(1.0_rad), 1.0, 1e-9);
  EZ_ASSERT_NEAR(b.convert(1.0_deg), 180.0 / PI, 1e-9);
}

EZTEST(angle_trig_functions) {
  EZ_ASSERT_NEAR(ez::sin(90_deg).getValue(), 1.0, 1e-9);
  EZ_ASSERT_NEAR(ez::cos(180_deg).getValue(), -1.0, 1e-9);
  EZ_ASSERT_NEAR(ez::atan2(ez::QLength(1.0), ez::QLength(1.0)).getValue(), PI / 4.0, 1e-9);
}
