#ifndef __INCLUDE_GUI_FRAME_H__
#define __INCLUDE_GUI_FRAME_H__

#include "LCD_VirtualDeviceParameter.h"
#include "GUI_Common.h"
#include "GUI_Basic.h"
#include "GUI_Text.h"

typedef struct
{
	uint16_t					EdgeLayers;
    GUI_FONT_SIZE				FontSize;
}GUI_BOX_FRAME_PARAMETER;

typedef struct
{
    char*						Title;
}GUI_BOX_FRAME_DATA;

typedef struct
{
	GUI_BOX_FRAME_PARAMETER		Parameter;
    GUI_BOX_FRAME_DATA			Data;
}GUI_BOX_FRAME_STRUCT;

void GUI_Frame_DrawFullScreenFrame(GUI_BOX_FRAME_STRUCT* pstFrameStyleData);

#endif // __INCLUDE_GUI_FRAME_H__
