#pragma once
#include <functional>

#include "PoseHandler.hpp"

namespace adas
{
// 函数式编程：用 std::function + lambda 取代继承体系
// 指令不再需要基类与虚函数，行为以"可调用对象"的形式直接保存在成员里
class MoveCommand final
{
public:
    const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept {
        if (poseHandler.IsFast()) {
            poseHandler.Move();
        }
        poseHandler.Move();
    };
};

class TurnLeftCommand final
{
public:
    const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept {
        if (poseHandler.IsFast()) {
            poseHandler.Move();
        }
        poseHandler.TurnLeft();
    };
};

class TurnRightCommand final
{
public:
    const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept {
        if (poseHandler.IsFast()) {
            poseHandler.Move();
        }
        poseHandler.TurnRight();
    };
};

class FastCommand final
{
public:
    const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept {
        poseHandler.Fast();
    };
};
}  // namespace adas
