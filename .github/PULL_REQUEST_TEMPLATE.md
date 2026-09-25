## Problem

What pipeline behavior, hazard, timing, parsing, or correctness issue does this address?

## Approach

What changed in the simulator model, and why is that behavior correct?

Explain stage ordering, hazard handling, forwarding, stalls, cycle accounting, or parser assumptions when relevant.

## Verification

### Automated

List the compiler, build, tests, and sanitizer checks you ran.

### Expected behavior

For behavioral changes, provide a small trace or case with:

- input instructions
- expected cycles or IPC
- observed cycles or IPC
- reason for any difference from the previous implementation

## Risks and limitations

Describe unsupported instructions, architectural assumptions, trace-format limits, or cases that are not modeled.

## References

Link architecture documentation, course specification, prior issue, or other source used to determine expected behavior.

## Checklist

- [ ] `make` passes.
- [ ] `make test` passes.
- [ ] Behavior changes have a regression test or a clear reason why not.
- [ ] Cycle or IPC claims are backed by a reproducible case.
