#pragma once
#include "Executor.hpp"

namespace adas
{
class Executorlmpl final : public Executor
{
public:
    explicit Executorlmpl(const Pose& pose) noexcept;
    ~Executorlmpl() noexcept = default;

    Executorlmpl(const Executorlmpl&) = delete;
    Executorlmpl& operator=(const Executorlmpl&) = delete;

public:
    void Execute(const std::string& command) noexcept override;
    Pose Query(void) const noexcept override;

private:
    Pose pose;
};
}  // namespace adas