// Only built by the okapi-fixture test target (tests/fixtures on the include
// path). Verifies the implicit converting constructor from okapi::RQuantity
// into ez::RQuantity (and the three named types) compiles and produces the
// correct converted value, and that EZ_UNITS_HAS_OKAPI_BRIDGE is defined.
#include "EZ-Units/units.hpp"
#include "framework.hpp"
#include <cstring>
#include <type_traits>
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QTime.hpp"

#ifndef EZ_UNITS_HAS_OKAPI_BRIDGE
#error "EZ_UNITS_HAS_OKAPI_BRIDGE should be defined when okapi headers are visible"
#endif

static void takes_ez_qlength(ez::QLength q, double *out) {
  *out = q.getValue();
}

static void takes_ez_qangle(ez::QAngle q, double *out) {
  *out = q.getValue();
}

static void takes_ez_qtime(ez::QTime q, double *out) {
  *out = q.getValue();
}

EZTEST(okapi_values_convert_implicitly_into_ez_parameters) {
  const okapi::QLength okLen = 5.0 * okapi::inch;
  const okapi::QAngle okAng = 45.0 * okapi::degree;
  const okapi::QTime okTime = 200.0 * okapi::millisecond;

  double lenOut = 0.0, angOut = 0.0, timeOut = 0.0;
  takes_ez_qlength(okLen, &lenOut);
  takes_ez_qangle(okAng, &angOut);
  takes_ez_qtime(okTime, &timeOut);

  EZ_ASSERT_NEAR(lenOut, 5.0 * 0.0254, 1e-9);
  EZ_ASSERT_NEAR(angOut, 45.0 * 3.1415926535897932384626433832795 / 180.0, 1e-9);
  EZ_ASSERT_NEAR(timeOut, 0.2, 1e-9);
}

// ---------------------------------------------------------------------------
// Bitwise equivalence with okapi. EZ-Template's hard cut from okapi to ez types
// relies on ez producing exactly the same doubles okapi did, so these compare
// object bytes with memcmp instead of using a tolerance. If one of these fails,
// ez and okapi have diverged - do not loosen it to EZ_ASSERT_NEAR.
// ---------------------------------------------------------------------------

// True if a and b have identical object representations. Both must be plain
// 8-byte values (a double or an RQuantity wrapping one), otherwise memcmp would
// be comparing something other than the value.
template <typename A, typename B> static bool same_bits(const A &a, const B &b) {
  static_assert(sizeof(A) == sizeof(double) && sizeof(B) == sizeof(double),
                "same_bits only compares 8-byte double-backed values");
  static_assert(std::is_trivially_copyable<A>::value && std::is_trivially_copyable<B>::value,
                "same_bits requires trivially copyable types");
  return std::memcmp(&a, &b, sizeof(double)) == 0;
}

// Each namespace pulls in exactly one library's literals, so 24_in etc. are not
// ambiguous inside it (see compile_fail/literal_ambiguity.cpp for what happens
// when both are visible at once).
namespace ez_lit {
using namespace ez::literals;
inline ez::QLength inches() { return 24_in; }
inline ez::QAngle degrees() { return 90_deg; }
inline ez::QTime millis() { return 100_ms; }
inline ez::QAngle tiny_degrees() { return 0.0000000000000000000001_deg; }
} // namespace ez_lit

namespace ok_lit {
using namespace okapi::literals;
inline okapi::QLength inches() { return 24_in; }
inline okapi::QAngle degrees() { return 90_deg; }
inline okapi::QTime millis() { return 100_ms; }
inline okapi::QAngle tiny_degrees() { return 0.0000000000000000000001_deg; }
} // namespace ok_lit

EZTEST(bitwise_unit_constants_match_okapi) {
  EZ_ASSERT(same_bits(ez::degree, okapi::degree));
  EZ_ASSERT(same_bits(ez::inch, okapi::inch));
  EZ_ASSERT(same_bits(ez::millisecond, okapi::millisecond));
}

EZTEST(bitwise_literals_match_okapi) {
  EZ_ASSERT(same_bits(ez_lit::inches(), ok_lit::inches()));
  EZ_ASSERT(same_bits(ez_lit::degrees(), ok_lit::degrees()));
  EZ_ASSERT(same_bits(ez_lit::millis(), ok_lit::millis()));
  EZ_ASSERT(same_bits(ez_lit::tiny_degrees(), ok_lit::tiny_degrees()));
}

EZTEST(bitwise_convert_matches_okapi) {
  const double values[] = {0.0, 1.0, -1.0, 0.5, 3.7, 24.0, -5.5, 100.0, 1e6, 1e-9};
  for (double v : values) {
    EZ_ASSERT(same_bits(ez::QLength(v).convert(ez::inch), okapi::QLength(v).convert(okapi::inch)));
    EZ_ASSERT(same_bits(ez::QAngle(v).convert(ez::degree), okapi::QAngle(v).convert(okapi::degree)));
    EZ_ASSERT(same_bits(ez::QTime(v).convert(ez::millisecond),
                        okapi::QTime(v).convert(okapi::millisecond)));
  }
}
