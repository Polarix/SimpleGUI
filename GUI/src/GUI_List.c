/*************************************************************************/
/** Copyright.															**/
/** FileName: GUI_List.c												**/
/** Author: XuYulin														**/
/** Version: 1.0.0.0													**/
/** Description: Draw list interface.									**/
/** History:															**/
/**	XuyYulin	2017/4/25	2.0.0.0		New create.						**/
/** XuYulin 2017/4/25 1.0 build this moudle								**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "LCD_OperationIF.h"
#include "GUI_Common.h"
#include "GUI_Basic.h"
#include "GUI_Text.h"
#include "GUI_ScrollBar.h"
#include "GUI_List.h"
#include "GUI_Frame.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
#define						LIST_FONT_SIZE						(GUI_FONT_SIZE_H12)
#define						LIST_EDGE_MULTIPLE					(1)
						#if(LIST_EDGE_MULTIPLE == 0)
#define 					LIST_EDGE_SIZE						(0)
						#else
#define						LIST_EDGE_SIZE						(LIST_EDGE_MULTIPLE*2-1)
						#endif
#define						LIST_TITLE_HEIGHT					(g_stFontSize[LIST_FONT_SIZE].Height+2)
#define						LIST_SCROLLBAR_WIDTH				(5)
#define						LIST_SCROLLBAR_POSX					(LCD_SIZE_WIDTH-LIST_EDGE_SIZE-LIST_SCROLLBAR_WIDTH)

#define						LIST_ITEM_RECT_POSX					(LIST_EDGE_SIZE+2)
#define						LIST_ITEM_RECT_WIDTH				(LCD_SIZE_WIDTH-(LIST_ITEM_RECT_POSX*2)-LIST_SCROLLBAR_WIDTH)
#define						LIST_ITEM_TEXT_BLANK_EDGEX			(2)
#define						LIST_ITEM_TEXT_BLANK_EDGEY			(1)
#define						LIST_ITEM_TEXT_AREA_WIDTH			(LIST_ITEM_RECT_WIDTH-(LIST_ITEM_TEXT_BLANK_EDGEX*2))
#define						LIST_ITEM_PARAMETER_SPLIT_WIDTH		(4)
#define						LIST_ITEM_PARAMETER_AREA_WIDTH		((LIST_ITEM_TEXT_AREA_WIDTH/2)-LIST_ITEM_PARAMETER_SPLIT_WIDTH)
#define						LIST_ITEM_PARAMETER_STARTX			(LIST_ITEM_RECT_POSX+LIST_ITEM_TEXT_BLANK_EDGEX+(LIST_ITEM_TEXT_AREA_WIDTH-LIST_ITEM_PARAMETER_AREA_WIDTH))

#define						LIST_ITEM_PARAMETER_TEXT_LENGTH_MAX	(16)


//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static inline void			GUI_List_RefreshListItems(GUI_LIST_STRUCT* pstList);
static inline void			GUI_List_DrawItem(GUI_LIST_STRUCT* pstList, size_t uiIndex);

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
/*****************************************************************************/
/** Function Name:	GUI_List_InitializeListData								**/
/** Purpose:		Initialize a list control data.							**/
/** Resources:		List item data.											**/
/** Params:																	**/
/**	@pstList[in]:		Pointer of list data will be initialized.			**/
/** Return:			None.													**/
/** Notice:			None.													**/
/*****************************************************************************/
void GUI_List_InitializeListData(GUI_LIST_STRUCT* pstList)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	GUI_LIST_CONTROL*		pstListControl;
	GUI_LIST_DATA*			pstListData;
	GUI_LIST_SUBELEMENT*	pstSubElement;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstList)
	{
		pstListControl = &(pstList->ControlVariable);
		pstListData = &(pstList->Data);
		pstSubElement = &(pstList->SubElement);

		pstListControl->ListTitleHeight = LIST_TITLE_HEIGHT;
		pstListControl->PageStartIndex = 0;
		pstListControl->SelectIndex = 0;
		pstListControl->ItemPosYOffSet = 0;
		pstListControl->FirstVisibleItemPosY = LIST_EDGE_SIZE;
		pstListControl->ListItemHeight = g_stFontSize[LIST_FONT_SIZE].Height + (LIST_ITEM_TEXT_BLANK_EDGEY*2);
		pstListControl->VisibleItemsAreaHeight = LCD_SIZE_HEIGHT-LIST_EDGE_SIZE*2;
		if(NULL != pstList->Data.Title)
		{
			pstListControl->FirstVisibleItemPosY += LIST_TITLE_HEIGHT + 1;
			pstListControl->VisibleItemsAreaHeight -= LIST_TITLE_HEIGHT + 1;
		}
		pstListControl->VisibleIntegralItemsNum = pstListControl->VisibleItemsAreaHeight/(pstListControl->ListItemHeight);
		if(pstListControl->VisibleIntegralItemsNum > pstList->Data.Count)
		{
			pstListControl->VisibleIntegralItemsNum = pstList->Data.Count;
		}
		pstListControl->VisibleItemsNum = (pstListControl->VisibleItemsAreaHeight-1)/pstListControl->ListItemHeight+1;

		pstSubElement->ScrollBar.Parameter.eDirection = GUI_SCROLLBAR_VERTICAL;
		pstSubElement->ScrollBar.Parameter.PosX = LIST_SCROLLBAR_POSX;
		pstSubElement->ScrollBar.Parameter.PosY = pstListControl->FirstVisibleItemPosY;
		pstSubElement->ScrollBar.Parameter.Width = LIST_SCROLLBAR_WIDTH;
		pstSubElement->ScrollBar.Parameter.Height = pstListControl->VisibleItemsAreaHeight;
		pstSubElement->ScrollBar.Data.Index = 0;
		pstSubElement->ScrollBar.Parameter.MaxIndex = (pstListData->Count>pstListControl->VisibleIntegralItemsNum)?(pstListData->Count-pstListControl->VisibleIntegralItemsNum-1):0;
	}

}

/*****************************************************************************/
/** Function Name:	GUI_List_RefreshListItems								**/
/** Purpose:		Refresh all visible list item display.					**/
/** Resources:		List item data.											**/
/** Params:																	**/
/**	@pstList[in]:		Pointer of list data will be refreshed.				**/
/** Notice:			This only refresh visible items and scrollbar.			**/
/*****************************************************************************/
void GUI_List_RefreshListItems(GUI_LIST_STRUCT* pstList)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	GUI_LIST_CONTROL*		pstListControl;
	GUI_LIST_SUBELEMENT*	pstSubElement;
	GUI_LIST_DATA*			pstListData;

	uint16_t				uiCurrentItemIndex;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	if(NULL != pstList)
	{
		pstListControl = &(pstList->ControlVariable);
		pstListData = &(pstList->Data);
		pstSubElement = &(pstList->SubElement);

		uiCurrentItemIndex = pstListControl->PageStartIndex;
	}

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstList)
	{
		if(pstList->Data.Count > 0)
		{
			// Clear list item display area.
			GUI_Basic_DrawRectangle(LIST_ITEM_RECT_POSX, pstListControl->FirstVisibleItemPosY, LIST_ITEM_RECT_WIDTH, pstListControl->VisibleItemsAreaHeight, GUI_COLOR_BKGCLR, GUI_COLOR_BKGCLR);
			// Update scroll bar
			pstSubElement->ScrollBar.Data.Index = pstListControl->PageStartIndex;
			GUI_ScrollBar_UpdateScrollBar(&(pstSubElement->ScrollBar));
			// Draw all visible items.
			while((uiCurrentItemIndex < pstListControl->PageStartIndex+pstListControl->VisibleItemsNum) && (uiCurrentItemIndex < pstListData->Count))
			{
				GUI_List_DrawItem(pstList, uiCurrentItemIndex++);
			}
			// High light focused items.
			GUI_Basic_ReverseBlockColor(LIST_ITEM_RECT_POSX, pstListControl->FirstVisibleItemPosY+(pstListControl->SelectIndex-pstListControl->PageStartIndex)*pstListControl->ListItemHeight-pstListControl->ItemPosYOffSet,
										LIST_ITEM_RECT_WIDTH, pstListControl->ListItemHeight);
		}
	}
}

/*****************************************************************************/
/** Function Name:	GUI_List_RefreshList									**/
/** Purpose:		Refresh list display.									**/
/** Resources:		List item data.											**/
/** Params:																	**/
/**	@pstList[in]:		Pointer of list data will be refreshed.				**/
/** Return:			None.													**/
/** Notice:			This function will refresh all list display on screen, 	**/
/**					include edge, items, title and scrollbar.				**/
/*****************************************************************************/
void GUI_List_RefreshList(GUI_LIST_STRUCT* pstList)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	GUI_BOX_FRAME_STRUCT	stFrameStyleData;
	GUI_LIST_DATA*			pstListData;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstList)
	{
		pstListData = &(pstList->Data);
		// Draw frame
		stFrameStyleData.Parameter.EdgeLayers = LIST_EDGE_MULTIPLE;
		stFrameStyleData.Parameter.FontSize = LIST_FONT_SIZE;
		stFrameStyleData.Data.Title = pstListData->Title;
		GUI_Frame_DrawFullScreenFrame(&stFrameStyleData);
		// Draw list items
		GUI_List_RefreshListItems(pstList);
	}
}

/*****************************************************************************/
/** Function Name:	GUI_List_SelectUpItem									**/
/** Purpose:		Select previous list item if existed.					**/
/** Resources:		List item data.											**/
/** Params:																	**/
/**	@pstList[in]:		Pointer of list will be selected.					**/
/** Return:			None.													**/
/** Notice:			None.													**/
/*****************************************************************************/
void GUI_List_SelectUpItem(GUI_LIST_STRUCT* pstList)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	GUI_LIST_CONTROL*		pstListControl;
	GUI_LIST_DATA*			pstListData;
	uint16_t				uiReverseBlockPosY;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	if(NULL != pstList)
	{
		pstListControl = &(pstList->ControlVariable);
		pstListData = &(pstList->Data);
	}

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((pstListControl->SelectIndex > 0) && (pstListData->Count > 1))
	{
		//Focused item and select item is visible and Integral;
		if((pstListControl->SelectIndex>pstListControl->PageStartIndex+1) && (pstListControl->VisibleIntegralItemsNum>1))
		{
			// Unfocused current item.
			uiReverseBlockPosY = pstListControl->FirstVisibleItemPosY+(pstListControl->SelectIndex-pstListControl->PageStartIndex)*pstListControl->ListItemHeight-pstListControl->ItemPosYOffSet;
			GUI_Basic_ReverseBlockColor(LIST_ITEM_RECT_POSX, uiReverseBlockPosY, LIST_ITEM_RECT_WIDTH, pstListControl->ListItemHeight);
			pstListControl->SelectIndex--;
			// Focused previous item.
			uiReverseBlockPosY = pstListControl->FirstVisibleItemPosY+(pstListControl->SelectIndex-pstListControl->PageStartIndex)*pstListControl->ListItemHeight-pstListControl->ItemPosYOffSet;
			GUI_Basic_ReverseBlockColor(LIST_ITEM_RECT_POSX, uiReverseBlockPosY, LIST_ITEM_RECT_WIDTH, pstListControl->ListItemHeight);
		}
		else
		{
			pstListControl->SelectIndex--;
			if(pstListControl->PageStartIndex == pstListControl->SelectIndex)
			{
				pstListControl->ItemPosYOffSet = 0;
			}
			if(pstListControl->SelectIndex < pstListControl->PageStartIndex)
			{
				pstListControl->PageStartIndex--;
			}
			GUI_List_RefreshListItems(pstList);
		}
	}
}

/*****************************************************************************/
/** Function Name:	GUI_List_SelectDownItem									**/
/** Purpose:		Select next list item if existed.						**/
/** Resources:		List item data.											**/
/** Params:																	**/
/**	@pstList[in]:		Pointer of list will be selected.					**/
/** Return:			None.													**/
/** Notice:			None.													**/
/*****************************************************************************/
void GUI_List_SelectDownItem(GUI_LIST_STRUCT* pstList)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	GUI_LIST_CONTROL*		pstListControl;
	GUI_LIST_DATA*			pstListData;
	uint16_t				uiReverseBlockPosY;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	if(NULL != pstList)
	{
		pstListControl = &(pstList->ControlVariable);
		pstListData = &(pstList->Data);
	}

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((pstListControl->SelectIndex < pstListData->Count-1) && (pstListData->Count > 1))
	{
		//Focused item and select item is visible and Integral;
		if((pstListControl->VisibleIntegralItemsNum>1) && ((pstListControl->SelectIndex)<(pstListControl->PageStartIndex+pstListControl->VisibleIntegralItemsNum-1)))
		{
			// Unfocused current item.
			uiReverseBlockPosY = pstListControl->FirstVisibleItemPosY+(pstListControl->SelectIndex-pstListControl->PageStartIndex)*pstListControl->ListItemHeight-pstListControl->ItemPosYOffSet;
			GUI_Basic_ReverseBlockColor(LIST_ITEM_RECT_POSX, uiReverseBlockPosY, LIST_ITEM_RECT_WIDTH, pstListControl->ListItemHeight);
			pstListControl->SelectIndex++;
			// Focused previous item.
			uiReverseBlockPosY = pstListControl->FirstVisibleItemPosY+(pstListControl->SelectIndex-pstListControl->PageStartIndex)*pstListControl->ListItemHeight-pstListControl->ItemPosYOffSet;
			GUI_Basic_ReverseBlockColor(LIST_ITEM_RECT_POSX, uiReverseBlockPosY, LIST_ITEM_RECT_WIDTH, pstListControl->ListItemHeight);
		}
		else
		{
			pstListControl->SelectIndex++;
			if((pstListControl->SelectIndex-pstListControl->PageStartIndex+1) == pstListControl->VisibleItemsNum)
			{
				pstListControl->ItemPosYOffSet = pstListControl->ListItemHeight-pstListControl->VisibleItemsAreaHeight%pstListControl->ListItemHeight;
			}
			if((pstListControl->SelectIndex-pstListControl->PageStartIndex+1) > pstListControl->VisibleItemsNum)
			{
				pstListControl->PageStartIndex++;
			}
			GUI_List_RefreshListItems(pstList);
		}
	}
}

/*****************************************************************************/
/** Function Name:	GUI_List_DrawItem										**/
/** Purpose:		Draw a visible list item.								**/
/** Resources:		List item data.											**/
/** Params:																	**/
/**	@pstList[in]:		Pointer of list will be selected.					**/
/**	@uiIndex[in]:		List item index will be draw.						**/
/** Return:			None.													**/
/** Notice:			This function only draw visible items, it's depending	**/
/**					on the first visible item index and count of visible 	**/
/**					items.													**/
/*****************************************************************************/
void GUI_List_DrawItem(GUI_LIST_STRUCT* pstList, size_t uiIndex)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	RECTANGLE				stItemTextDisplayArea;
	RECTANGLE				stItemTextDataArea;
	GUI_LIST_CONTROL*		pstListControl;
	GUI_LIST_DATA*			pstListData;
	GUI_LIST_ITEM*			pstListItemPointer;
	char					szParameterStringBuffer[LIST_ITEM_PARAMETER_TEXT_LENGTH_MAX];
	size_t					uiParameterTextWidth;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	if(NULL != pstList)
	{
		pstListControl = &(pstList->ControlVariable);
		pstListData = &(pstList->Data);
		pstListItemPointer = pstListData->Items + uiIndex;
		szParameterStringBuffer[0] = '\0';
	}

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstList)
	{
		if((uiIndex >= pstListControl->PageStartIndex) && (uiIndex < pstListControl->PageStartIndex+pstListControl->VisibleItemsNum))
		{
			// Prepare draw list item text.
			stItemTextDataArea.PosX = 0;
			stItemTextDataArea.PosY = LIST_ITEM_TEXT_BLANK_EDGEY;
			stItemTextDisplayArea.PosX = LIST_ITEM_RECT_POSX + LIST_ITEM_TEXT_BLANK_EDGEX;
			stItemTextDisplayArea.Width = LIST_ITEM_TEXT_AREA_WIDTH;

			if(uiIndex == pstListControl->PageStartIndex)
			{
				stItemTextDataArea.PosY -= pstListControl->ItemPosYOffSet;
				stItemTextDisplayArea.PosY = pstListControl->FirstVisibleItemPosY;
				stItemTextDisplayArea.Height = pstListControl->ListItemHeight-pstListControl->ItemPosYOffSet;
			}
			else if(uiIndex == pstListControl->PageStartIndex+pstListControl->VisibleItemsNum-1)
			{
				stItemTextDisplayArea.PosY = pstListControl->FirstVisibleItemPosY+pstListControl->ListItemHeight*(uiIndex-pstListControl->PageStartIndex)-pstListControl->ItemPosYOffSet;

				if((0==pstListControl->ItemPosYOffSet) && (0 != pstListControl->VisibleItemsAreaHeight%pstListControl->ListItemHeight))
				{
					stItemTextDisplayArea.Height = (pstListControl->VisibleItemsAreaHeight%pstListControl->ListItemHeight);
				}
				else
				{
					stItemTextDisplayArea.Height = pstListControl->ListItemHeight;
				}
				//stItemTextDisplayArea.Height = (0==pstListControl->ItemPosYOffSet)?(pstListControl->VisibleItemsAreaHeight%pstListControl->ListItemHeight):(pstListControl->ListItemHeight);
			}
			else
			{
				stItemTextDisplayArea.PosY = pstListControl->FirstVisibleItemPosY+pstListControl->ListItemHeight*(uiIndex-pstListControl->PageStartIndex)-pstListControl->ItemPosYOffSet;
				stItemTextDisplayArea.Height = pstListControl->ListItemHeight;
			}

			// Draw list item text.
			GUI_Text_DrawSingleLineText(ENCODE(pstListItemPointer->Text), LIST_FONT_SIZE,
												&stItemTextDisplayArea, &stItemTextDataArea, GUI_DRAW_NORMAL);

			// Prepare draw parameter text.
			stItemTextDataArea.PosX = LIST_ITEM_PARAMETER_SPLIT_WIDTH+1;
			stItemTextDisplayArea.PosX = LIST_ITEM_PARAMETER_STARTX;
			stItemTextDisplayArea.Width = LIST_ITEM_PARAMETER_AREA_WIDTH;
			if(LIST_ITEM_NORMAL != pstListItemPointer->Type)
			{
				if(pstListItemPointer->Valid.Value > pstListItemPointer->Valid.Max)
				{
					pstListItemPointer->Valid.Value = pstListItemPointer->Valid.Max;
				}
				else if(pstListItemPointer->Valid.Value < pstListItemPointer->Valid.Min)
				{
					pstListItemPointer->Valid.Value = pstListItemPointer->Valid.Min;
				}
				if(pstListItemPointer->Decimal.Value > pstListItemPointer->Decimal.Max)
				{
					pstListItemPointer->Decimal.Value = pstListItemPointer->Decimal.Max;
				}
				else if(pstListItemPointer->Decimal.Value < pstListItemPointer->Decimal.Min)
				{
					pstListItemPointer->Decimal.Value = pstListItemPointer->Decimal.Min;
				}

				switch(pstListItemPointer->Type)
				{
					case LIST_ITEM_ENUM:
					{
						strncpy(szParameterStringBuffer, ENCODE(pstListItemPointer->EnumerationValues[pstListItemPointer->Valid.Value]), LIST_ITEM_PARAMETER_TEXT_LENGTH_MAX-1);
						szParameterStringBuffer[LIST_ITEM_PARAMETER_TEXT_LENGTH_MAX-1] = '\0';
						uiParameterTextWidth =  GUI_Text_GetTextGraphicsWidth(szParameterStringBuffer, LIST_FONT_SIZE);
						if(uiParameterTextWidth < LIST_ITEM_PARAMETER_AREA_WIDTH)
						{
							stItemTextDataArea.PosX += (LIST_ITEM_PARAMETER_AREA_WIDTH-LIST_ITEM_PARAMETER_SPLIT_WIDTH)-uiParameterTextWidth;
						}
						break;
					}
					case LIST_ITEM_DIGIT:
					{
						GUI_Common_IntegerToStringWithDecimalPoint(pstListItemPointer->Valid.Value, pstListItemPointer->Decimal.Value, szParameterStringBuffer, 0, ' ');
						uiParameterTextWidth = GUI_Text_GetTextGraphicsWidth(szParameterStringBuffer,LIST_FONT_SIZE);
						if(uiParameterTextWidth < LIST_ITEM_PARAMETER_AREA_WIDTH)
						{
							stItemTextDataArea.PosX += (LIST_ITEM_PARAMETER_AREA_WIDTH-LIST_ITEM_PARAMETER_SPLIT_WIDTH)-uiParameterTextWidth;
						}
						break;
					}
					default:
					{
						// Undefined list item type, no any process.
						break;
					}
				}
				// Draw parameter text.
				GUI_Text_DrawSingleLineText(szParameterStringBuffer, LIST_FONT_SIZE, &stItemTextDisplayArea, &stItemTextDataArea, GUI_DRAW_NORMAL);
			}
		}
	}
}

/*****************************************************************************/
/** Function Name:	GUI_List_SetListItemValue								**/
/** Purpose:		Set list parameter value if supported.					**/
/** Resources:		List item data.											**/
/** Params:																	**/
/**	@pstList[in]:		Pointer of list will be selected.					**/
/**	@uiItemIndex[in]:	Index of list item index will be changed.			**/
/**	@iSetValid[in]:		Valid value will be set.							**/
/**	@iSetDecimal[in]:	Decimal value will be set.							**/
/** Return:			None.													**/
/** Notice:			The bind value will update if existed.					**/
/*****************************************************************************/
void GUI_List_SetListItemValue(GUI_LIST_STRUCT* pstList, size_t uiItemIndex, int32_t iSetValid, int32_t iSetDecimal)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	GUI_LIST_ITEM			*pstSelectedListItem;
	GUI_LIST_CONTROL		*pstListControl;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	pstSelectedListItem		= NULL;
	if(NULL != pstList)
	{
		if(uiItemIndex < pstList->Data.Count)
		{
			pstSelectedListItem = pstList->Data.Items+uiItemIndex;
		}
		pstListControl = &(pstList->ControlVariable);
	}

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstSelectedListItem)
	{
		// Set valid.
		if(iSetValid > pstSelectedListItem->Valid.Max)
		{
			pstSelectedListItem->Valid.Value = pstSelectedListItem->Valid.Max;
		}
		else if(iSetValid < pstSelectedListItem->Valid.Min)
		{
			pstSelectedListItem->Valid.Value = pstSelectedListItem->Valid.Min;
		}
		else
		{
			pstSelectedListItem->Valid.Value = iSetValid;
		}
		// Sync bind if existed.
		if(NULL != pstSelectedListItem->Valid.Bind)
		{
			*(pstSelectedListItem->Valid.Bind) = pstSelectedListItem->Valid.Value;
		}
		// Set decimal.
		if(iSetDecimal > pstSelectedListItem->Decimal.Max)
		{
			pstSelectedListItem->Decimal.Value = pstSelectedListItem->Decimal.Max;
		}
		else if(iSetDecimal < pstSelectedListItem->Decimal.Min)
		{
			pstSelectedListItem->Decimal.Value = pstSelectedListItem->Decimal.Min;
		}
		else
		{
			pstSelectedListItem->Decimal.Value = iSetDecimal;
		}
		// Sync bind if existed.
		if(NULL != pstSelectedListItem->Decimal.Bind)
		{
			*(pstSelectedListItem->Decimal.Bind) = pstSelectedListItem->Decimal.Value;
		}
		// Clear list item area.
		GUI_Basic_DrawRectangle(LIST_ITEM_RECT_POSX, pstListControl->FirstVisibleItemPosY+(pstListControl->SelectIndex-pstListControl->PageStartIndex)*pstListControl->ListItemHeight-pstListControl->ItemPosYOffSet,
								LIST_ITEM_RECT_WIDTH, pstListControl->ListItemHeight, GUI_COLOR_BKGCLR, GUI_COLOR_BKGCLR);
		// refresh list item
		GUI_List_DrawItem(pstList, uiItemIndex);
		// High light selected item.
		GUI_Basic_ReverseBlockColor(LIST_ITEM_RECT_POSX, pstListControl->FirstVisibleItemPosY+(pstListControl->SelectIndex-pstListControl->PageStartIndex)*pstListControl->ListItemHeight-pstListControl->ItemPosYOffSet,
		 							LIST_ITEM_RECT_WIDTH, pstListControl->ListItemHeight);
	}
}

/*****************************************************************************/
/** Function Name:	GUI_List_GetListItemValue								**/
/** Purpose:		Get list parameter value if supported.					**/
/** Resources:		List item data.											**/
/** Params:																	**/
/**	@pstList[in]:		Pointer of list will be read.						**/
/**	@uiItemIndex[in]:	Index of list item index will be read.				**/
/**	@piSetValid[out]:	Valid value will be read.							**/
/**	@piSetDecimal[out]:	Decimal value will be read.							**/
/** Return:			None.													**/
/** Notice:			None.													**/
/*****************************************************************************/
void GUI_List_GetListItemValue(GUI_LIST_STRUCT* pstList, size_t uiItemIndex, int32_t* piValid, int32_t* piDecimal)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	GUI_LIST_ITEM			*pstSelectedListItem;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	pstSelectedListItem		= NULL;
	if(NULL != pstList)
	{
		if(uiItemIndex < pstList->Data.Count)
		{
			pstSelectedListItem = pstList->Data.Items+uiItemIndex;
		}
	}

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstSelectedListItem)
	{
		// Read valid value.
		if(NULL != piValid)
		{
			*piValid = pstSelectedListItem->Valid.Value;
		}

		// Read decimal value.
		if(NULL != piDecimal)
		{
			*piDecimal = pstSelectedListItem->Decimal.Value;
		}
	}
}

/*****************************************************************************/
/** Function Name:	GUI_List_BindData										**/
/** Purpose:		Bind a 32-bit integer variable by pointer.				**/
/** Resources:		List item data.											**/
/** Params:																	**/
/**	@pstList[in]:		Pointer of list will be read.						**/
/**	@uiItemIndex[in]:	Index of list item index will be read.				**/
/**	@piValid[out]:		Valid variable pointer.								**/
/**	@piDecimal[out]:	Decimal variable pointer.							**/
/** Return:			None.													**/
/** Notice:			Variable pointer and decimal variable can be NULL.		**/
/*****************************************************************************/
void GUI_List_BindData(GUI_LIST_STRUCT* pstList, size_t uiItemIndex, int32_t* piValid, int32_t* piDecimal)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	GUI_LIST_ITEM			*pstSelectedListItem;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	pstSelectedListItem		= NULL;
	if(NULL != pstList)
	{
		if(uiItemIndex < pstList->Data.Count)
		{
			pstSelectedListItem = pstList->Data.Items+uiItemIndex;
		}
	}

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstSelectedListItem)
	{
		pstSelectedListItem->Valid.Bind = piValid;
		pstSelectedListItem->Decimal.Bind = piDecimal;
	}
}
