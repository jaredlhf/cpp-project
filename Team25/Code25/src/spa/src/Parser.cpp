#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Parser.h"


bool Parser::isValidName(string variable) {
    if (!((variable[0] >= 'a' && variable[0] <= 'z')
          || (variable[0] >= 'A' && variable[0] <= 'Z')
          || variable[0] == '_'))
        return false;
    for (int i = 1; i < variable.length(); i++) {
        if (!((variable[i] >= 'a' && variable[i] <= 'z')
              || (variable[i] >= 'A' && variable[i] <= 'Z')
              || (variable[i] >= '0' && variable[i] <= '9')
              || variable[i] == '_'))
            return false;
    }
    return true;
}

string Parser::getNextToken() {
    string next = this->tokens.front();
    tokens.erase(tokens.begin());
    return next;
}

void Parser::expect(const Token &expectedToken) {
    string next = getNextToken();
    if (expectedToken.isValidToken(next)) {
        std::cout << "error: unexpected token found" << std::endl;
        throw 1;
    }
}

void Parser::parseProgram(vector<string> tokenList) {
    this->tokens = tokenList;

    do {
        if (tokens.empty()) {
            std::cout << "error: no procedures found" << std::endl;
            throw 1;
        } else {
            parseProcedure();
        }
    } while (!tokens.empty());
}


ProcedureNode Parser::parseProcedure() {
    expect(Procedure());
    expect(Name());
    expect(LeftBrace());
    StmtLstNode stmtLst = parseStmtLst();
    ProcedureNode node = ProcedureNode(stmtLst);
    expect(RightBrace());
    return node;
}

StmtLstNode Parser::parseStmtLst() {
    vector<StmtNode> StmtLsts;
    do {
        StmtNode sn = parseStmt();
        StmtLsts.push_back(sn);
    } while(!RightBrace().isValidToken(tokens.front()));
    StmtLstNode node = StmtLstNode(StmtLsts);
    return node;
}

