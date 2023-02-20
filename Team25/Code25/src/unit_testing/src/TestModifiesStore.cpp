#include "PKB/ModifiesStore.h"

#include "catch.hpp"

SCENARIO("Populating modifies store") {
	GIVEN("New instance of modifies store") {
		ModifiesStore modStore;

		THEN("It should start empty") {
			REQUIRE(modStore.getAllStmt().size() == 0);
			REQUIRE(modStore.getAllVar().size() == 0);
		}

		WHEN("One modifies is added") {
			modStore.add(1, "x");

			THEN("Statement should be mapped to variable") {
				REQUIRE(modStore.getStmt("x") == std::unordered_set<int>({ 1 }));
				REQUIRE(modStore.getVar(1) == "x");
			}

			WHEN("Duplicate modifies is added") {
				modStore.add(1, "x");

				THEN("Modifies store should remain the same") {
					REQUIRE(modStore.getStmt("x") == std::unordered_set<int>({ 1 }));
					REQUIRE(modStore.getVar(1) == "x");
				}
			}
		}

		WHEN("Three modifies are added") {
			modStore.add(1, "x");
			modStore.add(2, "x");
			modStore.add(3, "y");

			THEN("There should be 3 statements and 2 variables") {
				REQUIRE(modStore.getAllStmt() == std::unordered_set<int>({ 1, 2, 3 }));
				REQUIRE(modStore.getAllVar() == std::unordered_set<std::string>({ "x", "y"}));
			}

			THEN("Statements should be mapped to variables correctly") {
				REQUIRE(modStore.getStmt("x") == std::unordered_set<int>({1, 2}));
				REQUIRE(modStore.getStmt("y") == std::unordered_set<int>({ 3 }));
				REQUIRE(modStore.getVar(1) == "x");
				REQUIRE(modStore.getVar(2) == "x");
				REQUIRE(modStore.getVar(3) == "y");
			}
		}
	}
}

