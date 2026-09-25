# Contributing

Keep changes small enough to understand and test.

## Before a pull request

Run:

```bash
make clean
make
make test
```

If behaviour changes, add a test that shows the expected cycle count or hazard behaviour.

## Workflow

1. Start from the latest `master`.
2. Create a short branch for one change.
3. Make the change.
4. Run the local checks.
5. Open a pull request.

Examples:

```text
fix/control-stall
test/load-store-hazard
docs/trace-format
```

For simulator changes, explain any effect on cycle count, IPC, hazards or trace parsing.
