#include "Punctuation.h"

std::unordered_map<std::string_view, TokenKind> puncList = {
    {"(", TokenKind::LParen},
    {")", TokenKind::RParen},
    {"{", TokenKind::LBrace},
    {"}", TokenKind::RBrace},
    {";", TokenKind::Semicolon}};

bool isPunc(char c)
{
    std::string string_c(1, c);
    return puncList.count(string_c) != 0;
}

TokenKind getKindOfPunctuation(std::string_view punctuation)
{
    if (puncList.count(punctuation) != 0)
    {
        return puncList[punctuation];
    }
    else
    {
        return Invalid;
    }
}