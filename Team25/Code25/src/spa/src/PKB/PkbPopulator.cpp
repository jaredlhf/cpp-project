#include<stdio.h>
#include <vector>
#include <string>

#include "PkbPopulator.h"

/*
 * Constructor class for PkbPopulator
 * param: VarStorage* varStore
 */
PkbPopulator::PkbPopulator(shared_ptr<VariableStore> varStore, shared_ptr<ConstantStore> constStore, shared_ptr<FollowsStore> followsStore, shared_ptr<ProcedureStore> procedureStore, 
	shared_ptr<StatementStore> statementStore, shared_ptr<PatternStore> patternStore, shared_ptr<FollowsStarStore> followsStarStore, shared_ptr<ModifiesProcStore> modifiesProcStore, 
	shared_ptr<ModifiesStore> modifiesStore, shared_ptr<ParentStarStore> parentStarStore, shared_ptr<ParentStore> parentStore, shared_ptr<UsesProcStore> usesProcStore, 
	shared_ptr<UsesStore> usesStore, shared_ptr<CallsStore> callsStore, shared_ptr<CallsStarStore> callsStarStore, shared_ptr<PrintAttribute> printAttrStore, 
	shared_ptr<ReadAttribute> readAttrStore, shared_ptr<CallAttribute> callAttrStore, shared_ptr<NextStore> nextStore, shared_ptr<CFGStore> cfgStore, shared_ptr<ContainCallsStore> conCallStore) {
	this->varStorage = varStore;
	this->constStorage = constStore;
	this->followsStorage = followsStore;
	this->procedureStorage = procedureStore;
	this->statementStorage = statementStore;
	this->patternStorage = patternStore;
	this->followsStarStorage = followsStarStore;
	this->modifiesProcStorage = modifiesProcStore;
	this->modifiesStorage = modifiesStore;
	this->parentStarStorage = parentStarStore;
	this->parentStorage = parentStore;
	this->usesProcStorage = usesProcStore;
	this->usesStorage = usesStore;
	this->callsStorage = callsStore;
	this->callsStarStorage = callsStarStore;
	this->printAttrStorage = printAttrStore;
	this->readAttrStorage = readAttrStore;
	this->callAttrStorage = callAttrStore;
	this->nextStorage = nextStore;
	this->cfgStorage = cfgStore;
	this->conCallStorage = conCallStore;
}


void PkbPopulator::addVar(std::string varName) {
	this->varStorage->addVar(varName);
}

void PkbPopulator::addConst(int constNum) {
	this->constStorage->addConst(constNum);
}

void PkbPopulator::addFollows(int leftLineNum, int rightLineNum) {
	this->followsStorage->addFollows(leftLineNum, rightLineNum);
}

void PkbPopulator::addProc(std::string procName, int lineNum) {
	this->procedureStorage->addProc(procName, lineNum);
}

void PkbPopulator::addStmt(std::string stmtType, int lineNum) {
	this->statementStorage->addStmt(stmtType, lineNum);
}

void PkbPopulator::addAssignLhs(std::string leftVar, int stmtNo) {
	this->patternStorage->addAssignLhs(leftVar, stmtNo);
}

void PkbPopulator::addAssignRhs(int stmtNo, std::string rightStmt) {
	this->patternStorage->addAssignRhs(stmtNo, rightStmt);
}

void PkbPopulator::addFollowsStar(int followee, std::unordered_set<int> followerLst) {
	this->followsStarStorage->addFollowsStar(followee, followerLst);
}

void PkbPopulator::addModifiesProc(std::string procName, std::string varName) {
	this->modifiesProcStorage->addModifiesProc(procName, varName);
}

void PkbPopulator::addModifies(int lineNum, std::string varName) {
	this->modifiesStorage->addModifies(lineNum, varName);
}

void PkbPopulator::addParentStar(int parent, int child) {
	this->parentStarStorage->addParentStar(parent, child);
}

void PkbPopulator::addParent(int parent, int child) {
	this->parentStorage->addParent(parent, child);
}

void PkbPopulator::addUsesProc(std::string procName, std::string varName) {
	this->usesProcStorage->addUsesProc(procName, varName);
}

void PkbPopulator::addUses(int lineNum, std::string varName) {
	this->usesStorage->addUses(lineNum, varName);
}

void PkbPopulator::addCallsStar(std::string leftProc, std::string rightProc) {
	this->callsStarStorage->addCallsStar(leftProc, rightProc);
}

void PkbPopulator::addCalls(std::string leftProc, std::string rightProc) {
	this->callsStorage->addCalls(leftProc, rightProc);
}

void PkbPopulator::addIfStatement(int stmtNo, std::string varName) {
	this->patternStorage->addIfStatement(stmtNo, varName);
}

void PkbPopulator::addIfStatementVar(std::string varName, int stmtNo) {
	this->patternStorage->addIfStatementVar(varName, stmtNo);
}

void PkbPopulator::addWhileStatement(int stmtNo, std::string varName) {
	this->patternStorage->addWhileStatement(stmtNo, varName);
}

void PkbPopulator::addWhileStatementVar(std::string varName, int stmtNo) {
	this->patternStorage->addWhileStatementVar(varName, stmtNo);
}

void PkbPopulator::addPrintAttr(std::string varName, int lineNum) {
	this->printAttrStorage->addAttr(varName, lineNum);
}

void PkbPopulator::addReadAttr(std::string varName, int lineNum) {
	this->readAttrStorage->addAttr(varName, lineNum);
}

void PkbPopulator::addCallAttr(std::string procName, int lineNum) {
	this->callAttrStorage->addAttr(procName, lineNum);
}

void PkbPopulator::addNext(int leftLineNum, int rightLineNum) {
	this->nextStorage->addNext(leftLineNum, rightLineNum);
}

void PkbPopulator::addCFGNode(std::string procName, shared_ptr<CFGNode> node) {
	this->cfgStorage->addCFGNode(procName, node);
}

void PkbPopulator::addContainCalls(int lineNum, std::string procName) {
	this->conCallStorage->addContainCall(lineNum, procName);
}