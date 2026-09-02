#include "Parser.h"
#include "Keyword.h"

Parser::Parser(const std::vector<Token> &tokens) : m_tokens(tokens)
{
}

std::unique_ptr<AST_statement> Parser::ParseStatement()
{
    Expects(Kw_Return);
    std::unique_ptr<AST_statement> result = std::make_unique<AST_statement>(ParseExpression());
    Expects(Semicolon);
    return result;
}

std::unique_ptr<AST_program> Parser::ParseProgram()
{
    return std::make_unique<AST_program>(ParseFunction());
}

std::unique_ptr<AST_exp> Parser::ParseExpression()
{
    return ParseInt();
}

std::unique_ptr<AST_function_definition> Parser::ParseFunction()
{
    Expects(Kw_Int);
    std::unique_ptr<AST_identifier> name = ParseIdentifier();
    Expects(LParen);
    Expects(Kw_Void);
    Expects(RParen);
    Expects(LBrace);
    std::unique_ptr<AST_statement> body = ParseStatement();
    Expects(RBrace);
    return std::make_unique<AST_function_definition>(std::move(name), std::move(body));
}

std::unique_ptr<AST_int> Parser::ParseInt()
{
    return std::make_unique<AST_int>(Expects(Constant));
}

std::unique_ptr<AST_identifier> Parser::ParseIdentifier()
{
    Token identifier = Expects(Identifier);
    return std::make_unique<AST_identifier>(identifier);
}

/// @brief This function takes in a token and see if the token type is what we want
/// if not we throw an error
/// @param expected TokenKind
/// @param actual Token
/// @return
Token Parser::Expects(TokenKind expected)
{
    Token actual = m_tokens[curIndex];
    if (actual.m_kind != expected)
    {
        throw std::logic_error("Syntax Error");
        return actual;
    }
    curIndex++; // consumes the current token
    return actual;
}

Token Parser::Peek(int offset)
{
    int requestedIndex = curIndex + offset;
    if (requestedIndex >= m_tokens.size() || requestedIndex < 0)
    {
        return Token(Invalid);
    }
    return m_tokens[curIndex + offset];
}