#include "AST_statement.h"
#include "AST_exp.h"

AST_return::AST_return(AST_exp *exp)
{
    m_expression = exp;
}