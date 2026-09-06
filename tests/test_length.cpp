#include "EZ-Units/units.hpp"
#include "framework.hpp"

using namespace ez::literals;

EZTEST(length_literals_produce_correct_base_values_in_meters) {
  EZ_ASSERT_NEAR((1_mm).getValue(), 0.001, 1e-12);
  EZ_ASSERT_NEAR((1_cm).getValue(), 0.01, 1e-12);
  EZ_ASSERT_NEAR((1_m).getValue(), 1.0, 1e-12);
  EZ_ASSERT_NEAR((1_km).getValue(), 1000.0, 1e-9);
  EZ_ASSERT_NEAR((1_in).getValue(), 0.0254, 1e-12);
  EZ_ASSERT_NEAR((1_ft).getValue(), 0.3048, 1e-12);
  EZ_ASSERT_NEAR((1_yd).getValue(), 0.9144, 1e-12);
  EZ_ASSERT_NEAR((1_mi).getValue(), 1609.344, 1e-9);
  EZ_ASSERT_NEAR((1_tile).getValue(), 0.6096, 1e-12);
}

EZTEST(length_round_trip_conversion_every_unit) {
  const ez::QLength d = 24_in;
  EZ_ASSERT_NEAR(d.convert(1.0_in), 24.0, 1e-9);
  EZ_ASSERT_NEAR(d.convert(1.0_mm), 24.0 * 25.4, 1e-6);
  EZ_ASSERT_NEAR(d.convert(1.0_cm), 24.0 * 2.54, 1e-9);
  EZ_ASSERT_NEAR(d.convert(1.0_m), 24.0 * 0.0254, 1e-9);
  EZ_ASSERT_NEAR(d.convert(1.0_km), 24.0 * 0.0254 / 1000.0, 1e-12);
  EZ_ASSERT_NEAR(d.convert(1.0_ft), 2.0, 1e-9);
  EZ_ASSERT_NEAR(d.convert(1.0_yd), 2.0 / 3.0, 1e-9);
  EZ_ASSERT_NEAR(d.convert(1.0_mi), 24.0 * 0.0254 / 1609.344, 1e-12);
  EZ_ASSERT_NEAR(d.convert(1.0_tile), 1.0, 1e-9);
}

EZTEST(length_convert_to_macro) {
  EZ_ASSERT_NEAR(ConvertTo(24_in, in), 24.0, 1e-9);
  EZ_ASSERT_NEAR(ConvertTo(2_ft, in), 24.0, 1e-9);
  EZ_ASSERT_NEAR(ConvertTo(1_tile, in), 24.0, 1e-9);
}
