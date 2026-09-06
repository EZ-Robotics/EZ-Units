#include "EZ-Units/units.hpp"
#include "framework.hpp"

using namespace ez::literals;

EZTEST(time_literals_produce_correct_base_values_in_seconds) {
  EZ_ASSERT_NEAR((1_s).getValue(), 1.0, 1e-12);
  EZ_ASSERT_NEAR((1_ms).getValue(), 0.001, 1e-12);
  EZ_ASSERT_NEAR((1_min).getValue(), 60.0, 1e-9);
  EZ_ASSERT_NEAR((1_h).getValue(), 3600.0, 1e-9);
  EZ_ASSERT_NEAR((1_day).getValue(), 86400.0, 1e-6);
}

EZTEST(time_round_trip_conversion_every_unit) {
  const ez::QTime t = 100_ms;
  EZ_ASSERT_NEAR(t.convert(1.0_ms), 100.0, 1e-9);
  EZ_ASSERT_NEAR(t.convert(1.0_s), 0.1, 1e-9);
  EZ_ASSERT_NEAR(t.convert(1.0_min), 0.1 / 60.0, 1e-9);
  EZ_ASSERT_NEAR(t.convert(1.0_h), 0.1 / 3600.0, 1e-9);
  EZ_ASSERT_NEAR(t.convert(1.0_day), 0.1 / 86400.0, 1e-9);
}
