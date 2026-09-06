// Small hand-rolled test framework for EZ-Units host tests. No dependencies
// beyond the standard library, so tests build with a plain host g++/clang++
// and don't need PROS or an ARM toolchain.
#pragma once

#include <cmath>
#include <cstdio>
#include <vector>

namespace eztest {

struct TestCase {
  const char *name;
  void (*fn)();
};

inline std::vector<TestCase> &registry() {
  static std::vector<TestCase> r;
  return r;
}

struct Registrar {
  Registrar(const char *name, void (*fn)()) {
    registry().push_back({name, fn});
  }
};

inline int g_failures = 0;
inline int g_total = 0;
inline const char *g_current_test = "";

} // namespace eztest

#define EZTEST(name)                                                                             \
  static void eztest_##name();                                                                    \
  static ::eztest::Registrar eztest_reg_##name(#name, eztest_##name);                             \
  static void eztest_##name()

#define EZ_ASSERT(cond)                                                                           \
  do {                                                                                             \
    ++::eztest::g_total;                                                                           \
    if (!(cond)) {                                                                                 \
      ++::eztest::g_failures;                                                                      \
      std::fprintf(stderr, "FAIL [%s] %s:%d: %s\n", ::eztest::g_current_test, __FILE__, __LINE__,  \
                   #cond);                                                                         \
    }                                                                                               \
  } while (0)

#define EZ_ASSERT_NEAR(a, b, eps) EZ_ASSERT(std::fabs((double)(a) - (double)(b)) < (eps))
