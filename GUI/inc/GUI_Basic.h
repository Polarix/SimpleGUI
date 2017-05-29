#ifndef __INCLUDE_GUI_BASIC__
#define __INCLUDE_GUI_BASIC__
#include <stddef.h>
#include <stdint.h>
#ifdef __SIMULATOR__
#include "LCD_OperationIF.h"
#else
// Insert screen driver head file here.
#endif

#define		BASIC_FONT_HEIGHT				(8)
#define		BASIC_FONT_WIDTH				(6)
#define		BASIC_FONT_CHAR_DATA_SIZE		(((BASIC_FONT_HEIGHT-1)/8)+1)*BASIC_FONT_WIDTH
#define		BASIC_FONT_DATA					(BASIC_FONT_H8)

typedef struct _st_rectangle_
{
	int16_t		PosX;
	int16_t		PosY;
	uint16_t	Width;
	uint16_t	Height;
}RECTANGLE;

#define 	RECTANGLE_X_START(ST)			((ST).PosX)
#define 	RECTANGLE_X_END(ST)				(((ST).PosX + (ST).Width - 1))
#define 	RECTANGLE_Y_START(ST)			((ST).PosY)
#define 	RECTANGLE_Y_END(ST)				(((ST).PosY + (ST).Height - 1))
#define 	RECTANGLE_WIDTH(ST)				((ST).Width)
#define 	RECTANGLE_HEIGHT(ST)			((ST).Height)
#define 	RECTANGLE_VALID_WIDTH(ST)		((RECTANGLE_X_START(ST)>0)?RECTANGLE_WIDTH(ST):(RECTANGLE_WIDTH(ST)+RECTANGLE_X_START(ST)))
#define		RECTANGLE_VALID_HEIGHT(ST)		((RECTANGLE_Y_START(ST)>0)?RECTANGLE_HEIGHT(ST):(RECTANGLE_HEIGHT(ST)+RECTANGLE_Y_START(ST)))

typedef enum
{
	GUI_COLOR_BKGCLR = 0,
	GUI_COLOR_FRGCLR = 1,
	GUI_COLOR_TRANS	 = 2,
}GUI_COLOR;

typedef enum
{
	GUI_DRAW_NORMAL = 0,
	GUI_DRAW_REVERSE = 1,
}DRAW_MODE;

#define GET_BIT(PAGE, Bit)		((((PAGE) & (0x01 << (Bit)))>0)?1:0)

extern const uint8_t	BASIC_FONT_H8[];
extern const uint8_t	BASIC_FONT_H6[];

void					GUI_ClearScreen(void);
void					GUI_Basic_DrawPoint(uint8_t uiPosX, uint8_t uiPosY, GUI_COLOR eColor);
void					GUI_Basic_DrawLine(uint16_t uiStartX, uint16_t uiStartY, uint16_t uiEndX, uint16_t uiEndY, GUI_COLOR eColor);
void					GUI_Basic_DrawRectangle(uint16_t uiStartX, uint16_t uiStartY, uint16_t uiWidth, uint16_t uiHeight, GUI_COLOR eEdgeColor, GUI_COLOR eFillColor);
void					GUI_Basic_DrawCircle(uint16_t uiCx, uint16_t uiCy, uint16_t uiRadius, GUI_COLOR eEdgeColor, GUI_COLOR eFillColor);
void					GUI_Basic_ReverseBlockColor(uint16_t uiStartX, uint16_t uiStartY, uint16_t uiWidth, uint16_t uiHeight);
void					GUI_Basic_DrawBitMap(RECTANGLE* pstDisplayArea, RECTANGLE* pstDataArea, uint8_t* pDataBuffer, DRAW_MODE eDrawMode);

#endif
