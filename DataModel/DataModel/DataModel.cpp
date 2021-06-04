// DataModel.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DataModel.h"


std::vector<char*> DataModel::GetObjects(HWND hwnd, HWND edit_box)
{
    std::size_t len = GetWindowTextLength(edit_box);
    char* text = new char[len];
    GetWindowTextA(edit_box, text, len);
    if(len == 0)
    {
        throw "data is empty !";
    }

    char* end = text + len - 1;
    char* start = text;
    char * position;
    int len_obj = 0;

    std::vector<char*> data_object(0);

    position  = std::find(start, end, '[');
    if(position == end)
    {
        //throw std::runtime_error("No any object in data ");
        throw "No any object in data";
    }
    int i = 0;
    do
    {
        i++;
        std::size_t size;
        size = len;
        start = position;
        position  = std::find(position + 1, end, '[');

        len_obj = position - start;
            
        data_object.resize(i);

        data_object[i-1] = new char[len_obj + 1];
        std::strncpy(data_object[i-1], start, len_obj);

    } while(position != end);
    //MessageBox(hwnd, "get object !", "Notify", MB_OK | MB_ICONINFORMATION); /// delete after

    delete text;
    return data_object;
}

void DataModel::ClassObjects(HWND hwnd, std::vector<char*> obj)
{

}

std::string DataModel::CharArray2String(char* a, std::size_t &len)
{
    std::string str = "";
    for(int i = 0; i < len; i++)
    {
        str += *(a+i);
    }
    return str;
}

