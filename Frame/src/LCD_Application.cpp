#include "wx\wx.h"
#include "LCD_Application.h"
#include "LCD_VirtualDevice.h"

IMPLEMENT_APP(LCD_Application);

bool LCD_Application::OnInit(void)
{
	LCD_VirtualDevice*	CFrmMain = new LCD_VirtualDevice((wxWindow*)NULL);
	wxInitAllImageHandlers();
	SetTopWindow(CFrmMain);
	CFrmMain->Show();
    return true;
}

int LCD_Application::OnExit()
{
    return 0;
}
