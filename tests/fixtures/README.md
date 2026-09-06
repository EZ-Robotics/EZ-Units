# Test fixtures

`okapi/api/units/{RQuantity,QLength,QAngle,QTime}.hpp` are unmodified, verbatim
copies of the same files from
[purduesigbots/OkapiLib](https://github.com/purduesigbots/OkapiLib)
(`include/okapi/api/units/`), licensed MPL-2.0 (see the license header inside
each file). They're vendored here solely so the okapi-bridge tests
(`tests/test_okapi_bridge.cpp`, `tests/compile_fail/literal_ambiguity.cpp`,
`tests/compile_fail/okapi_bridge_arithmetic.cpp`) can run without requiring a
full OkapiLib install on the test machine. They are not part of EZ-Units
itself - see `include/EZ-Units/units.hpp` and the main README's Attribution
section for that.
