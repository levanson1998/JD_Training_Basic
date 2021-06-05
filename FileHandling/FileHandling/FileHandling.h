#ifdef FILEHANDLING_EXPORTS
#define FILEHANDLING_API __declspec(dllexport) 
#else
//#define DLLTEST_API __declspec(dllimport) 
#define FILEHANDLING_API
#endif

#include "array"
#include <windows.h>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <vector>
#include "CommDlg.h" // for OPENFILENAME
#include "windows.h"
//#include <iostream>
#include <algorithm>

#include "winbase.h"

class FileHandling
{
public:

    FILEHANDLING_API void ReadFile(HWND hwnd, HWND edit_box); // get address of file
    FILEHANDLING_API void SaveFile(HWND hwnd, HWND edit_box);
};