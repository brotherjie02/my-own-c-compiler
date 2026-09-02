#ifndef AST_NODE_H
#define AST_NODE_H

#include <memory>
#include <string>
#include <utility>
#include "Token.h"
#include <iostream>

class AST_node
{
public:
    virtual ~AST_node() = default;
    virtual void print(int indent) = 0;
};

class AST_identifier : public AST_node
{
public:
    AST_identifier(Token token) : m_token(token) {};
    std::string_view GetLexeme()
    {
        return m_token.m_lexeme;
    }
    void print(int indent) override
    {
        std::cout << GetLexeme();
    }

protected:
    Token m_token;
};

class AST_exp : public AST_node
{
};

class AST_statement : public AST_node
{
public:
    AST_statement(std::unique_ptr<AST_exp> exp) : m_exp(std::move(exp)) {}
    void print(int indent) override
    {
        m_exp->print(indent);
    }

protected:
    std::unique_ptr<AST_exp> m_exp;
};

class AST_function_definition : public AST_node
{
public:
    AST_function_definition(std::unique_ptr<AST_identifier> name, std::unique_ptr<AST_statement> body) : m_functionName(std::move(name)), m_functionBody(std::move(body)) {}

    void print(int indent) override
    {
        std::cout << std::string(indent, ' ') << "Function(" << std::endl;
        indent++;
        std::cout << std::string(indent, ' ') << "name=" << m_functionName->GetLexeme() << "," << std::endl;
        std::cout << std::string(indent, ' ') << "body=Return(\n";
        indent++;
        m_functionBody->print(indent);
        indent--;
        std::cout << std::string(indent, ' ') << ")" << std::endl;
    }

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
    void print(int indent) override
    {
        std::cout << std::string(indent, '   ') << "Program(" << std::endl;
        indent++;
        m_functionDefinition->print(indent);
        std::cout << std::string(indent, '   ') << ")" << std::endl;
    }

protected:
    std::unique_ptr<AST_function_definition> m_functionDefinition;
};

class AST_int : public AST_exp
{
public:
    AST_int(Token token) : m_constantToken(token)
    {
    }

    void print(int indent) override
    {
        std::cout << std::string(indent, ' ') << "Constant(" << m_constantToken.m_lexeme << ")";
    }

protected:
    Token m_constantToken;
};

#endif
