#ifndef ASTSTATEMENT_H
#define ASTSTATEMENT_H
#include "AST_node.h"
#include <memory>

class AST_exp;

class AST_statement : public AST_node
{
};

class AST_return : public AST_statement
{
public:
    AST_return(std::unique_ptr<AST_exp> exp)
    {
        m_expression = std::move(exp);
    }

protected:
    std::unique_ptr<AST_exp> m_expression;
};

#endif