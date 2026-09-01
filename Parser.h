#ifndef PARSER_H
#define PARSER_H

#include "AST_node.h"
#include "Token.h"
#include <vector>
#include <memory>

class Parser
{
public:
    Parser(std::vector<Token> &tokens);

private:
    std::unique_ptr<AST_statement> ParseStatement();
    std::unique_ptr<AST_program> ParseProgram();
    std::unique_ptr<AST_exp> ParseExpression();
    std::unique_ptr<AST_function_definition> ParseFunction();
    std::unique_ptr<AST_identifier> ParseIdentifier();
    std::unique_ptr<AST_int> ParseInt();

    Token Expects(TokenKind expected);
    int curIndex = 0;
    const std::vector<Token> &m_tokens;
};

#endif