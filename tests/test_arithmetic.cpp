#include "EZ-Units/units.hpp"
#include "framework.hpp"

using namespace ez::literals;

EZTEST(addition_and_subtraction) {
  const ez::QLength a = 1_m + 1_m;
  EZ_ASSERT_NEAR(a.getValue(), 2.0, 1e-9);

  const ez::QLength b = 1_m - 25_cm;
  EZ_ASSERT_NEAR(b.getValue(), 0.75, 1e-9);

  const ez::QTime t = 500_ms + 500_ms;
  EZ_ASSERT_NEAR(t.convert(1.0_s), 1.0, 1e-9);
}

EZTEST(scalar_multiplication_and_division) {
  const ez::QLength a = 2.0 * 1_m;
  EZ_ASSERT_NEAR(a.getValue(), 2.0, 1e-9);

  const ez::QLength b = 1_m * 3.0;
  EZ_ASSERT_NEAR(b.getValue(), 3.0, 1e-9);

  const ez::QLength c = (4_m) / 2.0;
  EZ_ASSERT_NEAR(c.getValue(), 2.0, 1e-9);
}

EZTEST(compound_result_length_divided_by_time) {
  // 24 in / 100 ms is a velocity - it has no named ez type, so it stays a
  // bare RQuantity, same as it always was in OkapiLib.
  const auto velocity = 24_in / 100_ms;
  EZ_ASSERT_NEAR(velocity.getValue(), (24.0 * 0.0254) / 0.1, 1e-9);
}

EZTEST(compound_result_length_times_length_is_area) {
  const auto area = 2_m * 3_m;
  EZ_ASSERT_NEAR(area.getValue(), 6.0, 1e-9);
}

EZTEST(comparison_operators) {
  EZ_ASSERT(1_m == 100_cm);
  EZ_ASSERT(1_m != 99_cm);
  EZ_ASSERT(1_m > 99_cm);
  EZ_ASSERT(99_cm < 1_m);
  EZ_ASSERT(1_m >= 100_cm);
  EZ_ASSERT(1_m <= 100_cm);
}

EZTEST(abs_and_sqrt) {
  const ez::QLength negDiff = 1_m - 2_m;
  EZ_ASSERT_NEAR(ez::abs(negDiff).getValue(), 1.0, 1e-9);
  EZ_ASSERT_NEAR(negDiff.abs().getValue(), 1.0, 1e-9);

  // sqrt(4 m^2) == 2 m - area's dims halve back down to QLength's dims, and
  // the result implicitly converts back into a named QLength.
  const auto area = 4_m * 1_m;
  const ez::QLength side = ez::sqrt(area);
  EZ_ASSERT_NEAR(side.getValue(), 2.0, 1e-9);
  const ez::QLength side2 = area.sqrt();
  EZ_ASSERT_NEAR(side2.getValue(), 2.0, 1e-9);
}
