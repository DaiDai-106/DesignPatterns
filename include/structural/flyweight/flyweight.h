#ifndef INCLUDE_STRUCTURAL_FLYWEIGHT_FLYWEIGHT_H
#define INCLUDE_STRUCTURAL_FLYWEIGHT_FLYWEIGHT_H

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>

namespace DesignPatterns::Flyweight
{

// 游戏对象示例 - 另一个享元模式应用
class GameObject
{
 public:
  virtual ~GameObject()                     = default;
  virtual void render( int x, int y ) const = 0;
};

// 树的享元对象 - 内部状态是树的类型和颜色
class Tree : public GameObject
{
 private:
  std::string type;   // 内部状态
  std::string color;  // 内部状态
  std::string model;  // 内部状态（复杂对象）

 public:
  Tree( const std::string &t, const std::string &c ) : type( t ), color( c )
  {
    // 模拟加载复杂模型数据
    model = "加载了" + type + "的3D模型数据...";
    std::cout << "创建新的树类型: " << type << std::endl;
  }

  void render( int x, int y ) const override
  {
    std::cout << "在位置(" << x << "," << y << ")渲染" << color << "的" << type << " - " << model << std::endl;
  }

  const std::string &getType() const { return type; }
  const std::string &getColor() const { return color; }
};

// 树工厂 - 管理树的共享对象
class TreeFactory
{
 private:
  std::map<std::string, std::shared_ptr<Tree>> trees;

  std::string getKey( const std::string &type, const std::string &color ) const { return type + "_" + color; }

 public:
  std::shared_ptr<Tree> getTree( const std::string &type, const std::string &color )
  {
    std::string key = getKey( type, color );

    if ( trees.find( key ) != trees.end() ) { return trees[ key ]; }

    auto newTree = std::make_shared<Tree>( type, color );
    trees[ key ] = newTree;
    return newTree;
  }

  size_t getTreeTypesCount() const { return trees.size(); }
};

// 森林类 - 管理大量树对象的位置（外部状态）
class Forest
{
 private:
  std::vector<std::pair<std::shared_ptr<Tree>, std::pair<int, int>>> trees;
  std::shared_ptr<TreeFactory> factory;

 public:
  Forest( std::shared_ptr<TreeFactory> f ) : factory( f ) {}

  void plantTree( int x, int y, const std::string &type, const std::string &color )
  {
    auto tree = factory->getTree( type, color );
    trees.push_back( {
        tree, { x, y }
    } );
  }

  void render() const
  {
    std::cout << "\n渲染森林中的所有树木 (" << trees.size() << " 棵树, " << factory->getTreeTypesCount()
              << " 种类型):\n";

    for ( const auto &[ tree, position ] : trees ) { tree->render( position.first, position.second ); }
  }
};

}  // namespace DesignPatterns::Flyweight
#endif  // INCLUDE_STRUCTURAL_FLYWEIGHT_FLYWEIGHT_H