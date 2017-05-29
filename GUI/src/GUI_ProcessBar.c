/*************************************************************************/
/** Copyright.															**/
/** FileName: GUI_ProcessBar.c											**/
/** Author: XuYulin														**/
/** Version: 1.0.0.0													**/
/** Description: XML operations.										**/
/** History:															**/
/**	XuyYulin	2017/2/27	2.0.0.0		New create.						**/
/** XuYulin 2017/2/27 1.0 build this moudle								**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "GUI_Basic.h"
#include "GUI_ProcessBar.h"

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//

/*************************************************************************/
/** Function Name:	GUI_UpdateProcessBar								**/
/** Purpose:		Display or update a process bar.					**/
/** Resources:		Process bar data structure.							**/
/** Params:																**/
/**	@pProcessBarData:	Process bar data whitch will update on screen.	**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void GUI_UpdateProcessBar(GUI_PROCBAR_STRUCT *pProcessBarData)
{
	uint8_t uiProcessBlockStartX, uiProcessBlockStartY;
	uint8_t uiProcessBlockWidth, uiProcessBlockHeight;
	GUI_COLOR eBackColor, eFillColor;
	if(NULL != pProcessBarData)
	{
		if((pProcessBarData->Parameter.Width > 3) && (pProcessBarData->Parameter.Height > 3))
		{
			// Check value must be less then PROCBAR_VALUE_MAX.
			if(pProcessBarData->Data.Value > pProcessBarData->Parameter.MaxValue)
			{
				pProcessBarData->Data.Value = pProcessBarData->Parameter.MaxValue;
			}
			// Update process bar data.
			switch(pProcessBarData->Parameter.Direction)
			{
				case GUI_PROCBAR_DOWN:	// Process from up to down.
				{
					uiProcessBlockStartX	= pProcessBarData->Parameter.PosX + 1;
					uiProcessBlockStartY	= pProcessBarData->Parameter.PosY + 1;
					uiProcessBlockWidth		= pProcessBarData->Parameter.Width - 2;
					uiProcessBlockHeight	= (pProcessBarData->Parameter.Height - 2) * (pProcessBarData->Data.Value) / pProcessBarData->Parameter.MaxValue;
					eBackColor = GUI_COLOR_BKGCLR;
					eFillColor = GUI_COLOR_FRGCLR;
					break;
				}
				case GUI_PROCBAR_LEFT:	// Process from right to left.
				{
					uiProcessBlockStartX	= pProcessBarData->Parameter.PosX + 1;
					uiProcessBlockStartY	= pProcessBarData->Parameter.PosY + 1;
					uiProcessBlockWidth		= (pProcessBarData->Parameter.Width - 2) * (pProcessBarData->Parameter.MaxValue - pProcessBarData->Data.Value) / pProcessBarData->Parameter.MaxValue;
					uiProcessBlockHeight	= pProcessBarData->Parameter.Height - 2;
					eBackColor = GUI_COLOR_FRGCLR;
					eFillColor = GUI_COLOR_BKGCLR;
					break;
				}
				case GUI_PROCBAR_RIGHT:	// Process from left to right.
				{
					uiProcessBlockStartX	= pProcessBarData->Parameter.PosX + 1;
					uiProcessBlockStartY	= pProcessBarData->Parameter.PosY + 1;
					uiProcessBlockWidth		= (pProcessBarData->Parameter.Width - 2) * (pProcessBarData->Data.Value) / pProcessBarData->Parameter.MaxValue;
					uiProcessBlockHeight	= pProcessBarData->Parameter.Height - 2;
					eBackColor = GUI_COLOR_BKGCLR;
					eFillColor = GUI_COLOR_FRGCLR;
					break;
				}
				case GUI_PROCBAR_UP:	// Process from down to up.
				default:
				{
					uiProcessBlockStartX	= pProcessBarData->Parameter.PosX + 1;
					uiProcessBlockStartY	= pProcessBarData->Parameter.PosY + 1;
					uiProcessBlockWidth		= pProcessBarData->Parameter.Width - 2;
					uiProcessBlockHeight	= (pProcessBarData->Parameter.Height - 2) * (pProcessBarData->Parameter.MaxValue - pProcessBarData->Data.Value) / pProcessBarData->Parameter.MaxValue;
					eBackColor = GUI_COLOR_FRGCLR;
					eFillColor = GUI_COLOR_BKGCLR;
				}
			}
			// Redraw edge and clean up area.
			GUI_Basic_DrawRectangle(pProcessBarData->Parameter.PosX, pProcessBarData->Parameter.PosY, pProcessBarData->Parameter.Width, pProcessBarData->Parameter.Height, GUI_COLOR_FRGCLR, eBackColor);
			// Draw process block.
			GUI_Basic_DrawRectangle(uiProcessBlockStartX, uiProcessBlockStartY, uiProcessBlockWidth, uiProcessBlockHeight, eFillColor, eFillColor);
		}
	}
}
