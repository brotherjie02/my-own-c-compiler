#ifndef ASTSTATEMENT_H
#define ASTSTATEMENT_H
#include "AST_node.h"

class AST_exp;

class AST_statement : public AST_node
{
public:
protected:
};

class AST_return : public AST_statement
{
public:
    AST_return(AST_exp *exp);
    ~AST_return();

protected:
    AST_exp *m_expression;
};

#endif