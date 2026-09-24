#include "EZ-Units/units.hpp"
#include "framework.hpp"

using namespace ez::literals;

EZTEST(mass_literals_produce_correct_base_values_in_kg) {
  EZ_ASSERT_NEAR((1_kg).getValue(), 1.0, 1e-12);
  EZ_ASSERT_NEAR((1_g).getValue(), 0.001, 1e-12);
  EZ_ASSERT_NEAR((1_t).getValue(), 1000.0, 1e-9);
  EZ_ASSERT_NEAR((1_oz).getValue(), 0.028349523125, 1e-12);
  EZ_ASSERT_NEAR((1_lb).getValue(), 0.45359237, 1e-12);
  EZ_ASSERT_NEAR((1_st).getValue(), 6.35029318, 1e-12);
}

EZTEST(mass_round_trip_conversion_every_unit) {
  const ez::QMass m = 10_lb;
  EZ_ASSERT_NEAR(m.convert(1.0_lb), 10.0, 1e-9);
  EZ_ASSERT_NEAR(m.convert(1.0_kg), 10.0 * 0.45359237, 1e-9);
  EZ_ASSERT_NEAR(m.convert(1.0_g), 10.0 * 0.45359237 / 0.001, 1e-6);
  EZ_ASSERT_NEAR(m.convert(1.0_t), 10.0 * 0.45359237 / 1000.0, 1e-12);
  EZ_ASSERT_NEAR(m.convert(1.0_oz), 10.0 * 0.45359237 / 0.028349523125, 1e-6);
  EZ_ASSERT_NEAR(m.convert(1.0_st), 10.0 * 0.45359237 / 6.35029318, 1e-9);
}

EZTEST(force_literals_produce_correct_base_values_in_newton) {
  EZ_ASSERT_NEAR((1_n).getValue(), 1.0, 1e-12);
  EZ_ASSERT_NEAR((1_lbf).getValue(), 4.4482216152605, 1e-12);
  EZ_ASSERT_NEAR((1_kp).getValue(), 9.80665, 1e-12);
}

EZTEST(force_named_constants_match_literals) {
  EZ_ASSERT_NEAR(ez::newton.getValue(), 1.0, 1e-12);
  EZ_ASSERT_NEAR(ez::poundforce.getValue(), 4.4482216152605, 1e-12);
  EZ_ASSERT_NEAR(ez::kilopond.getValue(), 9.80665, 1e-12);
}

EZTEST(force_round_trip_conversion_every_unit) {
  const ez::QForce f = 5_lbf;
  EZ_ASSERT_NEAR(f.convert(1.0_lbf), 5.0, 1e-9);
  EZ_ASSERT_NEAR(f.convert(1.0_n), 5.0 * 4.4482216152605, 1e-9);
  EZ_ASSERT_NEAR(f.convert(1.0_kp), 5.0 * 4.4482216152605 / 9.80665, 1e-9);
}

EZTEST(pressure_literals_produce_correct_base_values_in_pascal) {
  EZ_ASSERT_NEAR((1_Pa).getValue(), 1.0, 1e-12);
  EZ_ASSERT_NEAR((1_bar).getValue(), 100000.0, 1e-9);
  EZ_ASSERT_NEAR((1_psi).getValue(), 6894.75729316836, 1e-9);
}

EZTEST(pressure_named_constants_match_literals) {
  EZ_ASSERT_NEAR(ez::pascal.getValue(), 1.0, 1e-12);
  EZ_ASSERT_NEAR(ez::bar.getValue(), 100000.0, 1e-9);
  EZ_ASSERT_NEAR(ez::psi.getValue(), 6894.75729316836, 1e-9);
}

EZTEST(pressure_round_trip_conversion_every_unit) {
  const ez::QPressure p = 2_psi;
  EZ_ASSERT_NEAR(p.convert(1.0_psi), 2.0, 1e-9);
  EZ_ASSERT_NEAR(p.convert(1.0_Pa), 2.0 * 6894.75729316836, 1e-6);
  EZ_ASSERT_NEAR(p.convert(1.0_bar), 2.0 * 6894.75729316836 / 100000.0, 1e-9);
}

EZTEST(torque_literals_produce_correct_base_values_in_newton_meter) {
  EZ_ASSERT_NEAR((1_nM).getValue(), 1.0, 1e-12);
  EZ_ASSERT_NEAR((1_ftLb).getValue(), 1.355817948, 1e-12);
  EZ_ASSERT_NEAR((1_inLb).getValue(), 0.11298482854806069, 1e-12);
}

EZTEST(torque_named_constants_match_literals) {
  EZ_ASSERT_NEAR(ez::newtonMeter.getValue(), 1.0, 1e-12);
  EZ_ASSERT_NEAR(ez::footPound.getValue(), 1.355817948, 1e-12);
  EZ_ASSERT_NEAR(ez::inchPound.getValue(), 0.11298482854806069, 1e-12);
}

EZTEST(torque_round_trip_conversion_every_unit) {
  const ez::QTorque t = 3_ftLb;
  EZ_ASSERT_NEAR(t.convert(1.0_ftLb), 3.0, 1e-9);
  EZ_ASSERT_NEAR(t.convert(1.0_nM), 3.0 * 1.355817948, 1e-9);
  EZ_ASSERT_NEAR(t.convert(1.0_inLb), 3.0 * 1.355817948 / 0.11298482854806069, 1e-9);
}

EZTEST(derived_force_from_mass_times_acceleration) {
  const ez::QForce F = 1_kg * 1_G;
  EZ_ASSERT_NEAR(F.getValue(), 9.80665, 1e-12);
}

EZTEST(derived_torque_from_force_times_length) {
  const ez::QTorque tq = 1_n * 1_m;
  EZ_ASSERT_NEAR(tq.getValue(), 1.0, 1e-12);
}

EZTEST(derived_pressure_from_force_over_area) {
  const ez::QPressure p = 1_lbf / ez::inch2;
  EZ_ASSERT_NEAR(p.getValue(), 4.4482216152605 / 0.0006451600000000001, 1e-6);
}
