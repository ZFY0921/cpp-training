#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
// 加速状态下 M：前进 2 格（两次单格 Move，没有跳格特判）
TEST(ExecutorFastTest, should_return_x_plus_2_given_status_is_fast_command_is_M_and_facing_is_E)
{
    // given: 初始位置 (0,0)，朝向 E
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when: F 进入加速状态，M 在加速状态下朝 E 前进 2 格
    executor->Execute("FM");

    // then: 预期 X 增加 2，朝向不变
    const Pose target({2, 0, 'E'});
    ASSERT_EQ(target, executor->Query());
}

// 加速状态下 L：先前进 1 格，再左转 90°
TEST(ExecutorFastTest, should_return_N_and_x_plus_1_given_status_is_fast_command_is_L_and_facing_is_E)
{
    // given: 初始位置 (0,0)，朝向 E
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when: F 进入加速状态，L 在加速状态下先朝 E 前进 1 格再左转
    executor->Execute("FL");

    // then: 先前进 1 格（X+1），再左转 E -> N
    const Pose target({1, 0, 'N'});
    ASSERT_EQ(target, executor->Query());
}

// 加速状态下 R：先前进 1 格，再右转 90°
TEST(ExecutorFastTest, should_return_S_and_x_plus_1_given_status_is_fast_given_command_is_R_and_facing_is_E)
{
    // given: 初始位置 (0,0)，朝向 E
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when: F 进入加速状态，R 在加速状态下先朝 E 前进 1 格再右转
    executor->Execute("FR");

    // then: 先前进 1 格（X+1），再右转 E -> S
    const Pose target({1, 0, 'S'});
    ASSERT_EQ(target, executor->Query());
}

// 连续两次 F：第一次进入加速，第二次取消加速，M 恢复正常速度
TEST(ExecutorFastTest, should_return_y_plus_1_given_command_is_FFM_and_facing_is_N)
{
    // given: 初始位置 (0,0)，朝向 N
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

    // when: 第一次 F 进入加速状态，第二次 F 取消加速状态，M 恢复正常前进 1 格
    executor->Execute("FFM");

    // then: 恢复正常后朝 N 前进 1 格
    const Pose target({0, 1, 'N'});
    ASSERT_EQ(target, executor->Query());
}

}  // namespace adas
