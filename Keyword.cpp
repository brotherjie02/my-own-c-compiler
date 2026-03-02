#include "Keyword.h"
#include <unordered_map>

using namespace std;

unordered_map<string_view, TokenKind> kwDict = {
    {"int", TokenKind::Kw_Int},
    {"return", TokenKind::Kw_Return},
    {"void", TokenKind::Kw_Void},
    {"main", TokenKind::Kw_Main}};

TokenKind GetKindOfIdentifier(string_view input)
{
    auto it = kwDict.find(input);
    if (it == kwDict.end())
    {
        return Kw_Invalid;
    }
    return it->second;
}