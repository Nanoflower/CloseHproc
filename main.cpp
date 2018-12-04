#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include "processthreadsapi.h"

//using namespace std;

void GetProcId(char* ProcName);

DWORD ProcId = 0; // THIS IS OUR GLOBAL VARIABLE FOR THE PROC ID;

int main()
{
    std::cout << "Cortesia de la casa Diego & Josua" << std::endl;
    char* ProcName = "runplugin.exe";
    GetProcId(ProcName);
    return 0;
}
void GetProcId(char* ProcName)
{
	for(;;)
        {
        PROCESSENTRY32   pe32;
        HANDLE         hSnapshot = NULL;
        HANDLE         explorer;

        pe32.dwSize = sizeof(PROCESSENTRY32);
        hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if(Process32First(hSnapshot, &pe32))
        {
            do{
                if(strcmp(pe32.szExeFile, ProcName) == 0)
                    break;
            }while(Process32Next(hSnapshot, &pe32));
        }
        else
        {
            std::cout << "No se ha encontrado";
            break;
        }

        if(hSnapshot != INVALID_HANDLE_VALUE)
            CloseHandle(hSnapshot);

        ProcId = pe32.th32ProcessID;
        std::cout << "Proceso encontrado, eliminando proceso con PID: ";
        std::cout << pe32.th32ProcessID << std::endl;


        explorer = OpenProcess(PROCESS_ALL_ACCESS, false, ProcId);
        TerminateProcess(explorer,1); // terminar proceso
    }
}

