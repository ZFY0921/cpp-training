#pragma once
#include "Executor.hpp"

namespace adas
{
class Executorlmpl final : public Executor
{
public:
    explicit Executorlmpl(const Pose& pose) noexcept;
    ~Executorlmpl() noexcept = default;

    Executorlmpl(const Executorlmpl&) = delete;
    Executorlmpl& operator=(const Executorlmpl&) = delete;

public:
    void Execute(const std::string& command) noexcept override;
    Pose Query(void) const noexcept override;

private:
    void Move(void) noexcept;
    void TurnLeft(void) noexcept;
    void TurnRight(void) noexcept;

private:
    // 每种指令的行为封装为一个独立的小类，对外只暴露统一的 DoOperate 操作接口
    class MoveCommand final
    {
    public:
        void DoOperate(Executorlmpl& executor) const noexcept
        {
            executor.Move();
        }
    };

    class TurnLeftCommand final
    {
    public:
        void DoOperate(Executorlmpl& executor) const noexcept
        {
            executor.TurnLeft();
        }
    };

    class TurnRightCommand final
    {
    public:
        void DoOperate(Executorlmpl& executor) const noexcept
        {
            executor.TurnRight();
        }
    };

private:
    Pose pose;
};
}  // namespace adas
