#include "Executorlmpl.hpp"
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
}

Pose Executorlmpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas