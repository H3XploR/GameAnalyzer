// GameAnalyzer.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "Header.h"

// If compiling as 64-bit
#ifdef _M_X64
#pragma comment (lib, "detoursx64.lib")
#endif // _M_X64


// If compiling as 32-bit
#ifdef _M_IX86
#pragma comment (lib, "detoursx86.lib")
#endif // _M_IX86


const bool affiche_process_handle = 1;
const bool affiche_pid = 1;
const bool affiche_image_filename = 1;

std::string GetProcessName(const char* imageFileName)
{
    const char* processName = strrchr(imageFileName, '\\');
    return processName != nullptr ? processName + 1 : imageFileName;
}

std::string ToLower(std::string text)
{
    std::transform(text.begin(), text.end(), text.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return text;
}

bool ContainsIgnoreCase(const std::string& text, const std::string& search)
{
    return ToLower(text).find(ToLower(search)) != std::string::npos;
}



int main(int argc, char** argv)
{
    if (argc > 2) {
        std::cout << "Usage: GameAnalyzer.exe <process_name_part>" << std::endl;
        return 1;
    }

    bool filterByProcessName = argc == 2;
    std::string processNameArgument = filterByProcessName ? argv[1] : "";
    std::ostringstream output;
    DWORD lpidProcess[99999], lpcbNeeded;
    BOOL ret_enum_process = EnumProcesses(lpidProcess,
                                        sizeof(lpidProcess),
                                        &lpcbNeeded);

    if (ret_enum_process == FALSE) {
        std::cout << "EnumProcesses failed." << std::endl;
        return 1;
    }

    DWORD processCount = lpcbNeeded / sizeof(DWORD);
    for (DWORD i = 0; i < processCount; i++) {
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, lpidProcess[i]);
        if (hProcess != NULL) {
            char imageFileName[MAX_PATH] = {};
            DWORD lengthBuffer = MAX_PATH;
            BOOL hasImageFileName = QueryFullProcessImageNameA(hProcess, 0, imageFileName, &lengthBuffer);

            if (hasImageFileName == TRUE
                && affiche_image_filename == 1
                && (!filterByProcessName || ContainsIgnoreCase(GetProcessName(imageFileName), processNameArgument))) {
                if (affiche_pid == 1)
                    output << "pid: " << lpidProcess[i];
                if (affiche_process_handle == 1)
                    output << "-->" << hProcess;
                if (affiche_process_handle || affiche_pid)
                    output << "--->";
                output << imageFileName << std::endl;
                bool ret_analyze_process_handle = analyze_process_handle(hProcess);
            }
            CloseHandle(hProcess);
        }
    }

    std::cout << output.str();
}

