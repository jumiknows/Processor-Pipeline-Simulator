#pragma once

#include "dependency_checker.h"

#include <cstddef>
#include <deque>
#include <string>

class Simulation {
public:
    Simulation(std::string trace_file, std::size_t start_instruction,
               std::size_t instruction_count, std::size_t width);

    void run();

private:
    struct Statistics {
        std::size_t integer{};
        std::size_t floating_point{};
        std::size_t branch{};
        std::size_t load{};
        std::size_t store{};
        std::size_t cycles{};
    };

    static Instruction parseInstruction(const std::string& line);
    void advance(PipelineManager& pipeline, std::deque<Instruction>& pending);
    void recordType(const Instruction& instruction);
    void printStatistics() const;

    std::string trace_file_;
    std::size_t start_instruction_;
    std::size_t instruction_count_;
    std::size_t width_;
    DependencyChecker checker_;
    Statistics stats_;
};
