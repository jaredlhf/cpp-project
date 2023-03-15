#ifndef SPA_SPCONSTANTS_H
#define SPA_SPCONSTANTS_H

namespace SPConstants {
const int INVALID_LINE_NO = -1;
const int PROCEDURE = -2;

const std::string ASSIGN_TYPE = "assign";
const std::string READ_TYPE = "read";
const std::string PRINT_TYPE = "print";
const std::string WHILE_TYPE = "while";
const std::string IF_TYPE = "if";
const std::string CALL_TYPE = "call";

const std::string EQUAL_TOKEN = "=";

const char TAB = '\t';
const char NEWLINE = '\n';
const char SPACE = ' ';
const char RIGHT_BRACE = '{';
const char LEFT_BRACE = '}';
const char RIGHT_BRACKET = '(';
const char LEFT_BRACKET = ')';
const char SEMICOLON = ';';
const char PLUS = '+';
const char MINUS = '-';
const char TIMES = '*';
const char DIVIDE = '/';
const char MODULO = '%';
const char EQUALS = '=';
const char MORE_THAN = '>';
const char LESS_THAN = '<';
const char NOT = '!';
const char SINGLE_AND = '&';
const char SINGLE_OR = '|';

} // namespace SPConstants

#endif
