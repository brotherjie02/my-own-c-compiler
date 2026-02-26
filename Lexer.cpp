#include "Lexer.h"
#include <string_view>
#include <fstream>
#include <iostream>
#include "Keyword.h"
#include "Token.h"

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
    char outputChar = m_buffer[m_pos];
    m_pos++;
    return outputChar;
}

Token Lexer::nextToken()
{
    char currentChar = peak();
    // peak to see what type
    if (currentChar == '\0')
    {
        return Token(Endoffile, '\0');
    }
    else if (isAlpha(currentChar) || currentChar == '_')
    {
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

int main(void)
{
    Lexer lexer = Lexer("test.c");
}