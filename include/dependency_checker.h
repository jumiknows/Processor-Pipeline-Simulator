#pragma once

#include "pipeline_manager.h"

#include <cstddef>

class DependencyChecker {
public:
    explicit DependencyChecker(std::size_t width) : width_(width) {}

    [[nodiscard]] bool canFetch(const PipelineManager& pipeline) const;
    [[nodiscard]] bool canDecode(const PipelineManager& pipeline) const;
    [[nodiscard]] bool canExecute(const PipelineManager& pipeline, const Instruction& instruction) const;
    [[nodiscard]] bool canAccessMemory(const PipelineManager& pipeline, const Instruction& instruction) const;

private:
    std::size_t width_;
};
