#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <stdio.h>
#include <iostream>
#include "ParserResponse.h"
#include "constants/Synonym.h"
#include "constants/Value.h"

class ValidatePatternResponse {
    private:
        std::shared_ptr<Synonym> assignSynonym;
        std::shared_ptr<Entity> entRef;
        std::shared_ptr<Entity> pattern;
    public: 
        void setAssignSyn(std::shared_ptr<Synonym> a) {
            this->assignSynonym = a;
        }
        void setEntRef(std::shared_ptr<Entity> e) {
            this->entRef = e;
        }
        void setPattern(std::shared_ptr<Entity> p) {
            this->pattern = p;
        }
        std::shared_ptr<Synonym> getAssignSyn() {
            return this->assignSynonym;
        }
        std::shared_ptr<Entity> getEntRef() {
            return this->entRef;
        }
        std::shared_ptr<Entity> getPattern() {
            return this->pattern;
        }
        bool isIncomplete() {
            return this->assignSynonym == nullptr || this->entRef == nullptr || this->pattern == nullptr; 
        }
};

class QueryParser {
    private:
        bool isValidIntegerString(const std::string& s);
        bool isValidNaming(const std::string& s);
        bool isValidDeclaration(std::vector<std::string> s,
            std::unordered_set<std::string>& declared_synonyms, 
            std::unordered_set<std::string>& assignment_synonyms);
        std::vector<std::shared_ptr<Synonym>> processDeclaration(std::vector<std::string> declaration, std::unordered_set<std::string> declared_synonyms);
        // static bool isValidSuchThatClause(vector<string> s);
        ValidatePatternResponse validatePatternClause(std::vector<std::string> s, std::unordered_set<std::string> assignment_synonyms, std::vector<std::shared_ptr<Synonym>> declarations);
        bool isValidEntRef(const std::string& s);
        bool isValidExpression(std::vector<std::string> s);
        // static bool isStmtRef(string s);
        std::string removeQuotations(const std::string& s);
        ParserResponse generateSyntaxErrorResponse();
        ParserResponse generateSemanticErrorResponse();

    public:
        ParserResponse parseQueryTokens(std::vector<std::string> tokens);
};