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
    // 表驱动 + 函数式：表里存的是"行为"，不再是多态对象
    std::unordered_map<char, std::function<void(PoseHandler&)>> cmderMap;

    MoveCommand moveCommand;
    cmderMap.emplace('M', moveCommand.operate);

    TurnLeftCommand turnLeftCommand;
    cmderMap.emplace('L', turnLeftCommand.operate);

    TurnRightCommand turnRightCommand;
    cmderMap.emplace('R', turnRightCommand.operate);

    FastCommand fastCommand;
    cmderMap.emplace('F', fastCommand.operate);

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
