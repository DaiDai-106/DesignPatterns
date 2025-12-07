#include "structural/adapter/adapter.h"
#include <iostream>
#include <memory>

void client_expects_square_peg( DesignPatterns::Adapter::SquarePeg &peg )
{
  std::cout << "Client: I have a square hole. Inserting peg..." << std::endl;
  peg.insert( 10 );
}

void client_expects_round_peg( DesignPatterns::Adapter::RoundPeg &peg )
{
  std::cout << "Client: I have a round hole. Inserting peg..." << std::endl;
  peg.insert_into_hole( 10 );
}

int main()
{
  std::cout << "\n=== 1. Two-Way Adapter Test ===" << std::endl;
  // PegAdapter 同时实现了 SquarePeg 和 RoundPeg 接口
  DesignPatterns::Adapter::PegAdapter sticky_peg;

  // 场景 A: 作为一个 SquarePeg 使用
  client_expects_square_peg( sticky_peg );

  // 场景 B: 作为一个 RoundPeg 使用
  client_expects_round_peg( sticky_peg );

  return 0;
}
