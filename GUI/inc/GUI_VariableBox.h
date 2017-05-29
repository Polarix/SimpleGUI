#ifndef __INCLUDE_GUI_VARIABLEBOX_H__
#define __INCLUDE_GUI_VARIABLEBOX_H__

#include <stddef.h>
#include <stdint.h>
#include "GUI_Basic.h"
#include "GUI_Text.h"

#define VARBOX_FONT_SIZE				(GUI_FONT_SIZE_H12)
#define VARBOX_WIDTH(L)					(L*(g_stFontSize[VARBOX_FONT_SIZE].Width)-4)
#define VARBOX_HEIGHT					(g_stFontSize[VARBOX_FONT_SIZE].Height+2)
#define VARBOX_TEXT_AREA_WIDTH(W)		((W>2)?(W-2):0)
#define VARBOX_TEXT_AREA_HEIGHT			(g_stFontSize[VARBOX_FONT_SIZE].Height)

#define VARBOX_TEXT_LENGTH_MAX			(32)
#define VARBOX_TEXT_BUFFER_SIZE			(VARBOX_TEXT_LENGTH_MAX+1)
#define VARBOX_TEXT_WIDTH(L)			(L*(g_stFontSize[VARBOX_FONT_SIZE].Width))

typedef struct
{
	uint16_t	PosX;
	uint16_t	PosY;
	uint16_t	Width;
	int32_t		Min;
	int32_t		Max;
	int32_t		Value;
}GUI_INT_VARBOX_STRUCT;

typedef struct
{
	uint16_t	PosX;
	uint16_t	PosY;
	uint16_t	Width;
	uint16_t	FocusIndex;
	uint16_t	MaxTextLength;
	char*		Value;
}GUI_TXT_VARBOX_STRUCT;

typedef enum
{
	GUI_RIGHT = 0,
	GUI_CENTER,
	GUI_LEFT,
}GUI_VARBOX_ALIG;

enum
{
	GUI_TEXT_NUMBER			= 0x0100,
	GUI_TEXT_ALPHA			= 0x0200,
	GUI_TEXT_PUNCTUATION	= 0x0400,
	GUI_TEXT_DATE			= 0x0800,
	GUI_TEXT_TIME			= 0x1000,
};

typedef enum
{
    GUI_TXT_VARBOX_OPT_PREV = -1,
    GUI_TXT_VARBOX_OPT_NONE = 0,
    GUI_TXT_VARBOX_OPT_NEXT = 1,
}GUI_TXT_VARBOX_OPT;

#define GUI_TEXT_ASCII					(GUI_TEXT_NUMBER|GUI_TEXT_ALPHA|GUI_TEXT_PUNCTUATION)

#define GUI_TEXT_ISDIGIT(C)				((C>='0' && C<='9')?true:false)
#define GUI_TEXT_ISUPPER(C)				((C>='A' && C<='Z')?true:false)
#define GUI_TEXT_ISLOWER(C)				((C>='a' && C<='z')?true:false)
#define GUI_TEXT_ISALPHA(C)				(GUI_TEXT_ISUPPER(C) || GUI_TEXT_ISLOWER(C))
#define GUI_TEXT_ISASCII(C)				((C>=0x20 && C<=0x7E)?true:false)

size_t			GUI_GetNumberTextWidth(int32_t iValue);
void			GUI_IntegerVariableBox_Refresh(GUI_INT_VARBOX_STRUCT* pstValue, GUI_VARBOX_ALIG eAlignment, DRAW_MODE eMode);
void			GUI_TextVariableBox_Refresh(GUI_TXT_VARBOX_STRUCT* pstTextValue, DRAW_MODE eMode);
void			GUI_TextVariableBox_ChangeCharacter(GUI_TXT_VARBOX_STRUCT* pstTextValue, DRAW_MODE eMode, uint16_t uiCharacterSet, GUI_TXT_VARBOX_OPT eOpt);



#endif // __INCLUDE_GUI_VARIABLEBOX_H__
