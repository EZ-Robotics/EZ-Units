// Only built by the okapi-fixture test target (tests/fixtures on the include
// path). For the 13 types added for OkapiLib parity: every ez constant must
// equal its okapi counterpart to 1e-12 (both are the same formula over the
// same doubles, so in practice these match bit-for-bit), and an okapi value
// must implicitly convert into the matching ez type via the bridge ctor.
#include "EZ-Units/units.hpp"
#include "framework.hpp"
#include "okapi/api/units/QAcceleration.hpp"
#include "okapi/api/units/QAngularAcceleration.hpp"
#include "okapi/api/units/QAngularJerk.hpp"
#include "okapi/api/units/QAngularSpeed.hpp"
#include "okapi/api/units/QArea.hpp"
#include "okapi/api/units/QForce.hpp"
#include "okapi/api/units/QFrequency.hpp"
#include "okapi/api/units/QJerk.hpp"
#include "okapi/api/units/QMass.hpp"
#include "okapi/api/units/QPressure.hpp"
#include "okapi/api/units/QSpeed.hpp"
#include "okapi/api/units/QTorque.hpp"
#include "okapi/api/units/QVolume.hpp"

using namespace ez::literals;

EZTEST(okapi_bridge_speed) {
  EZ_ASSERT_NEAR(ez::mps.getValue(), okapi::mps.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::miph.getValue(), okapi::miph.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::kmph.getValue(), okapi::kmph.getValue(), 1e-12);
  const ez::QSpeed s = 3.5 * okapi::miph;
  EZ_ASSERT_NEAR(s.getValue(), (3.5 * okapi::miph).getValue(), 1e-12);
}

EZTEST(okapi_bridge_acceleration) {
  EZ_ASSERT_NEAR(ez::mps2.getValue(), okapi::mps2.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::G.getValue(), okapi::G.getValue(), 1e-12);
  const ez::QAcceleration a = 2.0 * okapi::G;
  EZ_ASSERT_NEAR(a.getValue(), (2.0 * okapi::G).getValue(), 1e-12);
}

EZTEST(okapi_bridge_jerk) {
  const okapi::QJerk okJerk(2.5);
  const ez::QJerk j = okJerk;
  EZ_ASSERT_NEAR(j.getValue(), 2.5, 1e-12);
}

EZTEST(okapi_bridge_angular_speed) {
  EZ_ASSERT_NEAR(ez::radps.getValue(), okapi::radps.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::rpm.getValue(), okapi::rpm.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::cps.getValue(), okapi::cps.getValue(), 1e-12);
  const ez::QAngularSpeed w = 60.0 * okapi::rpm;
  EZ_ASSERT_NEAR(w.getValue(), (60.0 * okapi::rpm).getValue(), 1e-12);
}

EZTEST(okapi_bridge_angular_acceleration) {
  const okapi::QAngularAcceleration okWa(1.5);
  const ez::QAngularAcceleration wa = okWa;
  EZ_ASSERT_NEAR(wa.getValue(), 1.5, 1e-12);
}

EZTEST(okapi_bridge_angular_jerk) {
  const okapi::QAngularJerk okWj(0.75);
  const ez::QAngularJerk wj = okWj;
  EZ_ASSERT_NEAR(wj.getValue(), 0.75, 1e-12);
}

EZTEST(okapi_bridge_frequency) {
  EZ_ASSERT_NEAR(ez::Hz.getValue(), okapi::Hz.getValue(), 1e-12);
  const ez::QFrequency f = 5.0 * okapi::Hz;
  EZ_ASSERT_NEAR(f.getValue(), (5.0 * okapi::Hz).getValue(), 1e-12);
}

EZTEST(okapi_bridge_area) {
  EZ_ASSERT_NEAR(ez::kilometer2.getValue(), okapi::kilometer2.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::meter2.getValue(), okapi::meter2.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::decimeter2.getValue(), okapi::decimeter2.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::centimeter2.getValue(), okapi::centimeter2.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::millimeter2.getValue(), okapi::millimeter2.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::inch2.getValue(), okapi::inch2.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::foot2.getValue(), okapi::foot2.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::mile2.getValue(), okapi::mile2.getValue(), 1e-12);
  const ez::QArea a = 2.0 * okapi::foot2;
  EZ_ASSERT_NEAR(a.getValue(), (2.0 * okapi::foot2).getValue(), 1e-12);
}

EZTEST(okapi_bridge_volume) {
  EZ_ASSERT_NEAR(ez::kilometer3.getValue(), okapi::kilometer3.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::meter3.getValue(), okapi::meter3.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::decimeter3.getValue(), okapi::decimeter3.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::centimeter3.getValue(), okapi::centimeter3.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::millimeter3.getValue(), okapi::millimeter3.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::inch3.getValue(), okapi::inch3.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::foot3.getValue(), okapi::foot3.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::mile3.getValue(), okapi::mile3.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::litre.getValue(), okapi::litre.getValue(), 1e-12);
  const ez::QVolume v = 2.0 * okapi::litre;
  EZ_ASSERT_NEAR(v.getValue(), (2.0 * okapi::litre).getValue(), 1e-12);
}

EZTEST(okapi_bridge_mass) {
  EZ_ASSERT_NEAR(ez::kg.getValue(), okapi::kg.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::gramme.getValue(), okapi::gramme.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::tonne.getValue(), okapi::tonne.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::ounce.getValue(), okapi::ounce.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::pound.getValue(), okapi::pound.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::stone.getValue(), okapi::stone.getValue(), 1e-12);
  const ez::QMass m = 2.0 * okapi::pound;
  EZ_ASSERT_NEAR(m.getValue(), (2.0 * okapi::pound).getValue(), 1e-12);
}

EZTEST(okapi_bridge_force) {
  EZ_ASSERT_NEAR(ez::newton.getValue(), okapi::newton.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::poundforce.getValue(), okapi::poundforce.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::kilopond.getValue(), okapi::kilopond.getValue(), 1e-12);
  const ez::QForce f = 2.0 * okapi::poundforce;
  EZ_ASSERT_NEAR(f.getValue(), (2.0 * okapi::poundforce).getValue(), 1e-12);
}

EZTEST(okapi_bridge_pressure) {
  EZ_ASSERT_NEAR(ez::pascal.getValue(), okapi::pascal.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::bar.getValue(), okapi::bar.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::psi.getValue(), okapi::psi.getValue(), 1e-12);
  const ez::QPressure p = 2.0 * okapi::psi;
  EZ_ASSERT_NEAR(p.getValue(), (2.0 * okapi::psi).getValue(), 1e-12);
}

EZTEST(okapi_bridge_torque) {
  EZ_ASSERT_NEAR(ez::newtonMeter.getValue(), okapi::newtonMeter.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::footPound.getValue(), okapi::footPound.getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::inchPound.getValue(), okapi::inchPound.getValue(), 1e-12);
  const ez::QTorque t = 2.0 * okapi::footPound;
  EZ_ASSERT_NEAR(t.getValue(), (2.0 * okapi::footPound).getValue(), 1e-12);
}
