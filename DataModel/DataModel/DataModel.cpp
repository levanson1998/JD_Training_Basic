// DataModel.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DataModel.h"


//std::vector<char*> DataModel::GetObjects(HWND hwnd, HWND edit_box)
//{
//    std::size_t len = GetWindowTextLength(edit_box);
//    char* text = new char[len];
//    GetWindowTextA(edit_box, text, len);
//    if(len == 0)
//    {
//        throw "data is empty !";
//    }
//
//    char* end = text + len - 1;
//    char* start = text;
//    char * position;
//    int len_obj = 0;
//
//    std::vector<char*> data_object(0);
//
//    position  = std::find(start, end, '[');
//    if(position == end)
//    {
//        //throw std::runtime_error("No any object in data ");
//        throw "No any object in data";
//    }
//    int i = 0;
//    do
//    {
//        i++;
//        std::size_t size;
//        size = len;
//        start = position;
//        position  = std::find(position + 1, end, '[');
//
//        len_obj = position - start;
//            
//        data_object.resize(i);
//
//        data_object[i-1] = new char[len_obj + 1];
//        std::strncpy(data_object[i-1], start, len_obj);
//
//    } while(position != end);
//    //MessageBox(hwnd, "get object !", "Notify", MB_OK | MB_ICONINFORMATION); /// delete after
//
//    delete text;
//    return data_object;
//}
//
//void DataModel::GetDataObjects(HWND hwnd, std::vector<char*> obj)
//{
//    std::size_t obj_size = 0;
//    for(int i = 0; i < obj_size; i++)
//    {
//        std::size_t len = sizeof(obj[0]) / sizeof(obj[0]);
//        char* p_find = this->FindChar(obj[0], len, "type");
//    }
//}
//
//char* DataModel::FindChar(char* c, std::size_t size_c, char* find) // const char* c //
//{
//    std::size_t len = sizeof(find) / sizeof(find[0]);
//    
//    int j = 0, i = 0;
//    
//    for(i = 0; i < size_c; i++)
//    {
//        for(j = 0; j < len; j++)
//        {
//            if(find[j] != c[i + j])
//            {
//                break;
//            }
//        }
//        if((j == len)) // && (c[i-1] < 97) && (c[i-1] > 173) && (c[i+len] < 97) && (c[i+len] > 173))
//        {
//            break;
//        }
//    }
//    return c + i ;
//}
//
//std::string DataModel::CharArray2String(char* a, std::size_t &len)
//{
//    std::string str = "";
//    for(int i = 0; i < len; i++)
//    {
//        str += *(a+i);
//    }
//    return str;
//}

void DataModel::GetObjects(HWND hwnd, HWND edit_box)
{
    std::size_t len = GetWindowTextLength(edit_box);
    std::ofstream temp_file;
    char* text = new char[len];

    GetWindowTextA(edit_box, text, len);
    if(len == 0)
    {
        throw "data is empty !";
    }

    temp_file.open(this->szFile, std::ofstream::out | std::ofstream::trunc);
    temp_file.close();
    temp_file.open(this->szFile, std::ofstream::out | std::ofstream::app);
    temp_file << text;
    delete text;
    temp_file.close();
    

    // -----

    char data[100];
    std::size_t len1 = GetPrivateProfileSectionNames(data, 100, this->szFile);

    if(len1 == NULL)
    {
        throw "No any object in data";
    }


    int size_v = 0;
    int j = 0;
    for(std::size_t i = 0; i < len1; i++)
    {
        j++;
        if(data[i] == '\0')
        {
            size_v++;
            this->obj_sec.resize(size_v);
            this->obj_sec[size_v - 1] = (char*)malloc(j);
            std::memcpy(this->obj_sec[size_v - 1], &data[i - j + 1], j);
            j = 0;
        }
    }



}

void DataModel::PaintObject(HDC hdc, HWND static_control)
{
    // clear static control
    //RECT full;
    ////HBRUSH hBrush = CreateSolidBrush(RGB(33, 33, 33));
    //full.left = 0;
    //full.top = 0;
    //full.right = 660;
    //full.bottom = 510;
    //FillRect(hdc, &full, (HBRUSH) (COLOR_WINDOW+100));

    for(std::size_t i = 0; i < obj_sec.size(); i++)
    {
        char data[100];
        std::size_t len = GetPrivateProfileString(obj_sec[i], "type", NULL, data, 100, this->szFile);
        if(len == 0)
        {
            throw "object have incorrect type";
        }
        //char c11[50] = "rectangle";
        if( this->CompareChar(data, "rectangle"))
        {
            this->DrawRect(static_control, i);
        }
        if( this->CompareChar(data, "circle"))
        {
            this->DrawCircle(static_control, i);
        }
        if( this->CompareChar(data, "line"))
        {
            this->DrawLine(static_control, i);
        }
        else
        {
            // Message box 
        }
    }
}


void DataModel::DrawRect(HWND hwnd, int obj_index)
{
    //MessageBox(hwnd, "DrawRect !", "Notify", MB_OK | MB_ICONINFORMATION);
}

void DataModel::DrawCircle(HWND hwnd, int obj_index)
{
    //MessageBox(hwnd, "DrawCircle !", "Notify", MB_OK | MB_ICONINFORMATION);
}

void DataModel::DrawLine(HWND static_control, int obj_index)
{
    //MessageBox(hwnd, "DrawLine !", "Notify", MB_OK | MB_ICONINFORMATION);
    int x1, y1, x2, y2;
    x1 = GetPrivateProfileInt(this->obj_sec[obj_index], "x1", 0, this->szFile);
    y1 = GetPrivateProfileInt(this->obj_sec[obj_index], "y1", 0, this->szFile);
    x2 = GetPrivateProfileInt(this->obj_sec[obj_index], "x2", 0, this->szFile);
    y2 = GetPrivateProfileInt(this->obj_sec[obj_index], "y2", 0, this->szFile);

    HDC hdc=GetDC(static_control);
    HPEN hp=CreatePen(PS_SOLID ,2,RGB(34,100,67));
    SelectObject(hdc,hp); 
    MoveToEx(hdc, x1, y1, 0);
    LineTo(hdc, x2, y2);
    ReleaseDC(static_control, hdc);
    /// check error for x1, y1,...  incorrect format (ex: x1 = g)
}


bool DataModel::CompareChar(const char *c1, char *c2)
{
    int i = 0;
    while(c1[i] != '\0')
    {
        if(c1[i] != c2[i])
        {
            return false;
        }
        i++;
    }

    return true;
}

