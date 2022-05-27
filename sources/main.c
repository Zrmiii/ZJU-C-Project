#ifndef _MAIN_C_
#define _MAIN_C_

#include "main.h"

#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "linkedlist.h"
#include "imgui.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

//=============================================================================================================================================//
/* 默认值定义 */
//=============================================================================================================================================//

/* 菜单控件高度 */
double MenuH = 0.4;

/* 菜单控件宽度 */
double MenuW = 1.0;

/* 窗口宽度 */
double WindowX = 1280;

/* 窗口高度 */
double WindowY = 720;



//=============================================================================================================================================//
/* 函数实现 */
//=============================================================================================================================================//

void Main()
{
	InitGraphics();
	InitConsole();

	registerKeyboardEvent(KeyboardEventProcess);
	registerCharEvent(CharEventProcess);
	registerMouseEvent(MouseEventProcess);

	display();
}

void display()
{
	DisplayClear();

	DrawMenu();
}

void DrawMenu()
{
	if(button(GenUIID(0), GetWindowWidth()/2, GetWindowHeight()/2, MenuW, MenuH, "OK")){
		printf("OK button clicked\n");
	}

	static char * menuListFile[] = {
		"File",  
		"Open  | Ctrl-O",
		"Close",
		"Exit   | Ctrl-E"};
}

void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event);
	display();
}

void CharEventProcess(char c)
{
	uiGetChar(c);
	display();
}

void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event);
	display();
}

#endif
