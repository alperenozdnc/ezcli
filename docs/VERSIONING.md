# a guide on versioning ezcli for future contributors (probably just me)

so, i have a really simple guideline to follow that i think makes versioning
easier and more deterministic (although the problem of versioning is always
subjective, of course). here's the checklist.

let's assume we start from `v0.0.0`:

- did your changes fix or patch something the users use? -> `v0.0.1` (patch)
- did your changes add new entries to the public api? -> `v0.1.0` (minor)
- does your changes fundamentally change base assumptions or break currently
  working code? -> `v1.0.0` (major)

and that's it. i believe bumps should be rated on _effect_ of change, **not** the
size of it. because you could be writing a 1000-line utility and that still wouldn't
really constitute a major bump.

also, to note: if your bump doesn't bump the least significant field (patch),
then all fields before it should be zeroed out.

for example:

- `v1.2.5` -> `v1.3.0`
- `v0.99.98` -> `v1.0.0`
- `v0.0.2` -> `v0.0.3`
