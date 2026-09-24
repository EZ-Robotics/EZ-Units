# Contributing to EZ-Units

- EZ-Units has no `dev` branch. PRs target `main`.
- Branch names: `<type>/<short-description>` (`bug/`, `feature/`, `docs/`, `test/`, `build/`, `cleanup/`, `safety/`).
- Everything lives in the one header, `include/EZ-Units/units.hpp`. [EZ-Template](https://github.com/EZ-Robotics/EZ-Template)
  vendors that exact file byte-for-byte, so it never gets split into multiple headers.

## Commits & PR titles

Lead with a [gitmoji](https://gitmoji.dev):

| | |
| --- | --- |
| 🐛 | Bug fix |
| ✨ | New feature |
| 💥 | Breaking change |
| ♻️ | Refactor |
| 🔥 | Remove code |
| 🚨 | Fix warnings |
| 🧪 | Tests |
| 📝 | Docs |
| 👷 | CI/build |
| 🔧 | Config |
| ⬆️ | Upgrade dependency |
| ⏪️ | Revert |

## Rules specific to this repo

- Every name and signature in `include/EZ-Units/units.hpp` is ABI for EZ-Template, which vendors
  the header directly. Removing or changing one is 💥 and bumps `EZ_UNITS_VERSION_MAJOR`.
- Additions bump `EZ_UNITS_VERSION_MINOR`, `VERSION` in the `Makefile`, and the README's
  [Unit list](README.md#unit-list) together.
- Any change EZ-Template should pick up needs a matching PR there that copies the header and
  bumps `EZ_UNITS_TAG`.

## Before opening a PR

- `tests/run_tests.sh` — host-only, no PROS needed.
- `pros make` — builds the full project.
- Match `.clang-format`.
- CI runs `host-tests` (across compilers/standards) and `pros-build` on every PR.

## Merging

Prefer **Create a merge commit**, so every gitmoji-prefixed commit lands on `main`
individually instead of getting collapsed into one. **Squash and merge** is fine too — e.g.
for a branch with messy or non-gitmoji intermediate commits — as long as the resulting squash
commit still leads with a gitmoji.
