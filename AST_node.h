#ifndef AST_NODE_H
#define AST_NODE_H

#include <memory>
#include <string>
#include <utility>
#include "Token.h"

class AST_node
{
public:
    virtual ~AST_node() = default;
};

class AST_identifier : public AST_node
{
public:
    AST_identifier(Token token) : m_token(token) {};

protected:
    Token m_token;
};

class AST_exp : public AST_node
{
};

class AST_constant : public AST_exp
{
protected:
    int m_value;
};

class AST_statement : public AST_node
{
public:
    AST_statement(std::unique_ptr<AST_exp> exp) : m_exp(std::move(exp)) {}

protected:
    std::unique_ptr<AST_exp> m_exp;
};

class AST_function_definition : public AST_node
{
public:
    AST_function_definition(std::unique_ptr<AST_identifier> name, std::unique_ptr<AST_statement> body) : m_functionName(std::move(name)), m_functionBody(std::move(body)) {}

protected:
    std::unique_ptr<AST_identifier> m_functionName;
    std::unique_ptr<AST_statement> m_functionBody;
};

class AST_program : public AST_node
{
public:
    AST_program(std::unique_ptr<AST_function_definition> function) : m_functionDefinition(std::move(function))
    {
    }

protected:
    std::unique_ptr<AST_function_definition> m_functionDefinition;
};

class AST_int : public AST_exp
{
protected:
    Token m_constantToken;
};

#endif
