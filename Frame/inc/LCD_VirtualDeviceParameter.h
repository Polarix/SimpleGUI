#ifndef __INCLUDE_LCD_VIRTUALDEVICEPARAMETER_H_INCLUDED__
#define __INCLUDE_LCD_VIRTUALDEVICEPARAMETER_H_INCLUDED__

// Parameter
#define LCD_SIZE_MARGIN			        (10)
#define LCD_DISPLAY_EDGE				(2)
#define	LCD_PIXSIZE				        (2)

#define LCD_SIZE_WIDTH					(132)
#define LCD_SIZE_HEIGHT					(64)
#define LCD_COLOR_OBJ_PIX				(wxColor(88,120,20))
#define LCD_COLOR_OBJ_BKG				(wxColor(202,246,22))
#define LCD_COLOR_OBJ_EDGE				(wxColor(116,164,25))

#define FRM_COLOR_OBJ_BKG		        (wxColor(51,100,195))

#if LCD_SIZE_WIDTH < 16
#error Define width of LCD size must greater then 16.
#endif
#if LCD_SIZE_HEIGHT < 16
#error Define height of LCD size must greater then 16.
#endif

//Common operation
//#define SET_BIT(PAGE, Bit)		((PAGE) = (PAGE) | (0x01 << (Bit)))
//#define CLR_BIT(PAGE, Bit)		((PAGE) = (PAGE) & (~(0x01 << (Bit))))
#define GET_BIT(PAGE, Bit)		((((PAGE) & (0x01 << (Bit)))>0)?1:0)

#endif //__INCLUDE_LCD_VIRTUALDEVICEPARAMETER_H_INCLUDED__
