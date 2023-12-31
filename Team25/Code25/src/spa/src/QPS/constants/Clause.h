#pragma once

#include <string>
#include <memory>
#include <unordered_set>
#include "Constants.h"
#include "Entity.h"
#include "Wildcard.h"
#include "Synonym.h"
#include "Value.h"
#include "PKB/PkbRetriever.h"
#include "QPS/QpsTable.h"
#include "QPS/utils/AttrUtils.h"
#include "QPS/utils/StringUtils.h"
#include "QPS/constants/strategy/ClauseStrat.h"

class Clause : public std::enable_shared_from_this<Clause> {
protected:
	std::string keyword;
	std::shared_ptr<Entity> arg1;
	std::shared_ptr<Entity> arg2;

public:
	// Constructor functions
	Clause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);

	// Clause functions
	std::string getKeyword();
	bool compare(std::shared_ptr<Clause> other);

	// Functions to be overriden by subclasses of Clause
	virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolve(std::shared_ptr<PkbRetriever> pkbRet);
	virtual bool isWrongArgs();
	virtual bool isSemInvalid();
	virtual bool isPatternClause();

	// Factory method for Clause subclasses
	static std::shared_ptr<Clause> create(const std::string clauseType, std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);

	// Static functions
	static std::unordered_set<int> getEveryStmt(std::shared_ptr<PkbRetriever> pkbRet);
};

class UsesClause : public Clause {
public:
	UsesClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual bool isWrongArgs() override;
	virtual bool isSemInvalid() override;
	virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolve(std::shared_ptr<PkbRetriever> pkbRet) override;
};

class ModifiesClause : public Clause {
public:
	ModifiesClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual bool isWrongArgs() override;
	virtual bool isSemInvalid() override;
	virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolve(std::shared_ptr<PkbRetriever> pkbRet) override;
};

class ParentClause : public Clause {
public:
	ParentClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual bool isWrongArgs() override;
	virtual bool isSemInvalid() override;
	virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolve(std::shared_ptr<PkbRetriever> pkbRet) override;
};

class FollowsClause : public Clause {
public:
	FollowsClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual bool isWrongArgs() override;
	virtual bool isSemInvalid() override;
	virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolve(std::shared_ptr<PkbRetriever> pkbRet) override;
};

class ParentStClause : public Clause {
public:
	ParentStClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual bool isWrongArgs() override;
	virtual bool isSemInvalid() override;
	virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolve(std::shared_ptr<PkbRetriever> pkbRet) override;
};

class FollowsStClause : public Clause {
public:
	FollowsStClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual bool isWrongArgs() override;
	virtual bool isSemInvalid() override;
	virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolve(std::shared_ptr<PkbRetriever> pkbRet) override;
};

class PatternClause : public Clause {
public:
	PatternClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual bool isWrongArgs() override;
	virtual bool isSemInvalid() override;
	virtual bool isPatternClause() override;
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolve(
		std::shared_ptr<PkbRetriever> pkbRet, std::shared_ptr<Synonym> patternSynonym);
};

class CallsClause : public Clause {
public:
	CallsClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual bool isWrongArgs() override;
	virtual bool isSemInvalid() override;
	virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolve(std::shared_ptr<PkbRetriever> pkbRet) override;
};

class NextClause : public Clause {
public:
	NextClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual bool isWrongArgs() override;
	virtual bool isSemInvalid() override;
	virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolve(std::shared_ptr<PkbRetriever> pkbRet) override;
};

class CallsStClause : public Clause {
public:
	CallsStClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual bool isWrongArgs() override;
	virtual bool isSemInvalid() override;
	virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolve(std::shared_ptr<PkbRetriever> pkbRet) override;
};

class NextStClause : public Clause {
public:
	NextStClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual bool isWrongArgs() override;
	virtual bool isSemInvalid() override;
	virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolve(std::shared_ptr<PkbRetriever> pkbRet) override;
};

class AffectsClause : public Clause {
public:
	AffectsClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual bool isWrongArgs() override;
	virtual bool isSemInvalid() override;
	virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolve(std::shared_ptr<PkbRetriever> pkbRet) override;
};

class AffectsStClause : public Clause {
public:
	AffectsStClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual bool isWrongArgs() override;
	virtual bool isSemInvalid() override;
	virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolve(std::shared_ptr<PkbRetriever> pkbRet) override;
};

class WithClause : public Clause {
public:
	WithClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual bool isWrongArgs() override;
	virtual bool isSemInvalid() override;
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolve(std::shared_ptr<PkbRetriever> pkbRet) override;
};