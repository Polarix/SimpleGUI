#ifndef __INCLUDE_GUI_COMMON_H__
#define __INCLUDE_GUI_COMMON_H__
#include <stddef.h>
#include <stdint.h>

#define		GUI_NUMBER_STR_LENGTH_MAX		(12)
//#define		GUI_PLACEHOLDER_CHARACTER		('*')

#ifdef GB2312_ENCV
char*					GUI_EncodeConvert(char *szSourceEncode, char *szDestinationEncode, char *szSource);
#define		ENCODE_BUFFER_SIZE				(512)
#define		ENCODE(S)						(GUI_EncodeConvert("UTF-8", "GB2312", (char *)S))
#else
#define ENCODE(S)							(S)
#endif // GB2312_ENCV

#define		GUI_ISDIGIT(C)					(((C>='0')&&(C<='9'))?true:false)
#define		GUI_ISALPHA(C)					((((C>='A')&&(C<='Z'))||((C>='a')&&(C<='z')))?true:false)
#define		GUI_ISHEXDIGIT(C)				((((C>='A')&&(C<='F'))||((C>='a')&&(C<='f'))||((C>='0')&&(C<='9')))?true:false)
#define		GUI_ISUPPER(C)					(((C>='A')&&(C<='Z'))?true:false)
#define		GUI_TOUPPER(C)					(GUI_ISUPPER(C)?(C):(C-32))


uint16_t				GUI_Common_IntegerToStringWithDecimalPoint(int32_t iInteger, uint16_t uiDecimalPlaces, char* szStringBuffer, int16_t iAlignment, char cFillCharacter);
uint16_t				GUI_Common_IntegerToString(int32_t iInteger, char* szStringBuffer, uint16_t uiBase, int16_t iAlignment, char cFillCharacter);
uint32_t				GUI_Common_ConvertStringToUnsignedInteger(char* szString, char** pcEndPointer, uint16_t uiBase);
int32_t					GUI_Common_ConvertStringToInteger(char* szString, char** pcEndPointer, uint16_t uiBase);
size_t					GUI_Common_StringLength(char* szString);
void					GUI_Common_RefreshScreen(void);


#endif // __INCLUDE_GUI_COMMON_H__
