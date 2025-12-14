#ifndef INCLUDE_BEHAVIORAL_COMMAND_COMMAND_H
#define INCLUDE_BEHAVIORAL_COMMAND_COMMAND_H

#include <iostream>
#include <memory>

namespace DesignPatterns::Command
{

// 接收者
struct BankAccount {
  int balance         = 0;
  int overdraft_limit = -500;

  void deposit( int amount ) { balance += amount; }
  void withdraw( int amount )
  {
    if ( balance - amount >= overdraft_limit ) { balance -= amount; }
  }

  int getBalance() const { return balance; }  // 查询方法
};

// 抽象命令
struct Command {
  virtual void execute() = 0;
  virtual void undo()    = 0;
  virtual ~Command()     = default;
};

// 具体命令
struct DepositCommand : Command {
  BankAccount &account;
  int amount;
  DepositCommand( BankAccount &acc, int amt ) : account( acc ), amount( amt ) {}

  void execute() override { account.deposit( amount ); }
  void undo() override { account.withdraw( amount ); }
};

struct WithdrawCommand : Command {
  BankAccount &account;
  int amount;
  bool succeeded = false;

  WithdrawCommand( BankAccount &acc, int amt ) : account( acc ), amount( amt ) {}

  void execute() override
  {
    if ( account.balance - amount >= account.overdraft_limit ) {
      account.withdraw( amount );
      succeeded = true;
    }
  }

  void undo() override
  {
    if ( succeeded ) { account.deposit( amount ); }
  }
};

}  // namespace DesignPatterns::Command

#endif