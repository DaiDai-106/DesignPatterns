#include "structural/composite/composite.h"
#include <iostream>
#include <memory>

int test_composite()
{
  using namespace DesignPatterns::Composite;

  std::cout << "=== Composite Pattern Test (File System) ===" << std::endl;

  // 创建叶子节点 (文件)
  auto file1 = std::make_shared<File>( "resume.pdf", 200 );
  auto file2 = std::make_shared<File>( "photo.png", 500 );
  auto file3 = std::make_shared<File>( "notes.txt", 10 );

  // 创建组合节点 (目录)
  auto dir_docs = std::make_shared<Directory>( "Documents" );
  dir_docs->add( file1 );
  dir_docs->add( file3 );

  auto dir_root = std::make_shared<Directory>( "Root" );
  dir_root->add( dir_docs );
  dir_root->add( file2 );

  // 测试递归操作 (print 和 get_size)
  std::cout << "\nPrinting File System Structure:" << std::endl;
  dir_root->print();

  std::cout << "\nTotal Size of Root: " << dir_root->get_size() << " KB" << std::endl;

  return 0;
}
