# Processor Pipeline Simulator

A C++17 command-line simulator for a configurable-width, five-stage processor pipeline.

It reads an instruction trace, moves instructions through **IF → ID → EX → MEM → WB**, models common pipeline hazards, then reports instruction mix, total cycles, and IPC.

## Quick start

```bash
make
./pipeline_simulator examples/sample_trace.txt 1 15 2
```

Example output:

```text
integer instructions: 46.67%
floating point instructions: 0.00%
branch instructions: 6.67%
load instructions: 0.00%
store instructions: 46.67%
clock cycles: 21
IPC: 0.71
```

## What it models

- configurable pipeline width
- five pipeline stages
- data dependencies between instructions
- branch-related control stalls
- structural conflicts in execute and memory stages
- instruction mix and cycle statistics

## Usage

```text
./pipeline_simulator <trace-file> <start-instruction> <instruction-count> <width>
```

Example:

```bash
./pipeline_simulator examples/sample_trace.txt 1 15 2
```

Arguments:

| Argument | Meaning |
| --- | --- |
| `trace-file` | Input instruction trace |
| `start-instruction` | First instruction to simulate, starting at 1 |
| `instruction-count` | Number of instructions to simulate |
| `width` | Maximum instructions processed per pipeline stage each cycle |

## Trace format

Each line contains an instruction address, instruction type, and optional dependency addresses.

```text
<hex-address>,<type>,<dependency-1>,<dependency-2>,...
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

The included trace is synthetic and lives at `examples/sample_trace.txt`.

## Project structure

```text
.
├── include/                 # Pipeline data types and interfaces
├── src/                     # Simulator and hazard logic
├── examples/                # Sample trace
├── tests/                   # Smoke test
├── .github/workflows/       # CI
└── Makefile
```

The main pieces are:

- `Simulation` controls trace loading, clock cycles, and stage movement
- `DependencyChecker` decides whether an instruction can advance
- `PipelineManager` stores the instructions currently in each stage
- `Instruction` represents one trace instruction and its dependencies

## Build and test

Requires a C++17 compiler and `make`.

```bash
make
make test
```

The build enables `-Wall`, `-Wextra`, `-Wpedantic`, and `-Werror`.

GitHub Actions builds with both GCC and Clang, runs the smoke test, and runs an AddressSanitizer/UndefinedBehaviorSanitizer build for pull requests.

## Scope

This is a small systems-programming simulator built to explore pipeline scheduling and hazards. It focuses on clear pipeline behavior rather than reproducing a specific commercial CPU microarchitecture.

## Collaboration

This was built as a team course project and is kept as a fork so the original shared history stays visible.

My contributions are also visible in that history under **Ernest Wong / jumiknows**. They include the original dependency-checking component, control-dependency handling, simulation test work, and the later repository cleanup that added the current structure, CI and documentation.

Other parts of the simulator were developed by my teammate. The commit history is the source of truth for individual contributions.


## Engineering workflow

Focused changes use pull requests, structured issues, CODEOWNERS, dependency updates for GitHub Actions, and a PR-title policy. See [CONTRIBUTING.md](CONTRIBUTING.md).
