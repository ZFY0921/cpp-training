#include "ExecutorImpl.hpp"

#include <memory>

namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}

ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : pose(pose)
{
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    // 只负责指令的识别与分发，具体行为由对应的指令类实现
    for (const auto cmd : commands) {
        if (cmd == 'M') {
            std::unique_ptr<MoveCommand> cmder = std::make_unique<MoveCommand>();

            cmder->DoOperate(*this);
        } else if (cmd == 'L') {
            std::unique_ptr<TurnLeftCommand> cmder = std::make_unique<TurnLeftCommand>();

            cmder->DoOperate(*this);
        } else if (cmd == 'R') {
            std::unique_ptr<TurnRightCommand> cmder = std::make_unique<TurnRightCommand>();

            cmder->DoOperate(*this);
        }
    }
}

void ExecutorImpl::Move() noexcept
{
    // 处理前进指令
    if (pose.heading == 'E') {
        ++pose.x;
    } else if (pose.heading == 'W') {
        --pose.x;
    } else if (pose.heading == 'N') {
        ++pose.y;
    } else if (pose.heading == 'S') {
        --pose.y;
    }
}

void ExecutorImpl::TurnLeft() noexcept
{
    // 处理左转指令（逆时针旋转 90 度）
    if (pose.heading == 'E') {
        pose.heading = 'N';
    } else if (pose.heading == 'N') {
        pose.heading = 'W';
    } else if (pose.heading == 'W') {
        pose.heading = 'S';
    } else if (pose.heading == 'S') {
        pose.heading = 'E';
    }
}

void ExecutorImpl::TurnRight() noexcept
{
    // 处理右转指令（顺时针旋转 90 度）
    if (pose.heading == 'E') {
        pose.heading = 'S';
    } else if (pose.heading == 'S') {
        pose.heading = 'W';
    } else if (pose.heading == 'W') {
        pose.heading = 'N';
    } else if (pose.heading == 'N') {
        pose.heading = 'E';
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas
