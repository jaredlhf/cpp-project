#pragma once

#include<stdio.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

class StmtVarStore {
	virtual std::unordered_set<std::string> getVar(int lineNum) = 0;
	virtual std::unordered_set<int> getStmt(std::string varName) = 0;
	virtual bool hasVar(std::string varName) = 0;
	virtual bool hasStmt(int lineNum) = 0;
	virtual std::unordered_set<std::string> getAllVar() = 0;
	virtual std::unordered_set<int> getAllStmt() = 0;
	
};

class ProcVarStore {
	virtual std::unordered_set<std::string> getVar(std::string procName) = 0;
	virtual std::unordered_set<std::string> getProc(std::string varName) = 0;
	virtual bool hasVar(std::string varName) = 0;
	virtual bool hasProc(std::string procName) = 0;
	virtual std::unordered_set<std::string> getAllVar() = 0;
	virtual std::unordered_set<std::string> getAllProc() = 0;
};

class StmtStmtStore {
	virtual bool hasLeftStmt(int lineNum) = 0;
	virtual bool hasRightStmt(int lineNum) = 0;
	virtual std::unordered_set<int> getAllLeft() = 0;
	virtual std::unordered_set<int> getAllRight() = 0;
};

class StmtStmtStarStore {
	virtual std::unordered_set<int> getLeftStar(int rightStmt) = 0;
	virtual std::unordered_set<int> getRightStar(int leftStmt) = 0;
	virtual bool hasLeftStmt(int lineNum) = 0;
	virtual bool hasRightStmt(int lineNum) = 0;
	virtual std::unordered_set<int> getAllLeft() = 0;
	virtual std::unordered_set<int> getAllRight() = 0;
};

class ProcProcStore {
	virtual bool hasLeftProc(std::string procName) = 0;
	virtual bool hasRightProc(std::string procName) = 0;
	virtual std::unordered_set<std::string> getAllLeft() = 0;
	virtual std::unordered_set<std::string> getAllRight() = 0;
};

class ProcProcStarStore {
	virtual std::unordered_set<std::string> getLeftStar(std::string rightProc) = 0;
	virtual std::unordered_set<std::string> getRightStar(std::string leftProc) = 0;
	virtual bool hasLeftProc(std::string procName) = 0;
	virtual bool hasRightProc(std::string procName) = 0;
	virtual std::unordered_set<std::string> getAllLeft() = 0;
	virtual std::unordered_set<std::string> getAllRight() = 0;
};

class ProcStmtStore {
	virtual std::unordered_set<std::string> getProc(int lineNum) = 0;
	virtual std::unordered_set<int> getStmt(std::string varName) = 0;
	virtual bool hasProc(std::string varName) = 0;
	virtual bool hasStmt(int lineNum) = 0;
	virtual std::unordered_set<std::string> getAllProc() = 0;
	virtual std::unordered_set<int> getAllStmt() = 0;
};

