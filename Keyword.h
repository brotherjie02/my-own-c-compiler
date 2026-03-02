#ifndef TOKEN_H
#define TOKEN_H
#include "Token.h"
#include <string_view>

TokenKind GetKindOfIdentifier(std::string_view input);
#endif TOKEN_H