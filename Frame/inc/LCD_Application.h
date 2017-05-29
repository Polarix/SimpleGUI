/***************************************************************
 * Name:      LCDSimulatorMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2017-02-25
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef __INCLUDE_LCD_APPLICATION_H__
#define __INCLUDE_LCD_APPLICATION_H__

#include <wx/dialog.h>
#include <wx/app.h>


class LCD_Application : public wxApp
{
    public:

    private:

		bool OnInit(void);
		int OnExit(void);

};

#endif //__INCLUDE_LCD_APPLICATION_H__
