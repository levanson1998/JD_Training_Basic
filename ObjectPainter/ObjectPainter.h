#include "stdafx.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include "DataModel.h"
#include "FileHandling.h"

#define SAVE_BUTTON  123
#define EXIT_BUTTON  124
#define LFF_BUTTON   125
#define APPLY_BUTTON 126
#define SCM_PAINT    127 // static control message paint

const char* LOGFILE = "./logfile.txt";

const char g_szClassName[] = "Object Painter";
HWND edit_box, static_control, save_button, apply_button, lff_button, exit_button;

inline void Loginfo( const std::string LogMsg);
void DesignWindows(HWND hwnd);
