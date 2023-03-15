#include<stdio.h>
#include <iostream>

#include "NextStore.h"

NextStore::NextStore() : leftStmtStore{ }, rightStmtStore{ } {}
NextStore::NextStore(std::unordered_map<int, std::unordered_set<int>> leftStmtStore, std::unordered_map<int, std::unordered_set<int>> rightStmtStore)
	: leftStmtStore{ leftStmtStore }, rightStmtStore{ rightStmtStore } {}

void NextStore::addNext(int leftStmt, int rightStmt) {
	leftStmtStore[rightStmt].emplace(leftStmt);
	rightStmtStore[leftStmt].emplace(rightStmt);
}

std::unordered_set<int> NextStore::getLeftStmt(int rightStmt) {
	if (hasRightStmt(rightStmt)) {
		return leftStmtStore[rightStmt];
	}
	else {
		return {};
	}
}

std::unordered_set<int> NextStore::getRightStmt(int leftStmt) {
	if (hasLeftStmt(leftStmt)) {
		return rightStmtStore[leftStmt];
	}
	else {
		return {};
	}
}

bool NextStore::hasLeftStmt(int lineNum) {
	if (rightStmtStore.find(lineNum) != rightStmtStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool NextStore::hasRightStmt(int lineNum) {
	if (leftStmtStore.find(lineNum) != leftStmtStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

std::unordered_set<int> NextStore::getAllLeft() {
	std::unordered_set<int> leftStmtList;
	for (const auto& [key, value] : leftStmtStore) {
		leftStmtList.insert(value.begin(), value.end());
	}
	return leftStmtList;
}


std::unordered_set<int> NextStore::getAllRight() {
	std::unordered_set<int> rightStmtList;
	for (const auto& [key, value] : rightStmtStore) {
		rightStmtList.insert(value.begin(), value.end());
	}
	return rightStmtList;
}


std::unordered_set<int> NextStore::getRightStmtStar(int leftStmt) {
	std::unordered_set<int> rightStmtList;
	std::unordered_set<int> temp1 = getRightStmt(leftStmt);

	for (const auto& value : temp1) {
		rightStmtList.insert(value);
		if (hasLeftStmt(value)) {
			std::unordered_set<int> temp2 = getRightStmtStar(value);
			rightStmtList.insert(temp2.begin(), temp2.end());
		}
	}
	return rightStmtList;
}

std::unordered_set<int> NextStore::getLeftStmtStar(int rightStmt) {
	std::unordered_set<int> leftStmtList;
	std::unordered_set<int> temp1 = getLeftStmt(rightStmt);

	for (const auto& value : temp1) {
		leftStmtList.insert(value);
		if (hasLeftStmt(value)) {
			std::unordered_set<int> temp2 = getLeftStmtStar(value);
			leftStmtList.insert(temp2.begin(), temp2.end());
		}
	}
	return leftStmtList;
}