#include <iostream>
#include <cstdlib>
#include <string>
#include <map>

void wrongArguments(char* argv[], const std::map<std::string, std::string>& passToLib)
{
    std::cerr << "Usage: " << argv[0] << " <pass-name> <bitcode-file-path>" << std::endl;
    std::cerr << std::endl << "Available passes:" << std::endl;

    for (const auto& [fst, snd] : passToLib)
        std::cerr << " " << fst << std::endl;

    exit(1);
}

void runPass(const std::string& passName, const std::string& bitcodeFilePath, const std::map<std::string, std::string>& passToLib)
{
    std::string optDir = std::string(LLVM_ROOT_DIR) + "/build/bin/opt";
    std::string libName = passToLib.find(passName)->second;

    const std::string command = optDir + " -load-pass-plugin " + std::string(LIB_DIR) + "/" + libName + " --passes=" + passName + " -disable-output " + bitcodeFilePath;

    std::cerr << "Running " << passName << "..." << std::endl << std::endl;
    int result = std::system(command.c_str());

    if (result != 0)
        std::cerr << std::endl << "Error: Failed to execute pass " << passName << std::endl;
    else
        std::cout << std::endl << "Pass " << passName << " executed successfully." << std::endl;
}


int main(int argc, char* argv[])
{
    std::map<std::string, std::string> passToLib;
    passToLib["1_functions"] = "lib1_Functions.so";
    passToLib["2_basic-blocks-count"] = "lib2_BasicBlocksCount.so";
    passToLib["3_instructions-in-bb"] = "lib3_InstructionsInBB.so";
    passToLib["4_opcodes"] = "lib4_Opcodes.so";
    passToLib["5_function-calls-count"] = "lib5_FunctionCallsCount.so";
    passToLib["6_add-to-sub"] = "6_AddToSub.so";

    if (argc != 3)
        wrongArguments(argv, passToLib);

    const std::string passName = argv[1];
    const std::string bitcodeFilePath = argv[2];

    if (passToLib.find(passName) == passToLib.end())
        wrongArguments(argv, passToLib);

    runPass(passName, bitcodeFilePath, passToLib);

    return 0;
}
