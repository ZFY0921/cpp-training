#pragma once
#include "Executor.hpp"
#include "PoseHandler.hpp"

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
    // 状态数据已抽离到 PoseHandler：Executorlmpl 只保留"执行"职责
    PoseHandler poseHandler;
};
}  // namespace adas
