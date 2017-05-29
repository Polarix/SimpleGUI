#ifndef __INCLUDE_LCD_OPERATIONIF_H__
#define __INCLUDE_LCD_OPERATIONIF_H__
#include "LCD_VirtualDeviceParameter.h"
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define		RECT_START_X(R)				(R.StartPosX)
#define		RECT_START_Y(R)				(R.StartPosY)
#define		RECT_END_X(R)				(R.EndPosX)
#define		RECT_END_Y(R)				(R.EndPosY)
#define		RECT_INVALID_POSITION		(-1)
#define		RECT_RESET(R)				{R.StartPosX=RECT_INVALID_POSITION;R.EndPosX=RECT_INVALID_POSITION;R.StartPosY=RECT_INVALID_POSITION;R.EndPosY=RECT_INVALID_POSITION;}

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
	uint16_t		StartPosX;
	uint16_t		StartPosY;
	uint16_t		EndPosX;
	uint16_t		EndPosY;
}TRect;

typedef struct
{
	uint8_t			Pixregister[LCD_SIZE_WIDTH][LCD_SIZE_HEIGHT];
	bool			InUpdating;
	TRect			ChangedArea;
}TPixArray;

// LCD Pix data array.
extern TPixArray			g_LCDPixArray;

// Interface function declare
void		VTIF_KeyBoardEvent(bool bShift, bool bCtrl, bool bAlt, uint16_t uiKeyCode);
void		VTIF_LCDInitializeDisplay(void);
void		VTIF_SetPoint(uint16_t uiPosX, uint16_t uiPosY, uint8_t uiPixValue);
uint8_t		VTIF_GetPoint(uint16_t uiPosX, uint16_t uiPosY);
void		VTIF_ClearScreen(void);


#ifdef __cplusplus
}
#endif

#endif // __INCLUDE_LCD_OPERATIONIF_H__
