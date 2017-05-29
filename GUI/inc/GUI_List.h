#ifndef __INCLUDE_GUI_LIST_H__
#define __INCLUDE_GUI_LIST_H__
#include "GUI_Basic.h"
#include "GUI_Text.h"
#include "GUI_ScrollBar.h"
#include "LCD_VirtualDeviceParameter.h"


typedef enum
{
	LIST_ITEM_NORMAL		= 0,
	LIST_ITEM_ENUM,
	LIST_ITEM_DIGIT,
	LIST_ITEM_DATE,
	LIST_ITEM_TIME
}GUI_LIST_ITEM_TYPE;

typedef struct
{
	int32_t						Value;
	int32_t						Min;
	int32_t						Max;
	int32_t*					Bind;
}GUI_LIST_PARAMETER_VALUE;

typedef struct
{
	const char*					Text;
	GUI_LIST_ITEM_TYPE			Type;
	GUI_LIST_PARAMETER_VALUE	Valid;
	GUI_LIST_PARAMETER_VALUE	Decimal;
    const char**				EnumerationValues;
    size_t						EnumerationCount;
}GUI_LIST_ITEM;

typedef struct
{
	uint16_t					ListTitleHeight;				// Read only
	uint16_t					VisibleItemsAreaHeight;			// Read only
	uint16_t					ListItemHeight;					// Read only
	uint16_t					FirstVisibleItemPosY;			// Read only
	uint16_t					VisibleIntegralItemsNum;		// Read only
	uint16_t					VisibleItemsNum;				// Read only
	size_t						SelectIndex;					// Control
	size_t						PageStartIndex;					// Control
	uint16_t					ItemPosYOffSet;					// Control
}GUI_LIST_CONTROL;

typedef struct
{
	char*						Title;
	size_t						Count;
	GUI_LIST_ITEM*				Items;
}GUI_LIST_DATA;

typedef struct
{
	GUI_SCROLLBAR_STRUCT		ScrollBar;
}GUI_LIST_SUBELEMENT;

typedef struct
{
	GUI_LIST_DATA				Data;
	// Initialize parameter.
	GUI_LIST_CONTROL			ControlVariable;
	GUI_LIST_SUBELEMENT			SubElement;
}GUI_LIST_STRUCT;


void		GUI_List_InitializeListData(GUI_LIST_STRUCT* pstList);
void		GUI_List_RefreshList(GUI_LIST_STRUCT* pstList);
void		GUI_List_SelectUpItem(GUI_LIST_STRUCT* pstList);
void		GUI_List_SelectDownItem(GUI_LIST_STRUCT* pstList);
void		GUI_List_SetListItemValue(GUI_LIST_STRUCT* pstList, size_t uiItemIndex, int32_t iSetValid, int32_t iSetDecimal);
void		GUI_List_GetListItemValue(GUI_LIST_STRUCT* pstList, size_t uiItemIndex, int32_t* piValid, int32_t* piDecimal);

#endif // __INCLUDE_GUI_LIST_H__
