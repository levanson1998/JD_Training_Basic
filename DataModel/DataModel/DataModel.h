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
#include "windows.h"
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
    //char* text = new char[len+1];
    DATAMODEL_API std::string CharArray2String(char* a, std::size_t &len);
    DATAMODEL_API void ClassObjects(HWND hwnd, std::vector<char*> obj);

public:
    //DataModel();
    //~DataModel();


    // Read data from file and get object from it
    DATAMODEL_API std::vector<char*> GetObjects(HWND hwnd, HWND edit_box);
};