//
// Created by Jason on 2026/2/3.
//
#include <cstdlib>
#include <string>
#include <iostream>
#include <cstdio>
#include <filesystem>

int main(int argc, char **argv)
{
    std::string inputFileName = argv[1]; // first argument is always the input file
    std::filesystem::path inputPath(inputFileName);
    std::string baseName = inputPath.stem();
    inputPath = inputPath.parent_path();

    std::string preprocessedName = inputPath / ("PREPROCESSED_" + baseName + ".c");

    std::string command = "gcc -E -P " + inputFileName + " -o " + preprocessedName;

    if (std::system(command.c_str()) == 0)
    {
        // gcc commands usually return 0 on success
        std::cout << "Preprocessed Stage Success" << std::endl;
    }
    else
    {
        std::cout << "Preprocessed Stage Failed" << std::endl;
    }
    std::string asmName = inputPath / (baseName + ".s");

    command = "gcc -S " + preprocessedName + " -o " + asmName;
    if (std::system(command.c_str()) == 0)
    {
        std::cout << "Compiled Stage Success" << std::endl;
    }
    else
    {
        std::cout << "Compiled Stage Failed" << std::endl;
    }

    if (remove(preprocessedName.c_str()) == 0)
    {
        std::cout << "Removed Preprocessed Stage Success" << std::endl;
    }
    else
    {
        std::cout << "Removed Preprocessed Stage Failed" << std::endl;
    }

    std::string objectName = inputPath / baseName;

    command = "gcc " + asmName + " -o " + objectName;
    if (std::system(command.c_str()) == 0)
    {
        std::cout << "Assemble and Linking Stage Success" << std::endl;
    }
    else
    {
        std::cout << "Assemble and Linking Stage Failed" << std::endl;
    }
    if (remove(asmName.c_str()) == 0)
    {
        std::cout << "Removed Asm Stage Success" << std::endl;
    }
    else
    {
        std::cout << "Removed Asm Stage Failed" << std::endl;
    }

    return 0;
}
