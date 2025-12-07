#include "creational/singleton/singleton.h"
#include <cassert>
#include <iostream>
#include <thread>
#include <vector>

void worker_thread( int id )
{
  auto &db = DesignPatterns::Singleton::Database::get_instance();

  // 模拟读写竞争
  if ( id % 2 == 0 ) {
    std::string new_conn = "daidai-" + std::to_string( id );
    db.set_connection_string( new_conn );
    std::cout << "[Thread " << id << "] Set connection: " << new_conn << std::endl;
  } else {
    std::string current_conn = db.get_connection_string();
    std::cout << "[Thread " << id << "] Read connection: " << current_conn << std::endl;
  }

  db.execute_query( "SELECT * FROM users WHERE id=" + std::to_string( id ) );
}

int test_singleton()
{
  std::cout << "--- Singleton Test Start ---" << std::endl;

  // 1. 验证单一实例
  auto &db1 = DesignPatterns::Singleton::Database::get_instance();
  auto &db2 = DesignPatterns::Singleton::Database::get_instance();

  std::cout << "Address of db1: " << &db1 << std::endl;
  std::cout << "Address of db2: " << &db2 << std::endl;

  if ( &db1 == &db2 ) {
    std::cout << "PASS: Both references point to the same instance." << std::endl;
  } else {
    std::cerr << "FAIL: Different instances created!" << std::endl;
    return 1;
  }

  // 2. 验证状态共享
  db1.set_connection_string( "jxxxxx" );
  std::cout << "db2 Connection String: " << db2.get_connection_string() << std::endl;
  assert( db2.get_connection_string() == "jxxxxx" );

  // 3. 多线程访问测试 (验证 Meyers Singleton 的线程安全性)
  std::cout << "\n--- Multithreaded Access Test ---" << std::endl;
  std::vector<std::thread> threads;
  for ( int i = 0; i < 10; ++i ) { threads.emplace_back( worker_thread, i ); }

  for ( auto &t : threads ) {
    if ( t.joinable() ) { t.join(); }
  }

  std::cout << "--- Singleton Test End ---" << std::endl;
  return 0;
}
