#include "dependency_checker.h"

namespace {
bool isComputeType(InstructionType type) {
    return type == InstructionType::Integer ||
           type == InstructionType::FloatingPoint ||
           type == InstructionType::Branch;
}

bool isMemoryType(InstructionType type) {
    return type == InstructionType::Load || type == InstructionType::Store;
}
}  // namespace

bool DependencyChecker::canFetch(const PipelineManager& pipeline) const {
    if (pipeline.fetch.size() >= width_) {
        return false;
    }

    for (const auto& instruction : pipeline.fetch) {
        if (instruction.type == InstructionType::Branch) {
            return false;
        }
    }

    for (const auto& instruction : pipeline.decode) {
        if (instruction.type == InstructionType::Branch) {
            return false;
        }
    }

    for (const auto& instruction : pipeline.execute) {
        if (instruction.type == InstructionType::Branch && !instruction.executed) {
            return false;
        }
    }

    return true;
}

bool DependencyChecker::canDecode(const PipelineManager& pipeline) const {
    return pipeline.decode.size() < width_;
}

bool DependencyChecker::canExecute(const PipelineManager& pipeline,
                                   const Instruction& instruction) const {
    if (pipeline.execute.size() >= width_) {
        return false;
    }

    for (const auto& active : pipeline.execute) {
        if (active.type == instruction.type && !active.executed &&
            isComputeType(instruction.type)) {
            return false;
        }
    }

    for (const auto dependency : instruction.dependencies) {
        for (const auto& active : pipeline.execute) {
            if (active.address != dependency) {
                continue;
            }

            if ((!active.executed &&
                 (active.type == InstructionType::Integer ||
                  active.type == InstructionType::FloatingPoint)) ||
                isMemoryType(active.type)) {
                return false;
            }
        }

        for (const auto& active : pipeline.memory) {
            if (active.address == dependency && isMemoryType(active.type)) {
                return false;
            }
        }
    }

    return true;
}

bool DependencyChecker::canAccessMemory(const PipelineManager& pipeline,
                                        const Instruction& instruction) const {
    if (pipeline.memory.size() >= width_) {
        return false;
    }

    for (const auto& active : pipeline.memory) {
        if (active.type == instruction.type && isMemoryType(instruction.type)) {
            return false;
        }
    }

    return true;
}
