/*************************************************************************/
/** Copyright.															**/
/** FileName: GUI_Font.c												**/
/** Author: XuYulin														**/
/** Version: 1.0.0.0													**/
/** Description: XML operations.										**/
/** History:															**/
/**	XuyYulin	2017/2/24	2.0.0.0		New create.						**/
/** XuYulin 2017/2/24 1.0 build this moudle								**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "GUI_Common.h"
#include "GUI_Text.h"
#include "GUI_Basic.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
#include "FONT_H12.h"
#include "FONT_H16.h"

uint8_t						auiFontDataBuffer[FONT_DATA_BUFFER_SIZE] = {0x00};
const GUI_FONT_SIZE_STRUCT	g_stFontSize[GUI_FONT_SIZE_MAX] = {	{6, 4, 6},
														{8, 6, 8},
														{12, 6, 12},
														{16, 8, 16},
														{24, 12, 24},
														{32, 16, 32}};

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static void					GUI_Text_ReadExtendedFontData(GUI_FONT_SIZE eFontSize, uint32_t uiCharacterCode, uint8_t* pOutPutBuffer, uint32_t uiFontBufferSize);
static size_t				GUI_Text_GetCharacterTableIndex(uint16_t uiCharacterCode);

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//

/*****************************************************************************/
/** Function Name:	GUI_DrawText											**/
/** Purpose:		Write a basic font character module to lcd buffer.		**/
/** Resources:		Basic character font module data.						**/
/** Params:																	**/
/**	@szTextBuffer:		Text array pointer.									**/
/**	@uiFontSize:		Font size.											**/
/**	@pstDisplayArea:	Display area size.									**/
/**	@pstStringDataArea:	Text area size.										**/
/**	@eFontMode			Character display mode(normal or reverse color).	**/
/** Return:			Next character X coordinate in current line.			**/
/** Limitation:		None.													**/
/*****************************************************************************/
void GUI_Text_DrawSingleLineText(char* szTextBuffer, GUI_FONT_SIZE eFontSize, RECTANGLE* pstDisplayArea, RECTANGLE* pstTextDataArea, DRAW_MODE eFontMode)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	char*		pcTextPointer;										// Text character pointer.
	uint16_t	uiCodeHighByte, uiCodeLowByte, uiCharacterCode;		// Character byte, might be tow bytes.
	uint16_t	uiFontWidth, uiFontHeight, uiCharacterWidth;		// Font size and character graphics width.
	RECTANGLE	stCharacterDataArea = {0};
	GUI_COLOR	eBackColor;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	// Initialize variable.
	pcTextPointer				= szTextBuffer;
	uiCharacterCode				= 0x0000;
	eBackColor					= (eFontMode == GUI_DRAW_NORMAL)?GUI_COLOR_BKGCLR:GUI_COLOR_FRGCLR;
	// Get font graphics size.
	uiFontWidth					= g_stFontSize[eFontSize].Width;
	uiFontHeight				= g_stFontSize[eFontSize].Height;
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((szTextBuffer != NULL) && (RECTANGLE_X_START(*pstDisplayArea) < LCD_SIZE_WIDTH))
	{
		// Recalculate text display area and data area.
        if(RECTANGLE_X_START(*pstDisplayArea) < 0)
		{
			RECTANGLE_X_START(*pstTextDataArea) += RECTANGLE_X_START(*pstDisplayArea);
			RECTANGLE_WIDTH(*pstDisplayArea) += RECTANGLE_X_START(*pstDisplayArea);
			RECTANGLE_X_START(*pstDisplayArea) = 0;
		}
		if(RECTANGLE_Y_START(*pstDisplayArea) < 0)
		{
			RECTANGLE_Y_START(*pstTextDataArea) += RECTANGLE_Y_START(*pstDisplayArea);
			RECTANGLE_HEIGHT(*pstDisplayArea) += RECTANGLE_Y_START(*pstDisplayArea);
			RECTANGLE_Y_START(*pstDisplayArea) = 0;
		}
		// Clear text area.
        GUI_Basic_DrawRectangle(RECTANGLE_X_START(*pstDisplayArea), RECTANGLE_Y_START(*pstDisplayArea),
						RECTANGLE_WIDTH(*pstDisplayArea), RECTANGLE_HEIGHT(*pstDisplayArea),
						eBackColor, eBackColor);
		// Initialize drawing area data.
		RECTANGLE_X_START(stCharacterDataArea) = RECTANGLE_X_START(*pstTextDataArea);
		RECTANGLE_Y_START(stCharacterDataArea) = RECTANGLE_Y_START(*pstTextDataArea);
		RECTANGLE_HEIGHT(stCharacterDataArea) = uiFontHeight;
		// Loop for Each char.
		while((*pcTextPointer != '\0') && (RECTANGLE_X_START(stCharacterDataArea) < RECTANGLE_WIDTH(*pstDisplayArea)))
		{
			// Get character.
			uiCodeHighByte = 0x00;
			uiCodeLowByte = 0x00;
			// Process with ASCII code.
			if((uint8_t)(*pcTextPointer) < 0x7F)
			{
				uiCodeLowByte = (uint8_t)*pcTextPointer++;
				uiCharacterWidth = uiFontWidth;
			}
			// Process with GB2312.
			else if(((uint8_t)(*pcTextPointer) >= 0xA1) && ((uint8_t)(*pcTextPointer) <= 0xF7))
			{
				uiCodeHighByte = (uint8_t)*pcTextPointer++;
				uiCodeLowByte = (uint8_t)*pcTextPointer++;
				uiCharacterWidth = uiFontWidth << 1;	//uiCharacterWidth = uiFontWidth * 2; for full-width character;
			}
			// Invalid character
			else
			{
				uiCharacterWidth = 0;
				pcTextPointer++;
			}
			uiCharacterCode = uiCodeHighByte;
			uiCharacterCode = uiCharacterCode << 8;
			uiCharacterCode = uiCharacterCode | uiCodeLowByte;

			RECTANGLE_WIDTH(stCharacterDataArea) = uiCharacterWidth;

			if(RECTANGLE_X_END(stCharacterDataArea) >= 0)
			{
				// Read Font data.
				GUI_Text_ReadExtendedFontData(eFontSize, uiCharacterCode, (uint8_t*)auiFontDataBuffer, 512);
				// Display character.
				GUI_Basic_DrawBitMap(pstDisplayArea, &stCharacterDataArea, (uint8_t*)auiFontDataBuffer, (DRAW_MODE)eFontMode);
			}
			RECTANGLE_X_START(stCharacterDataArea) += uiCharacterWidth;
		}
	}
}


/*****************************************************************************/
/** Function Name:	GUI_DrawMultipleLinesText								**/
/** Purpose:		Write a mulitiplt line text in a rectangular area.		**/
/** Resources:		Character font module data.								**/
/** Params:																	**/
/**	@szTextBuffer:		Text array pointer.									**/
/**	@uiFontSize:		Font size.											**/
/**	@pstDisplayArea:	Display area size.									**/
/**	@eFontMode			Character display mode(normal or reverse color).	**/
/** Return:			Next character X coordinate in current line.			**/
/** Notice:			None.													**/
/*****************************************************************************/
uint16_t GUI_Text_DrawMultipleLinesText(char* szTextBuffer, GUI_FONT_SIZE eFontSize, RECTANGLE* pstDisplayArea, int16_t iTopOffset, DRAW_MODE eFontMode)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	char*						pcTextPointer;
	uint16_t					uiCodeHighByte, uiCodeLowByte, uiCharacterCode;
	uint16_t					uiFontWidth, uiFontHeight;
	uint16_t					uiLines;
	RECTANGLE					stCharacterDataArea = {0};
	GUI_COLOR					eBackColor;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	pcTextPointer				= szTextBuffer;
	uiCharacterCode				= 0x0000;
	uiLines						= 0;
	eBackColor					= (eFontMode == GUI_DRAW_NORMAL)?GUI_COLOR_BKGCLR:GUI_COLOR_FRGCLR;
	// Get font graphics size.
	uiFontWidth					= g_stFontSize[eFontSize].Width;
	uiFontHeight				= g_stFontSize[eFontSize].Height;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((szTextBuffer != NULL) && (RECTANGLE_X_START(*pstDisplayArea) < LCD_SIZE_WIDTH))
	{
		// Recalculate text display area and data area.
		if(RECTANGLE_X_START(*pstDisplayArea) < 0)
		{
			RECTANGLE_X_START(stCharacterDataArea) += RECTANGLE_X_START(*pstDisplayArea);
			RECTANGLE_WIDTH(*pstDisplayArea) += RECTANGLE_X_START(*pstDisplayArea);
			RECTANGLE_X_START(*pstDisplayArea) = 0;
		}
		if(RECTANGLE_Y_START(*pstDisplayArea) < 0)
		{
			RECTANGLE_Y_START(stCharacterDataArea) += RECTANGLE_Y_START(*pstDisplayArea);
			RECTANGLE_HEIGHT(*pstDisplayArea) += RECTANGLE_Y_START(*pstDisplayArea);
			RECTANGLE_Y_START(*pstDisplayArea) = 0;
		}
		// Clear text area.
        GUI_Basic_DrawRectangle(RECTANGLE_X_START(*pstDisplayArea), RECTANGLE_Y_START(*pstDisplayArea),
						RECTANGLE_WIDTH(*pstDisplayArea), RECTANGLE_HEIGHT(*pstDisplayArea),
						eBackColor, eBackColor);
		// Initialize drawing area data.
		RECTANGLE_X_START(stCharacterDataArea)		= 0;
		RECTANGLE_Y_START(stCharacterDataArea)		= iTopOffset;
		RECTANGLE_HEIGHT(stCharacterDataArea)		= uiFontHeight;
		uiLines										= 1;

		// Loop for each word in display area.
		while(*pcTextPointer != '\0')
		{
			uiCodeHighByte = 0x00;
			uiCodeLowByte = 0x00;
			// Judge change line symbol.
			if(*pcTextPointer == '\n')
			{
                if(RECTANGLE_X_START(stCharacterDataArea) == 0)
				{
					// Ignore change lines in line start.
				}
				else
				{
					// Change lines.
					RECTANGLE_X_START(stCharacterDataArea) = 0;
					RECTANGLE_Y_START(stCharacterDataArea) += uiFontHeight;
					uiLines ++;
				}
				pcTextPointer++;
				continue;
			}
			// Process with ASCII code.
			if(((uint8_t)(*pcTextPointer) < 0x7F) && ((uint8_t)(*pcTextPointer) >= 0x20))
			{
				uiCodeLowByte = (uint8_t)*pcTextPointer++;
				RECTANGLE_WIDTH(stCharacterDataArea) = uiFontWidth;
			}
			// Process with GB2312.
			else if(((uint8_t)(*pcTextPointer) >= 0xA1) && ((uint8_t)(*pcTextPointer) <= 0xF7))
			{
				uiCodeHighByte = (uint8_t)*pcTextPointer++;
				uiCodeLowByte = (uint8_t)*pcTextPointer++;
				RECTANGLE_WIDTH(stCharacterDataArea) = uiFontWidth << 1;
			}
			// Invalid character
			else
			{
				pcTextPointer++;
				RECTANGLE_WIDTH(stCharacterDataArea) = 0;
				continue;
			}
			uiCharacterCode = uiCodeHighByte;
			uiCharacterCode = uiCharacterCode << 8;
			uiCharacterCode = uiCharacterCode | uiCodeLowByte;

			// Judge change line
			if(RECTANGLE_X_END(stCharacterDataArea) >= RECTANGLE_WIDTH(*pstDisplayArea))
			{
				// Change lines.
				RECTANGLE_X_START(stCharacterDataArea) = 0;
				RECTANGLE_Y_START(stCharacterDataArea) += uiFontHeight;
				uiLines ++;
			}
			// Draw characters.
			if((RECTANGLE_Y_END(stCharacterDataArea) >= 0) && (RECTANGLE_Y_START(stCharacterDataArea) < RECTANGLE_HEIGHT(*pstDisplayArea)))
			{
				// Read Font data.
				GUI_Text_ReadExtendedFontData(eFontSize, uiCharacterCode, (uint8_t*)auiFontDataBuffer, 512);
				GUI_Basic_DrawBitMap(pstDisplayArea, &stCharacterDataArea, (uint8_t*)auiFontDataBuffer, eFontMode);
			}
			else
			{
				// character is not in visible area, ignore.
			}
			RECTANGLE_X_START(stCharacterDataArea) += RECTANGLE_WIDTH(stCharacterDataArea);
		}
	}
	return uiLines;
}

/*****************************************************************************/
/** Function Name:	GUI_Text_ReadExtendedFontData							**/
/** Purpose:		Read font from internal or external flash memory.		**/
/** Resources:		External flash read interface.							**/
/** Params:																	**/
/**	@uiFontSize: 		Start address of font data.							**/
/**	@uiCharacterCode:	Data buffer pointer of read font data.				**/
/**	@pDataBuffer:		Read data size.										**/
/**	@uiFontBufferSize:	Free space for font buffer, 0 means ignore the		**/
/**						data size judgment.									**/
/** Return:			None.													**/
/** Limitation:		None.													**/
/*****************************************************************************/
void GUI_Text_ReadExtendedFontData(GUI_FONT_SIZE eFontSize, uint32_t uiCharacterCode, uint8_t* pOutPutBuffer, uint32_t uiFontBufferSize)
{
	// Need rewrite this function for use each different external font data.
	uint32_t	uiCharacterIndex;
	uint16_t	uiFontWidth, uiFontHeight;
	uint32_t	uiCharacterDataSize;
	uint8_t*	puiFontDataArrayPointer;
	uint16_t	i;

	// Get character font data index in font table.
	uiCharacterIndex = GUI_Text_GetCharacterTableIndex(uiCharacterCode);
	// Calculates the byte used by each half-width character.
	// Get font graphics size.
	uiFontWidth					= g_stFontSize[eFontSize].Width;
	uiFontHeight				= g_stFontSize[eFontSize].Height;

	uiCharacterDataSize = (((uiFontHeight-1)/8)+1)*uiFontWidth;
	switch(eFontSize)
	{

		case(GUI_FONT_SIZE_H12):
		{
			puiFontDataArrayPointer = (uint8_t*)FONT_H12;
			break;
		}
		case(GUI_FONT_SIZE_H16):
		{
			puiFontDataArrayPointer = (uint8_t*)FONT_H16;
			break;
		}
		/*
		case(FONT_SIZE_H24):
		{
			puiFontDataArrayPointer = (uint8_t*)FONT_H24;
			break;
		}
		case(FONT_SIZE_H32):
		{
			puiFontDataArrayPointer = (uint8_t*)FONT_H32;
			break;
		}
		*/
		default:
		{
			// In other cases, the basic font is used.
			puiFontDataArrayPointer = (uint8_t*)BASIC_FONT_DATA;
			uiFontWidth = 6;
			uiFontHeight = 8;
		}
	}
	// Set character font data head pointer.
	puiFontDataArrayPointer = puiFontDataArrayPointer + (uiCharacterDataSize * uiCharacterIndex);
	// Check Buffer size area.
	if(uiCharacterCode > 127)
	{
		// Non-ASCII characters
		// For GB2312, full-width character use 2 bytes encoding.
		uiCharacterDataSize = uiCharacterDataSize * 2;
	}
	// Copy data to buffer.
	for(i=0; i<uiCharacterDataSize; i++)
	{
		*(pOutPutBuffer+i) = *(puiFontDataArrayPointer + i);
	}
}

size_t GUI_Text_GetCharacterTableIndex(uint16_t uiCharacterCode)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint8_t						uiCharacterCodeHighByte;
	uint8_t						uiCharacterCodeLowByte;
	size_t						uiFontTableIndex;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	uiCharacterCodeHighByte =	(uiCharacterCode >> 8) & 0x00FF;
	uiCharacterCodeLowByte =	uiCharacterCode & 0x00FF;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// ASCII code.
	if((0 == uiCharacterCodeHighByte) && (uiCharacterCodeLowByte < 128))
	{
		uiFontTableIndex = (uiCharacterCodeLowByte + FONT_LIB_OFFSET_ASCII);
	}
	// GB2312 punctuation
	else if((0xAA > uiCharacterCodeHighByte) && (0xA0 < uiCharacterCodeHighByte))
	{
		uiFontTableIndex = ((((uiCharacterCodeHighByte-0xA1)*94 + (uiCharacterCodeLowByte-0xA1))*2) + FONT_LIB_OFFSET_GB2312_SYMBOL);
	}
	// GB2312 level one character.
	else if((0xF8 > uiCharacterCodeHighByte) && (0xAF < uiCharacterCodeHighByte))
	{
		uiFontTableIndex = ((((uiCharacterCodeHighByte-0xB0)*94 + (uiCharacterCodeLowByte-0xA1))*2) + FONT_LIB_OFFSET_GB2312_CHARL1);
	}
	// Other to return full width space.
	else
	{
        uiFontTableIndex = FONT_LIB_OFFSET_GB2312_SYMBOL;	// Full-size space.
	}

	return uiFontTableIndex;
}

/*****************************************************************************/
/** Function Name:	GUI_Text_GetTextGraphicsWidth							**/
/** Purpose:		Get text displayed full width.							**/
/** Resources:		None.													**/
/** Params:																	**/
/**	@szText[in]: 		Text pointer.										**/
/**	@eFontSize[in]:		Font size, usually means font height.				**/
/** Return:			None.													**/
/** Notice:			Only used with Equal-width characters. 					**/
/*****************************************************************************/
size_t	GUI_Text_GetTextGraphicsWidth(char* szText, GUI_FONT_SIZE eFontSize)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
    size_t						uiTextHalfCharLength;
    uint16_t					uiHalfFontWidth;
    size_t						uiTextGraphicsWidth;
	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	uiTextHalfCharLength =		0;
	uiTextGraphicsWidth =		0;
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != szText)
	{
		uiTextHalfCharLength = GUI_Common_StringLength(szText);
		uiHalfFontWidth = g_stFontSize[eFontSize].Width;
		uiTextGraphicsWidth = uiHalfFontWidth * uiTextHalfCharLength;
	}
	return uiTextGraphicsWidth;
}
