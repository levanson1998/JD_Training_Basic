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
#include <vector>
#include "CommDlg.h"
//#include <iostream>
#include <algorithm>



//struct rectangle
//{
//    std::array<double, 2> xy1;
//    std::array<double, 2> xy2;
//    std::array<double, 2> xy3;
//    std::array<double, 2> xy4;
//};
//
//struct line
//{
//    std::array<double, 2> xy1;
//    std::array<double, 2> xy2;
//};
//
//struct circle
//{
//    std::array<double, 2> o;
//    double r;
//};

class DataModel
{
private:
    LPCTSTR szFile;
    std::vector<char*> obj_sec;
    //char* text = new char[len+1];
    DATAMODEL_API std::string CharArray2String(char* a, std::size_t &len);
    DATAMODEL_API void GetDataObjects(HWND hwnd, std::vector<char*> obj);
    DATAMODEL_API char* FindChar(char* c, std::size_t size_c, char* find);
    DATAMODEL_API bool CompareChar(const char *c1, char *c2);
    DATAMODEL_API void DrawRect(HWND hwnd, int obj_index);
    DATAMODEL_API void DrawCircle(HWND hwnd, int obj_index);
    DATAMODEL_API void DrawLine(HWND hwnd, int obj_index);

public:
    DataModel()
    {
        szFile = "./temp/temp_data.ini";
    }
    ~DataModel()\
    {
        for(std::size_t i = 0; i < obj_sec.size(); i++)
        {
            delete obj_sec[i];
        }
    }


    // Read data from file and get object from it
    DATAMODEL_API void GetObjects(HWND hwnd, HWND edit_box);
    DATAMODEL_API void PaintObject(HDC hdc, HWND hwnd);
};