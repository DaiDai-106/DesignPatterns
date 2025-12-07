#ifndef DESIGN_PATTERNS_STRUCTURAL_COMPOSITE_H
#define DESIGN_PATTERNS_STRUCTURAL_COMPOSITE_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace DesignPatterns::Composite
{

// 1. Component (抽象组件)
class FileSystemNode
{
 public:
  explicit FileSystemNode( const std::string &name ) : name_( name ) {}
  virtual ~FileSystemNode() = default;

  // 公共操作
  virtual void print( int indent = 0 ) const = 0;
  virtual int get_size() const               = 0;
  virtual void add( std::shared_ptr<FileSystemNode> node ) { throw std::runtime_error( "Cannot add to a leaf node" ); }

  std::string get_name() const { return name_; }

 protected:
  std::string name_;

  // 辅助函数：打印缩进
  void print_indent( int indent ) const
  {
    for ( int i = 0; i < indent; ++i ) { std::cout << "  "; }
  }
};

class File : public FileSystemNode
{
 public:
  File( const std::string &name, int size ) : FileSystemNode( name ), size_( size ) {}

  void print( int indent = 0 ) const override
  {
    print_indent( indent );
    std::cout << "- File: " << name_ << " (" << size_ << " KB)" << std::endl;
  }

  int get_size() const override { return size_; }

 private:
  int size_;
};

// 3. Composite (组合节点)
class Directory : public FileSystemNode
{
 public:
  explicit Directory( const std::string &name ) : FileSystemNode( name ) {}

  void add( std::shared_ptr<FileSystemNode> node ) override { children_.push_back( node ); }

  void print( int indent = 0 ) const override
  {
    print_indent( indent );
    std::cout << "+ Directory: " << name_ << std::endl;
    for ( const auto &child : children_ ) { child->print( indent + 1 ); }
  }

  int get_size() const override
  {
    int total_size = 0;
    for ( const auto &child : children_ ) { total_size += child->get_size(); }
    return total_size;
  }

 private:
  std::vector<std::shared_ptr<FileSystemNode>> children_;
};

}  // namespace DesignPatterns::Composite

#endif  // DESIGN_PATTERNS_STRUCTURAL_COMPOSITE_H
