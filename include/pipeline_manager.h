#pragma once

#include "instruction.h"

#include <deque>

struct PipelineManager {
    std::deque<Instruction> fetch;
    std::deque<Instruction> decode;
    std::deque<Instruction> execute;
    std::deque<Instruction> memory;
    std::deque<Instruction> writeback;

    [[nodiscard]] bool empty() const {
        return fetch.empty() && decode.empty() && execute.empty() &&
               memory.empty() && writeback.empty();
    }
};
