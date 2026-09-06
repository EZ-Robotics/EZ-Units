#include "EZ-Units/units.hpp"
#include "framework.hpp"

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
