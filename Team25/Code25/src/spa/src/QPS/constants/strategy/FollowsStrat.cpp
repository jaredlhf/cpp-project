#include <algorithm>
#include "FollowsStrat.h"

// Constructor function for UsesStrat
FollowsStrat::FollowsStrat(std::string clauseKeyword, std::shared_ptr<Entity> arg1,
    std::shared_ptr<Entity> arg2, std::shared_ptr<PkbRetriever> pkbRet)
    : ClauseStrat(clauseKeyword, arg1, arg2, pkbRet) {
}


std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> FollowsStrat::resolve() {
    return createReturnStrategy();
}

// Factory function for strategy used
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> FollowsStrat::createReturnStrategy() {
    if (this->arg1->isWildcard() && this->arg2->isWildcard()) return wildcardWildcard();
    if (this->arg1->isWildcard() && this->arg2->isConstant()) return wildcardConst();
    if (this->arg1->isWildcard() && this->arg2->isSynonym()) return wildcardSyn();
    if (this->arg1->isConstant() && this->arg2->isWildcard()) return constWildcard();
    if (this->arg1->isConstant() && this->arg2->isConstant()) return constConst();
    if (this->arg1->isConstant() && this->arg2->isSynonym()) return constSyn();
    if (this->arg1->isSynonym() && this->arg2->isWildcard()) return synWildcard();
    if (this->arg1->isSynonym() && this->arg2->isConstant()) return synConst();
    if (this->arg1->isSynonym() && this->arg2->isSynonym()) return synSyn();

    return QpsTable::getDefaultSynErr();
}

// Case: Follows(_, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> FollowsStrat::wildcardWildcard() {
    return QueryUtils::isNotEmpty(pkbRet->getAllFollowees())
        ? QpsTable::getDefaultOk()
        : QpsTable::getDefaultNoMatch();
}

// Case: Follows(_, 2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> FollowsStrat::wildcardConst() {
    std::unordered_set<int> stmts = pkbRet->getAllFollowers();
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
    return QueryUtils::contains(stmts, std::stoi(arg2Val))
        ? QpsTable::getDefaultOk()
        : QpsTable::getDefaultNoMatch();
}

// Case: Follows(_, s2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> FollowsStrat::wildcardSyn() {
    std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
    std::unordered_set<int> s2Stmts = s2Syn->matchesKeyword(Constants::STMT)
        ? Clause::getEveryStmt(pkbRet)
        : pkbRet->getAllStmt(s2Syn->getKeyword());
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s2Syn->getName() });
    for (int stNum : s2Stmts) {
        if (pkbRet->getFollowee(stNum) != -1) {
            resTable->addRow({ std::to_string(stNum) });
        }
    }

    return QueryUtils::isNotEmpty(resTable->getData())
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: Follows(1, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> FollowsStrat::constWildcard() {
    std::unordered_set<int> stmts = pkbRet->getAllFollowees();
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    return QueryUtils::contains(stmts, std::stoi(arg1Val))
        ? QpsTable::getDefaultOk()
        : QpsTable::getDefaultNoMatch();
}

// Case: Follows(1, 2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> FollowsStrat::constConst() {
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();

    if (pkbRet->getFollower(std::stoi(arg1Val)) == std::stoi(arg2Val)) {
        return QpsTable::getDefaultOk();
    }
    return QpsTable::getDefaultNoMatch();
}

// Case: Follows(1, s2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> FollowsStrat::constSyn() {
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
    std::unordered_set<int> s2Stmts = s2Syn->matchesKeyword(Constants::STMT)
        ? Clause::getEveryStmt(pkbRet)
        : pkbRet->getAllStmt(s2Syn->getKeyword());
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s2Syn->getName() });

    for (int stNum : s2Stmts) {
        if (pkbRet->getFollower(std::stoi(arg1Val)) == stNum) {
            resTable->addRow({ std::to_string(stNum) });
        }
    }
    return QueryUtils::isNotEmpty(resTable->getData())
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: Follows(s1, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> FollowsStrat::synWildcard() {
    std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
    std::unordered_set<int> s1Stmts = s1Syn->matchesKeyword(Constants::STMT)
        ? Clause::getEveryStmt(pkbRet)
        : pkbRet->getAllStmt(s1Syn->getKeyword());
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName() });
    for (int stNum : s1Stmts) {
        if (pkbRet->getFollower(stNum) != -1) {
            resTable->addRow({ std::to_string(stNum) });
        }
    }

    return QueryUtils::isNotEmpty(resTable->getData())
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: Follows(s1, 2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> FollowsStrat::synConst() {
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
    std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
    std::unordered_set<int> s1Stmts = s1Syn->matchesKeyword(Constants::STMT)
        ? Clause::getEveryStmt(pkbRet)
        : pkbRet->getAllStmt(s1Syn->getKeyword());
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName() });

    for (int stNum : s1Stmts) {
        if (pkbRet->getFollowee(std::stoi(arg2Val)) == stNum) {
            resTable->addRow({ std::to_string(stNum) });
        }
    }
    return QueryUtils::isNotEmpty(resTable->getData())
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: Follows(s1, s2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> FollowsStrat::synSyn() {
    std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
    std::unordered_set<int> s1Stmts = s1Syn->matchesKeyword(Constants::STMT)
        ? Clause::getEveryStmt(pkbRet)
        : pkbRet->getAllStmt(s1Syn->getKeyword());

    std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
    std::unordered_set<int> s2Stmts = s2Syn->matchesKeyword(Constants::STMT)
        ? Clause::getEveryStmt(pkbRet)
        : pkbRet->getAllStmt(s2Syn->getKeyword());

    // Edge case: if s1 and s2 are the same var name, return no match
    if (s1Syn->getName() == s2Syn->getName()) {
        return QpsTable::getDefaultNoMatch();
    }

    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName(), s2Syn->getName() });
    std::vector<std::pair<int, int>> argCombis;
    for (int arg1StNum : s1Stmts) {
        for (int arg2StNum : s2Stmts) {
            argCombis.push_back({ arg1StNum, arg2StNum });
        }
    }

    for (std::pair<int, int> argPair : argCombis) {
        int arg1StNum = argPair.first;
        int arg2StNum = argPair.second;
        if (pkbRet->getFollower(arg1StNum) == arg2StNum) {
            resTable->addRow({ std::to_string(arg1StNum), std::to_string(arg2StNum) });
        }

    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}
