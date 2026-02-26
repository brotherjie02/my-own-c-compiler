#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class Token;

enum LexerState
{
    P_Identifier,
    P_Constant,
    Default
};

class Lexer
{
public:
    Lexer();
    Lexer(const char *filepath);
    char peak();    // look at next character without moving
    char advance(); // consume and move next character
    Token nextToken();

private:
    bool isAlpha(char c);
    bool isNum(char c);

    std::vector<Token> m_tokens;
    const char *m_filepath;
    std::string m_buffer;
    int m_fileSize;
    LexerState m_state;
    size_t m_pos;
};