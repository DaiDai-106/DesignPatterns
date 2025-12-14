#include "behavioral/command/command.h"

using namespace DesignPatterns::Command;
int test_command()
{
  BankAccount account;
  std::unique_ptr<Command> cmd1 = std::make_unique<DepositCommand>( account, 100 );
  std::unique_ptr<Command> cmd2 = std::make_unique<WithdrawCommand>( account, 50 );

  cmd1->execute();
  cmd2->execute();

  std::cout << "Balance after commands: " << account.getBalance() << "\n";

  cmd2->undo();
  cmd1->undo();

  std::cout << "Balance after undo: " << account.getBalance() << "\n";
  return 0;
}