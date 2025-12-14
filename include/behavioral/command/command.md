# Command Pattern(命令模式)

## 1. 介绍
这里首先想一个赋值命令， a = 6。此时变量已经被赋值了，但是并没有任何的记录表示该变量已经进行了修改，也没有办法知道之前的值是什么。
从这个角度看，这是比较有风险的操作，因为没有了修改记录，就无法进行有效的回滚和测试。

## 2. 银行账户
这里简单模拟一个银行账户，该对象有余额和透支限额。
```cpp
struct BankAccount
{
    int balance = 0;
    int overdraft_limit = -500;

    void deposit( int amount ); // 省略实现了
    void withdraw( int amount )
    {
        if(balance - amount >= overdraft_limit )
        {
            blance -= amount;
        }

    }
}
```
此时，处于审计的目的，假设想记录每一笔交易的记录，同时我们不能在BankAccount类内部记录这些信息（因为我们已经完成了设计），在这个情况下，可以引入命令设计模式。

那该设计模式适合如下的场景：
1. 调用者与接收者需要解耦， 调用者只关心“执行某个动作”，不关心具体对象或执行方式。典型例子：GUI 按钮、菜单系统。例子：按钮按下 → Command 对象 → 调用接收者执行操作。
2.需要支持撤销/重做（Undo / Redo）， 每个操作封装成对象后，可以保存历史栈，支持撤销。例子：文本编辑器、CAD 软件的操作记录。
3. 需要请求排队、延迟执行或定时执行。命令对象可以存到队列、日志或网络传输。例子：任务调度系统、异步执行系统。
4. 操作需要可序列化或远程传输，通过命令对象传递请求，可方便存储或网络传输。例子：RPC 调用、远程控制设备。
5. 容易扩展新操作，新操作只需增加一个具体命令类，不需要修改调用者或其他命令。

## 3. 命令模式实现
```cpp
struct Command
{
    virtual void call() const = 0;
}
```
根据上述的抽象接口，便可以定义BankAccountCommand， 该Command封装了银行账户相关操作的信息。
```cpp
struct BankAccountCommand : Command
{
    BankAccount& account;
    enum action {d, w} action;
    int amount;

    void call() override;
};
```
BankAccountCommand包含了被操作的银行账户，对银行账户采取的操作， 存款和取款的总额。只要用户提供了这些信息，就可以进行相关的操作。通过这样的实现，我们便可以创建命令，然后通过命令对账户进行修改。

## 4. 撤销操作
在上述的基础上，还可以继续增加撤销操作，因为command中包含了正常的操作，所以撤销就是反操作。当然我们肯定对于取款是否成功要有个标志位，否则反操作就会有很大的问题了。
```cpp
struct Command {
    virtual void call() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

// 具体命令
struct BankAccountCommand : Command {
    BankAccount& account;
    enum Action { deposit, withdraw } action;
    int amount;
    bool succeeded = false;  // 记录操作是否成功

    BankAccountCommand(BankAccount& acc, Action act, int amt)
        : account(acc), action(act), amount(amt) {}

    void call() override {
        switch(action) {
            case deposit:
                account.deposit(amount);
                succeeded = true;
                break;
            case withdraw:
                if(account.balance - amount >= account.overdraft_limit) {
                    account.withdraw(amount);
                    succeeded = true;
                } else {
                    std::cout << "Withdrawal declined\n";
                    succeeded = false;
                }
                break;
        }
    }

    void undo() override {
        if(!succeeded) return; // 如果操作未成功，直接返回

        switch(action) {
            case deposit:
                account.withdraw(amount); // 撤销存款
                std::cout << "[Undo] deposit " << amount << "\n";
                break;
            case withdraw:
                account.deposit(amount);  // 撤销取款
                std::cout << "[Undo] withdraw " << amount << "\n";
                break;
        }
    }
};
```
## 5. 命令查询分离
CQS 原则：一个方法要么是 命令（Command），要么是 查询（Query），但不能两者兼顾。这里用下面的例子展示错误和正确的例子
```cpp
struct BankAccount {
    int balance = 0;
    int overdraft_limit = -500;

    void deposit(int amount) { balance += amount; }
    void withdraw(int amount) { balance -= amount; }
};

struct Command {
    virtual int execute() = 0;  // ❌ 错误：命令返回状态
    virtual void undo() = 0;
    virtual ~Command() = default;
};

struct DepositCommand : Command {
    BankAccount& account;
    int amount;
    DepositCommand(BankAccount& acc, int amt) : account(acc), amount(amt) {}

    int execute() override {   // ❌ 返回余额 → 查询 + 命令混合
        account.deposit(amount);
        return account.balance;
    }

    void undo() override {
        account.withdraw(amount);
    }
```
而正确的命令和查询分离的方式如下
```cpp
struct BankAccount {
    int balance = 0;
    int overdraft_limit = -500;

    void deposit(int amount) { balance += amount; }
    void withdraw(int amount) { 
        if(balance - amount >= overdraft_limit) balance -= amount; 
    }

    int getBalance() const { return balance; } // 查询方法
};

// 抽象命令
struct Command {
    virtual void execute() = 0; // ✅ 不返回状态
    virtual void undo() = 0;
    virtual ~Command() = default;
};

// 具体命令
struct DepositCommand : Command {
    BankAccount& account;
    int amount;
    DepositCommand(BankAccount& acc, int amt) : account(acc), amount(amt) {}

    void execute() override { account.deposit(amount); }
    void undo() override { account.withdraw(amount); }
};
```