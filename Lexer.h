#pragma once
#include <string>

enum Kind
{
    IDENTIFIER,
    CONSTANT,
    PUNCTUATION,
    ENDOFFILE,

};

struct Token
{
    Token();
};

class Lexer
{
public:
    Lexer();
    Lexer(const char *filepath);

private:
    const char *m_filepath;
    std::string m_buffer;
};