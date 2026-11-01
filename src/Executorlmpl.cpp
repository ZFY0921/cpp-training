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
    // 表驱动 + 操作符()重载：表里直接存"可调用对象"，不再暴露任何成员
    std::unordered_map<char, std::function<void(PoseHandler&)>> cmderMap;
    cmderMap.emplace('M', MoveCommand());
    cmderMap.emplace('L', TurnLeftCommand());
    cmderMap.emplace('R', TurnRightCommand());
    cmderMap.emplace('F', FastCommand());

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
