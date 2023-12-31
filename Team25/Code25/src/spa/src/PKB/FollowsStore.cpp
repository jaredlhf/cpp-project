#include<stdio.h>
#include <algorithm>
#include <iostream>

#include "FollowsStore.h"

FollowsStore::FollowsStore() : leftStmtStore{ }, rightStmtStore{ } {}
FollowsStore::FollowsStore(std::unordered_map<int, int> leftStmtStore, std::unordered_map<int, int> rightStmtStore) 
	: leftStmtStore{ leftStmtStore }, rightStmtStore{ rightStmtStore } {}

void FollowsStore::addFollows(int leftStmt, int rightStmt) {
	leftStmtStore[rightStmt] = leftStmt;
	rightStmtStore[leftStmt] = rightStmt;
}

int FollowsStore::getLeftStmt(int rightStmt) {
	if (leftStmtStore.find(rightStmt) != leftStmtStore.end()) {
		return leftStmtStore[rightStmt];
	}
	else {
		return -1;
	}
}

int FollowsStore::getRightStmt(int leftStmt) {
	if (rightStmtStore.find(leftStmt) != rightStmtStore.end()) {
		return rightStmtStore[leftStmt];
	}
	else {
		return -1;
	}
}


std::unordered_set<int> FollowsStore::getAllLeft() {
	std::unordered_set<int> leftStmtList;
	for (const auto& [key, value] : leftStmtStore) {
		leftStmtList.insert(value);
	}
	return leftStmtList;
}


std::unordered_set<int> FollowsStore::getAllRight() {
	std::unordered_set<int> rightStmtList;
	for (const auto& [key, value] : rightStmtStore) {
		rightStmtList.insert(value);
	}
	return rightStmtList;
}
