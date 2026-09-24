#include "EZ-Units/units.hpp"
#include "framework.hpp"

using namespace ez::literals;

EZTEST(speed_literals_produce_correct_base_values_in_mps) {
  EZ_ASSERT_NEAR((1_mps).getValue(), 1.0, 1e-12);
  EZ_ASSERT_NEAR((1_miph).getValue(), 0.44704, 1e-12);
  EZ_ASSERT_NEAR((1_kmph).getValue(), 0.2777777777777778, 1e-12);
}

EZTEST(speed_round_trip_conversion_every_unit) {
  const ez::QSpeed s = 10_mps;
  EZ_ASSERT_NEAR(s.convert(1.0_mps), 10.0, 1e-9);
  EZ_ASSERT_NEAR(s.convert(1.0_miph), 10.0 / 0.44704, 1e-9);
  EZ_ASSERT_NEAR(s.convert(1.0_kmph), 10.0 / 0.2777777777777778, 1e-9);
}

EZTEST(acceleration_literals_produce_correct_base_values_in_mps2) {
  EZ_ASSERT_NEAR((1_mps2).getValue(), 1.0, 1e-12);
  EZ_ASSERT_NEAR((1_G).getValue(), 9.80665, 1e-12);
}

EZTEST(acceleration_round_trip_conversion_every_unit) {
  const ez::QAcceleration a = 2_G;
  EZ_ASSERT_NEAR(a.convert(1.0_mps2), 2.0 * 9.80665, 1e-9);
  EZ_ASSERT_NEAR(a.convert(1.0_G), 2.0, 1e-9);
}

EZTEST(jerk_has_no_named_constants_or_literals_but_is_a_real_type) {
  // Only reachable via arithmetic: acceleration / time.
  const ez::QJerk j = 1_mps2 / 1_s;
  EZ_ASSERT_NEAR(j.getValue(), 1.0, 1e-12);
}

EZTEST(angular_speed_literals_produce_correct_base_values_in_radps) {
  EZ_ASSERT_NEAR((1_rpm).getValue(), 0.10471975511965977, 1e-12);
}

EZTEST(angular_speed_named_constants_produce_correct_base_values_in_radps) {
  EZ_ASSERT_NEAR(ez::radps.getValue(), 1.0, 1e-12);
  EZ_ASSERT_NEAR(ez::rpm.getValue(), 0.10471975511965977, 1e-12);
  EZ_ASSERT_NEAR(ez::cps.getValue(), 0.00017453292519943296, 1e-12);
}

EZTEST(angular_speed_round_trip_conversion_every_unit) {
  const ez::QAngularSpeed w = 60_rpm;
  EZ_ASSERT_NEAR(w.convert(1.0_rpm), 60.0, 1e-9);
  EZ_ASSERT_NEAR(w.convert(ez::radps), 60.0 * 0.10471975511965977, 1e-9);
  EZ_ASSERT_NEAR(w.convert(ez::cps), 60.0 * 0.10471975511965977 / 0.00017453292519943296, 1e-6);
}

EZTEST(angular_acceleration_has_no_named_constants_or_literals_but_is_a_real_type) {
  const ez::QAngularAcceleration wa = 1_rpm / 1_s;
  EZ_ASSERT_NEAR(wa.getValue(), 0.10471975511965977, 1e-12);
}

EZTEST(angular_jerk_has_no_named_constants_or_literals_but_is_a_real_type) {
  const ez::QAngularJerk wj = (1_rpm / 1_s) / 1_s;
  EZ_ASSERT_NEAR(wj.getValue(), 0.10471975511965977, 1e-12);
}

EZTEST(frequency_literals_produce_correct_base_values_in_hz) {
  EZ_ASSERT_NEAR((1_Hz).getValue(), 1.0, 1e-12);
  EZ_ASSERT_NEAR(ez::Hz.getValue(), 1.0, 1e-12);
}

EZTEST(frequency_round_trip_conversion) {
  const ez::QFrequency f = 5_Hz;
  EZ_ASSERT_NEAR(f.convert(1.0_Hz), 5.0, 1e-9);
}

EZTEST(frequency_from_dividing_number_by_time) {
  // 1.0 / QTime -> RQuantity<0,0,-1,0>, implicitly convertible to QFrequency.
  const ez::QFrequency f = 1.0 / 10_ms;
  EZ_ASSERT_NEAR(f.convert(1.0_Hz), 100.0, 1e-9);
}

EZTEST(derived_speed_from_length_over_time) {
  const ez::QSpeed s = 24_in / 1_s;
  EZ_ASSERT_NEAR(s.getValue(), 24.0 * 0.0254, 1e-12);
}

EZTEST(derived_angular_speed_from_angle_over_time) {
  const ez::QAngularSpeed w = 90_deg / 1_s;
  EZ_ASSERT_NEAR(w.convert(ez::radps), 90.0 * (3.1415926535897932384626433832795 / 180.0), 1e-9);
}

EZTEST(frequency_and_angular_speed_are_different_types) {
  // Both have dims T^-1, but QFrequency is T^-1 A^0 and QAngularSpeed is
  // T^-1 A^1 - they must not be assignable to each other. This is exercised
  // as a positive check here (RQuantity values with matching dims still
  // compare correctly); the compile_fail suite pins the negative case.
  const ez::QFrequency f = 2_Hz;
  const ez::QAngularSpeed w = 2_rpm;
  EZ_ASSERT(f.getValue() != w.getValue());
}
