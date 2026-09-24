#include <cstring>

#include "EZ-Units/units.hpp"
#include "framework.hpp"

using namespace ez::literals;

EZTEST(short_unit_name_covers_every_named_length_unit) {
  EZ_ASSERT(std::strcmp(ez::getShortUnitName(ez::QLength(ez::meter)), "m") == 0);
  EZ_ASSERT(std::strcmp(ez::getShortUnitName(ez::QLength(ez::decimeter)), "dm") == 0);
  EZ_ASSERT(std::strcmp(ez::getShortUnitName(ez::QLength(ez::centimeter)), "cm") == 0);
  EZ_ASSERT(std::strcmp(ez::getShortUnitName(ez::QLength(ez::millimeter)), "mm") == 0);
  EZ_ASSERT(std::strcmp(ez::getShortUnitName(ez::QLength(ez::kilometer)), "km") == 0);
  EZ_ASSERT(std::strcmp(ez::getShortUnitName(ez::QLength(ez::inch)), "in") == 0);
  EZ_ASSERT(std::strcmp(ez::getShortUnitName(ez::QLength(ez::foot)), "ft") == 0);
  EZ_ASSERT(std::strcmp(ez::getShortUnitName(ez::QLength(ez::yard)), "yd") == 0);
  EZ_ASSERT(std::strcmp(ez::getShortUnitName(ez::QLength(ez::mile)), "mi") == 0);
  EZ_ASSERT(std::strcmp(ez::getShortUnitName(ez::QLength(ez::tile)), "tile") == 0);
}

EZTEST(short_unit_name_covers_every_named_angle_unit) {
  EZ_ASSERT(std::strcmp(ez::getShortUnitName(ez::QAngle(ez::degree)), "deg") == 0);
  EZ_ASSERT(std::strcmp(ez::getShortUnitName(ez::QAngle(ez::radian)), "rad") == 0);
}

EZTEST(short_unit_name_via_literal) {
  EZ_ASSERT(std::strcmp(ez::getShortUnitName(1_in), "in") == 0);
  EZ_ASSERT(std::strcmp(ez::getShortUnitName(1_deg), "deg") == 0);
}

EZTEST(short_unit_name_returns_empty_string_for_unnamed_value) {
  // Not equal to any of the ten named QLength constants.
  const ez::QLength weird(12.5);
  EZ_ASSERT(std::strcmp(ez::getShortUnitName(weird), "") == 0);

  // Not equal to degree or radian.
  const ez::QAngle weird_angle(0.5);
  EZ_ASSERT(std::strcmp(ez::getShortUnitName(weird_angle), "") == 0);
}

EZTEST(short_unit_name_is_constexpr) {
  constexpr const char *name = ez::getShortUnitName(ez::QLength(ez::inch));
  static_assert(name[0] == 'i' && name[1] == 'n' && name[2] == '\0');
  EZ_ASSERT(name[0] == 'i');
}
