#ifndef __INCLUDE_GUI_PROCESSBAR_H__
#define __INCLUDE_GUI_PROCESSBAR_H__

typedef enum
{
	GUI_PROCBAR_UP = 0,							//Process bar direction to up.
	GUI_PROCBAR_DOWN,							//Process bar direction to down.
	GUI_PROCBAR_LEFT,							//Process bar direction to left.
	GUI_PROCBAR_RIGHT,							//Process bar direction to right.
}GUI_PROCBAR_DIRECTION;

typedef struct
{
	uint16_t				PosX;
	uint16_t				PosY;
	uint16_t				Width;
	uint16_t				Height;
	GUI_PROCBAR_DIRECTION	Direction;
	size_t					MaxValue;

}GUI_PROCBAR_PARAMETER;

typedef struct
{
	size_t					Value;
}GUI_PROCBAR_DATA;

typedef struct
{
	GUI_PROCBAR_PARAMETER	Parameter;
	GUI_PROCBAR_DATA		Data;
}GUI_PROCBAR_STRUCT;


void GUI_UpdateProcessBar(GUI_PROCBAR_STRUCT *pProcessBarData);

#endif // __INCLUDE_GUI_PROCESSBAR_H__
