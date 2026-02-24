#include "Keyword.h"
#include <unordered_map>

using namespace std;

unordered_map<string_view, TokenKind> kwDict = {
    {"int", TokenKind::Kw_Int},
    {"return", TokenKind::Kw_Return},
    {"void", TokenKind::Kw_Void},
    {"(", TokenKind::LParen},
    {")", TokenKind::RParen},
    {"{", TokenKind::LBrace},
    {"}", TokenKind::RBrace},
    {";", TokenKind::Semicolon}};

TokenKind GetKindOfIdentifier(string_view input)
{
    auto it = kwDict.find(input);
    if (it == kwDict.end())
    {
        return Kw_Invalid;
    }
    return it->second;
}