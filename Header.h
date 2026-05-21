#pragma once
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <sstream>
#include <string>
#include <windows.h>
#include <psapi.h>

#include <detours.h>
// If compiling as 64-bit
#ifdef _M_X64
#pragma comment (lib, "detoursx64.lib")
#endif // _M_X64

// If compiling as 32-bit
#ifdef _M_IX86
#pragma comment (lib, "detoursx86.lib")
#endif // _M_IX86

bool analyze_process_handle(HANDLE hProcess);