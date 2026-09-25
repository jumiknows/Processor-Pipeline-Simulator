# Contributing

Keep simulator changes focused and easy to validate.

## Workflow

1. Start from the latest default branch.
2. Create one branch per logical change.
3. Add or update tests when behavior changes.
4. Run the build and smoke test.
5. Open a pull request with the expected pipeline behavior and results.

Example branches:

```text
feat/forwarding-model
fix/control-stall
test/load-store-hazard
docs/trace-format
```

## Local checks

```bash
make clean
make
make test
```

The project treats compiler warnings as errors.

## Pull requests

Use Conventional Commit-style titles such as:

```text
fix: prevent dependent instruction from advancing early
test: cover branch stall behavior
docs: clarify trace dependency format
```

Explain any change that affects cycle count, IPC, hazard behavior, or trace parsing.

Prefer squash merge after CI passes.
