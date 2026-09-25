# Processor Pipeline Simulator

A C++17 simulator for a configurable five-stage processor pipeline.

It reads an instruction trace, models stalls and reports total cycles, instruction mix and IPC.

## Run it

```bash
make
./pipeline_simulator examples/sample_trace.txt 1 15 2
```

Usage:

```text
pipeline_simulator <trace-file> <start-instruction> <instruction-count> <width>
```

| Argument | Meaning |
| --- | --- |
| `trace-file` | Input instruction trace |
| `start-instruction` | First instruction to simulate, starting at 1 |
| `instruction-count` | Number of instructions to simulate |
| `width` | Maximum instructions handled by a stage each cycle |

## Pipeline

The five stages are:

```text
IF
ID
EX
MEM
WB
```

The simulator models:

- data dependencies
- branch stalls
- execute-stage conflicts
- memory-stage conflicts
- configurable pipeline width

## Trace format

Each line contains a hexadecimal instruction address, an instruction type and optional dependency addresses.

```text
<address>,<type>,<dependency-1>,<dependency-2>,...
```

Example:

```text
ffff000008082840,1
ffff000008082844,5,ffff000008082840
```

Instruction types:

| Value | Type |
| ---: | --- |
| 1 | Integer |
| 2 | Floating point |
| 3 | Branch |
| 4 | Load |
| 5 | Store |

A small synthetic trace is included at `examples/sample_trace.txt`.

## Code map

`src/simulation.cpp`

Loads the trace, advances the pipeline and reports statistics.

`src/dependency_checker.cpp`

Decides whether an instruction can move forward.

`include/pipeline_manager.h`

Stores the instructions in each pipeline stage.

`include/instruction.h`

Defines instruction type, address and dependencies.

## Test it

```bash
make clean
make
make test
```

The build treats warnings as errors.

CI builds with GCC and Clang, runs the smoke test and checks a sanitizer build.

## Scope

This is a teaching and systems-programming simulator. It focuses on scheduling and hazards rather than reproducing a commercial CPU.

The next useful improvement is exact correctness testing with small traces that have known cycle counts. A visual timeline only becomes useful after the simulator can expose cycle-by-cycle state.

## Collaboration

This began as a team course project and remains a fork so the original history stays visible.

My commits under Ernest Wong and `jumiknows` include dependency checking, control-dependency handling, simulation test work and later repository maintenance.

The commit history is the source of truth for individual contributions.
