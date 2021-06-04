// FileHandling.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "FileHandling.h"
#include <windows.h>
#include <stdexcept>


void FileHandling::ReadFile(HWND hwnd, HWND edit_box)
{
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    char szFile[MAX_PATH] = "";

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "txt";

    if(GetOpenFileName(&ofn))
    {
        std::fstream file_data;
        std::string text;
        file_data.open(szFile, std::ios_base::in);

        if(file_data.is_open())
        {
            std::string text2box = "";
            
            while(getline(file_data, text))
            {
                text2box.append(text).append("\r\n");
                //text2box.append(text);
            }
            SetWindowTextA(edit_box, text2box.c_str());
            file_data.close();
        }
    }
    else
    {
        MessageBox(hwnd, "Could not open file", "Error", MB_OK | MB_ICONERROR);
    }
}

void FileHandling::SaveFile(HWND hwnd, HWND edit_box)
{
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    char szFile[MAX_PATH] = "";

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
    ofn.lpstrDefExt = "txt";
    
    if(GetSaveFileName(&ofn))
    {
        std::ofstream save_file;

        save_file.open(szFile, std::ofstream::out | std::ofstream::trunc);
        save_file.close();

        int len = GetWindowTextLength(edit_box);
        char *text = new char[len+1];

        GetWindowTextA(edit_box, text, len);
        save_file.open(szFile, std::ofstream::out | std::ofstream::app);

        save_file << text;
        delete text;
    }
}
