//
// Created by Jason on 2026/2/3.
//
#include <cstdlib>
#include <string>
#include <iostream>
#include <cstdio>
#include <filesystem>
#include <vector>
#include "Lexer.h"
#include "Token.h"

enum Stage
{
    FULL,
    STOPAFTERLEXER,
    STOPAFTERPARSER,
    STOPAFTERCODEGEN
};

void FailCleanUp(std::vector<std::string> &generatedFiles)
{
    for (auto file : generatedFiles)
    {
        remove(file.c_str());
    }
}

static bool IsStageFlag(const std::string &s)
{
    return s == "--lex" || s == "--parse" || s == "--codegen";
}

static Stage StageFromFlag(const std::string &s)
{
    if (s == "--lex")
        return STOPAFTERLEXER;
    if (s == "--parse")
        return STOPAFTERPARSER;
    if (s == "--codegen")
        return STOPAFTERCODEGEN;
    return FULL;
}

static std::string QuoteIfNeeded(const std::string &s)
{
    // crude but effective for paths with spaces
    if (s.find(' ') != std::string::npos)
        return "\"" + s + "\"";
    return s;
}

void RunLex(std::string preprocessedFileName)
{
    Lexer lexer(preprocessedFileName.data());
    lexer.makeTokenFromStart();
    lexer.DEBUG_printAllTokens();
}

int main(int argc, char **argv)
{
    if (argc < 2 || argc > 3)
    {
        std::cerr << "usage: CompilerDriver [--lex|--parse|--codegen] <input.c>\n";
        return 1;
    }

    Stage stageFlag = FULL;
    std::string inputFileName;

    if (argc == 2)
    {
        inputFileName = argv[1];
    }
    else // argc == 3
    {
        std::string a1 = argv[1];
        std::string a2 = argv[2];

        if (IsStageFlag(a1) && !IsStageFlag(a2))
        {
            stageFlag = StageFromFlag(a1);
            inputFileName = a2;
        }
        else if (!IsStageFlag(a1) && IsStageFlag(a2))
        {
            stageFlag = StageFromFlag(a2);
            inputFileName = a1;
        }
        else
        {
            std::cerr << "error: expected one stage flag and one input file\n";
            return 1;
        }
    }
    std::vector<std::string> generatedFiles;

    std::filesystem::path inputPath(inputFileName);
    std::string baseName = inputPath.stem();
    inputPath = inputPath.parent_path();

    // PREPROCESSING
    std::string preprocessedName = inputPath / ("PREPROCESSED_" + baseName + ".c");

    std::string command = "gcc -E -P " + inputFileName + " -o " + preprocessedName;

    if (std::system(command.c_str()) == 0)
    {
        // gcc commands usually return 0 on success
        std::cout << "Preprocessed Stage Success" << std::endl;
        generatedFiles.push_back(preprocessedName);
    }
    else
    {
        std::cout << "Preprocessed Stage Failed" << std::endl;
    }

    // LEXER
    try
    {
        RunLex(preprocessedName);
    }
    catch (const std::logic_error &e)
    {
        FailCleanUp(generatedFiles);
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    if (stageFlag == STOPAFTERLEXER)
    {
        FailCleanUp(generatedFiles);
        return 0;
    }

    // COMPILATION
    std::string asmName = inputPath / (baseName + ".s");
    command = "gcc -S " + preprocessedName + " -o " + asmName;
    if (std::system(command.c_str()) == 0)
    {
        std::cout << "Compiled Stage Success" << std::endl;
        generatedFiles.push_back(asmName);
    }
    else
    {
        std::cout << "Compiled Stage Failed" << std::endl;
        FailCleanUp(generatedFiles);
        return 1;
    }

    // REMOVING PREPROCESSED FILE
    if (remove(preprocessedName.c_str()) == 0)
    {
        std::cout << "Removed Preprocessed Stage Success" << std::endl;
        generatedFiles.erase(std::find(generatedFiles.begin(), generatedFiles.end(), preprocessedName));
    }
    else
    {
        std::cout << "Removed Preprocessed Stage Failed" << std::endl;
    }

    // ASSEMBLE AND LINKING STAGE
    std::string objectName = inputPath / baseName;

    command = "gcc " + asmName + " -o " + objectName;
    if (std::system(command.c_str()) == 0)
    {
        std::cout << "Assemble and Linking Stage Success" << std::endl;
    }
    else
    {
        FailCleanUp(generatedFiles);
        std::cout << "Assemble and Linking Stage Failed" << std::endl;
        return 1;
    }

    // REMOVING ASM FILE
    if (remove(asmName.c_str()) == 0)
    {
        std::cout << "Removed Asm Stage Success" << std::endl;
        generatedFiles.erase(std::find(generatedFiles.begin(), generatedFiles.end(), asmName));
    }
    else
    {
        std::cout << "Removed Asm Stage Failed" << std::endl;
    }

    return 0;
}