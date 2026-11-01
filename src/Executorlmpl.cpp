#include "Executorlmpl.hpp"
#include <functional>
#include <new>
#include <unordered_map>

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
    // 初始化列表 + 表驱动：注册指令从 4 条 emplace 收成一次构造
    const std::unordered_map<char, std::function<void(PoseHandler&)>> cmderMap{
        {'M', MoveCommand()},
        {'L', TurnLeftCommand()},
        {'R', TurnRightCommand()},
        {'F', FastCommand()},
    };

    for (const auto cmd : commands) {
        const auto it = cmderMap.find(cmd);
        if (it != cmderMap.end()) {
            it->second(poseHandler);
        }
    }
}
Pose Executorlmpl::Query() const noexcept
{
    return poseHandler.Query();
}
}  // namespace adas
