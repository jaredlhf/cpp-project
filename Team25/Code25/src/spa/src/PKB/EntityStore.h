#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <unordered_set>

class EntityStore {
public:
  virtual int size() = 0;
};

class ConstantStore : public EntityStore {
private:
  std::unordered_set<int> store;

public:
  ConstantStore();
  ConstantStore(std::unordered_set<int> store);
  void addConst(int constNum);
  std::unordered_set<int> getAllConst();
  bool has(int constNum);
  int size() override;
};

class VariableStore : public EntityStore {
private:
  std::unordered_set<std::string> store;

public:
  VariableStore();
  VariableStore(std::unordered_set<std::string> store);
  void addVar(std::string varName);
  std::unordered_set<std::string> getAllVar();
  bool has(std::string varName);
  int size() override;
};

class ProcedureStore : public EntityStore {
private:
  std::unordered_set<std::string> store;

public:
  ProcedureStore();
  ProcedureStore(std::unordered_set<std::string> store);
  void addProc(std::string procName);
  std::unordered_set<std::string> getAllProc();
  bool has(std::string procName);
  int size() override;
};

class StatementStore : public EntityStore {
private:
  std::unordered_map<std::string, std::unordered_set<int>> store;

public:
  StatementStore();
  StatementStore(
      std::unordered_map<std::string, std::unordered_set<int>> store);
  void addStmt(std::string stmtType, int lineNum);
  std::unordered_set<int> getAllStmt(std::string stmtType);
  bool has(std::string stmtType);
  int size() override;
};