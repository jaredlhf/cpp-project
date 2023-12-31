#include "ClauseStrat.h"
#include "UsesStrat.h"
#include "ModStrat.h"
#include "ParentStrat.h"
#include "FollowsStrat.h"
#include "ParentStStrat.h"
#include "FollowsStStrat.h"
#include "PatternStrat.h"
#include "CallsStrat.h"
#include "CallsStStrat.h"
#include "NextStrat.h"
#include "NextStStrat.h"
#include "AffectsStrat.h"
#include "AffectsStStrat.h"
#include "WithStrat.h"


// Constructor function for ClauseStrat

ClauseStrat::ClauseStrat(std::string clauseKeyword, std::shared_ptr<Entity> arg1,
	std::shared_ptr<Entity> arg2, std::shared_ptr<PkbRetriever> pkbRet) {
	this->clauseKeyword = clauseKeyword;
	this->arg1 = arg1;
	this->arg2 = arg2;
	this->pkbRet = pkbRet;
}

// Factory function for ClauseStrat
std::shared_ptr<ClauseStrat> ClauseStrat::create(std::string clauseKeyword, std::shared_ptr<Entity> arg1,
	std::shared_ptr<Entity> arg2, std::shared_ptr<PkbRetriever> pkbRet) {
	if (clauseKeyword == Constants::USES) {
		return std::make_shared<UsesStrat>(UsesStrat(clauseKeyword, arg1, arg2, pkbRet));
	}
	if (clauseKeyword == Constants::MODIFIES) {
		return std::make_shared<ModStrat>(ModStrat(clauseKeyword, arg1, arg2, pkbRet));
	}
	if (clauseKeyword == Constants::PARENT) {
		return std::make_shared<ParentStrat>(ParentStrat(clauseKeyword, arg1, arg2, pkbRet));
	}
	if (clauseKeyword == Constants::FOLLOWS) {
		return std::make_shared<FollowsStrat>(FollowsStrat(clauseKeyword, arg1, arg2, pkbRet));
	}
	if (clauseKeyword == Constants::PARENTST) {
		return std::make_shared<ParentStStrat>(ParentStStrat(clauseKeyword, arg1, arg2, pkbRet));
	}
	if (clauseKeyword == Constants::FOLLOWSST) {
		return std::make_shared<FollowsStStrat>(FollowsStStrat(clauseKeyword, arg1, arg2, pkbRet));
	}
	if (clauseKeyword == Constants::CALLS) {
		return std::make_shared<CallsStrat>(CallsStrat(clauseKeyword, arg1, arg2, pkbRet));
	}
	if (clauseKeyword == Constants::CALLSST) {
		return std::make_shared<CallsStStrat>(CallsStStrat(clauseKeyword, arg1, arg2, pkbRet));
	}
	if (clauseKeyword == Constants::NEXT) {
		return std::make_shared<NextStrat>(NextStrat(clauseKeyword, arg1, arg2, pkbRet));
	}
	if (clauseKeyword == Constants::NEXTST) {
		return std::make_shared<NextStStrat>(NextStStrat(clauseKeyword, arg1, arg2, pkbRet));
	}
	if (clauseKeyword == Constants::AFFECTS) {
		return std::make_shared<AffectsStrat>(AffectsStrat(clauseKeyword, arg1, arg2, pkbRet));
	}
	if (clauseKeyword == Constants::AFFECTSST) {
		return std::make_shared<AffectsStStrat>(AffectsStStrat(clauseKeyword, arg1, arg2, pkbRet));
	}
	if (clauseKeyword == Constants::WITH) {
		return std::make_shared<WithStrat>(WithStrat(clauseKeyword, arg1, arg2, pkbRet));
	}

	return std::make_shared<ClauseStrat>(ClauseStrat(clauseKeyword, arg1, arg2, pkbRet));
}

std::shared_ptr<ClauseStrat> ClauseStrat::create(std::string clauseKeyword, std::shared_ptr<Entity> arg1,
	std::shared_ptr<Entity> arg2, std::shared_ptr<PkbRetriever> pkbRet, std::shared_ptr<Synonym> pairedSyn) {
	if (clauseKeyword == Constants::PATTERN) {
		return std::make_shared<PatternStrat>(PatternStrat(clauseKeyword, arg1, arg2, pkbRet, pairedSyn));
	}

	return create(clauseKeyword, arg1, arg2, pkbRet);
}

// Overridable functions for ClauseStrat
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ClauseStrat::resolve() {
	return QpsTable::getDefaultSynErr();
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ClauseStrat::createReturnStrategy() {
	return QpsTable::getDefaultSynErr();
}
