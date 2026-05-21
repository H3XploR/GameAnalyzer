// GameAnalyzer.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <iostream>
#include <windows.h>
#include <psapi.h>

const bool affiche_process_handle = 0;
int main()
{
    std::cout << "Hello World!\n";
	DWORD lpidProcess[99999], lpcbNeeded;
    BOOL ret_enum_process = EnumProcesses(lpidProcess,
                                        sizeof(lpidProcess),
                                        &lpcbNeeded);

    for (unsigned int i = 0; i < 99999; i++) {
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, lpidProcess[i]);
        if (hProcess != NULL) {
            std::cout << i << ": " << "pid: " << lpidProcess[i];
            if (affiche_process_handle == 1)
                std::cout << "-->" << hProcess;
            LPSTR lpImageFileName = new char[256];
            DWORD  nSize = 256;
            DWORD lenght_buffer = GetProcessImageFileNameA(hProcess, lpImageFileName, nSize);
            if (lenght_buffer != 0)
                std::cout << "--->" << lpImageFileName << std::endl;
            CloseHandle(hProcess);
            delete[] lpImageFileName;
        }
    }
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
