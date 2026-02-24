#include "Lexer.h"
#include <string_view>
#include <fstream>
#include "Keyword.h"

using namespace std;

Lexer::Lexer(const char *filepath)
{
    m_filepath = filepath;
    ifstream fileStream = ifstream(filepath);
    // seekg with end move the cursor to the end
    fileStream.seekg(0, std::ios::end);
    size_t fileSize = fileStream.tellg(); // tellg gives us the position of the cursor
    fileStream.seekg(0, std::ios::beg);   // reseting pos for later read, beg is relative to beginning

    string buffer(fileSize, '/0');
    fileStream.read(buffer.data(), fileSize);
}

void Lexer::Peak()
{
}