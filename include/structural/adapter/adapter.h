#ifndef DESIGN_PATTERNS_STRUCTURAL_ADAPTER_H
#define DESIGN_PATTERNS_STRUCTURAL_ADAPTER_H

#include <iostream>
#include <string>

namespace DesignPatterns::Adapter
{

class RoundPeg
{
 public:
  virtual void insert_into_hole( int diameter )
  {
    std::cout << "RoundPeg: insert into hole diameter " << diameter << std::endl;
  }
};

class SquarePeg
{
 public:
  virtual void insert( int width ) { std::cout << "SquarePeg: insert width " << width << std::endl; }
};

class PegAdapter : public RoundPeg, public SquarePeg
{
 public:
  void insert( int width ) override
  {
    std::cout << "[Adapter] SquarePeg interface called. Acting as RoundPeg..." << std::endl;
    // 简单的数学转换：方钉宽度对应的最小外接圆直径
    SquarePeg::insert( width );
  }

  // 适配 RoundPeg 接口 -> 假装自己是圆钉
  void insert_into_hole( int diameter ) override
  {
    // 如果需要反向逻辑，这里写。但通常双向适配是指一个对象能被系统 A 当作接口 A，被系统 B 当作接口 B。
    RoundPeg::insert_into_hole( diameter );
  }
};

}  // namespace DesignPatterns::Adapter

#endif  // DESIGN_PATTERNS_STRUCTURAL_ADAPTER_H
