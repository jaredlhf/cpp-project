#pragma once

#include <iostream>
#include <stdio.h>
#include <unordered_map>
#include <unordered_set>

#include "AbstractionStore.h"

class CallsStarStore : public ProcProcStarStore {
private:
  std::unordered_map<std::string, std::unordered_set<std::string>> leftProcStar;
  std::unordered_map<std::string, std::unordered_set<std::string>>
      rightProcStar;

public:
  CallsStarStore();
  CallsStarStore(
      std::unordered_map<std::string, std::unordered_set<std::string>>
          leftProcStar,
      std::unordered_map<std::string, std::unordered_set<std::string>>
          rightProcStar);

  void addCallsStar(std::string leftProc, std::string rightProc);
  std::unordered_set<std::string> getLeftStar(std::string rightProc) override;
  std::unordered_set<std::string> getRightStar(std::string leftProc) override;
  bool hasLeftProc(std::string procName) override;
  bool hasRightProc(std::string procName) override;
  std::unordered_set<std::string> getAllLeft() override;
  std::unordered_set<std::string> getAllRight() override;
};