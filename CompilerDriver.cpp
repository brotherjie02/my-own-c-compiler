//
// Created by 林家陞 on 2026/2/3.
//
#include <cstdlib>
#include <string>
#include <iostream>
#include <cstdio>

int main(int argc, char **argv)
{
    std::string inputFileName = argv[1]; // first argument is always the input file
    // Strip extension
    std::string baseName = inputFileName;
    size_t dot = baseName.find_last_of('.');
    if (dot != std::string::npos)
    {
        baseName = baseName.substr(0, dot);
    }

    std::string command = "gcc -E -P " + inputFileName + " -o PREPROCESSED_" + inputFileName;

    if (std::system(command.c_str()) == 0)
    {
        // gcc commands usually return 0 on success
        std::cout << "Preprocessed Stage Success" << std::endl;
    }
    else
    {
        std::cout << "Preprocessed Stage Failed" << std::endl;
    }

    std::string preName = "PREPROCESSED_" + inputFileName;

    command = "gcc -S PREPROCESSED_" + inputFileName + " -o " + baseName + ".s";
    if (std::system(command.c_str()) == 0)
    {
        std::cout << "Compiled Stage Success" << std::endl;
    }
    else
    {
        std::cout << "Compiled Stage Failed" << std::endl;
    }

    if (remove(preName.c_str()) == 0)
    {
        std::cout << "Removed Preprocessed Stage Success" << std::endl;
    }
    else
    {
        std::cout << "Removed Preprocessed Stage Failed" << std::endl;
    }

    command = "gcc " + baseName + ".s -o " + baseName;
    if (std::system(command.c_str()) == 0)
    {
        std::cout << "Assemble and Linking Stage Success" << std::endl;
    }
    else
    {
        std::cout << "Assemble and Linking Stage Failed" << std::endl;
    }
    std::string asmFileName = baseName + ".s";
    if (remove(asmFileName.c_str()) == 0)
    {
        std::cout << "Removed Preprocessed Stage Success" << std::endl;
    }
    else
    {
        std::cout << "Removed Preprocessed Stage Failed" << std::endl;
    }

    return 0;
}