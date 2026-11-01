#include "PoseHandler.hpp"
#include "Point.hpp"

namespace adas
{
namespace
{
// 方向编码：E=0, S=1, W=2, N=3，顺时针递增
const char kHeadings[] = {'E', 'S', 'W', 'N'};
constexpr int kHeadingCount = 4;
constexpr int kInvalidHeading = -1;

// 字符 -> 编码：查表代替四段 if/else
int HeadingToCode(const char heading) noexcept
{
    for (int i = 0; i < kHeadingCount; ++i) {
        if (kHeadings[i] == heading) {
            return i;
        }
    }
    return kInvalidHeading;
}

// 编码 -> 单位位移向量：M 指令不再需要逐朝向判断
// 非法朝向返回零向量，保持"不移动"的原有语义
Point HeadingStep(const char heading) noexcept
{
    static const Point steps[kHeadingCount] = {Point(1, 0), Point(0, -1), Point(-1, 0), Point(0, 1)};
    const int code = HeadingToCode(heading);
    return code == kInvalidHeading ? Point(0, 0) : steps[code];
}
}  // namespace

PoseHandler::PoseHandler(const Pose& pose) noexcept : pose(pose)
{
}

void PoseHandler::Move() noexcept
{
    // 状态抽象：位置也是向量，按当前朝向累加单位位移
    Point position(pose.x, pose.y);
    position += HeadingStep(pose.heading);
    pose.x = position.GetX();
    pose.y = position.GetY();
}

void PoseHandler::TurnLeft() noexcept
{
    // 左转 = 编码 -1（等价于 +3），取模处理跨越 0 的溢出
    const int code = HeadingToCode(pose.heading);
    if (code != kInvalidHeading) {
        pose.heading = kHeadings[(code + 3) % kHeadingCount];
    }
}

void PoseHandler::TurnRight() noexcept
{
    // 右转 = 编码 +1
    const int code = HeadingToCode(pose.heading);
    if (code != kInvalidHeading) {
        pose.heading = kHeadings[(code + 1) % kHeadingCount];
    }
}

void PoseHandler::Fast() noexcept
{
    fast = !fast;
}

bool PoseHandler::IsFast() const noexcept
{
    return fast;
}

Pose PoseHandler::Query() const noexcept
{
    return pose;
}
}  // namespace adas
