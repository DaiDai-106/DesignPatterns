#include "structural/proxy/proxy.h"
#include <iostream>

int test_proxy()
{
  std::cout << "=== 值代理示例 ===" << std::endl;

  // 示例1：温度监控
  std::cout << "\n示例1：温度监控系统" << std::endl;
  DesignPatterns::Proxy::TemperatureMonitor monitor;

  monitor.displayStatus();

  // 通过代理修改温度值
  monitor.temperature = 30.5;  // 会触发回调
  monitor.displayStatus();

  monitor.temperature = 85.0;  // 会触发高温警告
  monitor.displayStatus();

  return 0;
}