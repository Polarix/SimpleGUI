/*************************************************************************/
/** Copyright.															**/
/** FileName: GUI_ScrollBar.c											**/
/** Author: XuYulin														**/
/** Version: 1.0.0.0													**/
/** Description: Create and display a scrollbar on screen.				**/
/** History:															**/
/**	XuyYulin	2017/2/27	2.0.0.0		New create.						**/
/** XuYulin 2017/2/27 1.0 build this moudle								**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "GUI_Basic.h"
#include "GUI_ScrollBar.h"

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
/** Function Name:	GUI_ScrollBar_UpdateScrollBar						**/
/** Purpose:		Display or update a scroll bar.						**/
/** Resources:		Scroll bar data structure.							**/
/** Params:																**/
/** @pstScrollBar[in]:	Scroll bar data pointer.						**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void GUI_ScrollBar_UpdateScrollBar(GUI_SCROLLBAR_STRUCT* pstScrollBar)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint16_t	uiScrollBlockPos;
	uint16_t	uiScrollBlockSize;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	if(GUI_SCROLLBAR_VERTICAL == pstScrollBar->Parameter.eDirection)
	{
		uiScrollBlockSize	= pstScrollBar->Parameter.Width-2;
	}
	else
	{
		uiScrollBlockSize	= pstScrollBar->Parameter.Height-2;
	}

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(((pstScrollBar->Parameter.Height > 2) && (pstScrollBar->Parameter.Width > 2)) && (pstScrollBar->Parameter.Height != pstScrollBar->Parameter.Width))
	{
		// Check new value must be less then max value.
		if(pstScrollBar->Data.Index > pstScrollBar->Parameter.MaxIndex)
		{
			pstScrollBar->Data.Index = pstScrollBar->Parameter.MaxIndex;
		}

		if(GUI_SCROLLBAR_VERTICAL == pstScrollBar->Parameter.eDirection)
		{
			// Draw scroll bar edge.
			GUI_Basic_DrawRectangle(pstScrollBar->Parameter.PosX, pstScrollBar->Parameter.PosY,
									pstScrollBar->Parameter.Width, pstScrollBar->Parameter.Height,
									GUI_COLOR_FRGCLR, GUI_COLOR_BKGCLR);
			// Value lower limit is 0, scroll blocks must be greater then 0.
			if(pstScrollBar->Parameter.MaxIndex > 0)
			{
				uiScrollBlockPos = pstScrollBar->Parameter.PosY+1+((pstScrollBar->Parameter.Height-uiScrollBlockSize-2)*pstScrollBar->Data.Index/pstScrollBar->Parameter.MaxIndex);
				// Redraw process block
				GUI_Basic_DrawRectangle(pstScrollBar->Parameter.PosX+1, uiScrollBlockPos,
										uiScrollBlockSize, uiScrollBlockSize, GUI_COLOR_FRGCLR, GUI_COLOR_FRGCLR);
			}
			else
			{
				GUI_Basic_DrawRectangle(pstScrollBar->Parameter.PosX+1, pstScrollBar->Parameter.PosY+1,
										uiScrollBlockSize, uiScrollBlockSize, GUI_COLOR_FRGCLR, GUI_COLOR_FRGCLR);
			}
		}
		else // Horizontal
		{
			// Draw scroll bar edge.
			GUI_Basic_DrawRectangle(pstScrollBar->Parameter.PosX, pstScrollBar->Parameter.PosY,
									pstScrollBar->Parameter.Width, pstScrollBar->Parameter.Height,
									GUI_COLOR_FRGCLR, GUI_COLOR_BKGCLR);
			// Value lower limit is 0, scroll blocks must be greater then 0.
			if(pstScrollBar->Parameter.MaxIndex > 0)
			{
				uiScrollBlockPos = pstScrollBar->Parameter.PosX+1+((pstScrollBar->Parameter.Width-uiScrollBlockSize-2)*pstScrollBar->Data.Index/pstScrollBar->Parameter.MaxIndex);
				// Redraw process block
				GUI_Basic_DrawRectangle(uiScrollBlockPos, pstScrollBar->Parameter.PosY+1,
										uiScrollBlockSize, uiScrollBlockSize, GUI_COLOR_FRGCLR, GUI_COLOR_FRGCLR);
			}
			else
			{
				GUI_Basic_DrawRectangle(pstScrollBar->Parameter.PosX+1, pstScrollBar->Parameter.PosY+1,
										uiScrollBlockSize, uiScrollBlockSize, GUI_COLOR_FRGCLR, GUI_COLOR_FRGCLR);
			}
		}
	}
}
