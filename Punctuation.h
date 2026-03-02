#ifndef PUNCTUATION_H
#define PUNCTUATION_H

#include "Token.h"
#include <unordered_map>
#include <string>
#include <string_view>

bool isPunc(char c);
TokenKind getKindOfPunctuation(std::string_view c);

#endif