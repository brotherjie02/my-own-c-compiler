#ifndef AST_NODE_H
#define AST_NODE_H

#include <memory>
#include <string>
#include <utility>

class AST_node
{
public:
    virtual ~AST_node() = default;
};

class AST_identifer : public AST_node
{
public:
    std::string name;
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
};

class AST_return : public AST_statement
{
public:
    explicit AST_return(std::unique_ptr<AST_exp> exp)
        : m_expression(std::move(exp))
    {
    }

protected:
    std::unique_ptr<AST_exp> m_expression;
};

/// @brief A function definition consists of a name and a statement body.
class AST_function_definition : public AST_node
{
protected:
    std::unique_ptr<AST_identifer> m_functionName;
    std::unique_ptr<AST_statement> m_functionBody;
};

/// @brief A program consists of a function definition.
class AST_program : public AST_node
{
protected:
    std::unique_ptr<AST_function_definition> m_functionDefinition;
};

#endif
