#ifndef ASTEXP_H
#define ASTEXP_H
#include "AST_node.h"

class AST_exp : public AST_node
{
};

class AST_constant : public AST_exp
{
protected:
    int m_value;
};

#endif