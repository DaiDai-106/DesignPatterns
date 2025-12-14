#include <iostream>
#include <string>

// 声明各个测试文件的入口函数
// 这样链接器就能找到它们，无需头文件
int test_builder();
int test_factory();
int test_prototype();
int test_singleton();
int test_adapter();
int test_bridge();
int test_composite();
int test_facade();
int test_flyweight();
int test_proxy();
int test_responsibility_chain();
int test_command();

int main( int argc, char *argv[] )
{
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[ 0 ] << " <test_name>" << std::endl;
    std::cout << "Available tests:\n"
              << "  builder\n"
              << "  factory\n"
              << "  prototype\n"
              << "  singleton\n"
              << "  adapter\n"
              << "  bridge\n"
              << "  composite\n"
              << "  facade\n"
              << "  flyweight\n"
              << "  proxy\n"
              << "  responsibility_chain\n"
              << "  command" << std::endl;
    return 1;
  }

  std::string test_name = argv[ 1 ];
  std::cout << "Running test: " << test_name << "...\n" << std::endl;

  if ( test_name == "builder" ) { return test_builder(); }
  if ( test_name == "factory" ) { return test_factory(); }
  if ( test_name == "prototype" ) { return test_prototype(); }
  if ( test_name == "singleton" ) { return test_singleton(); }
  if ( test_name == "adapter" ) { return test_adapter(); }
  if ( test_name == "bridge" ) { return test_bridge(); }
  if ( test_name == "composite" ) { return test_composite(); }
  if ( test_name == "facade" ) { return test_facade(); }
  if ( test_name == "flyweight" ) { return test_flyweight(); }
  if ( test_name == "proxy" ) { return test_proxy(); }
  if ( test_name == "responsibility_chain" ) { return test_responsibility_chain(); }
  if ( test_name == "command" ) { return test_command(); }

  std::cerr << "Error: Unknown test '" << test_name << "'" << std::endl;
  return 1;
}
