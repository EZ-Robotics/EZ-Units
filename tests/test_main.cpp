#include "framework.hpp"

int main() {
  for (auto &t : eztest::registry()) {
    eztest::g_current_test = t.name;
    t.fn();
  }
  std::printf("%d/%d assertions passed\n", eztest::g_total - eztest::g_failures, eztest::g_total);
  return eztest::g_failures == 0 ? 0 : 1;
}
