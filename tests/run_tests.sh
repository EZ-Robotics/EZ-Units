#!/usr/bin/env bash
# Host test runner for EZ-Units. Builds and runs with a plain host compiler
# (no PROS, no ARM toolchain, no hardware). Override CXX/STD to use a
# different compiler or C++ standard, e.g.:
#   CXX=clang++ STD=c++20 tests/run_tests.sh
set -u

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TESTS_DIR="$ROOT_DIR/tests"
INCLUDE_DIR="$ROOT_DIR/include"
FIXTURES_DIR="$TESTS_DIR/fixtures"
BUILD_DIR="$TESTS_DIR/.build"

CXX="${CXX:-g++}"
STD="${STD:-gnu++20}"
EXTRA_CXXFLAGS="${EXTRA_CXXFLAGS:-}"

mkdir -p "$BUILD_DIR"

fail=0

echo "== Building default test suite (no okapi on include path) =="
"$CXX" -std="$STD" -Wall -Wextra $EXTRA_CXXFLAGS \
  -I "$INCLUDE_DIR" -I "$TESTS_DIR" \
  "$TESTS_DIR/test_main.cpp" \
  "$TESTS_DIR/test_length.cpp" \
  "$TESTS_DIR/test_angle.cpp" \
  "$TESTS_DIR/test_time.cpp" \
  "$TESTS_DIR/test_arithmetic.cpp" \
  "$TESTS_DIR/test_misc.cpp" \
  "$TESTS_DIR/test_no_okapi.cpp" \
  -o "$BUILD_DIR/host_tests" || { echo "FAIL: default test suite failed to compile"; fail=1; }

if [ -x "$BUILD_DIR/host_tests" ]; then
  "$BUILD_DIR/host_tests" || { echo "FAIL: default test suite reported failing assertions"; fail=1; }
fi

echo
echo "== Building okapi-bridge test suite (okapi fixture on include path) =="
"$CXX" -std="$STD" -Wall -Wextra $EXTRA_CXXFLAGS \
  -I "$INCLUDE_DIR" -I "$TESTS_DIR" -I "$FIXTURES_DIR" \
  "$TESTS_DIR/test_main.cpp" \
  "$TESTS_DIR/test_okapi_bridge.cpp" \
  -o "$BUILD_DIR/host_tests_okapi_bridge" || { echo "FAIL: okapi-bridge test suite failed to compile"; fail=1; }

if [ -x "$BUILD_DIR/host_tests_okapi_bridge" ]; then
  "$BUILD_DIR/host_tests_okapi_bridge" || { echo "FAIL: okapi-bridge test suite reported failing assertions"; fail=1; }
fi

echo
echo "== Negative-compile tests (each file below must FAIL to compile) =="
for f in "$TESTS_DIR"/compile_fail/*.cpp; do
  name="$(basename "$f")"
  if "$CXX" -std="$STD" $EXTRA_CXXFLAGS -I "$INCLUDE_DIR" -I "$FIXTURES_DIR" -c "$f" -o "$BUILD_DIR/$name.o" 2>"$BUILD_DIR/$name.log"; then
    echo "FAIL: $name compiled successfully but was expected to fail"
    cat "$BUILD_DIR/$name.log"
    fail=1
  else
    echo "OK (expected failure): $name"
  fi
done

echo
if [ "$fail" -eq 0 ]; then
  echo "All host tests passed."
else
  echo "One or more host tests FAILED."
fi
exit "$fail"
