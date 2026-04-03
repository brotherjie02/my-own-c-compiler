#ifndef ASTPROGRAM_H
#define ASTPROGRAM_H
#include "AST_node.h"
#include "AST_identifier.h"
#include "AST_statement.h"
#include <memory>

/// @brief A program consists of a function definition
class AST_program : public AST_node
{
protected:
    std::unique_ptr<AST_function_definition> m_functionDefinition;
};

/// @brief A function definition consists of a name and a statement body
class AST_function_definition : public AST_node
{
protected:
    std::unique_ptr<AST_identifer> m_functionName;
    std::unique_ptr<AST_statement> m_functionBody;
};

#endif