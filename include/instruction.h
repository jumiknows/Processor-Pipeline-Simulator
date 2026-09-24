#pragma once

#include <cstdint>
#include <vector>

enum class InstructionType : int {
    Integer = 1,
    FloatingPoint = 2,
    Branch = 3,
    Load = 4,
    Store = 5,
};

struct Instruction {
    std::uint64_t address{};
    InstructionType type{InstructionType::Integer};
    std::vector<std::uint64_t> dependencies;
    bool executed{false};
};
