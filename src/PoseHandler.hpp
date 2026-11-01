#pragma once
#include "Executor.hpp"

namespace adas
{
class PoseHandler final
{
public:
    PoseHandler(const Pose& pose) noexcept;
    PoseHandler(const PoseHandler&) = delete;
    PoseHandler& operator=(const PoseHandler&) = delete;

public:
    void Move(void) noexcept;
    void TurnLeft(void) noexcept;
    void TurnRight(void) noexcept;
    void Fast(void) noexcept;
    bool IsFast(void) const noexcept;

    // 倒车状态：B 指令切换，与 F 状态可叠加
    void Reverse(void) noexcept;
    bool IsReverse(void) const noexcept;

    Pose Query(void) const noexcept;

private:
    Pose pose;
    bool fast{false};
    bool reverse{false};
};
}  // namespace adas
