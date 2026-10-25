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
    void Fast(void) noexcept;
    bool IsFast(void) const noexcept;

private:
    // 接口抽象：指令的行为统一为 DoOperate 这一个抽象操作
    class ICommand
    {
    public:
        virtual ~ICommand() = default;
        virtual void DoOperate(Executorlmpl& executor) const noexcept = 0;
    };

    // 继承与多态：各指令类只实现自己的 DoOperate，由基类指针统一调用
    class MoveCommand final : public ICommand
    {
    public:
        void DoOperate(Executorlmpl& executor) const noexcept override
        {
            // 加速状态下前进两格（逐格前进，不能跳跃）
            if (executor.IsFast()) {
                executor.Move();
            }

            executor.Move();
        }
    };

    class TurnLeftCommand final : public ICommand
    {
    public:
        void DoOperate(Executorlmpl& executor) const noexcept override
        {
            // 加速状态下先前进一格，再左转
            if (executor.IsFast()) {
                executor.Move();
            }

            executor.TurnLeft();
        }
    };

    class TurnRightCommand final : public ICommand
    {
    public:
        void DoOperate(Executorlmpl& executor) const noexcept override
        {
            // 加速状态下先前进一格，再右转
            if (executor.IsFast()) {
                executor.Move();
            }

            executor.TurnRight();
        }
    };

    // F 指令：切换加速状态
    class FastCommand final : public ICommand
    {
    public:
        void DoOperate(Executorlmpl& executor) const noexcept override
        {
            executor.Fast();
        }
    };

private:
    Pose pose;
    bool fast{false};
};
}  // namespace adas
