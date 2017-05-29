///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __INCLUDE_LCD_VIRTUAL_DEVICE_H__
#define __INCLUDE_LCD_VIRTUAL_DEVICE_H__

#include "LCD_VirtualDeviceParameter.h"
#include "LCD_OperationIF.h"

#include <wx/dcbuffer.h>
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/string.h>
#include <wx/statusbr.h>
#include <wx/toolbar.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////
#define FRAME_TITLE						(_T("SimpleGUI Simulator"))

#define wxID_MAIN						1000
#define wxID_TOOLBAR					2000
#define wxID_TOOLBAR_SCREENSHOTS		2100
#define wxID_TOOLBAR_COPY				2101
#define wxID_TOOLBAR_SCREENSHOTS_FOLDER	2102
#define wxID_TOOLBAR_ABOUT				2103
#define wxID_TOOLBAR_EXIT				2104
#define wxID_STATUSBAR					3000
#define wxID_PANEL						4000

#define DC_PREPARE(DC)					{DC.SetBrush(m_CBrush); DC.SetPen(m_CPen);}
#define DC_RELEASE(DC)					{DC.SetBrush(wxNullBrush); DC.SetPen(wxNullPen);}
#if LCD_PIXSIZE > 1
#define DC_DRAW_POINT(DC, POSX, POSY)	{DC.DrawRectangle(wxPoint(LCD_SIZE_MARGIN+POSX*LCD_PIXSIZE, LCD_SIZE_MARGIN+POSY*LCD_PIXSIZE), wxSize(LCD_PIXSIZE, LCD_PIXSIZE));}
#else
#define DC_DRAW_POINT(DC, POSX, POSY)	{DC.DrawPoint(wxPoint(LCD_SIZE_MARGIN+POSX*LCD_PIXSIZE, LCD_SIZE_MARGIN+POSY*LCD_PIXSIZE));}
#endif // LCD_PIXSIZE
#define	DC_SET_COLOR(COLOR)				{m_CPen.SetColour(COLOR);m_CBrush.SetColour(COLOR);}

#define SCREENSHOTS_FOLDER_T			"..\\..\\ScreenShots"
#define SCREENSHOTS_FILE_NAME_T			"LCD_%04u%02u%02u_%02u%02u-%u.bmp"
#define SCREENSHOTS_FILE_FULLNAME_T		wxString::Format("%s\\%s", SCREENSHOTS_FOLDER_T, SCREENSHOTS_FILE_NAME_T)
#define N_YEAR							wxDateTime::Now().GetYear()
#define N_MONTH							wxDateTime::Now().GetMonth()
#define N_DAY							wxDateTime::Now().GetDay()
#define N_HOUR							wxDateTime::Now().GetHour()
#define N_MINUTE						wxDateTime::Now().GetMinute()
#define SCREENSHOTS_FOLDER				_T(SCREENSHOTS_FOLDER_T)
#define SCREENSHOTS_FILE_NAME(IDX)		wxString::Format(SCREENSHOTS_FILE_NAME_T, N_YEAR, N_MONTH, N_DAY, N_HOUR, N_MINUTE, IDX)
#define SCREENSHOTS_FILE_FULLNAME(IDX)	wxString::Format(SCREENSHOTS_FILE_FULLNAME_T, N_YEAR, N_MONTH, N_DAY, N_HOUR, N_MINUTE, IDX)

///////////////////////////////////////////////////////////////////////////////
/// Class LCD_DisplayPanel
///////////////////////////////////////////////////////////////////////////////
class LCD_DisplayPanel : public wxPanel
{
	private:
		// Private object
		wxPen				m_CPen;
		wxBrush				m_CBrush;
		wxClientDC			m_CDC;
		TPixArray*			m_PixRegister;
		void				wxEvent_OnKeyDown(wxKeyEvent& event);
		void				wxEvent_OnSetFocus(wxFocusEvent& event);
	protected:
	public:

							LCD_DisplayPanel(	wxWindow* parent,
												wxWindowID id = wxID_PANEL,
												const wxPoint& pos = wxDefaultPosition,
												const wxSize& size = wxSize(LCD_SIZE_WIDTH*LCD_PIXSIZE+2*LCD_SIZE_MARGIN, LCD_SIZE_HEIGHT*LCD_PIXSIZE+2*LCD_SIZE_MARGIN),
												long style = wxTAB_TRAVERSAL);
							~LCD_DisplayPanel(void);
		void				Paint(void);
		void				PartialPaint(void);
		virtual bool		SaveToFile(const wxString& CStrFilePath);
		virtual bool		CopyToClipBoard(void);
		DECLARE_EVENT_TABLE();
};

///////////////////////////////////////////////////////////////////////////////
/// Class LCD_VirtualDevice
///////////////////////////////////////////////////////////////////////////////
class LCD_VirtualDevice : public wxFrame
{
	private:
		void				SetStatusText(const wxString& cString);

		void				wxEvent_OnUpdateUI(wxUpdateUIEvent& event)	{OnUpdateUI(event);}
		void				wxEvent_OnSetFocus(wxFocusEvent& event)		{SetFocus();}
		void				wxEvent_OnClose(wxCloseEvent& event)		{OnClose(event);}
		void				wxEvent_OnKeyDown(wxKeyEvent& event)		{OnKeyDown(event);}
		void				wxEvent_OnPaint(wxPaintEvent &event)		{OnPaint(event);event.Skip();}
		void				wxEvent_OnScreenshots(wxCommandEvent &event){Screenshots();}
		void				wxEvent_OnToolCopy(wxCommandEvent &event)	{Copy();}
		void				wxEvent_OnOpenScreenshotsFolder(wxCommandEvent &event){OpenScreenshotsFolder();}
		void				wxEvent_OnAbout(wxCommandEvent &event)		{;}
		void				wxEvent_OnExit(wxCommandEvent &event)		{Destroy();}
	protected:
		// Controlers
		wxStatusBar*		m_CtrlStatusBar;
		wxToolBar*			m_CtrlToolBar;
		wxToolBarToolBase*	m_CtrlToolButton_Screenshots;
		wxToolBarToolBase*	m_CtrlToolButton_ScreenCpoy;
		wxToolBarToolBase*	m_CtrlToolButton_OpenFolder;
		wxToolBarToolBase*	m_CtrlToolButton_About;
		wxToolBarToolBase*	m_CtrlToolButton_Exit;
		LCD_DisplayPanel*	m_CtrlPaintPanel;

		virtual void		OnUpdateUI(wxUpdateUIEvent& event);
		virtual void		OnClose(wxCloseEvent& event)				{Destroy();}
		virtual void		OnKeyDown(wxKeyEvent& event);
		virtual void		OnPaint(wxPaintEvent &event);
		virtual void		Screenshots(void);
		virtual void		Copy(void);
		virtual void		OpenScreenshotsFolder(void);
	public:

							LCD_VirtualDevice(	wxWindow* parent,
												wxWindowID id			= wxID_MAIN,
												const wxString& title	= FRAME_TITLE,
												const wxPoint& pos		= wxDefaultPosition,
												const wxSize& size		= wxSize(500,300),
												long style				=  wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN);

							~LCD_VirtualDevice();

		DECLARE_EVENT_TABLE();

};

#endif //__INCLUDE_LCD_VIRTUAL_DEVICE_H__
