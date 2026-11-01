#include "Executorlmpl.hpp"
#include <memory>
#include "Command.hpp"

namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) Executorlmpl(pose);
}

Executorlmpl::Executorlmpl(const Pose& pose) noexcept : poseHandler(pose)
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
        } else if (cmd == 'F') {
            cmder = std::make_unique<FastCommand>();
        }

        // 指令只依赖 PoseHandler，不再依赖 Executorlmpl，循环依赖被打断
        if (cmder) {
            cmder->DoOperate(poseHandler);
        }
    }
}

Pose Executorlmpl::Query() const noexcept
{
    return poseHandler.Query();
}
}  // namespace adas
