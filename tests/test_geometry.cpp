#include "EZ-Units/units.hpp"
#include "framework.hpp"

using namespace ez::literals;

EZTEST(area_named_constants_produce_correct_base_values_in_meter2) {
  EZ_ASSERT_REL_NEAR(ez::kilometer2.getValue(), 1000000.0, 1e-12);
  EZ_ASSERT_NEAR(ez::meter2.getValue(), 1.0, 1e-12);
  EZ_ASSERT_NEAR(ez::decimeter2.getValue(), 0.010000000000000002, 1e-12);
  EZ_ASSERT_NEAR(ez::centimeter2.getValue(), 0.0001, 1e-12);
  EZ_ASSERT_NEAR(ez::millimeter2.getValue(), 1e-06, 1e-12);
  EZ_ASSERT_NEAR(ez::inch2.getValue(), 0.0006451600000000001, 1e-12);
  EZ_ASSERT_NEAR(ez::foot2.getValue(), 0.09290304, 1e-12);
  EZ_ASSERT_REL_NEAR(ez::mile2.getValue(), 2589988.110336, 1e-12);
}

EZTEST(area_round_trip_conversion_every_unit) {
  const ez::QArea a = 2 * ez::meter2;
  EZ_ASSERT_NEAR(a.convert(ez::meter2), 2.0, 1e-9);
  EZ_ASSERT_REL_NEAR(a.convert(ez::kilometer2), 2.0 / 1000000.0, 1e-9);
  EZ_ASSERT_NEAR(a.convert(ez::decimeter2), 2.0 / 0.010000000000000002, 1e-9);
  EZ_ASSERT_NEAR(a.convert(ez::centimeter2), 2.0 / 0.0001, 1e-9);
  EZ_ASSERT_NEAR(a.convert(ez::millimeter2), 2.0 / 1e-06, 1e-6);
  EZ_ASSERT_NEAR(a.convert(ez::inch2), 2.0 / 0.0006451600000000001, 1e-6);
  EZ_ASSERT_NEAR(a.convert(ez::foot2), 2.0 / 0.09290304, 1e-9);
  EZ_ASSERT_REL_NEAR(a.convert(ez::mile2), 2.0 / 2589988.110336, 1e-9);
}

EZTEST(volume_named_constants_produce_correct_base_values_in_meter3) {
  EZ_ASSERT_REL_NEAR(ez::kilometer3.getValue(), 1000000000.0, 1e-12);
  EZ_ASSERT_NEAR(ez::meter3.getValue(), 1.0, 1e-12);
  EZ_ASSERT_NEAR(ez::decimeter3.getValue(), 0.0010000000000000002, 1e-12);
  EZ_ASSERT_NEAR(ez::centimeter3.getValue(), 1.0000000000000002e-06, 1e-12);
  EZ_ASSERT_NEAR(ez::millimeter3.getValue(), 1e-09, 1e-12);
  EZ_ASSERT_NEAR(ez::inch3.getValue(), 1.6387064000000003e-05, 1e-12);
  EZ_ASSERT_NEAR(ez::foot3.getValue(), 0.028316846592000004, 1e-12);
  EZ_ASSERT_REL_NEAR(ez::mile3.getValue(), 4168181825.44058, 1e-9);
  EZ_ASSERT_NEAR(ez::litre.getValue(), 0.0010000000000000002, 1e-12);
}

EZTEST(volume_round_trip_conversion_every_unit) {
  const ez::QVolume v = 2 * ez::meter3;
  EZ_ASSERT_NEAR(v.convert(ez::meter3), 2.0, 1e-9);
  EZ_ASSERT_REL_NEAR(v.convert(ez::kilometer3), 2.0 / 1000000000.0, 1e-9);
  EZ_ASSERT_NEAR(v.convert(ez::decimeter3), 2.0 / 0.0010000000000000002, 1e-9);
  EZ_ASSERT_NEAR(v.convert(ez::centimeter3), 2.0 / 1.0000000000000002e-06, 1e-3);
  EZ_ASSERT_NEAR(v.convert(ez::millimeter3), 2.0 / 1e-09, 1.0);
  EZ_ASSERT_NEAR(v.convert(ez::inch3), 2.0 / 1.6387064000000003e-05, 1e-3);
  EZ_ASSERT_NEAR(v.convert(ez::foot3), 2.0 / 0.028316846592000004, 1e-9);
  EZ_ASSERT_REL_NEAR(v.convert(ez::mile3), 2.0 / 4168181825.44058, 1e-9);
  EZ_ASSERT_NEAR(v.convert(ez::litre), 2.0 / 0.0010000000000000002, 1e-9);
}

EZTEST(litre_equals_decimeter3) {
  EZ_ASSERT(ez::litre == ez::decimeter3);
}

EZTEST(derived_area_from_length_times_length) {
  const ez::QArea a = 1_in * 1_in;
  EZ_ASSERT_NEAR(a.getValue(), 0.0006451600000000001, 1e-12);
}
