#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <stdio.h>
#include <iostream>
#include "../constants/Constants.h"
#include "../constants/Synonym.h"
#include "../constants/Wildcard.h"
#include "../constants/Value.h"
#include "AttrUtils.h"
#include "../../SP/ExpressionParser.h"

class ParserUtils {
    public:
        static bool isValidIntegerString(const std::string& s);
        static bool isValidNaming(const std::string& s);
        static bool isDesignEntityToken(const std::string& s);
        static bool isRelRefToken(const std::string& s);
        static bool isValidExpression(const std::string& s);
        static bool isSyntaxError(std::shared_ptr<Entity> e);
        static bool isSemanticError(std::shared_ptr<Entity> e);
        static bool isExpectedSynonym(std::shared_ptr<Entity> e, const std::string& s);
        static std::string removeQuotations(const std::string& s);
        static std::shared_ptr<Entity> getValidEntRef(const std::string& s, const std::vector<std::shared_ptr<Synonym>>& declarations);
        static std::shared_ptr<Entity> getValidProcRef(const std::string& s, const std::vector<std::shared_ptr<Synonym>>& declarations);
        static std::shared_ptr<Entity> getValidStmtRef(const std::string& s, const std::vector<std::shared_ptr<Synonym>>& declarations);
        static std::shared_ptr<Synonym> getValidAttrRef(const std::string& s, const std::vector<std::shared_ptr<Synonym>>& declarations);
        static std::shared_ptr<Entity> getValidWithRef(const std::string& s, const std::vector<std::shared_ptr<Synonym>>& declarations);
        static std::shared_ptr<Synonym> getValidDeclaration(const std::string& s, const std::vector<std::shared_ptr<Synonym>>& declarations);
};