#include "Lexer.h"
#include <string_view>
#include <fstream>
#include <iostream>
#include "Keyword.h"
#include "Token.h"
#include "Punctuation.h"

using namespace std;

Lexer::Lexer(const char *filepath)
{
    m_filepath = filepath;
    ifstream fileStream = ifstream(filepath);
    // seekg with end move the cursor to the end
    fileStream.seekg(0, std::ios::end);
    size_t fileSize = fileStream.tellg(); // tellg gives us the position of the cursor
    fileStream.seekg(0, std::ios::beg);   // reseting pos for later read, beg is relative to beginning

    string buffer(fileSize, '\0');
    fileStream.read(buffer.data(), fileSize);
    m_buffer = buffer;
    m_state = LexerState::Default;
    m_fileSize = fileSize;
    m_pos = 0;
}

char Lexer::peak()
{
    if (m_pos >= m_fileSize)
    {
        return '\0';
    }
    return m_buffer[m_pos];
}

char Lexer::advance()
{
    m_pos++;
    char outputChar = m_buffer[m_pos];
    return outputChar;
}

Token Lexer::nextToken()
{
    char firstChar = peak();
    // peak to see what type
    if (firstChar == '\0')
    {
        return Token(Endoffile, '\0');
    }
    else if (isAlpha(firstChar) || firstChar == '_') // identifier
    {
        size_t tokenLength = 0;
        char curChar = peak();
        while (isAlpha(curChar) || isNum(curChar) || curChar == '_')
        {
            tokenLength++;
            curChar = advance();
        }
        string_view text(&m_buffer[m_pos], tokenLength);
        // keyword?
        TokenKind kind = GetKindOfIdentifier(text.data());

        if (kind != Kw_Invalid)
        {
            return Token(kind, text);
        }
        else
        {
            return Token(Identifier, text);
        }
    }
    else if (isNum(firstChar))
    {
        size_t tokenLength = 0;
        char curChar = peak();
        while (isNum(curChar))
        {
            tokenLength++;
            curChar = advance();
        }
        string_view text(&m_buffer[m_pos - tokenLength], tokenLength);
        return Token(Constant, text);
    }
    else if (isPunc(firstChar))
    {
        // since every punctuation is single length for now, no need to loop
        string_view text(&m_buffer[m_pos], 1);
        TokenKind kind = getKindOfPunctuation(text);
        return Token(kind, text);
    }
}

void Lexer::stripWhiteSpace()
{
    while (isWhiteSpace(peak()))
    {
        advance();
    }
}

bool Lexer::isAlpha(char c)
{
    if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
    {
        return true;
    }
    return false;
}

bool Lexer::isNum(char c)
{
    if (c >= '0' && c <= '9')
    {
        return true;
    }
    return false;
}

bool Lexer::isWhiteSpace(char c)
{
    if (c == ' ' || c == '\n')
    {
        return true;
    }
    return false;
}

void Lexer::makeTokenFromStart()
{
    while (m_pos < m_fileSize)
    {
        if (isWhiteSpace(peak()))
        {
            stripWhiteSpace();
        }
        else
        {
            // tidy, start to parse next token
            Token newToken = nextToken();
            m_tokens.push_back(newToken);
        }
    }
}

void Lexer::DEBUG_printAllTokens()
{
    for (int i = 0; i < m_tokens.size(); i++)
    {
        cout << "Kind: " << m_tokens[i].m_kind << " Text: " << m_tokens[i].m_lexeme << endl;
    }
}

int main(void)
{
    Lexer lexer = Lexer("test.c");
    lexer.makeTokenFromStart();
    lexer.DEBUG_printAllTokens();
    return 0;
}