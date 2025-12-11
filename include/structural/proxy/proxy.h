#ifndef INCLUDE_STRUCTURAL_PROXY_PROXY_H
#define INCLUDE_STRUCTURAL_PROXY_PROXY_H

#include <iostream>
#include <string>
#include <memory>
#include <functional>

namespace DesignPatterns::Proxy
{

// 这里主要实现一个值代理的例子
// 值代理模板类
template <typename T>
class ValueProxy
{
 private:
  T *actualValue;                          // 指向实际值的指针
  std::function<void( const T & )> onSet;  // 设置值时的回调
  std::function<void()> onGet;             // 获取值时的回调

 public:
  // 构造函数
  ValueProxy( T *value, std::function<void( const T & )> setCallback = nullptr,
              std::function<void()> getCallback = nullptr )
      : actualValue( value ), onSet( setCallback ), onGet( getCallback )
  {
  }

  // 隐式类型转换，让代理可以像值一样使用
  operator T() const
  {
    if ( onGet ) { onGet(); }
    return *actualValue;
  }

  // 赋值操作符
  ValueProxy &operator=( const T &newValue )
  {
    if ( onSet ) { onSet( newValue ); }
    *actualValue = newValue;
    return *this;
  }

  // 获取指针
  T *get() const { return actualValue; }

  // 比较操作符
  bool operator==( const T &other ) const { return *actualValue == other; }

  bool operator!=( const T &other ) const { return *actualValue != other; }
};

class TemperatureMonitor
{
 private:
  double currentTemp;  // 实际温度值

 public:
  // 创建温度值的代理
  ValueProxy<double> temperature;

  TemperatureMonitor()
      : currentTemp( 25.0 ),  // 初始温度
        temperature(
            &currentTemp,
            // 设置温度时的回调
            [ this ]( const double &newTemp ) {
              std::cout << "温度变化通知: " << currentTemp << "°C → " << newTemp << "°C" << std::endl;
              if ( newTemp > 80.0 ) { std::cout << "警告: 温度过高!" << std::endl; }
            },
            [ this ]() { std::cout << "读取当前温度: "; } )
  {
  }

  void displayStatus() const { std::cout << "当前系统状态: 温度 " << temperature << "°C" << std::endl; }
};

}  // namespace DesignPatterns::Proxy

#endif  // INCLUDE_STRUCTURAL_PROXY_PROXY_H