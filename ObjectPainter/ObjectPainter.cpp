//#include "stdafx.h"
#include "ObjectPainter.h"
#include "resource.h"
#include <iostream>


// Create a font for edit box, 
HFONT font=CreateFont(20,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_DONTCARE,"Courier New");

FileHandling file_data;
DataModel objects;

int test = 0;

/*
* Loginfo, Log message will append to logfile.txt file
* Y-m-d h:m:s  Messages
*/
inline void Loginfo( const char* LogMsg)
{
    static bool one_time = TRUE;
    std::ofstream log_file;

    time_t now = time(0);
    struct tm  tstruct;
    char  buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    if(one_time == TRUE)
    {
        one_time = FALSE;
        log_file.open(LOGFILE, std::ofstream::out | std::ofstream::trunc); // clear file
        log_file << buf << "\t" << "LOGFILE FirstApp" << std::endl << std::endl;
        log_file.close();
    }
    
    log_file.open(LOGFILE, std::ofstream::out | std::ofstream::app);
    log_file << buf << "\t" << LogMsg << std::endl;
    log_file.close();
}

void DesignWindows(HWND hwnd)
{
    HICON hIcon;
    
    // Create a logo for application
    hIcon = (HICON)LoadImage(NULL, "logo.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
    if(hIcon)
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    else
        MessageBox(hwnd, "Could not load large icon!", "Error", MB_OK | MB_ICONERROR);

    // create Load from file button
    lff_button = CreateWindowW(L"BUTTON", L"Load from file", WS_VISIBLE | WS_CHILD, \
        10, 530, 100, 25, hwnd, (HMENU)LFF_BUTTON, NULL, NULL);

    // create Apply button
    apply_button = CreateWindowW(L"BUTTON", L"Apply", WS_VISIBLE | WS_CHILD, \
        260, 530, 50, 25, hwnd, (HMENU)APPLY_BUTTON, NULL, NULL);

    // create Save button
    save_button = CreateWindowW(L"BUTTON", L"Save", WS_VISIBLE | WS_CHILD, \
        870, 530, 50, 25, hwnd, (HMENU)SAVE_BUTTON, NULL, NULL);

    // create Exit button
    exit_button = CreateWindowW(L"BUTTON", L"Exit", WS_VISIBLE | WS_CHILD, \
        930, 530, 50, 25, hwnd, (HMENU)EXIT_BUTTON, NULL, NULL);

    // create edit area
    edit_box = CreateWindowW(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_GROUP | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, \
        10, 10, 300, 510, hwnd, NULL, NULL, NULL);

    // create draw area
    static_control = CreateWindowW(L"STATIC", NULL, WS_VISIBLE | WS_CHILD | WS_GROUP | WS_BORDER , \
        320, 10, 660, 510, hwnd, NULL, NULL, NULL);

    // send WM_SETFONT with font
    SendMessage(edit_box, WM_SETFONT,(WPARAM)font,MAKELPARAM(true,0));
    SendMessage(save_button, BM_SETSTYLE,(WPARAM)BS_PUSHBUTTON, TRUE);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
            DesignWindows(hwnd);

        break;
        case WM_COMMAND:
            switch(wParam)
            {
            case SAVE_BUTTON:
                Loginfo("Save button is pushed !");
                //DataModel object_file1;
                file_data.SaveFile(hwnd, edit_box);
            break;

            case EXIT_BUTTON:
                 Loginfo("Exit button is pushed !");
                 DestroyWindow(hwnd);
            break;

            case APPLY_BUTTON:
                 Loginfo("Apply button is pushed !");
                 //DataModel object_file2;
                 try
                 {
                     
                      objects.GetObjects(hwnd, edit_box);
                      SendMessage(hwnd, WM_COMMAND, SCM_PAINT, NULL);
                 }
                 catch(const char *ex)
                 {
                       MessageBox(hwnd, ex, "Error", MB_OK | MB_ICONERROR);
                 }
                 Loginfo("Apply button is ok !");
            break;

            case LFF_BUTTON:
                test ++;
                Loginfo("Load from file button is pushed !");
                //DataModel object_file;

                file_data.ReadFile(hwnd, edit_box);
            break;

            case SCM_PAINT:
                 try
                 {
                     PAINTSTRUCT ps;
                     HDC hdc = BeginPaint(static_control, &ps); 
                     SetBkColor(hdc, RGB(255,255,255));
                     objects.PaintObject(hdc, static_control);

                     EndPaint(hwnd, &ps);
                 }
                 catch(const char *ex)
                 {
                       MessageBox(hwnd, ex, "Error", MB_OK | MB_ICONERROR);
                 }
            break;
            }
        break;

        case WM_CLOSE:
            Loginfo("DestroyWindow !");
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            Loginfo("PostQuitMessage !");
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    

    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    Loginfo("");
    Loginfo("Begin");


    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_WINDOWEDGE,
        g_szClassName,
        "Object Painter",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,
        50, 50, 1000, 600,
        NULL, NULL, hInstance, NULL);

    //hwnd = CreateWindow(TEXT("STATIC"), NULL, WS_DLGFRAME | WS_VISIBLE | WS_CHILD, 100, 100, 100, 200, NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        Loginfo("Window Creation Failed!");
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
