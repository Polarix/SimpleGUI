#ifndef __INCLUDE_GUI_SCROLLBAR__
#define __INCLUDE_GUI_SCROLLBAR__


typedef enum
{
	GUI_SCROLLBAR_VERTICAL = 0,						//Vertical scroll bar.
	GUI_SCROLLBAR_HORIZONTAL,						//Horizontal scroll bar.
}GUI_SCROLLBAR_DIRECTION;

typedef struct
{
	uint16_t					PosX;
	uint16_t					PosY;
	uint16_t					Width;
	uint16_t					Height;
	size_t						MaxIndex;
	GUI_SCROLLBAR_DIRECTION		eDirection;
}GUI_SCROLLBAR_PARAMETER;

typedef struct
{
	size_t						Index;
}GUI_SCROLLBAR_DATA;

typedef struct
{
	GUI_SCROLLBAR_PARAMETER		Parameter;
	GUI_SCROLLBAR_DATA			Data;
}GUI_SCROLLBAR_STRUCT;
//-- Constant definition -------------------------------------------------
//#define SCROLLBAR_BLOCK_SIZE				(3)
//#define SCROLLBAR_BAR_WIDTH					(SCROLLBAR_BLOCK_SIZE+2)
//-- Function declare													--
void	GUI_ScrollBar_UpdateScrollBar(GUI_SCROLLBAR_STRUCT* pstScrollBar);

#endif // __INCLUDE_GUI_SCROLLBAR_STRUCT__
