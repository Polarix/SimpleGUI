/*************************************************************************/
/** Copyright.															**/
/** FileName: UserAction.c												**/
/** Author: XuYulin														**/
/** Version: 1.0.0.0													**/
/** Description: User operation interface.								**/
/** History:															**/
/**	XuyYulin	2017/2/27	2.0.0.0		New create.						**/
/** XuYulin 2017/2/27 1.0 build this moudle								**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "UserAction.h"
#include "LCD_OperationIF.h"

#include "GUI_Basic.h"
#include "GUI_Text.h"
#include "GUI_VariableBox.h"
#include "GUI_Notice.h"
#include "GUI_List.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
const char*				arrszOptionGp1[]		= {	"选项1", "选项2", "选项3"};
const char*				arrszOptionGp2[]		= {	"组2 选项A", "组2 选项B", "组2 选项C", "组2 选项D"};
GUI_LIST_ITEM			arrstTestListItems[]	= {	{"列表项0 - 超长列表项",	LIST_ITEM_NORMAL,	{0}, 					{0, 0, 0}, NULL},
													{"列表项1 - 枚举",		LIST_ITEM_ENUM,			{2, 0, 2},				{0, 0, 2}, arrszOptionGp1},
													{"列表项2 - 枚举",		LIST_ITEM_ENUM,			{1, 0, 3},				{0, 0, 3}, arrszOptionGp2},
													{"列表项3 - 数字",		LIST_ITEM_DIGIT,		{9, 1, 9},				{0, 0, 0}, NULL},
													{"列表项4 - 数字",		LIST_ITEM_DIGIT,		{10, 5, 15},			{0, 0, 0}, NULL},
													{"列表项5 - 数字",		LIST_ITEM_DIGIT,		{100, 50, 100},			{0, 0, 0}, NULL},
													{"列表项6 - 数字",		LIST_ITEM_DIGIT,		{0, -50, 50},			{0, 0, 0}, NULL},
													{"列表项7 - 小数",		LIST_ITEM_DIGIT,		{12345, 0, 99999},		{2, 0, 2}, NULL},
													{"列表项8 - 小数",		LIST_ITEM_DIGIT,		{66, 66, 66},			{4, 0, 3}, NULL},
													{"列表项9 - 数字",		LIST_ITEM_DIGIT,		{-100, -100, 0},		{0, 0, 0}, NULL},
													{"列表项A - 小数",		LIST_ITEM_DIGIT,		{-123, -123, -123},		{1, 0, 1}, NULL},
													{"列表项B - 小数",		LIST_ITEM_DIGIT,		{-456, -500, -50},		{5, 0, 5}, NULL},
													{"列表项C",				LIST_ITEM_NORMAL,		{0}, 					{0, 0, 0}, NULL},
													{"列表项D",				LIST_ITEM_NORMAL,		{0},					{0, 0, 0}, NULL},
													{"列表项E",				LIST_ITEM_NORMAL,		{0},					{0, 0, 0}, NULL},
													{"列表项F - 超长列表项",	LIST_ITEM_NORMAL,	{0},					{0, 0, 0}, NULL},
};
GUI_LIST_STRUCT			stTestList = {{"测试列表 Test list", 16, arrstTestListItems}};
//GUI_LIST_STRUCT			stTestList = {{NULL, 16, arrstTestListItems}};

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
/*************************************************************************/
/** Function Name:	USR_ACT_OnInitialize								**/
/** Purpose:		Process with application startup.					**/
/** Resources:		None.												**/
/** Params:			None.												**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void USR_ACT_OnInitialize(void)
{
	GUI_List_InitializeListData(&stTestList);
	GUI_List_RefreshList(&stTestList);
}

/*************************************************************************/
/** Function Name:	USR_ACT_OnKeyPress									**/
/** Purpose:		Recive and process keyboard event.					**/
/** Resources:		None.												**/
/** Params:																**/
/** @uiKeyCode:			Key code.										**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void USR_ACT_OnKeyPress(bool bShift, bool bCtrl, bool bAlt, uint16_t uiKeyCode)
{
	char 					szText[16];
	RECTANGLE				stTextDisplayArea;
	RECTANGLE				stTextDataArea;

	stTextDisplayArea.PosX = 96;
	stTextDisplayArea.PosY = 2;
	stTextDisplayArea.Width = 24;
	stTextDisplayArea.Height = 14;
	stTextDataArea.PosX = 1;
	stTextDataArea.PosY = 1;
	switch(uiKeyCode)
	{
		case KEY_VALUE_SPACE:
		{
			sprintf(szText, "%u", stTestList.ControlVariable.SelectIndex);
			GUI_Text_DrawSingleLineText(szText, GUI_FONT_SIZE_H12, &stTextDisplayArea, &stTextDataArea, GUI_DRAW_NORMAL);
			break;
		}
		case KEY_VALUE_ENTER:
		{
			GUI_List_RefreshList(&stTestList);
			break;
		}
		case KEY_VALUE_ESC:
		{
			break;
		}
		case KEY_VALUE_UP:
		{
			GUI_List_SelectUpItem(&stTestList);
			break;
		}
		case KEY_VALUE_DOWN:
		{
			GUI_List_SelectDownItem(&stTestList);
			break;
		}
		case KEY_VALUE_RIGHT:
		{
			if(true == bShift)
			{
				GUI_List_SetListItemValue(&stTestList, stTestList.ControlVariable.SelectIndex, stTestList.Data.Items[stTestList.ControlVariable.SelectIndex].Valid.Value, stTestList.Data.Items[stTestList.ControlVariable.SelectIndex].Decimal.Value-1);
			}
			else
			{
				GUI_List_SetListItemValue(&stTestList, stTestList.ControlVariable.SelectIndex, stTestList.Data.Items[stTestList.ControlVariable.SelectIndex].Valid.Value+1, stTestList.Data.Items[stTestList.ControlVariable.SelectIndex].Decimal.Value);
			}
			break;
		}
		case KEY_VALUE_LEFT:
		{
			if(true == bShift)
			{
				GUI_List_SetListItemValue(&stTestList, stTestList.ControlVariable.SelectIndex, stTestList.Data.Items[stTestList.ControlVariable.SelectIndex].Valid.Value, stTestList.Data.Items[stTestList.ControlVariable.SelectIndex].Decimal.Value+1);
			}
			else
			{
				GUI_List_SetListItemValue(&stTestList, stTestList.ControlVariable.SelectIndex, stTestList.Data.Items[stTestList.ControlVariable.SelectIndex].Valid.Value-1, stTestList.Data.Items[stTestList.ControlVariable.SelectIndex].Decimal.Value);
			}
			break;
		}
		default:
		{
			break;
		}
	}
}

