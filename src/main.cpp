#include "main.h"

#include "EZ-Units/units.hpp"

// This project is header-only, so this file exists only so PROS has
// something to build. It is excluded from the library archive (see
// EXCLUDE_SRC_FROM_LIB in Makefile), so EZ-Units.a is expected to be empty.

using namespace ez::literals;

void initialize() {
  constexpr ez::QLength tile = 24_in;
  constexpr ez::QAngle turn = 90_deg;
  constexpr ez::QTime step = 100_ms;
  (void)tile;
  (void)turn;
  (void)step;
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {}
