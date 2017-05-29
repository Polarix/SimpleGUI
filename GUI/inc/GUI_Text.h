#ifndef _INCLUDE_GUI_FONT_H_
#define _INCLUDE_GUI_FONT_H_
#include <stddef.h>
#include <stdint.h>
#include "GUI_Basic.h"

#define FONT_LIB_ADDR					0X00000
#define FONT_LIB_OFFSET_ASCII			(-32)
#define FONT_LIB_OFFSET_GB2312_SYMBOL	(95)
#define FONT_LIB_OFFSET_GB2312_CHARL1	(659)
// Max font size is 64 pix, maximum of font data size is 64 * 8 = 512 Bytes.
#define FONT_DATA_BUFFER_SIZE			(512)
#define TEXT_NUMBER_STR_LENGTH_MAX		(12)
#define TEXT_PLACEHOLDER_CHARACTER		('*')

typedef enum
{
	FONT_MODULE_BASIC = 0,
	FONT_MODULE_NORMAL,
}FONT_MODULE;

typedef struct
{
	const uint16_t	Size;
	const uint16_t	Width;
	const uint16_t	Height;
}GUI_FONT_SIZE_STRUCT;

typedef enum
{
	GUI_FONT_SIZE_H6 = 0,
	GUI_FONT_SIZE_H8,
	GUI_FONT_SIZE_H12,
	GUI_FONT_SIZE_H16,
	GUI_FONT_SIZE_H24,
	GUI_FONT_SIZE_H32,
	GUI_FONT_SIZE_MAX,
}GUI_FONT_SIZE;

extern const GUI_FONT_SIZE_STRUCT g_stFontSize[];

void		GUI_Text_DrawSingleLineText(char* szTextBuffer, GUI_FONT_SIZE eFontSize, RECTANGLE* pstDisplayArea, RECTANGLE* pstStringDataArea, DRAW_MODE eFontMode);
uint16_t	GUI_Text_DrawMultipleLinesText(char* szTextBuffer, GUI_FONT_SIZE eFontSize, RECTANGLE* pstDisplayArea, int16_t iTopOffset, DRAW_MODE eFontMode);
size_t		GUI_Text_GetTextGraphicsWidth(char* szText, GUI_FONT_SIZE eFontSize);

#endif
