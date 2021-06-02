#ifdef DATAMODEL_EXPORTS
#define DATAMODEL_API __declspec(dllexport) 
#else
//#define DLLTEST_API __declspec(dllimport) 
#define DATAMODEL_API
#endif

#include <windows.h>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include "CommDlg.h"
#include "windows.h"



class DataModel
{
private:

public:
    //DataModel();
    //~DataModel();

    DATAMODEL_API void ReadFile(HWND hwnd, HWND edit_box); // get address of file
    DATAMODEL_API void SaveFile();

    // Read data from file and get object from it
    DATAMODEL_API void GetObject();
};