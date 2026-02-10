//
// Created by Jason on 2026/2/3.
//
#include <cstdlib>
#include <string>
#include <iostream>
#include <cstdio>
#include <filesystem>
#include <vector>

void FailCleanUp(std::vector<std::string> &generatedFiles)
{
    for (auto file : generatedFiles)
    {
        remove(file.c_str());
    }
}

int main(int argc, char **argv)
{
    std::string inputFileName = argv[1]; // first argument is always the input file
    for (int i = 2; i < argc; i++)
    {
        std::string flag = argv[i];
        if (flag == "--lex")
        {
        }
        else if (flag == "parse")
        {
        }
        else if (flag == "codegen")
        {
        }
        else if (flag == "-S")
        {
        }
        else
        {
            std::cout << "Invalid Flag Provided" << std::endl;
            return 1;
        }
    }
    std::vector<std::string> generatedFiles;

    std::filesystem::path inputPath(inputFileName);
    std::string baseName = inputPath.stem();
    inputPath = inputPath.parent_path();

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

    if (remove(preprocessedName.c_str()) == 0)
    {
        std::cout << "Removed Preprocessed Stage Success" << std::endl;
        generatedFiles.erase(std::find(generatedFiles.begin(), generatedFiles.end(), preprocessedName));
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
        FailCleanUp(generatedFiles);
        std::cout << "Assemble and Linking Stage Failed" << std::endl;
        return 1;
    }
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
