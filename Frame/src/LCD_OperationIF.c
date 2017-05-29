/*************************************************************************/
/** Copyright.															**/
/** FileName: LCD_OperationIF.c											**/
/** Author: XuYulin														**/
/** Version: 1.0.0.0													**/
/** Description: Virtual LCD operation interface.						**/
/** History:															**/
/**	XuyYulin	2017/2/27	2.0.0.0		New create.						**/
/** XuYulin 2017/2/27 1.0 build this moudle								**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "LCD_OperationIF.h"
#include "UserAction.h"
#include <memory.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
TPixArray	g_LCDPixArray;
//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static void VTIF_UpdateChangedArea(uint16_t uiPosX, uint16_t uiPosY);

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
void VTIF_KeyBoardEvent(bool bShift, bool bCtrl, bool bAlt, uint16_t uiKeyCode)
{
	USR_ACT_OnKeyPress(bShift, bCtrl, bAlt, uiKeyCode);
}

void VTIF_LCDInitializeDisplay(void)
{
	USR_ACT_OnInitialize();
}

void VTIF_SetPoint(uint16_t uiPosX, uint16_t uiPosY, uint8_t uiPixValue)
{
	if((uiPosX < LCD_SIZE_WIDTH) && (uiPosY < LCD_SIZE_HEIGHT))
	{
		VTIF_UpdateChangedArea(uiPosX, uiPosY);
		g_LCDPixArray.Pixregister[uiPosX][uiPosY] = uiPixValue;
	}
}

uint8_t VTIF_GetPoint(uint16_t uiPosX, uint16_t uiPosY)
{
	return g_LCDPixArray.Pixregister[uiPosX][uiPosY];
}

void VTIF_ClearScreen(void)
{
	memset(&(g_LCDPixArray.Pixregister), 0x00, sizeof(g_LCDPixArray.Pixregister));
	g_LCDPixArray.InUpdating = true;
	g_LCDPixArray.ChangedArea.StartPosX = 0;
	g_LCDPixArray.ChangedArea.EndPosX = LCD_SIZE_WIDTH-1;
	g_LCDPixArray.ChangedArea.StartPosY = 0;
	g_LCDPixArray.ChangedArea.EndPosY = LCD_SIZE_HEIGHT-1;
}

void VTIF_UpdateChangedArea(uint16_t uiPosX, uint16_t uiPosY)
{
    if(false == g_LCDPixArray.InUpdating)
	{
		g_LCDPixArray.InUpdating = true;
		g_LCDPixArray.ChangedArea.StartPosX = uiPosX;
		g_LCDPixArray.ChangedArea.EndPosX = uiPosX;
		g_LCDPixArray.ChangedArea.StartPosY = uiPosY;
		g_LCDPixArray.ChangedArea.EndPosY = uiPosY;
	}
	else
	{
        if(g_LCDPixArray.ChangedArea.StartPosX > uiPosX)
		{
			g_LCDPixArray.ChangedArea.StartPosX = uiPosX;
		}
		if(g_LCDPixArray.ChangedArea.EndPosX < uiPosX)
		{
			g_LCDPixArray.ChangedArea.EndPosX = uiPosX;
		}
		if(g_LCDPixArray.ChangedArea.StartPosY > uiPosY)
		{
			g_LCDPixArray.ChangedArea.StartPosY = uiPosY;
		}
		if(g_LCDPixArray.ChangedArea.EndPosY < uiPosY)
		{
			g_LCDPixArray.ChangedArea.EndPosY = uiPosY;
		}
	}
}


