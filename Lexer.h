#pragma once
#include <string>
#include <unordered_map>
#include "Token.h"

class Lexer
{
public:
    Lexer();
    Lexer(const char *filepath);
    void Peak();

private:
    const char *m_filepath;
    std::string m_buffer;
};