#ifndef ASTIDENTIFIER_H
#define ASTIDENTIFIER_H
#include "AST_node.h"
#include <string>

class AST_identifer : public AST_node
{
public:
    std::string name;
};

#endif