#pragma once
#include <string>

enum TokenKind
{
    // special
    Invalid,
    Endoffile,

    // identifers and literals
    Identifier,
    Constant,

    // Punctuations
    LParen,
    RParen,
    LBrace,
    RBrace,
    Semicolon,

    // Keywords
    Kw_Int,
    Kw_Void,
    Kw_Return,
    Kw_Invalid // used for finding keyword, and not finding correspondance
};

struct Token
{
    Token()
    {
    }
    TokenKind m_kind;
    std::string m_lexeme;
    int m_length;
};