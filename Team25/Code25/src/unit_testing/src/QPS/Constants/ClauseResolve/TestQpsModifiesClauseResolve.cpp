#include "QPS/Constants/Clause.h"
#include "catch.hpp"


// Scenario for testing ModifiesClause::resolve
SCENARIO("Mocking behavior of ModifiesClause::resolve") {
	GIVEN("An instance of a PkbRetriever class") {
		VariableStore vs;
		ConstantStore cs;
		FollowsStore fs;
		ProcedureStore ps;
		StatementStore ss;
		PatternStore patts;
		FollowsStarStore fstars;
		ModifiesProcStore mprocs;
		ModifiesStore ms;
		ParentStarStore pStars;
		ParentStore parents;
		UsesProcStore uprocs;
		UsesStore uses;
		CallsStore calls;
		CallsStarStore cStars;

		std::shared_ptr<VariableStore> vsPointer = std::make_shared<VariableStore>(vs);
		std::shared_ptr<ConstantStore> csPointer = std::make_shared<ConstantStore>(cs);
		std::shared_ptr<FollowsStore> fsPointer = std::make_shared<FollowsStore>(fs);
		std::shared_ptr<ProcedureStore> psPointer = std::make_shared<ProcedureStore>(ps);
		std::shared_ptr<StatementStore> ssPointer = std::make_shared<StatementStore>(ss);
		std::shared_ptr<PatternStore> pattsPointer = std::make_shared<PatternStore>(patts);
		std::shared_ptr<FollowsStarStore> fstarsPointer = std::make_shared<FollowsStarStore>(fstars);
		std::shared_ptr<ModifiesProcStore> mprocsPointer = std::make_shared<ModifiesProcStore>(mprocs);
		std::shared_ptr<ModifiesStore> msPointer = std::make_shared<ModifiesStore>(ms);
		std::shared_ptr<ParentStarStore> pStarsPointer = std::make_shared<ParentStarStore>(pStars);
		std::shared_ptr<ParentStore> parentsPointer = std::make_shared<ParentStore>(parents);
		std::shared_ptr<UsesProcStore> uprocsPointer = std::make_shared<UsesProcStore>(uprocs);
		std::shared_ptr<UsesStore> usesPointer = std::make_shared<UsesStore>(uses);
		std::shared_ptr<CallsStore> callsPointer = std::make_shared<CallsStore>(calls);
		std::shared_ptr<CallsStarStore> cStarsPointer = std::make_shared<CallsStarStore>(cStars);

		PkbRetriever pkbRetriever(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer,
			fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, usesPointer, callsPointer, cStarsPointer);
		std::shared_ptr<PkbRetriever> pkbRet = std::make_shared<PkbRetriever>(pkbRetriever);

		WHEN("PkbRetriever are populated queries that return a non-empty result") {
			// Mock variables appearing in the SIMPLE program
			vsPointer->addVar("x");
			vsPointer->addVar("y");
			vsPointer->addVar("z");

			// Mock constants appearing in the SIMPLE program
			csPointer->addConst(1);

			// Mock procedures appearing in the SIMPLE program
			psPointer->addProc("main");
			psPointer->addProc("f1");
			psPointer->addProc("f2");
			psPointer->addProc("f3");
			psPointer->addProc("f4");

			// Mock statements appearing in the SIMPLE program
			ssPointer->addStmt(Constants::ASSIGN, 1);
			ssPointer->addStmt(Constants::ASSIGN, 2);
			ssPointer->addStmt(Constants::PRINT, 3);
			ssPointer->addStmt(Constants::READ, 4);

			// Mock Modifies relationship in SIMPLE program
			msPointer->addModifies(1, "z");
			msPointer->addModifies(2, "x");
			msPointer->addModifies(4, "z");

			// Mock Modifies Relationship for Procedures in SIMPLE program
			mprocsPointer->addModifiesProc("main", "x");
			mprocsPointer->addModifiesProc("main", "y");
			mprocsPointer->addModifiesProc("main", "z");
			mprocsPointer->addModifiesProc("f1", "x");
			mprocsPointer->addModifiesProc("f1", "y");
			mprocsPointer->addModifiesProc("f2", "y");
			mprocsPointer->addModifiesProc("f3", "z");

			THEN("When ModifiesClause resolves wrong syntax, it should return the right results") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::SYN_ERR, QpsTable::create());

				std::shared_ptr<Value> wrongArg2 = Value::create("1");
				std::shared_ptr<Synonym> stmtSynArg1 = Synonym::create(Constants::STMT, "s1");
				std::shared_ptr<Synonym> varSynArg2 = Synonym::create(Constants::VARIABLE, "v2");

				std::shared_ptr<Clause> wrongClause2 = Clause::create(Constants::MODIFIES, stmtSynArg1, wrongArg2);

				REQUIRE(wrongClause2->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(wrongClause2->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
			}

			THEN("When ModifiesClause resolves wrong semantics, it should return the right results") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::SEM_ERR, QpsTable::create());

				std::shared_ptr<Synonym> wrongArg1 = Synonym::create(Constants::VARIABLE, "v1");
				std::shared_ptr<Synonym> wrongArg2 = Synonym::create(Constants::ASSIGN, "a2");
				std::shared_ptr<Wildcard> wcArg1 = Wildcard::create();

				std::shared_ptr<Synonym> stmtSynArg1 = Synonym::create(Constants::STMT, "s1");
				std::shared_ptr<Synonym> varSynArg2 = Synonym::create(Constants::VARIABLE, "v2");
				std::shared_ptr<Value> constArg2 = Value::create("x");
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

				std::shared_ptr<Clause> wrongClause1 = Clause::create(Constants::MODIFIES, wrongArg1, varSynArg2);
				std::shared_ptr<Clause> wrongClause2 = Clause::create(Constants::MODIFIES, stmtSynArg1, wrongArg2);
				std::shared_ptr<Clause> wrongClause3 = Clause::create(Constants::MODIFIES, wcArg1, varSynArg2);
				std::shared_ptr<Clause> wrongClause4 = Clause::create(Constants::MODIFIES, wcArg1, constArg2);
				std::shared_ptr<Clause> wrongClause5 = Clause::create(Constants::MODIFIES, wcArg1, wcArg2);

				REQUIRE(wrongClause1->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(wrongClause1->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
				REQUIRE(wrongClause2->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(wrongClause2->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
				REQUIRE(wrongClause3->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(wrongClause3->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
				REQUIRE(wrongClause4->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(wrongClause4->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
				REQUIRE(wrongClause5->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(wrongClause5->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());\
			}

			THEN("When ModifiesClause resolves case Modifies(1, _), it should return the right results") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::OK, QpsTable::create());

				std::shared_ptr<Value> constArg1 = Value::create("1");
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, constArg1, wcArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
			}

			THEN("When ModifiesClause resolves case Modifies(3, _), it should return no matches") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::NO_MATCH, QpsTable::create());

				std::shared_ptr<Value> constArg1 = Value::create("3");
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, constArg1, wcArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
			}

			THEN("When ModifiesClause resolves case Modifies(1, 'z'), it should return the right results") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::OK, QpsTable::create());

				std::shared_ptr<Value> constArg1 = Value::create("1");
				std::shared_ptr<Value> constArg2 = Value::create("z");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, constArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
			}

			THEN("When ModifiesClause resolves case Modifies(1, 'x'), it should return no matches") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::NO_MATCH, QpsTable::create());

				std::shared_ptr<Value> constArg1 = Value::create("1");
				std::shared_ptr<Value> constArg2 = Value::create("x");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, constArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
			}

			THEN("When ModifiesClause resolves case Modifies(1, v2), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "v2" });
				expectedTable->addRow({ "z" });

				std::shared_ptr<Value> constArg1 = Value::create("1");
				std::shared_ptr<Synonym> varSynArg2 = Synonym::create(Constants::VARIABLE, "v2");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, constArg1, varSynArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When ModifiesClause resolves case Modifies(3, v2), it should return no matches") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "v2" });

				std::shared_ptr<Value> constArg1 = Value::create("3");
				std::shared_ptr<Synonym> varSynArg2 = Synonym::create(Constants::VARIABLE, "v2");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, constArg1, varSynArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When ModifiesClause resolves case Modifies(s1, _), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "s1" });
				expectedTable->addRow({ "1" });
				expectedTable->addRow({ "2" });
				expectedTable->addRow({ "4" });


				std::shared_ptr<Synonym> stmtSynArg1 = Synonym::create(Constants::STMT, "s1");
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, stmtSynArg1, wcArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When ModifiesClause resolves case Modifies(w1, _), it should return no matches") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "w1" });


				std::shared_ptr<Synonym> whSynArg1 = Synonym::create(Constants::WHILE, "w1");
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, whSynArg1, wcArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When ModifiesClause resolves case Modifies(s1, 'z'), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "s1" });
				expectedTable->addRow({ "1" });
				expectedTable->addRow({ "4" });


				std::shared_ptr<Synonym> stmtSynArg1 = Synonym::create(Constants::STMT, "s1");
				std::shared_ptr<Value> constArg2 = Value::create("z");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, stmtSynArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When ModifiesClause resolves case Modifies(s1, 'y'), it should return no matches") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "s1" });


				std::shared_ptr<Synonym> stmtSynArg1 = Synonym::create(Constants::STMT, "s1");
				std::shared_ptr<Value> constArg2 = Value::create("y");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, stmtSynArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When ModifiesClause resolves case Modifies(a1, v2), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "a1", "v2"});
				expectedTable->addRow({ "1", "z" });
				expectedTable->addRow({ "2", "x" });


				std::shared_ptr<Synonym> asgSynArg1 = Synonym::create(Constants::ASSIGN, "a1");
				std::shared_ptr<Synonym> varSynArg1 = Synonym::create(Constants::VARIABLE, "v2");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, asgSynArg1, varSynArg1);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When ModifiesClause resolves case Modifies(w1, v2), it should return no matches") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "w1", "v2" });


				std::shared_ptr<Synonym> whSynArg1 = Synonym::create(Constants::WHILE, "w1");
				std::shared_ptr<Synonym> varSynArg1 = Synonym::create(Constants::VARIABLE, "v2");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, whSynArg1, varSynArg1);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When ModifiesClause resolves case Modifies('main', _), it should return the right results") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::OK, QpsTable::create());

				std::shared_ptr<Value> constArg1 = Value::create("main");
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, constArg1, wcArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
			}

			THEN("When ModifiesClause resolves case Modifies('f4', _), it should return no matches") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::NO_MATCH, QpsTable::create());

				std::shared_ptr<Value> constArg1 = Value::create("f4");
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, constArg1, wcArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
			}

			THEN("When ModifiesClause resolves case Modifies('f3', 'z'), it should return the right results") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::OK, QpsTable::create());

				std::shared_ptr<Value> constArg1 = Value::create("f3");
				std::shared_ptr<Value> constArg2 = Value::create("z");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, constArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
			}

			THEN("When ModifiesClause resolves case Modifies('f3', 'x'), it should return no matches") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::NO_MATCH, QpsTable::create());

				std::shared_ptr<Value> constArg1 = Value::create("f3");
				std::shared_ptr<Value> constArg2 = Value::create("x");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, constArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
			}

			THEN("When ModifiesClause resolves case Modifies('f1', v2), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "v2" });
				expectedTable->addRow({ "x" });
				expectedTable->addRow({ "y" });

				std::shared_ptr<Value> constArg1 = Value::create("f1");
				std::shared_ptr<Synonym> varSynArg2 = Synonym::create(Constants::VARIABLE, "v2");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, constArg1, varSynArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When ModifiesClause resolves case Modifies('f4', v2), it should return no matches") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "v2" });

				std::shared_ptr<Value> constArg1 = Value::create("f4");
				std::shared_ptr<Synonym> varSynArg2 = Synonym::create(Constants::VARIABLE, "v2");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, constArg1, varSynArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When ModifiesClause resolves case Uses(p1, _), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "p1" });
				expectedTable->addRow({ "main" });
				expectedTable->addRow({ "f1" });
				expectedTable->addRow({ "f2" });
				expectedTable->addRow({ "f3" });


				std::shared_ptr<Synonym> procSynArg1 = Synonym::create(Constants::PROCEDURE, "p1");
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, procSynArg1, wcArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When ModifiesClause resolves case Uses(p1, 'y'), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "p1" });
				expectedTable->addRow({ "main" });
				expectedTable->addRow({ "f1" });
				expectedTable->addRow({ "f2" });


				std::shared_ptr<Synonym> procSynArg1 = Synonym::create(Constants::PROCEDURE, "p1");
				std::shared_ptr<Value> constArg2 = Value::create("y");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, procSynArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When ModifiesClause resolves case Uses(p1, 'w'), it should return no match") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "p1" });


				std::shared_ptr<Synonym> procSynArg1 = Synonym::create(Constants::PROCEDURE, "p1");
				std::shared_ptr<Value> constArg2 = Value::create("w");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, procSynArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When ModifiesClause resolves case Uses(p1, v2), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "p1", "v2" });
				expectedTable->addRow({ "main", "x" });
				expectedTable->addRow({ "main", "y" });
				expectedTable->addRow({ "main", "z" });
				expectedTable->addRow({ "f1", "x" });
				expectedTable->addRow({ "f1", "y" });
				expectedTable->addRow({ "f2", "y" });
				expectedTable->addRow({ "f3", "z" });


				std::shared_ptr<Synonym> procSynArg1 = Synonym::create(Constants::PROCEDURE, "p1");
				std::shared_ptr<Synonym> varSynArg1 = Synonym::create(Constants::VARIABLE, "v2");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::MODIFIES, procSynArg1, varSynArg1);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}
		}
	}
}