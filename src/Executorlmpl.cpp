#include "Executorlmpl.hpp"

#include <memory>

namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) Executorlmpl(pose);
}

Executorlmpl::Executorlmpl(const Pose& pose) noexcept : pose(pose)
{
}

void Executorlmpl::Execute(const std::string& commands) noexcept
{
    // 只负责把字符映射为具体指令对象，执行动作由多态统一完成
    for (const auto cmd : commands) {
        std::unique_ptr<ICommand> cmder;

        if (cmd == 'M') {
            cmder = std::make_unique<MoveCommand>();
        } else if (cmd == 'L') {
            cmder = std::make_unique<TurnLeftCommand>();
        } else if (cmd == 'R') {
            cmder = std::make_unique<TurnRightCommand>();
        }

        if (cmder) {
            cmder->DoOperate(*this);
        }
    }
}

void Executorlmpl::Move() noexcept
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

void Executorlmpl::TurnLeft() noexcept
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

void Executorlmpl::TurnRight() noexcept
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

Pose Executorlmpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas
