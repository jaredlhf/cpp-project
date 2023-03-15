#include "QPS/constants/Clause.h"
#include "catch.hpp"

// Scenario for testing ParentClause::resolve
SCENARIO("Mocking behavior of ParentStClause::resolve") {
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
    PrintAttribute printA;
    ReadAttribute readA;
    CallAttribute callA;
    NextStore next;

    std::shared_ptr<VariableStore> vsPointer =
        std::make_shared<VariableStore>(vs);
    std::shared_ptr<ConstantStore> csPointer =
        std::make_shared<ConstantStore>(cs);
    std::shared_ptr<FollowsStore> fsPointer =
        std::make_shared<FollowsStore>(fs);
    std::shared_ptr<ProcedureStore> psPointer =
        std::make_shared<ProcedureStore>(ps);
    std::shared_ptr<StatementStore> ssPointer =
        std::make_shared<StatementStore>(ss);
    std::shared_ptr<PatternStore> pattsPointer =
        std::make_shared<PatternStore>(patts);
    std::shared_ptr<FollowsStarStore> fstarsPointer =
        std::make_shared<FollowsStarStore>(fstars);
    std::shared_ptr<ModifiesProcStore> mprocsPointer =
        std::make_shared<ModifiesProcStore>(mprocs);
    std::shared_ptr<ModifiesStore> msPointer =
        std::make_shared<ModifiesStore>(ms);
    std::shared_ptr<ParentStarStore> pStarsPointer =
        std::make_shared<ParentStarStore>(pStars);
    std::shared_ptr<ParentStore> parentsPointer =
        std::make_shared<ParentStore>(parents);
    std::shared_ptr<UsesProcStore> uprocsPointer =
        std::make_shared<UsesProcStore>(uprocs);
    std::shared_ptr<UsesStore> usesPointer = std::make_shared<UsesStore>(uses);
    std::shared_ptr<CallsStore> callsPointer =
        std::make_shared<CallsStore>(calls);
    std::shared_ptr<CallsStarStore> cStarsPointer =
        std::make_shared<CallsStarStore>(cStars);
    std::shared_ptr<PrintAttribute> printAPointer =
        std::make_shared<PrintAttribute>(printA);
    std::shared_ptr<ReadAttribute> readAPointer =
        std::make_shared<ReadAttribute>(readA);
    std::shared_ptr<CallAttribute> callAPointer =
        std::make_shared<CallAttribute>(callA);
    std::shared_ptr<NextStore> nextPointer = std::make_shared<NextStore>(next);

    PkbRetriever pkbRetriever(
        vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer,
        fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer,
        uprocsPointer, usesPointer, callsPointer, cStarsPointer, printAPointer,
        readAPointer, callAPointer, nextPointer);
    std::shared_ptr<PkbRetriever> pkbRet =
        std::make_shared<PkbRetriever>(pkbRetriever);

    WHEN("PkbRetriever are populated queries that return a non-empty result") {
      // Mock variables appearing in the SIMPLE program
      vsPointer->addVar("x");
      vsPointer->addVar("y");
      vsPointer->addVar("z");

      // Mock constants appearing in the SIMPLE program
      csPointer->addConst(1);

      // Mock procedures appearing in the SIMPLE program
      psPointer->addProc("main");

      // Mock statements appearing in the SIMPLE program
      ssPointer->addStmt(Constants::ASSIGN, 1);
      ssPointer->addStmt(Constants::WHILE, 2);
      ssPointer->addStmt(Constants::ASSIGN, 3);
      ssPointer->addStmt(Constants::IF, 4);
      ssPointer->addStmt(Constants::READ, 5);
      ssPointer->addStmt(Constants::PRINT, 6);
      ssPointer->addStmt(Constants::ASSIGN, 7);
      ssPointer->addStmt(Constants::WHILE, 8);
      ssPointer->addStmt(Constants::ASSIGN, 9);

      // Mock parentSt relationship in SIMPLE program
      pStarsPointer->addParentStar(2, 3);
      pStarsPointer->addParentStar(2, 4);
      pStarsPointer->addParentStar(2, 5);
      pStarsPointer->addParentStar(2, 6);
      pStarsPointer->addParentStar(2, 7);
      pStarsPointer->addParentStar(2, 8);
      pStarsPointer->addParentStar(2, 9);
      pStarsPointer->addParentStar(4, 5);
      pStarsPointer->addParentStar(4, 6);
      pStarsPointer->addParentStar(4, 7);
      pStarsPointer->addParentStar(8, 9);

      THEN("When ParentStClause resolves wrong syntax, it should return the "
           "right results") {
        std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>>
            expectedClauseRes = std::make_pair(Constants::ClauseResult::SYN_ERR,
                                               QpsTable::create());

        std::shared_ptr<Value> wrongArg1 = Value::create("x");
        std::shared_ptr<Value> wrongArg2 = Value::create("y");
        std::shared_ptr<Synonym> stmtSynArg1 =
            Synonym::create(Constants::STMT, "s1");
        std::shared_ptr<Synonym> stmtSynArg2 =
            Synonym::create(Constants::STMT, "s2");

        std::shared_ptr<Clause> wrongClause1 =
            Clause::create(Constants::PARENTST, wrongArg1, stmtSynArg2);
        std::shared_ptr<Clause> wrongClause2 =
            Clause::create(Constants::PARENTST, stmtSynArg1, wrongArg2);

        REQUIRE(wrongClause1->resolve(pkbRet).first == expectedClauseRes.first);
        REQUIRE(wrongClause1->resolve(pkbRet).second->getData() ==
                expectedClauseRes.second->getData());
        REQUIRE(wrongClause2->resolve(pkbRet).first == expectedClauseRes.first);
        REQUIRE(wrongClause2->resolve(pkbRet).second->getData() ==
                expectedClauseRes.second->getData());
      }

      THEN("When ParentStClause resolves wrong semantics, it should return the "
           "right results") {
        std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>>
            expectedClauseRes = std::make_pair(Constants::ClauseResult::SEM_ERR,
                                               QpsTable::create());

        std::shared_ptr<Synonym> wrongArg1 =
            Synonym::create(Constants::VARIABLE, "v1");
        std::shared_ptr<Synonym> wrongArg2 =
            Synonym::create(Constants::CONSTANT, "c2");
        std::shared_ptr<Synonym> stmtSynArg1 =
            Synonym::create(Constants::STMT, "s1");
        std::shared_ptr<Synonym> stmtSynArg2 =
            Synonym::create(Constants::STMT, "s2");

        std::shared_ptr<Clause> wrongClause1 =
            Clause::create(Constants::PARENTST, wrongArg1, stmtSynArg2);
        std::shared_ptr<Clause> wrongClause2 =
            Clause::create(Constants::PARENTST, stmtSynArg1, wrongArg2);

        REQUIRE(wrongClause1->resolve(pkbRet).first == expectedClauseRes.first);
        REQUIRE(wrongClause1->resolve(pkbRet).second->getData() ==
                expectedClauseRes.second->getData());
        REQUIRE(wrongClause2->resolve(pkbRet).first == expectedClauseRes.first);
        REQUIRE(wrongClause2->resolve(pkbRet).second->getData() ==
                expectedClauseRes.second->getData());
      }

      THEN("When ParentStClause resolves case ParentSt(_,_), it should return "
           "the right results") {
        std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>>
            expectedClauseRes =
                std::make_pair(Constants::ClauseResult::OK, QpsTable::create());

        std::shared_ptr<Wildcard> wcArg1 = Wildcard::create();
        std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

        std::shared_ptr<Clause> testClause =
            Clause::create(Constants::PARENTST, wcArg1, wcArg2);

        REQUIRE(testClause->resolve(pkbRet).first == expectedClauseRes.first);
        REQUIRE(testClause->resolve(pkbRet).second->getHeaders() ==
                expectedClauseRes.second->getHeaders());
        REQUIRE(testClause->resolve(pkbRet).second->getData() ==
                expectedClauseRes.second->getData());
      }

      THEN("When ParentStClause resolves case ParentSt(_,5), it should return "
           "the right results") {
        Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
        std::shared_ptr<QpsTable> expectedTable = QpsTable::create();

        std::shared_ptr<Wildcard> wcArg1 = Wildcard::create();
        std::shared_ptr<Value> constArg2 = Value::create("5");

        std::shared_ptr<Clause> testClause =
            Clause::create(Constants::PARENTST, wcArg1, constArg2);

        REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
        REQUIRE(testClause->resolve(pkbRet).second->getHeaders() ==
                expectedTable->getHeaders());
        REQUIRE(testClause->resolve(pkbRet).second->getData() ==
                expectedTable->getData());
      }

      THEN("When ParentStClause resolves case ParentSt(_,2), it should return "
           "no matches") {
        Constants::ClauseResult expectedStatus =
            Constants::ClauseResult::NO_MATCH;
        std::shared_ptr<QpsTable> expectedTable = QpsTable::create();

        std::shared_ptr<Wildcard> wcArg1 = Wildcard::create();
        std::shared_ptr<Value> constArg2 = Value::create("2");

        std::shared_ptr<Clause> testClause =
            Clause::create(Constants::PARENTST, wcArg1, constArg2);

        REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
        REQUIRE(testClause->resolve(pkbRet).second->getHeaders() ==
                expectedTable->getHeaders());
        REQUIRE(testClause->resolve(pkbRet).second->getData() ==
                expectedTable->getData());
      }

      THEN("When ParentStClause resolves case ParentSt(_,s2), it should return "
           "the right results") {
        Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
        std::shared_ptr<QpsTable> expectedTable = QpsTable::create({"s2"});
        expectedTable->addRow({"3"});
        expectedTable->addRow({"4"});
        expectedTable->addRow({"5"});
        expectedTable->addRow({"6"});
        expectedTable->addRow({"7"});
        expectedTable->addRow({"8"});
        expectedTable->addRow({"9"});

        std::shared_ptr<Wildcard> wcArg1 = Wildcard::create();
        std::shared_ptr<Synonym> synArg2 =
            Synonym::create(Constants::STMT, "s2");

        std::shared_ptr<Clause> testClause =
            Clause::create(Constants::PARENTST, wcArg1, synArg2);

        REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
        REQUIRE(testClause->resolve(pkbRet).second->getHeaders() ==
                expectedTable->getHeaders());
        REQUIRE(testClause->resolve(pkbRet).second->getData() ==
                expectedTable->getData());
      }

      THEN("When ParentStClause resolves case ParentSt(_,cll2), it should "
           "return no matches") {
        Constants::ClauseResult expectedStatus =
            Constants::ClauseResult::NO_MATCH;
        std::shared_ptr<QpsTable> expectedTable = QpsTable::create({"cll2"});

        std::shared_ptr<Wildcard> wcArg1 = Wildcard::create();
        std::shared_ptr<Synonym> synArg2 =
            Synonym::create(Constants::CALL, "cll2");

        std::shared_ptr<Clause> testClause =
            Clause::create(Constants::PARENTST, wcArg1, synArg2);

        REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
        REQUIRE(testClause->resolve(pkbRet).second->getHeaders() ==
                expectedTable->getHeaders());
        REQUIRE(testClause->resolve(pkbRet).second->getData() ==
                expectedTable->getData());
      }

      THEN("When ParentStClause resolves case ParentSt(4,_), it should return "
           "the right results") {
        Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
        std::shared_ptr<QpsTable> expectedTable = QpsTable::create();

        std::shared_ptr<Value> constArg1 = Value::create("4");
        std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

        std::shared_ptr<Clause> testClause =
            Clause::create(Constants::PARENTST, constArg1, wcArg2);

        REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
        REQUIRE(testClause->resolve(pkbRet).second->getHeaders() ==
                expectedTable->getHeaders());
        REQUIRE(testClause->resolve(pkbRet).second->getData() ==
                expectedTable->getData());
      }

      THEN("When ParentStClause resolves case ParentSt(3,_), it should return "
           "no matches") {
        Constants::ClauseResult expectedStatus =
            Constants::ClauseResult::NO_MATCH;
        std::shared_ptr<QpsTable> expectedTable = QpsTable::create();

        std::shared_ptr<Value> constArg1 = Value::create("3");
        std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

        std::shared_ptr<Clause> testClause =
            Clause::create(Constants::PARENTST, constArg1, wcArg2);

        REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
        REQUIRE(testClause->resolve(pkbRet).second->getHeaders() ==
                expectedTable->getHeaders());
        REQUIRE(testClause->resolve(pkbRet).second->getData() ==
                expectedTable->getData());
      }

      THEN("When ParentStClause resolves case ParentSt(2,5), it should return "
           "the right results") {
        Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
        std::shared_ptr<QpsTable> expectedTable = QpsTable::create();

        std::shared_ptr<Value> constArg1 = Value::create("2");
        std::shared_ptr<Value> constArg2 = Value::create("5");

        std::shared_ptr<Clause> testClause =
            Clause::create(Constants::PARENTST, constArg1, constArg2);

        REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
        REQUIRE(testClause->resolve(pkbRet).second->getHeaders() ==
                expectedTable->getHeaders());
        REQUIRE(testClause->resolve(pkbRet).second->getData() ==
                expectedTable->getData());
      }

      THEN("When ParentStClause resolves case ParentSt(4,9), it should return "
           "no matches") {
        Constants::ClauseResult expectedStatus =
            Constants::ClauseResult::NO_MATCH;
        std::shared_ptr<QpsTable> expectedTable = QpsTable::create();

        std::shared_ptr<Value> constArg1 = Value::create("4");
        std::shared_ptr<Value> constArg2 = Value::create("9");

        std::shared_ptr<Clause> testClause =
            Clause::create(Constants::PARENTST, constArg1, constArg2);

        REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
        REQUIRE(testClause->resolve(pkbRet).second->getHeaders() ==
                expectedTable->getHeaders());
        REQUIRE(testClause->resolve(pkbRet).second->getData() ==
                expectedTable->getData());
      }

      THEN("When ParentStClause resolves case ParentSt(2,s2), it should return "
           "the right results") {
        Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
        std::shared_ptr<QpsTable> expectedTable = QpsTable::create({"s2"});
        expectedTable->addRow({"3"});
        expectedTable->addRow({"4"});
        expectedTable->addRow({"5"});
        expectedTable->addRow({"6"});
        expectedTable->addRow({"7"});
        expectedTable->addRow({"8"});
        expectedTable->addRow({"9"});

        std::shared_ptr<Value> constArg1 = Value::create("2");
        std::shared_ptr<Synonym> synArg2 =
            Synonym::create(Constants::STMT, "s2");

        std::shared_ptr<Clause> testClause =
            Clause::create(Constants::PARENTST, constArg1, synArg2);

        REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
        REQUIRE(testClause->resolve(pkbRet).second->getHeaders() ==
                expectedTable->getHeaders());
        REQUIRE(testClause->resolve(pkbRet).second->getData() ==
                expectedTable->getData());
      }

      THEN("When ParentStClause resolves case ParentSt(1,s2), it should return "
           "no matches") {
        Constants::ClauseResult expectedStatus =
            Constants::ClauseResult::NO_MATCH;
        std::shared_ptr<QpsTable> expectedTable = QpsTable::create({"s2"});

        std::shared_ptr<Value> constArg1 = Value::create("1");
        std::shared_ptr<Synonym> synArg2 =
            Synonym::create(Constants::STMT, "s2");

        std::shared_ptr<Clause> testClause =
            Clause::create(Constants::PARENTST, constArg1, synArg2);

        REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
        REQUIRE(testClause->resolve(pkbRet).second->getHeaders() ==
                expectedTable->getHeaders());
        REQUIRE(testClause->resolve(pkbRet).second->getData() ==
                expectedTable->getData());
      }

      THEN("When ParentStClause resolves case ParentSt(s1,_), it should return "
           "the right results") {
        Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
        std::shared_ptr<QpsTable> expectedTable = QpsTable::create({"s1"});
        expectedTable->addRow({"2"});
        expectedTable->addRow({"4"});
        expectedTable->addRow({"8"});

        std::shared_ptr<Synonym> synArg1 =
            Synonym::create(Constants::STMT, "s1");
        std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

        std::shared_ptr<Clause> testClause =
            Clause::create(Constants::PARENTST, synArg1, wcArg2);

        REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
        REQUIRE(testClause->resolve(pkbRet).second->getHeaders() ==
                expectedTable->getHeaders());
        REQUIRE(testClause->resolve(pkbRet).second->getData() ==
                expectedTable->getData());
      }

      THEN("When ParentStClause resolves case ParentSt(a1,_), it should return "
           "no matches") {
        Constants::ClauseResult expectedStatus =
            Constants::ClauseResult::NO_MATCH;
        std::shared_ptr<QpsTable> expectedTable = QpsTable::create({"a1"});

        std::shared_ptr<Synonym> synArg1 =
            Synonym::create(Constants::ASSIGN, "a1");
        std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

        std::shared_ptr<Clause> testClause =
            Clause::create(Constants::PARENTST, synArg1, wcArg2);

        REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
        REQUIRE(testClause->resolve(pkbRet).second->getHeaders() ==
                expectedTable->getHeaders());
        REQUIRE(testClause->resolve(pkbRet).second->getData() ==
                expectedTable->getData());
      }

      THEN("When ParentStClause resolves case ParentSt(s1,6), it should return "
           "the right results") {
        Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
        std::shared_ptr<QpsTable> expectedTable = QpsTable::create({"s1"});
        expectedTable->addRow({"2"});
        expectedTable->addRow({"4"});

        std::shared_ptr<Synonym> synArg1 =
            Synonym::create(Constants::STMT, "s1");
        std::shared_ptr<Value> constArg2 = Value::create("6");

        std::shared_ptr<Clause> testClause =
            Clause::create(Constants::PARENTST, synArg1, constArg2);

        REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
        REQUIRE(testClause->resolve(pkbRet).second->getHeaders() ==
                expectedTable->getHeaders());
        REQUIRE(testClause->resolve(pkbRet).second->getData() ==
                expectedTable->getData());
      }

      THEN("When ParentStClause resolves case ParentSt(s1,1), it should return "
           "no match") {
        Constants::ClauseResult expectedStatus =
            Constants::ClauseResult::NO_MATCH;
        std::shared_ptr<QpsTable> expectedTable = QpsTable::create({"s1"});

        std::shared_ptr<Synonym> synArg1 =
            Synonym::create(Constants::STMT, "s1");
        std::shared_ptr<Value> constArg2 = Value::create("1");

        std::shared_ptr<Clause> testClause =
            Clause::create(Constants::PARENTST, synArg1, constArg2);

        REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
        REQUIRE(testClause->resolve(pkbRet).second->getHeaders() ==
                expectedTable->getHeaders());
        REQUIRE(testClause->resolve(pkbRet).second->getData() ==
                expectedTable->getData());
      }

      THEN("When ParentStClause resolves case ParentSt(w1,a2), it should "
           "return the right results") {
        Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
        std::shared_ptr<QpsTable> expectedTable =
            QpsTable::create({"w1", "a2"});
        expectedTable->addRow({"2", "3"});
        expectedTable->addRow({"2", "7"});
        expectedTable->addRow({"2", "9"});
        expectedTable->addRow({"8", "9"});

        std::shared_ptr<Synonym> synArg1 =
            Synonym::create(Constants::WHILE, "w1");
        std::shared_ptr<Synonym> synArg2 =
            Synonym::create(Constants::ASSIGN, "a2");

        std::shared_ptr<Clause> testClause =
            Clause::create(Constants::PARENTST, synArg1, synArg2);

        REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
        REQUIRE(testClause->resolve(pkbRet).second->getHeaders() ==
                expectedTable->getHeaders());
        REQUIRE(testClause->resolve(pkbRet).second->getData() ==
                expectedTable->getData());
      }

      THEN("When ParentStClause resolves case ParentSt(a1,s2), it should "
           "return no match") {
        Constants::ClauseResult expectedStatus =
            Constants::ClauseResult::NO_MATCH;
        std::shared_ptr<QpsTable> expectedTable =
            QpsTable::create({"a1", "s2"});

        std::shared_ptr<Synonym> synArg1 =
            Synonym::create(Constants::ASSIGN, "a1");
        std::shared_ptr<Synonym> synArg2 =
            Synonym::create(Constants::STMT, "s2");

        std::shared_ptr<Clause> testClause =
            Clause::create(Constants::PARENTST, synArg1, synArg2);

        REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
        REQUIRE(testClause->resolve(pkbRet).second->getHeaders() ==
                expectedTable->getHeaders());
        REQUIRE(testClause->resolve(pkbRet).second->getData() ==
                expectedTable->getData());
      }

      THEN("When ParentStClause resolves case ParentSt(s1,s1), it should "
           "return no match") {
        Constants::ClauseResult expectedStatus =
            Constants::ClauseResult::NO_MATCH;
        std::shared_ptr<QpsTable> expectedTable = QpsTable::create();

        std::shared_ptr<Synonym> synArg1 =
            Synonym::create(Constants::STMT, "s1");
        std::shared_ptr<Synonym> synArg2 =
            Synonym::create(Constants::STMT, "s1");

        std::shared_ptr<Clause> testClause =
            Clause::create(Constants::PARENTST, synArg1, synArg2);

        REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
        REQUIRE(testClause->resolve(pkbRet).second->getHeaders() ==
                expectedTable->getHeaders());
        REQUIRE(testClause->resolve(pkbRet).second->getData() ==
                expectedTable->getData());
      }
    }
  }
}