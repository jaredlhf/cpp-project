#pragma once
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

#include "VariableStore.h"
#include "ConstantStore.h"
#include "FollowsStore.h"
#include "ProcedureStore.h"
#include "StatementStore.h"

class PkbPopulator {

private:
	shared_ptr<VariableStore> varStorage;
	shared_ptr<ConstantStore> constStorage;
	shared_ptr<FollowsStore> followsStorage;
	shared_ptr<ProcedureStore> procedureStorage;
	shared_ptr<StatementStore> statementStorage;

public:
	PkbPopulator(shared_ptr<VariableStore> varStore, shared_ptr<ConstantStore> constStore, shared_ptr<FollowsStore> followsStore, shared_ptr<ProcedureStore> procedureStore, shared_ptr<StatementStore> statementStore);
	void addVar(std::string varName);
	void addConst(int constNum);
	void addFollows(int leftLineNum, int rightLineNum);
	void addProc(std::string procName);
	void addStmt(std::string stmtType, int lineNum);
};