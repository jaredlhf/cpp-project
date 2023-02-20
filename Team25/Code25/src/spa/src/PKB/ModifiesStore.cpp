#include<stdio.h>
#include <iostream>


#include "ModifiesStore.h"

ModifiesStore::ModifiesStore() {}

void ModifiesStore::add(int lineNum, std::string varName) {
	varStore[lineNum] = varName;
	stmtStore[varName].emplace(lineNum);
}

std::string ModifiesStore::getVar(int lineNum) {
	if (hasStmt(lineNum)) {
		return varStore[lineNum];
	}
	else {
		return {};
	}
}

std::unordered_set<int> ModifiesStore::getStmt(std::string varName) {
	if (hasVar(varName)) {
		return stmtStore[varName];
	}
	else {
		return std::unordered_set<int>{};
	}
}

bool ModifiesStore::hasVar(std::string varName) {
	if (stmtStore.find(varName) != stmtStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool ModifiesStore::hasStmt(int lineNum) {
	if (varStore.find(lineNum) != varStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

std::unordered_set<std::string> ModifiesStore::getAllVar() {
	std::unordered_set<std::string> varList;
	
	for (const auto& [key, value] : varStore) {
			varList.insert(value);
		}
	return varList;
}

std::unordered_set<int> ModifiesStore::getAllStmt() {
	std::unordered_set<int> stmtList;
	for (const auto& [key, value] : stmtStore) {
		stmtList.insert(value.begin(), value.end());
	}
	return stmtList;
}


void ModifiesStore::clear() {
	stmtStore.clear();
	varStore.clear();
}