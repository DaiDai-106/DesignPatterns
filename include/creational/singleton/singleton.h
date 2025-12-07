#ifndef DESIGN_PATTERNS_SINGLETON_H
#define DESIGN_PATTERNS_SINGLETON_H

#include <iostream>
#include <mutex>
#include <string>

namespace DesignPatterns::Singleton
{

class Database
{
 public:
  static Database &get_instance()
  {
    static Database instance;
    return instance;
  }

  void execute_query( const std::string &query )
  {
    std::cout << "Executing query: " << query << " on Database instance @" << this << std::endl;
  }

  // 使用锁保证线程安全
  void set_connection_string( const std::string &conn_str )
  {
    std::lock_guard<std::mutex> lock( mutex_ );
    connection_string_ = conn_str;
  }

  std::string get_connection_string() const
  {
    std::lock_guard<std::mutex> lock( mutex_ );
    return connection_string_;
  }

 private:
  // 私有构造函数，防止外部直接实例化
  Database() { std::cout << "Database initialized." << std::endl; }
  // 私有析构函数
  ~Database() { std::cout << "Database destroyed." << std::endl; }

  // 删除拷贝构造和赋值操作符，防止复制
  Database( const Database & )            = delete;
  Database &operator=( const Database & ) = delete;

  std::string connection_string_;
  mutable std::mutex mutex_;  // Added mutable mutex for thread safety in const methods
};

}  // namespace DesignPatterns::Singleton

#endif  // DESIGN_PATTERNS_SINGLETON_H
