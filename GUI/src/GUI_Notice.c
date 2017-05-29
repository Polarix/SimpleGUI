/*************************************************************************/
/** Copyright.															**/
/** FileName: GUI_Notice.c												**/
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
#include "GUI_Common.h"
#include "GUI_Basic.h"
#include "GUI_Text.h"
#include "GUI_Notice.h"

#include <string.h>

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
#if NOTICE_ICON_SIZE == 16
static const uint8_t ICON_DATA_ERROR[] = {
0xFF,0x01,0x01,0x19,0x39,0x71,0xE1,0xC1,0xC1,0xE1,0x71,0x39,0x19,0x01,0x01,0xFF,
0xFF,0x80,0x80,0x98,0x9C,0x8E,0x87,0x83,0x83,0x87,0x8E,0x9C,0x98,0x80,0x80,0xFF
};

static const uint8_t ICON_DATA_INFORMATION[] = {
0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0xED,0xED,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0xBF,0xBF,0x80,0x80,0x80,0x80,0x80,0x80,0xFF
};

static const uint8_t ICON_DATA_QUESTION[] = {
0xFF,0x01,0x01,0x01,0x31,0x39,0x1D,0x0D,0x0D,0x9D,0xF9,0xF1,0x01,0x01,0x01,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0xB6,0xB7,0x83,0x81,0x80,0x80,0x80,0x80,0xFF
};

static const uint8_t ICON_DATA_WARNING[] = {
0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0xFD,0xFD,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0xB7,0xB7,0x80,0x80,0x80,0x80,0x80,0x80,0xFF
};
#elif NOTICE_ICON_SIZE == 24
static const uint8_t ICON_DATA_ERROR[] = {
0xFF,0x01,0x01,0x01,0x71,0xF1,0xF1,0xE1,0xC1,0x81,0x01,0x01,0x01,0x01,0x81,0xC1,0xE1,0xF1,0xF1,0x71,0x01,0x01,0x01,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x81,0xC3,0xE7,0xFF,0xFF,0x7E,0x7E,0xFF,0xFF,0xE7,0xC3,0x81,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x80,0x80,0x80,0x8E,0x8F,0x8F,0x87,0x83,0x81,0x80,0x80,0x80,0x80,0x81,0x83,0x87,0x8F,0x8F,0x8E,0x80,0x80,0x80,0xFF
};

static const uint8_t ICON_DATA_INFORMATION[] = {
0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x79,0x79,0x79,0x79,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x98,0x9F,0x9F,0x9F,0x9F,0x98,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF
};

static const uint8_t ICON_DATA_QUESTION[] = {
0xFF,0x01,0x01,0x01,0x01,0x01,0xC1,0xE1,0xF1,0xF1,0x79,0x79,0x79,0x79,0xF1,0xF1,0xE1,0xC1,0x81,0x01,0x01,0x01,0x01,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x03,0x03,0x03,0x03,0x00,0xC0,0xE0,0xF0,0xF8,0x7C,0x3F,0x1F,0x0F,0x07,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x9E,0x9E,0x9E,0x9E,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF
};

static const uint8_t ICON_DATA_WARNING[] = {
0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xF1,0xF9,0xF9,0xF1,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFF,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x9E,0x9E,0x9E,0x9E,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF
};
#endif // NOTICE_ICON_SIZE

const uint8_t* g_arrNoticeIcon[] = {
	NULL,
	(const uint8_t*)ICON_DATA_ERROR,
	(const uint8_t*)ICON_DATA_INFORMATION,
	(const uint8_t*)ICON_DATA_QUESTION,
	(const uint8_t*)ICON_DATA_WARNING
};

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static uint16_t GUI_Notice_GetNoticeLines(char* szNoticeText, uint16_t uiNoticeLineByteMax);

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
/*****************************************************************************/
/** Function Name:	GUI_ShowNotice											**/
/** Purpose:		Show a notice box.										**/
/** Resources:		Icon data.												**/
/** Params:																	**/
/**	@szNoticeText:		Notice text.										**/
/**	@eIcon:				Notice icon.										**/
/** Return:			Remaining text height display.							**/
/** Notice:			None.													**/
/*****************************************************************************/
uint16_t GUI_Notice_ShowNotice(char* szNoticeText, uint16_t uiTextOffset, NOTICE_ICON eIcon)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint16_t	uiLineCount;
	uint16_t	uiNoticeBoxHeight;
	uint16_t	uiTextLines;
	RECTANGLE	stTextDisplayArea;
	RECTANGLE	stIconDisplayArea, stIconDataArea;
	char*       pszNoticeTextPtr;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Encode string if defined.
	#ifdef GB2312_ENCV
	pszNoticeTextPtr = ENCODE(szNoticeText);
	#else
	pszNoticeTextPtr = szNoticeText;
	#endif
	// Get max line of notice text.
	if(GUI_ICON_NONE != eIcon)
	{
		uiLineCount = GUI_Notice_GetNoticeLines(pszNoticeTextPtr, NOTICE_TEXT_LINES_MAX);
	}
	else
	{
		uiLineCount = GUI_Notice_GetNoticeLines(pszNoticeTextPtr, NOTICE_TEXT_LINES_MAX_NOICON);
	}
	if(uiLineCount < 2)
	{
		uiLineCount = 2;
	}
	uiNoticeBoxHeight = NOTICE_BOX_HEIGHT(uiLineCount);
	if(uiNoticeBoxHeight > NOTICE_BOX_HEIGHT_MAX)
	{
		uiNoticeBoxHeight = NOTICE_BOX_HEIGHT_MAX;
	}
	// Draw edge
    GUI_Basic_DrawRectangle(NOTICE_BOX_POSX, NOTICE_BOX_POSY(uiNoticeBoxHeight), NOTICE_BOX_WIDTH, uiNoticeBoxHeight, GUI_COLOR_FRGCLR, GUI_COLOR_BKGCLR);
    // Draw icon if exists.
    if(GUI_ICON_NONE != eIcon)
	{
		stIconDisplayArea.PosX = NOTICE_BOX_POSX+NOTICE_BOX_MARGIN;
		stIconDisplayArea.PosY = NOTICE_BOX_POSY(uiNoticeBoxHeight)+NOTICE_BOX_MARGIN;
		stIconDisplayArea.Width = NOTICE_ICON_SIZE;
		stIconDisplayArea.Height = NOTICE_ICON_SIZE;
		stIconDataArea.PosX = 0;
		stIconDataArea.PosY = 0;
		stIconDataArea.Width = NOTICE_ICON_SIZE;
		stIconDataArea.Height = NOTICE_ICON_SIZE;
		GUI_Basic_DrawBitMap(&stIconDisplayArea, &stIconDataArea, (uint8_t*)g_arrNoticeIcon[eIcon], GUI_DRAW_NORMAL);
	}
    // Draw text;
    if(GUI_ICON_NONE != eIcon)
	{
		stTextDisplayArea.PosX = NOTICE_TEXT_POSX;
		stTextDisplayArea.Width = NOTICE_TEXT_AREA_WIDTH;
	}
	else
	{
		stTextDisplayArea.PosX = NOTICE_TEXT_POSX_NOICON;
		stTextDisplayArea.Width = NOTICE_TEXT_AREA_WIDTH_NOICON;;
	}
	stTextDisplayArea.PosY = NOTICE_TEXT_POSY(uiNoticeBoxHeight);
	stTextDisplayArea.Height = NOTICE_TEXT_AREA_HEIGHT(uiLineCount);
    if(stTextDisplayArea.Height > NOTICE_TEXT_AREA_HEIGHT_MAX)
	{
		stTextDisplayArea.Height = NOTICE_TEXT_AREA_HEIGHT_MAX;
	}
    uiTextLines = GUI_Text_DrawMultipleLinesText(pszNoticeTextPtr, NOTICE_FONT_SIZE, &stTextDisplayArea, uiTextOffset, GUI_DRAW_NORMAL);

    return uiTextLines;
}

/*****************************************************************************/
/** Function Name:	GUI_GetNoticeLineIndex									**/
/** Purpose:		Break string and record line character index in global	**/
/**					array.													**/
/** Resources:		Line start index array(g_arrLineTextIndex).				**/
/** Params:																	**/
/**	@szNoticeText:		Notice text resource.								**/
/** Return:			Line number of will be displayed.						**/
/** Limitation:		None.													**/
/*****************************************************************************/
uint16_t GUI_Notice_GetNoticeLines(char* szNoticeText, uint16_t uiNoticeLineByteMax)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint16_t	uiLineCount, uiLineByteCount;
	char*		pcCur;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	uiLineByteCount				= 0;
	uiLineCount					= 1;
	pcCur						= szNoticeText;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pcCur)
	{
		while('\0' != *pcCur)
		{
			if(*pcCur == '\n')
			{
                if(uiLineByteCount > 0)
				{
					// Change lines.
					uiLineCount ++;
					uiLineByteCount = 0;
				}
				else
				{
					// Ignore change lines in line start.
				}
				pcCur++;
				continue;
			}

			if((uint8_t)(*pcCur) < 0x7F)
			{
				if(uiLineByteCount<uiNoticeLineByteMax)
				{
					uiLineByteCount++;
				}
				else
				{
					uiLineByteCount = 1;
					uiLineCount++;
				}
				pcCur++;
			}
			// Process with GB2312.
			else if(((uint8_t)(*pcCur) >= 0xA1) && ((uint8_t)(*pcCur) <= 0xF7))
			{
				//GB2312
				if((uiNoticeLineByteMax-uiLineByteCount)>2)
				{
					uiLineByteCount+=2;
				}
				else
				{
					uiLineByteCount = 2;
					uiLineCount++;
				}
				pcCur+=2;
			}
			// Invalid character
			else
			{
				pcCur++;
			}
		}
	}
	return uiLineCount;
}



