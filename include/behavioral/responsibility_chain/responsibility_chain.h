#ifndef INCLUDE_BEHAVIORAL_RESPONSIBILITY_CHAIN_RESPONSIBILITY_CHAIN_H
#define INCLUDE_BEHAVIORAL_RESPONSIBILITY_CHAIN_RESPONSIBILITY_CHAIN_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace DesignPatterns::ResponsibilityChain
{

/// 这里主要的目的是构造一个校验，分别对于笛卡尔路径和轴关节路径的校验
struct JointPoint {
  std::vector<double> joints;  // size should be 6
  double velocity;
};

struct JointPath {
  std::vector<JointPoint> points;
};

struct PathCheck {
  PathCheck *next = nullptr;

  virtual bool check( const JointPath &path )
  {
    if ( next ) { return next->check( path ); }
    return true;
  }

  virtual ~PathCheck() = default;
};

struct JointLengthCheck : PathCheck {
  bool check( const JointPath &path ) override
  {
    if ( path.points.empty() ) {
      std::cerr << "[Joint] path is empty\n";
      return false;
    }
    return PathCheck::check( path );
  }
};

struct JointDimensionCheck : PathCheck {
  bool check( const JointPath &path ) override
  {
    for ( size_t i = 0; i < path.points.size(); ++i ) {
      if ( path.points[ i ].joints.size() != 6 ) {
        std::cerr << "[Joint] joint size != 6 at index " << i << "\n";
        return false;
      }
    }
    return PathCheck::check( path );
  }
};

struct JointVelocityCheck : PathCheck {
  bool check( const JointPath &path ) override
  {
    for ( size_t i = 0; i < path.points.size(); ++i ) {
      if ( path.points[ i ].velocity <= 0.0 ) {
        std::cerr << "[Joint] velocity <= 0 at index " << i << "\n";
        return false;
      }
    }
    return PathCheck::check( path );
  }
};

// 这里封装一个校验类
struct Planner {
  bool validateJoint( const JointPath &path )
  {
    JointLengthCheck len;
    JointDimensionCheck dim;
    JointVelocityCheck vel;

    len.next = &dim;
    dim.next = &vel;

    return len.check( path );
  }
};
}  // namespace DesignPatterns::ResponsibilityChain

#endif