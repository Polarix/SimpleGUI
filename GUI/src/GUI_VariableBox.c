/*************************************************************************/
/** Copyright.															**/
/** FileName: GUI_VariableBox.c											**/
/** Author: XuYulin														**/
/** Version: 1.0.0.0													**/
/** Description: Show and change variable box.							**/
/** History:															**/
/**	XuyYulin	2017/3/10	1.0.0.0		New create.						**/
/** XuYulin 2017/3/10 1.0 build this moudle								**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "GUI_Common.h"
#include "GUI_Basic.h"
#include "GUI_Text.h"
#include "GUI_VariableBox.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
static char				g_TextBuffer[VARBOX_TEXT_BUFFER_SIZE] = {0x00};	//Used when convert a number to text.

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
void					GUI_TextVariableBox_UpdateCharacter(GUI_TXT_VARBOX_STRUCT* pstTextValue, char cNewCharacters, DRAW_MODE eMode);

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
/*************************************************************************/
/** Function Name:	GUI_RefreshVariableBox								**/
/** Purpose:		Display or refresh a integer value edit box.		**/
/** Resources:		12 pix ASCII font data.								**/
/** Params:																**/
/**	@pstValue:			Value structure, include max value, min value	**/
/**						and current value.								**/
/**	@eAlignment:		Alignment, might be right, center or left.		**/
/**	@eMode:				Display mode, normal or reveres.				**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void GUI_IntegerVariableBox_Refresh(GUI_INT_VARBOX_STRUCT* pstValue, GUI_VARBOX_ALIG eAlignment, DRAW_MODE eMode)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	RECTANGLE					stTextDisplayArea;
	RECTANGLE					stTextDataArea;
	size_t						uiTextLength;
	size_t						uiTextWidth;
	GUI_COLOR					eBackColor;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eBackColor					= ((eMode==GUI_DRAW_NORMAL)?GUI_COLOR_BKGCLR:GUI_COLOR_FRGCLR);
	// Draw edge
	GUI_Basic_DrawRectangle(pstValue->PosX, pstValue->PosY, pstValue->Width, VARBOX_HEIGHT, eBackColor, eBackColor);

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/

	if(NULL != pstValue)
	{
		// Check value limited.
		if(pstValue->Value > pstValue->Max)
		{
			pstValue->Value = pstValue->Max;
		}
		if(pstValue->Value < pstValue->Min)
		{
			pstValue->Value = pstValue->Min;
		}
		// Convert number to string
		uiTextLength = GUI_Common_IntegerToString(pstValue->Value, g_TextBuffer, 10, -1, ' ');
		uiTextWidth = VARBOX_TEXT_WIDTH(uiTextLength);
		stTextDisplayArea.PosX = pstValue->PosX+1;
		stTextDisplayArea.PosY = pstValue->PosY+1;
		stTextDisplayArea.Width = VARBOX_TEXT_AREA_WIDTH(pstValue->Width);
		stTextDisplayArea.Height = g_stFontSize[VARBOX_FONT_SIZE].Height;
		switch(eAlignment)
		{
			case GUI_RIGHT:
			{
				stTextDataArea.PosX = stTextDisplayArea.Width - uiTextWidth;
				break;
			}
			case GUI_CENTER:
			{
				stTextDataArea.PosX = (stTextDisplayArea.Width - uiTextWidth) / 2;
				break;
			}
			default:
			{
				stTextDataArea.PosX = 0;
			}
		}
		stTextDataArea.PosY = 0;
		GUI_Text_DrawSingleLineText(g_TextBuffer, VARBOX_FONT_SIZE, &stTextDisplayArea, &stTextDataArea, eMode);
	}
}

/*************************************************************************/
/** Function Name:	GUI_TextVariableBox_UpdateCharacter					**/
/** Purpose:		Display or refresh a integer value edit box.		**/
/** Resources:		12 pix ASCII font data.								**/
/** Params:																**/
/** @pstTextValue:		Text value edit box pointer.					**/
/** @cNewCharacters:	New character of value.							**/
/**	@eMode:				Display mode, normal or reveres.				**/
/** Return:			None.												**/
/** Notice:			Static function, call by others interface.			**/
/*************************************************************************/
void GUI_TextVariableBox_UpdateCharacter(GUI_TXT_VARBOX_STRUCT* pstTextValue, char cNewCharacters, DRAW_MODE eMode)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	GUI_COLOR					eBackColor;
	RECTANGLE					stTextDisplayArea, stTextDataArea;
	RECTANGLE					stFocusArea;
	uint16_t					uiFontWidth, uiFontHeight;
	uint16_t					uiTextLength;
	uint16_t					uiFillIndex;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eBackColor					= ((eMode==GUI_DRAW_NORMAL)?GUI_COLOR_BKGCLR:GUI_COLOR_FRGCLR);
	// Draw edge
	if(NULL != pstTextValue->Value)
	{
		GUI_Basic_DrawRectangle(pstTextValue->PosX, pstTextValue->PosY, pstTextValue->Width, VARBOX_HEIGHT, eBackColor, eBackColor);
	}
	// Get font graphics size.
	uiFontWidth					= g_stFontSize[VARBOX_FONT_SIZE].Width;
	uiFontHeight				= g_stFontSize[VARBOX_FONT_SIZE].Height;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pstTextValue) && (NULL != pstTextValue->Value))
	{
		// Get max text length and graphics width.

		if(pstTextValue->MaxTextLength > VARBOX_TEXT_LENGTH_MAX)
		{
			pstTextValue->MaxTextLength = VARBOX_TEXT_LENGTH_MAX;
		}
		// Ignore too long text string.
		uiTextLength = strlen(pstTextValue->Value);
		if(uiTextLength > pstTextValue->MaxTextLength)
		{
			uiTextLength = pstTextValue->MaxTextLength;
			*(pstTextValue->Value+uiTextLength) = '\0';
            // Point at to last character position if index is more then string length.
			if(pstTextValue->FocusIndex >= pstTextValue->MaxTextLength)
			{
				pstTextValue->FocusIndex = pstTextValue->MaxTextLength-1;
			}
		}
		// Update character in text string when index is valid.
		if(GUI_TEXT_ISASCII(cNewCharacters))
		{
			// Extend string with space if focus index is more then text length.
			if(pstTextValue->FocusIndex >= uiTextLength)
			{
				uiFillIndex = uiTextLength;
				while(uiFillIndex < pstTextValue->FocusIndex)
				{
					*(pstTextValue->Value+uiFillIndex) = ' ';
					uiFillIndex++;
				}
				*(pstTextValue->Value+uiFillIndex) = cNewCharacters;
				uiFillIndex++;
				*(pstTextValue->Value+uiFillIndex) = '\0';
			}
			else
			{
				*(pstTextValue->Value+pstTextValue->FocusIndex) = cNewCharacters;
			}
		}
		// Set text display area.
		stTextDisplayArea.PosX = pstTextValue->PosX+1;
		stTextDisplayArea.PosY = pstTextValue->PosY+1;
		stTextDisplayArea.Width = VARBOX_TEXT_AREA_WIDTH(pstTextValue->Width);
		stTextDisplayArea.Height = uiFontHeight;
		stTextDataArea.PosX = 0;
		stTextDataArea.PosY = 0;

		// Set focus character area.
		stFocusArea.PosX = stTextDisplayArea.PosX+pstTextValue->FocusIndex*uiFontWidth;
		stFocusArea.PosY = stTextDisplayArea.PosY;
		stFocusArea.Width = uiFontWidth;
		stFocusArea.Height = uiFontHeight;
		if(RECTANGLE_X_END(stFocusArea) > RECTANGLE_X_END(stTextDisplayArea))
		{
			stTextDataArea.PosX = RECTANGLE_X_END(stTextDisplayArea) - RECTANGLE_X_END(stFocusArea);
			stFocusArea.PosX = stFocusArea.PosX + stTextDataArea.PosX;
		}
		// Display text.
		GUI_Text_DrawSingleLineText(pstTextValue->Value, VARBOX_FONT_SIZE, &stTextDisplayArea, &stTextDataArea, eMode);
		// Focus first character.
        GUI_Basic_ReverseBlockColor(stFocusArea.PosX, stFocusArea.PosY, stFocusArea.Width, stFocusArea.Height);
	}
}

/*************************************************************************/
/** Function Name:	GUI_TextVariableBox_Refresh							**/
/** Purpose:		Display or refresh a integer value edit box.		**/
/** Resources:		12 pix ASCII font data.								**/
/** Params:																**/
/** @pstTextValue:		Text value edit box pointer.					**/
/**	@eMode:				Display mode, normal or reveres.				**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void GUI_TextVariableBox_Refresh(GUI_TXT_VARBOX_STRUCT* pstTextValue, DRAW_MODE eMode)
{

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstTextValue)
	{
		if(NULL != pstTextValue->Value)
		{
			if(pstTextValue->FocusIndex >= pstTextValue->MaxTextLength)
			{
				pstTextValue->FocusIndex = pstTextValue->MaxTextLength-1;
			}
			GUI_TextVariableBox_UpdateCharacter(pstTextValue, '\0', eMode);
		}
	}
}

/*************************************************************************/
/** Function Name:	GUI_TextVariableBox_PrevCharacter					**/
/** Purpose:		Select previous character at current index.			**/
/** Resources:		12 pix ASCII font data.								**/
/** Params:																**/
/** @pstTextValue:		Text value edit box pointer.					**/
/**	@eMode:				Display mode, normal or reveres.				**/
/**	@uiCharacterSet:	Mask of characters set.							**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void GUI_TextVariableBox_ChangeCharacter(GUI_TXT_VARBOX_STRUCT* pstTextValue, DRAW_MODE eMode, uint16_t uiCharacterSet, GUI_TXT_VARBOX_OPT eOpt)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	char						cCurChar;
	bool						bUpdated;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	cCurChar					= '\0';
	bUpdated					= false;
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstTextValue)
	{
		if(NULL != pstTextValue->Value)
		{
			cCurChar = *(pstTextValue->Value+pstTextValue->FocusIndex);
			while(false == bUpdated)
			{
				cCurChar += (int32_t)eOpt;
				if(cCurChar > 0x7E)
				{
					cCurChar = 0x20;
				}
				if(cCurChar < 0x20)
				{
					cCurChar = 0x7E;
				}
				if(GUI_TEXT_ISDIGIT(cCurChar) || ('.' == cCurChar) || ('-' == cCurChar))
				{
					if(uiCharacterSet & GUI_TEXT_NUMBER)
					{
						bUpdated = true;
					}
				}
				if(GUI_TEXT_ISALPHA(cCurChar))
				{
					if(uiCharacterSet & GUI_TEXT_ALPHA)
					{
						bUpdated = true;
					}
				}
				if((!GUI_TEXT_ISDIGIT(cCurChar)) && (!(GUI_TEXT_ISALPHA(cCurChar))))
				{
					if(uiCharacterSet & GUI_TEXT_PUNCTUATION)
					{
						bUpdated = true;
					}
				}
			}
			GUI_TextVariableBox_UpdateCharacter(pstTextValue, cCurChar, eMode);
		}
	}
}
