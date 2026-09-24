#include "simulation.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace {
std::vector<std::string> splitCsv(const std::string& line) {
    std::vector<std::string> fields;
    std::stringstream stream(line);
    std::string field;

    while (std::getline(stream, field, ',')) {
        fields.push_back(field);
    }

    return fields;
}

InstructionType parseType(const std::string& value) {
    const int type = std::stoi(value);
    if (type < static_cast<int>(InstructionType::Integer) ||
        type > static_cast<int>(InstructionType::Store)) {
        throw std::invalid_argument("instruction type must be between 1 and 5");
    }
    return static_cast<InstructionType>(type);
}
}  // namespace

Simulation::Simulation(std::string trace_file, std::size_t start_instruction,
                       std::size_t instruction_count, std::size_t width)
    : trace_file_(std::move(trace_file)),
      start_instruction_(start_instruction),
      instruction_count_(instruction_count),
      width_(width),
      checker_(width) {}

Instruction Simulation::parseInstruction(const std::string& line) {
    const auto fields = splitCsv(line);
    if (fields.size() < 2) {
        throw std::invalid_argument("trace line must contain address and instruction type");
    }

    Instruction instruction;
    instruction.address = std::stoull(fields[0], nullptr, 16);
    instruction.type = parseType(fields[1]);

    for (std::size_t index = 2; index < fields.size(); ++index) {
        if (!fields[index].empty()) {
            instruction.dependencies.push_back(
                std::stoull(fields[index], nullptr, 16));
        }
    }

    return instruction;
}

void Simulation::recordType(const Instruction& instruction) {
    switch (instruction.type) {
        case InstructionType::Integer:
            ++stats_.integer;
            break;
        case InstructionType::FloatingPoint:
            ++stats_.floating_point;
            break;
        case InstructionType::Branch:
            ++stats_.branch;
            break;
        case InstructionType::Load:
            ++stats_.load;
            break;
        case InstructionType::Store:
            ++stats_.store;
            break;
    }
}

void Simulation::advance(PipelineManager& pipeline,
                         std::deque<Instruction>& pending) {
    for (auto& instruction : pipeline.execute) {
        instruction.executed = true;
    }

    pipeline.writeback.clear();
    while (!pipeline.memory.empty()) {
        pipeline.writeback.push_back(pipeline.memory.front());
        pipeline.memory.pop_front();
    }

    for (std::size_t slot = 0; slot < width_ && !pipeline.execute.empty(); ++slot) {
        if (!checker_.canAccessMemory(pipeline, pipeline.execute.front())) {
            break;
        }
        pipeline.memory.push_back(pipeline.execute.front());
        pipeline.execute.pop_front();
    }

    for (std::size_t slot = 0; slot < width_ && !pipeline.decode.empty(); ++slot) {
        if (!checker_.canExecute(pipeline, pipeline.decode.front())) {
            break;
        }
        pipeline.execute.push_back(pipeline.decode.front());
        pipeline.decode.pop_front();
    }

    for (std::size_t slot = 0; slot < width_ && !pipeline.fetch.empty(); ++slot) {
        if (!checker_.canDecode(pipeline)) {
            break;
        }
        pipeline.decode.push_back(pipeline.fetch.front());
        pipeline.fetch.pop_front();
    }

    for (std::size_t slot = 0; slot < width_ && !pending.empty(); ++slot) {
        if (!checker_.canFetch(pipeline)) {
            break;
        }
        pipeline.fetch.push_back(pending.front());
        recordType(pending.front());
        pending.pop_front();
    }
}

void Simulation::printStatistics() const {
    const auto percentage = [this](std::size_t count) {
        return 100.0 * static_cast<double>(count) /
               static_cast<double>(instruction_count_);
    };

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "integer instructions: " << percentage(stats_.integer) << "%\n";
    std::cout << "floating point instructions: " << percentage(stats_.floating_point) << "%\n";
    std::cout << "branch instructions: " << percentage(stats_.branch) << "%\n";
    std::cout << "load instructions: " << percentage(stats_.load) << "%\n";
    std::cout << "store instructions: " << percentage(stats_.store) << "%\n";
    std::cout << "clock cycles: " << stats_.cycles << '\n';
    std::cout << "IPC: " << static_cast<double>(instruction_count_) /
                                  static_cast<double>(stats_.cycles)
              << '\n';
}

void Simulation::run() {
    std::ifstream trace(trace_file_);
    if (!trace) {
        throw std::runtime_error("could not open trace file: " + trace_file_);
    }

    std::string line;
    for (std::size_t index = 1; index < start_instruction_; ++index) {
        if (!std::getline(trace, line)) {
            throw std::runtime_error("start instruction is beyond the trace file");
        }
    }

    PipelineManager pipeline;
    std::deque<Instruction> pending;
    std::size_t loaded = 0;

    while (loaded < instruction_count_ || !pending.empty() || !pipeline.empty()) {
        while (pending.size() < 4 && loaded < instruction_count_) {
            if (!std::getline(trace, line)) {
                throw std::runtime_error("trace ended before the requested instruction count");
            }
            pending.push_back(parseInstruction(line));
            ++loaded;
        }

        advance(pipeline, pending);
        ++stats_.cycles;
    }

    printStatistics();
}
