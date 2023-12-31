#include "catch.hpp"
#include "QPS/Qps.h"

SCENARIO("Integration testing between PKB and QPS components") {
	GIVEN("The initialization and population of the PKB related classes") {
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
        CallsStarStore cstars;
        PrintAttribute prAtt;
        ReadAttribute readAtt;
        CallAttribute callAtt;
		NextStore next;
		CFGStore cfg;
		ContainCallsStore concall;

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
		std::shared_ptr<UsesStore> usesPointer = std::make_shared<UsesStore>(uses);
        std::shared_ptr<UsesProcStore> uprocsPointer = std::make_shared<UsesProcStore>(uprocs);
        std::shared_ptr<CallsStore> callsPointer = std::make_shared<CallsStore>(calls);
        std::shared_ptr<CallsStarStore> cstarsPointer = std::make_shared<CallsStarStore>(cstars);
        std::shared_ptr<PrintAttribute> printAttrStorage = std::make_shared<PrintAttribute>(prAtt);
        std::shared_ptr<ReadAttribute> readAttrStorage = std::make_shared<ReadAttribute>(readAtt);
        std::shared_ptr<CallAttribute> callAttrStorage = std::make_shared<CallAttribute>(callAtt);
		std::shared_ptr<NextStore> nextPointer = std::make_shared<NextStore>(next);
		std::shared_ptr<CFGStore> cfgPointer = std::make_shared<CFGStore>(cfg);
		std::shared_ptr<ContainCallsStore> concallPointer = std::make_shared<ContainCallsStore>(concall);

        // Populating variables appearing in the SIMPLE program
		vsPointer->addVar("w");
		vsPointer->addVar("x");
		vsPointer->addVar("y");
		vsPointer->addVar("z");

		// Populating constants appearing in the SIMPLE program
		csPointer->addConst(123);
		csPointer->addConst(456);
		csPointer->addConst(789);

		// Populating procedures appearing in the SIMPLE program
		psPointer->addProc("main", 1);
		psPointer->addProc("factorial", 1);
		psPointer->addProc("beta", 1);

		// Populating statements appearing in the SIMPLE program
		ssPointer->addStmt(Constants::ASSIGN, 1);
		ssPointer->addStmt(Constants::WHILE, 2);
		ssPointer->addStmt(Constants::ASSIGN, 3);
		ssPointer->addStmt(Constants::IF, 4);
		ssPointer->addStmt(Constants::READ, 5);
		ssPointer->addStmt(Constants::PRINT, 6);
		ssPointer->addStmt(Constants::ASSIGN, 7);
		ssPointer->addStmt(Constants::WHILE, 8);
		ssPointer->addStmt(Constants::ASSIGN, 9);

		// Populating followsSt relationship in SIMPLE program
		fstarsPointer->addFollowsStar(1, { 2 });
		fstarsPointer->addFollowsStar(3, { 4, 8 });
		fstarsPointer->addFollowsStar(4, { 8 });
		fstarsPointer->addFollowsStar(5, { 6, 7 });
		fstarsPointer->addFollowsStar(6, { 7 });

		// Populating follows relationship in SIMPLE program
		fsPointer->addFollows(1, 2);
		fsPointer->addFollows(3, 4);
		fsPointer->addFollows(4, 8);
		fsPointer->addFollows(5, 6);
		fsPointer->addFollows(6, 7);

		// Populating parentSt relationship in SIMPLE program
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

		// Populating parent relationship in SIMPLE program
		parentsPointer->addParent(2, 3);
		parentsPointer->addParent(2, 4);
		parentsPointer->addParent(2, 8);
		parentsPointer->addParent(4, 5);
		parentsPointer->addParent(4, 6);
		parentsPointer->addParent(4, 7);
		parentsPointer->addParent(8, 9);

		// Populating Modifies relationship in SIMPLE program
		msPointer->addModifies(1, "x");
		msPointer->addModifies(3, "w");
		msPointer->addModifies(5, "y");
		msPointer->addModifies(7, "x");
		msPointer->addModifies(9, "x");

		// Populating Uses relationship in SIMPLE program
		usesPointer->addUses(1, "y");
		usesPointer->addUses(3, "x");
		usesPointer->addUses(6, "x");
		usesPointer->addUses(7, "x");
		usesPointer->addUses(9, "x");

		// Populating Patterns in SIMPLE program
		pattsPointer->addAssignLhs("x", 1);
		pattsPointer->addAssignRhs(1, "y+1");
		pattsPointer->addAssignLhs("w", 3);
		pattsPointer->addAssignRhs(3, "x+1");
		pattsPointer->addAssignLhs("x", 7);
		pattsPointer->addAssignRhs(7, "x+1");
		pattsPointer->addAssignLhs("x", 9);
		pattsPointer->addAssignRhs(9, "x+1");

		// PKB class that interacts with the QPS class
		PkbRetriever pkbRet(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, usesPointer, callsPointer, cstarsPointer, printAttrStorage, readAttrStorage, callAttrStorage, nextPointer, cfgPointer, concallPointer);

		WHEN("The QPS object is instantiated and interacts with the PKB	") {
			Qps qps(std::make_shared<PkbRetriever>(pkbRet));

			THEN("For follows* query, the right result is returned") {
				list<string> expected = { "1", "3" };
				list<string> res;

				string query = "assign a1; stmt s2; Select a1 such that Follows*(a1, s2)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For parent* query, the right result is returned") {
				list<string> expected = { "2", "8" };
				list<string> res;

				string query = "while w1; Select w1 such that Parent*(2, _)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For empty parent* query, the no result is returned") {
				list<string> expected = {};
				list<string> res;

				string query = "while w1; Select w1 such that Parent*(1, _)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For parent query, the right result is returned") {
				list<string> expected = { "4" };
				list<string> res;

				string query = "if ifs; Select ifs such that Parent(_, 9)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For follows query, the right result is returned") {
				list<string> expected = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
				list<string> res;

				string query = "stmt stmt; Select stmt such that Follows(_, _)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For uses query, the right result is returned") {
				list<string> expected = { "3", "4", "5", "6", "7", "8", "9" };
				list<string> res;

				string query = "stmt s1; Select s1 such that Parent(_, s1)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For follows* query in the form (s1, _), the right result is returned") {
				list<string> expected = { "1", "3", "4", "5", "6" };
				list<string> res;

				string query = "stmt s1; Select s1 such that Follows*(s1, _)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For modifies query in the form (s1, 'y'), the right result is returned") {
				list<string> expected = { "5" };
				list<string> res;

				string query = "read rd1; Select rd1 such that Modifies(rd1, \"y\")";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For uses query in the form (1, 'y'), the right result is returned") {
				list<string> expected = { "6" };
				list<string> res;

				string query = "print pn1; Select pn1 such that Uses(1, \"y\")";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For follows query in the form (1, s2), the right result is returned") {
				list<string> expected = { "2" };
				list<string> res;

				string query = "stmt s2; Select s2 such that Follows(1, s2)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For pattern query in the form (_, 'x'), the right result is returned") {
				list<string> expected = { "3", "7", "9" };
				list<string> res;

				string query = "assign a1; stmt s2; Select a1 pattern a1 (_, _\"x\"_)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For pattern query in the form (_, _), the right result is returned") {
				list<string> expected = { "1", "3", "7", "9" };
				list<string> res;

				string query = "assign a1; stmt s2; Select a1 pattern a1 (_, _)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For pattern query in the form (v1, _), the right result is returned") {
				list<string> expected = { "w", "x" };
				list<string> res;

				string query = "assign a1; variable v1; Select v1 pattern a1 (v1, _)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For pattern query in the form (v1, _'y'_), the right result is returned") {
				list<string> expected = { "x" };
				list<string> res;

				string query = "assign a1; variable v1; Select v1 pattern a1 (v1, _\"y\"_)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For pattern query in the form ('x', _), the right result is returned") {
				list<string> expected = { "1", "7", "9" };
				list<string> res;

				string query = "assign a1; variable v1; Select a1 pattern a1 (\"x\", _)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For pattern query in the form ('x', _'y'_), the right result is returned") {
				list<string> expected = { "1" };
				list<string> res;

				string query = "assign a1; variable v1; Select a1 pattern a1 (\"x\", _\"y\"_)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For pattern query with var syn in pattern clause, the right result is returned") {
				list<string> expected = { "3", "7", "9" };
				list<string> res;

				string query = "assign a1; variable v1; Select a1 pattern a1 (v1, _\"x\"_)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For combined query, the right result is returned") {
				list<string> expected = { "w", "x" };
				list<string> res;

				string query = "assign a1; variable v1; Select v1 such that Parent(2,3) pattern a1 (v1, _)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For combined query with 1 overlapping synonym, the right result is returned") {
				list<string> expected = { "y" };
				list<string> res;

				string query = "assign a1; variable v1; stmt s1; Select v1 such that Uses(a1,v1) pattern a1 (_,_\"y\"_)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}
		}
	}
}