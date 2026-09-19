#include "EZ-Units/units.hpp"
#include "framework.hpp"
#include <algorithm>
#include <cmath>

using namespace ez::literals;

static_assert(sizeof(ez::QLength) == sizeof(double), "QLength must not carry any overhead over a plain double");
static_assert(sizeof(ez::QAngle) == sizeof(double), "QAngle must not carry any overhead over a plain double");
static_assert(sizeof(ez::QTime) == sizeof(double), "QTime must not carry any overhead over a plain double");

static_assert(EZ_UNITS_VERSION_MAJOR == 1, "EZ_UNITS_VERSION_MAJOR must be defined");
static_assert(EZ_UNITS_VERSION_MINOR == 0, "EZ_UNITS_VERSION_MINOR must be defined");

// constexpr evaluation at compile time
constexpr ez::QLength kTile = 24_in;
constexpr ez::QAngle kQuarterTurn = 90_deg;
constexpr ez::QTime kStep = 100_ms;
constexpr ez::QLength kSum = kTile + kTile;

static_assert(kTile.getValue() > 0.6095 && kTile.getValue() < 0.6097, "24in should be ~0.6096m");
static_assert(kQuarterTurn.getValue() > 1.5707 && kQuarterTurn.getValue() < 1.5709, "90deg should be ~pi/2 rad");
static_assert(kStep.getValue() == 0.1, "100ms should be 0.1s");
static_assert(kSum.getValue() > 1.2191 && kSum.getValue() < 1.2193, "24in + 24in should be ~1.2192m");

EZTEST(constexpr_values_match_runtime_values) {
  EZ_ASSERT_NEAR(kTile.getValue(), 0.6096, 1e-9);
  EZ_ASSERT_NEAR(kQuarterTurn.getValue(), 1.5707963267948966, 1e-9);
  EZ_ASSERT_NEAR(kStep.getValue(), 0.1, 1e-9);
}

// Control for compile_fail/namespace_ez_bare_*.cpp. Inside namespace ez the
// free functions units.hpp declares (abs, sin, sqrt, ...) hide the global
// <cmath> ones, so code there must write std::abs, std::sin, etc. This is the
// same shape as those compile_fail files with the calls qualified, so they can
// only be failing because of the unqualified name. Names that units.hpp does
// not declare (fabs, fmod, fmax, fmin, powf, exp, log) are still found bare.
namespace ez {
static double std_qualified_math_inside_namespace_ez() {
  double sum = 0.0;
  sum += std::abs(-3);
  sum += std::sin(0.0) + std::cos(0.0) + std::tan(0.0);
  sum += std::asin(0.0) + std::acos(1.0) + std::atan(0.0) + std::atan2(0.0, 1.0);
  sum += std::sinh(0.0) + std::cosh(0.0) + std::tanh(0.0);
  sum += std::asinh(0.0) + std::acosh(1.0) + std::atanh(0.0);
  sum += std::sqrt(4.0) + std::cbrt(8.0) + std::pow(2.0, 3.0) + std::hypot(3.0, 4.0);
  sum += std::copysign(1.0, -2.0) + std::ceil(1.5) + std::floor(1.5) + std::round(1.5) + std::trunc(1.5);
  sum += std::min(1.0, 2.0);
  // Not hidden: units.hpp declares no ez::fabs, ez::fmod, ez::fmax, ez::fmin, ez::powf, ez::exp, ez::log.
  sum += fabs(-1.0) + fmod(5.0, 3.0) + fmax(1.0, 2.0) + fmin(1.0, 2.0) + powf(2.0f, 3.0f) + exp(0.0) + log(1.0);
  return sum;
}
} // namespace ez

EZTEST(std_qualified_math_compiles_inside_namespace_ez) {
  // Per group: abs 3 | sin+cos+tan 1 | asin+acos+atan+atan2 0 | sinh+cosh+tanh 1 |
  // asinh+acosh+atanh 0 | sqrt+cbrt+pow+hypot 2+2+8+5=17 |
  // copysign+ceil+floor+round+trunc -1+2+1+2+1=5 | min 1 |
  // fabs+fmod+fmax+fmin+powf+exp+log 1+2+2+1+8+1+0=15.
  const double expected = 3 + 1 + 0 + 1 + 0 + 17 + 5 + 1 + 15;
  EZ_ASSERT_NEAR(ez::std_qualified_math_inside_namespace_ez(), expected, 1e-9);
}

EZTEST(ez_overloads_still_work_on_quantities) {
  EZ_ASSERT_NEAR(ez::sin(90_deg).getValue(), 1.0, 1e-12);
  EZ_ASSERT_NEAR(ez::abs(-5_in).getValue(), (5_in).getValue(), 1e-12);
  EZ_ASSERT_NEAR(ez::sqrt(ez::square(3_m)).getValue(), 3.0, 1e-12);
}
