#pragma once
#include "Executor.hpp"

namespace adas
{
// 为Pose提供==运算符重载，使得在测试中比较Pose对象简单明了，std::tie提高代码可读性
bool operator==(const Pose& lhs, const Pose& rhs);
}  // namespace adas
