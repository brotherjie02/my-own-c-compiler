#ifndef ASTASM_H
#define ASTASM_H

class AST_asm
{
public:
    virtual ~AST_asm() = default;
    virtual void print(int indent) = 0;
};

#endif ASTASM_H