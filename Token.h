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
    Token(TokenKind kind, std::string_view text)
    {
        m_kind = kind;
        m_lexeme = text;
        m_length = text.size();
    }
    TokenKind m_kind;
    std::string_view m_lexeme;
    int m_length;
};