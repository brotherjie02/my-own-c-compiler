#pragma once
#include "Token.h"
#include <string_view>

TokenKind GetKindOfIdentifier(std::string_view input);