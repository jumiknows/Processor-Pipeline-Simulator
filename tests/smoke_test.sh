#!/usr/bin/env bash
set -euo pipefail

output=$(./pipeline_simulator examples/sample_trace.txt 1 15 2)

grep -q "clock cycles:" <<<"$output"
grep -q "IPC:" <<<"$output"
grep -q "branch instructions:" <<<"$output"

printf '%s\n' "$output"
