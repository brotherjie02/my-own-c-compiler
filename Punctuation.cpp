#include "Punctuation.h"

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