# EZ-Units

A header-only C++ units library for VEX V5 / PROS, providing `QLength`, `QAngle`,
and `QTime` with compile-time dimensional analysis and user-defined literals like
`24_in`, `90_deg`, and `100_ms`.

## Why this exists

[EZ-Template](https://github.com/EZ-Robotics/EZ-Template) has always depended on
all of [OkapiLib](https://github.com/purduesigbots/OkapiLib) just to get these
three unit types. OkapiLib is now a maintenance fork with no new features, so
EZ-Robotics is pulling the units out into their own dependency: EZ-Units. It's
derived from OkapiLib's units implementation (see [Attribution](#attribution)),
lives in the `ez` namespace, and ships two ways:

- **Standalone**, for anyone who wants just the units, via `pros c apply EZ-Units`.
- **Vendored inside EZ-Template**, so EZ-Template users get it for free with one
  install.

Both paths install the header to the exact same path,
`include/EZ-Units/units.hpp`, so the two can never conflict via ODR even if a
project somehow ends up with both.

## Install

### Standalone

```
pros c fetch EZ-Units@1.0.0.zip   # or however you obtained the template
pros c apply EZ-Units
```

or, once EZ-Units is published to the PROS template depot:

```
pros c apply EZ-Units
```

### With EZ-Template

If you're using EZ-Template, you already have EZ-Units — it's vendored at the
same `include/EZ-Units/units.hpp` path. Nothing extra to install.

## Usage

```cpp
#include "EZ-Units/units.hpp"

using namespace ez::literals;

void autonomous() {
  constexpr ez::QLength tile_size = 24_in;
  constexpr ez::QAngle quarter_turn = 90_deg;
  constexpr ez::QTime settle_time = 100_ms;

  ez::QLength distance = 2 * tile_size;
  double distance_in_inches = distance.convert(1.0_in); // or ConvertTo(distance, in)
}
```

Arithmetic follows normal dimensional analysis rules at compile time — adding a
`QLength` to a `QTime` is a compile error, and dividing a `QLength` by a `QTime`
gives you back a velocity (an unnamed, but still fully checked, quantity type).

## Unit list

| Quantity  | Base unit    | Literals |
|-----------|--------------|----------|
| `QLength` | meter        | `_mm`, `_cm`, `_m`, `_km`, `_in`, `_ft`, `_yd`, `_mi`, `_tile` |
| `QAngle`  | radian       | `_rad`, `_deg` |
| `QTime`   | second       | `_s`, `_ms`, `_min`, `_h`, `_day` |

`ez::Number` (unitless) and the `_pi` literal (a plain `long double`, not a
quantity) are also available, matching OkapiLib.

## ⚠️ Literal ambiguity with OkapiLib

**If a translation unit has both `using namespace okapi::literals` and
`using namespace ez::literals` visible, every literal suffix the two libraries
share (`_in`, `_deg`, `_ms`, etc.) becomes a hard compile error:**

```
error: call to 'operator""_in' is ambiguous
```

This is the single most likely support question, so: **EZ-Units owns the global
literals.** If you still have code using OkapiLib's units directly (e.g. mid-
migration), qualify it explicitly — `okapi::literals::operator""_in(...)` or move
that code into its own translation unit that doesn't `using namespace ez::literals`.
Don't pull in both unqualified in the same file.

## The OkapiLib bridge

If a project has OkapiLib's units headers on its include path (true for most
existing EZ-Template projects mid-migration), EZ-Units detects this via
`__has_include` and adds an implicit converting constructor from the matching
`okapi::RQuantity` type. This means a function that takes an `ez`-typed
parameter keeps accepting `okapi` values without any code changes:

```cpp
void drive_forward(ez::QLength distance); // your new code, typed with ez

drive_forward(some_okapi_qlength_value); // still compiles - implicit bridge
```

This guard means EZ-Units compiles cleanly whether or not OkapiLib is present at
all.

**The bridge does not cover arithmetic.** `ez::QLength + okapi::QLength` fails to
compile — template argument deduction for the arithmetic operators won't go
through a converting constructor, only direct argument passing benefits from it.
In practice this rarely matters, since [the literal ambiguity above](#-literal-ambiguity-with-okapilib)
already pushes all new code onto `ez::literals`, so you're very unlikely to be
mixing `ez` and `okapi` values in the same expression.

## Version macro

```cpp
#define EZ_UNITS_VERSION_MAJOR 1
#define EZ_UNITS_VERSION_MINOR 0
```

This is load-bearing for EZ-Template: it `static_assert`s on
`EZ_UNITS_VERSION_MAJOR` so that a version mismatch between a standalone
EZ-Units install and the copy vendored inside EZ-Template becomes a clear
compile error instead of silent breakage.

## Testing

Tests run with a plain host compiler — no PROS, no ARM toolchain, no hardware:

```
tests/run_tests.sh
```

This builds and runs the unit test suite, plus a set of negative-compile checks
that assert certain expressions (dimension mismatches, the literal ambiguity
above, the arithmetic bridge limitation above) fail to compile as documented.
CI runs this as a required check on every push and PR, alongside a separate job
that builds the PROS template itself so packaging breakage (e.g. a stale
`TEMPLATE_FILES` glob) is caught too.

## Attribution

The unit implementation in `include/EZ-Units/units.hpp` is derived from
[OkapiLib](https://github.com/purduesigbots/OkapiLib)'s
`include/okapi/api/units/` (MPL-2.0), which itself is a modified version of
Benjamin Jurke's compile-time unit checking work — see his
[2015 blog post](https://benjaminjurke.com/content/articles/2015/compile-time-numerical-unit-dimension-checking/).
The original MPL-2.0 and attribution header is kept verbatim at the top of the
derived file.

EZ-Units is licensed under MPL-2.0, matching OkapiLib.
