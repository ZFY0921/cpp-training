#pragma once

namespace adas
{
// 状态抽象：把"位置/位移"抽象成向量模型，配合方向编码消减状态流转的圈复杂度
class Point final
{
public:
    Point(const int x, const int y) noexcept;
    Point(const Point& rhs) noexcept;
    Point& operator=(const Point& rhs) noexcept;

    Point& operator+=(const Point& rhs) noexcept;

public:
    int GetX(void) const noexcept;
    int GetY(void) const noexcept;

private:
    int x;
    int y;
};
}  // namespace adas
