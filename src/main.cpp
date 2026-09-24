#include "simulation.h"

#include <cstddef>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {
void printUsage(const char* program) {
    std::cerr << "Usage: " << program
              << " <trace-file> <start-instruction> <instruction-count> <width>\n"
              << "Example: " << program << " examples/sample_trace.txt 1 15 2\n";
}

std::size_t parsePositive(const char* value, const char* name) {
    const long long parsed = std::stoll(value);
    if (parsed <= 0) {
        throw std::invalid_argument(std::string(name) + " must be greater than 0");
    }
    return static_cast<std::size_t>(parsed);
}
}  // namespace

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printUsage(argv[0]);
        return 1;
    }

    try {
        const std::string trace_file = argv[1];
        const std::size_t start_instruction = parsePositive(argv[2], "start instruction");
        const std::size_t instruction_count = parsePositive(argv[3], "instruction count");
        const std::size_t width = parsePositive(argv[4], "pipeline width");

        Simulation simulation(trace_file, start_instruction, instruction_count, width);
        simulation.run();
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
