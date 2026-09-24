# Test fixtures

`okapi/api/units/*.hpp` are unmodified, verbatim copies of the same files from
[purduesigbots/OkapiLib](https://github.com/purduesigbots/OkapiLib)
(`include/okapi/api/units/`), licensed MPL-2.0 (see the license header inside
each file). They're vendored here solely so the okapi-bridge tests
(`tests/test_okapi_bridge.cpp`, `tests/compile_fail/literal_ambiguity.cpp`,
`tests/compile_fail/okapi_bridge_arithmetic.cpp`, and the tests added for
OkapiLib parity) can run without requiring a full OkapiLib install on the test
machine. They are not part of EZ-Units itself - see
`include/EZ-Units/units.hpp` and the main README's Attribution section for
that.

`RQuantity.hpp`, `QLength.hpp`, `QAngle.hpp`, and `QTime.hpp` were vendored
from `purduesigbots/OkapiLib@1355c29e1cc7a01dc2080434ecb7b32bec7b8328`
(`master`, checked 2026-09-24), matching the commit the remaining 13 were
pinned from below - all 17 files come from the same tree, byte-for-byte
identical to upstream at that commit.

`QAcceleration.hpp`, `QAngularAcceleration.hpp`, `QAngularJerk.hpp`,
`QAngularSpeed.hpp`, `QArea.hpp`, `QForce.hpp`, `QFrequency.hpp`,
`QJerk.hpp`, `QMass.hpp`, `QPressure.hpp`, `QSpeed.hpp`, `QTorque.hpp`, and
`QVolume.hpp` were vendored from
`purduesigbots/OkapiLib@1355c29e1cc7a01dc2080434ecb7b32bec7b8328`
(`master`, checked 2026-09-24), matching the constants and literals ported
into `include/EZ-Units/units.hpp` for OkapiLib parity.
