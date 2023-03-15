#pragma once

#include <iostream>
#include <stdio.h>
#include <unordered_map>
#include <unordered_set>

#include "AbstractionStore.h"

/* Storage class for Follows* relationship between direct and indirect
statements. In Follows*(s1, s2), Followee star is s1 and Follower star is s2 */
class FollowsStarStore : public StmtStmtStarStore {
private:
  std::unordered_map<int, std::unordered_set<int>> leftStmtStar;
  std::unordered_map<int, std::unordered_set<int>> rightStmtStar;

public:
  FollowsStarStore();
  FollowsStarStore(
      std::unordered_map<int, std::unordered_set<int>> leftStmtStar,
      std::unordered_map<int, std::unordered_set<int>> rightStmtStar);

  void addFollowsStar(int leftStmt, std::unordered_set<int> rightStmtLst);
  std::unordered_set<int> getLeftStar(int rightStmt) override;
  std::unordered_set<int> getRightStar(int leftStmt) override;
  bool hasLeftStmt(int lineNum) override;
  bool hasRightStmt(int lineNum) override;
  std::unordered_set<int> getAllLeft() override;
  std::unordered_set<int> getAllRight() override;
};
