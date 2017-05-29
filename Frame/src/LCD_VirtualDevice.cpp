///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////
#include "wx\wx.h"
#include "LCD_VirtualDevice.h"
#include <wx/dcbuffer.h>
#include <wx/clipbrd.h>
#include <wx/filefn.h>

///////////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE(LCD_DisplayPanel,wxPanel)
    EVT_KEY_DOWN(LCD_DisplayPanel::wxEvent_OnKeyDown)
    EVT_SET_FOCUS(LCD_DisplayPanel::wxEvent_OnSetFocus)
END_EVENT_TABLE()

LCD_DisplayPanel::LCD_DisplayPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ):
	wxPanel(parent, id, pos, size, style),
	m_CDC(this),
	m_PixRegister(&g_LCDPixArray)
{
	SetSizeHints(wxDefaultSize, wxDefaultSize);
}

LCD_DisplayPanel::~LCD_DisplayPanel()
{
}

void LCD_DisplayPanel::wxEvent_OnKeyDown(wxKeyEvent& event)
{
	event.ResumePropagation(1);
	event.Skip();
}

void LCD_DisplayPanel::wxEvent_OnSetFocus(wxFocusEvent& event)
{
	event.ResumePropagation(1);
	event.Skip();
}

void LCD_DisplayPanel::Paint(void)
{
	wxBitmap			CDCBufferImage(LCD_SIZE_WIDTH*LCD_PIXSIZE+2*LCD_SIZE_MARGIN, LCD_SIZE_HEIGHT*LCD_PIXSIZE+2*LCD_SIZE_MARGIN, wxBITMAP_SCREEN_DEPTH);
	wxBufferedDC		CDCBuffer(&m_CDC, CDCBufferImage);

	// Clear background
	DC_SET_COLOR(FRM_COLOR_OBJ_BKG);
	DC_PREPARE(CDCBuffer);
	CDCBuffer.DrawRectangle(wxPoint(0, 0), wxSize(LCD_SIZE_WIDTH*LCD_PIXSIZE+2*LCD_SIZE_MARGIN, LCD_SIZE_HEIGHT*LCD_PIXSIZE+2*LCD_SIZE_MARGIN));
	// Draw LCD edge.
    DC_SET_COLOR(LCD_COLOR_OBJ_EDGE);
    DC_PREPARE(CDCBuffer);
    CDCBuffer.DrawRectangle(	wxPoint(LCD_SIZE_MARGIN-LCD_DISPLAY_EDGE, LCD_SIZE_MARGIN-LCD_DISPLAY_EDGE),
								wxSize((LCD_SIZE_WIDTH * LCD_PIXSIZE)+(2*LCD_DISPLAY_EDGE), (LCD_SIZE_HEIGHT * LCD_PIXSIZE)+(2*LCD_DISPLAY_EDGE)));

    // Draw LCD display area
    DC_SET_COLOR(LCD_COLOR_OBJ_BKG);
    DC_PREPARE(CDCBuffer);
    CDCBuffer.DrawRectangle(wxPoint(LCD_SIZE_MARGIN, LCD_SIZE_MARGIN), wxSize((LCD_SIZE_WIDTH * LCD_PIXSIZE), (LCD_SIZE_HEIGHT * LCD_PIXSIZE)));

    for(size_t i_W=0; i_W<LCD_SIZE_WIDTH; i_W++)
	{
		for(size_t i_H=0; i_H<LCD_SIZE_HEIGHT; i_H++)
		{
			if(0 == m_PixRegister->Pixregister[i_W][i_H])
			{
				DC_SET_COLOR(LCD_COLOR_OBJ_BKG);
			}
			else
			{
				DC_SET_COLOR(LCD_COLOR_OBJ_PIX);
			}

			DC_PREPARE(CDCBuffer);
			DC_DRAW_POINT(CDCBuffer, i_W, i_H);
		}
	}
}

void LCD_DisplayPanel::PartialPaint(void)
{
	if(true == m_PixRegister->InUpdating)
    {
    	wxBitmap			CDCBufferImage(LCD_SIZE_WIDTH*LCD_PIXSIZE+2*LCD_SIZE_MARGIN, LCD_SIZE_HEIGHT*LCD_PIXSIZE+2*LCD_SIZE_MARGIN, wxBITMAP_SCREEN_DEPTH);
		wxBufferedDC		CDCBuffer(&m_CDC, CDCBufferImage);

		CDCBuffer.Blit(	wxPoint(0,0),
						wxSize(LCD_SIZE_WIDTH*LCD_PIXSIZE+2*LCD_SIZE_MARGIN, LCD_SIZE_HEIGHT*LCD_PIXSIZE+2*LCD_SIZE_MARGIN),
						&m_CDC,
						wxPoint(0, 0));

        for(uint32_t i_W=m_PixRegister->ChangedArea.StartPosX; i_W<=m_PixRegister->ChangedArea.EndPosX; i_W++)
        {
            for(uint32_t i_H=m_PixRegister->ChangedArea.StartPosY; i_H<=m_PixRegister->ChangedArea.EndPosY; i_H++)
            {
                if(0 == m_PixRegister->Pixregister[i_W][i_H])
                {
                    DC_SET_COLOR(LCD_COLOR_OBJ_BKG);
                }
                else
                {
                    DC_SET_COLOR(LCD_COLOR_OBJ_PIX);
                }
				DC_PREPARE(CDCBuffer);
                DC_DRAW_POINT(CDCBuffer, i_W, i_H);
            }
        }
        m_PixRegister->InUpdating = false;
        m_PixRegister->ChangedArea.StartPosX = LCD_SIZE_WIDTH;
        m_PixRegister->ChangedArea.StartPosY = LCD_SIZE_HEIGHT;
        m_PixRegister->ChangedArea.EndPosX = 0;
        m_PixRegister->ChangedArea.EndPosY = 0;
        DC_RELEASE(CDCBuffer);
    }
}

bool LCD_DisplayPanel::SaveToFile(const wxString& CStrFilePath)
{
	// Create and initialize bitmap.
	wxBitmap		CBitMap(LCD_SIZE_WIDTH*LCD_PIXSIZE+(2*LCD_DISPLAY_EDGE)+2, LCD_SIZE_HEIGHT*LCD_PIXSIZE+(2*LCD_DISPLAY_EDGE)+2, wxBITMAP_SCREEN_DEPTH);
	wxMemoryDC		CMemoryDC(CBitMap);
	CMemoryDC.Blit(	wxPoint(0, 0),
					wxSize(LCD_SIZE_WIDTH*LCD_PIXSIZE+(2*LCD_DISPLAY_EDGE)+2, LCD_SIZE_HEIGHT*LCD_PIXSIZE+(2*LCD_DISPLAY_EDGE)+2),
					&m_CDC,
					wxPoint(LCD_SIZE_MARGIN-(LCD_DISPLAY_EDGE+1), LCD_SIZE_MARGIN-(LCD_DISPLAY_EDGE+1)));
	return CBitMap.SaveFile(CStrFilePath, wxBITMAP_TYPE_BMP);
}

bool LCD_DisplayPanel::CopyToClipBoard(void)
{
	// Create and initialize bitmap.
	wxBitmap		CBitMap(LCD_SIZE_WIDTH*LCD_PIXSIZE+(2*LCD_DISPLAY_EDGE)+2, LCD_SIZE_HEIGHT*LCD_PIXSIZE+(2*LCD_DISPLAY_EDGE)+2, wxBITMAP_SCREEN_DEPTH);
	wxMemoryDC		CMemoryDC(CBitMap);
	CMemoryDC.Blit(	wxPoint(0, 0),
					wxSize(LCD_SIZE_WIDTH*LCD_PIXSIZE+(2*LCD_DISPLAY_EDGE)+2, LCD_SIZE_HEIGHT*LCD_PIXSIZE+(2*LCD_DISPLAY_EDGE)+2),
					&m_CDC,
					wxPoint(LCD_SIZE_MARGIN-(LCD_DISPLAY_EDGE+1), LCD_SIZE_MARGIN-(LCD_DISPLAY_EDGE+1)));

	if(wxTheClipboard->Open())
	{
		wxTheClipboard->SetData(new wxBitmapDataObject(CBitMap));
		wxTheClipboard->Close();
		return true;
	}
	else
	{
		return false;
	}
}


///////////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE(LCD_VirtualDevice,wxFrame)
	EVT_UPDATE_UI(wxID_MAIN, LCD_VirtualDevice::wxEvent_OnUpdateUI)
	EVT_SET_FOCUS(LCD_VirtualDevice::wxEvent_OnSetFocus)
    EVT_CLOSE(LCD_VirtualDevice::wxEvent_OnClose)
    EVT_SET_FOCUS(LCD_VirtualDevice::wxEvent_OnSetFocus)
    EVT_KEY_DOWN(LCD_VirtualDevice::wxEvent_OnKeyDown)
    EVT_PAINT(LCD_VirtualDevice::wxEvent_OnPaint)
    EVT_TOOL(wxID_TOOLBAR_SCREENSHOTS, LCD_VirtualDevice::wxEvent_OnScreenshots)
    EVT_TOOL(wxID_TOOLBAR_COPY, LCD_VirtualDevice::wxEvent_OnToolCopy)
    EVT_TOOL(wxID_TOOLBAR_SCREENSHOTS_FOLDER, LCD_VirtualDevice::wxEvent_OnOpenScreenshotsFolder)
    EVT_TOOL(wxID_TOOLBAR_EXIT, LCD_VirtualDevice::wxEvent_OnExit)
END_EVENT_TABLE()

LCD_VirtualDevice::LCD_VirtualDevice(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) :
	wxFrame(parent, id, title, pos, size, style)
{
	SetSizeHints( wxDefaultSize, wxDefaultSize );
	//Layout();
	SetIcon(wxIcon(_T("ID_ICON_MAIN"), wxBITMAP_TYPE_ICO_RESOURCE));
	m_CtrlStatusBar					= CreateStatusBar(1, wxST_SIZEGRIP, wxID_STATUSBAR);
	m_CtrlToolBar					= CreateToolBar(wxTB_HORIZONTAL, wxID_TOOLBAR);
	m_CtrlToolButton_Screenshots	= m_CtrlToolBar->AddTool(	wxID_TOOLBAR_SCREENSHOTS, _T("Screenshots"),
																wxBitmap(_T("ID_TOOL_SCREENSHOTS")),
																wxBitmap(_T("ID_TOOL_SCREENSHOTS")),
																wxITEM_NORMAL,
																_T("Screenshots"),
																_T("Save LCD screenshots to file."));
	m_CtrlToolButton_ScreenCpoy		= m_CtrlToolBar->AddTool(	wxID_TOOLBAR_COPY, _T("Copy LCD screen"),
																wxBitmap(_T("ID_TOOL_COPY")),
																wxBitmap(_T("ID_TOOL_COPY")),
																wxITEM_NORMAL,
																_T("Copy"),
																_T("Copy current LCD Screen image to clipboard."));
	m_CtrlToolButton_OpenFolder		= m_CtrlToolBar->AddTool(	wxID_TOOLBAR_SCREENSHOTS_FOLDER, _T("Open folder"),
																wxBitmap(_T("ID_TOOL_OPENFOLDER")),
																wxBitmap(_T("ID_TOOL_OPENFOLDER")),
																wxITEM_NORMAL,
																_T("Open screenshots folder"),
																_T("Open screenshots image saved folder."));
	m_CtrlToolBar->AddSeparator();
	m_CtrlToolButton_Exit			= m_CtrlToolBar->AddTool(	wxID_TOOLBAR_EXIT, _T("Exit"),
																wxBitmap(_T("ID_TOOL_EXIT")),
																wxBitmap(_T("ID_TOOL_EXIT")),
																wxITEM_NORMAL,
																_T("Exit"),
																_T("Exit."));
	m_CtrlToolBar->Realize();
	SetClientSize(LCD_SIZE_WIDTH*LCD_PIXSIZE+2*LCD_SIZE_MARGIN, LCD_SIZE_HEIGHT*LCD_PIXSIZE+2*LCD_SIZE_MARGIN);
	m_CtrlPaintPanel = new LCD_DisplayPanel(this, wxID_PANEL, wxPoint(0, 0), wxSize(LCD_SIZE_WIDTH*LCD_PIXSIZE+2*LCD_SIZE_MARGIN, LCD_SIZE_HEIGHT*LCD_PIXSIZE+2*LCD_SIZE_MARGIN));
	m_CtrlPaintPanel->SetBackgroundColour(FRM_COLOR_OBJ_BKG);
	Centre( wxBOTH );

	if(false == wxDirExists(SCREENSHOTS_FOLDER))
	{
        wxMkdir(SCREENSHOTS_FOLDER);
	}
	UpdateWindow(GetHandle());
}

LCD_VirtualDevice::~LCD_VirtualDevice()
{
	delete m_CtrlStatusBar;
	delete m_CtrlToolBar;
}

void LCD_VirtualDevice::SetStatusText(const wxString& cString)
{
    m_CtrlStatusBar->SetStatusText(cString, 0);
}

void LCD_VirtualDevice::OnKeyDown(wxKeyEvent& event)
{
    uint16_t	uiKeyCode;
    uiKeyCode = (uint16_t)event.GetKeyCode();

	VTIF_KeyBoardEvent(event.ShiftDown(), event.ControlDown(), event.AltDown(), uiKeyCode);
	m_CtrlPaintPanel->PartialPaint();
}

void LCD_VirtualDevice::Copy(void)
{
	bool	bResult = m_CtrlPaintPanel->CopyToClipBoard();
	if(true == bResult)
	{
		SetStatusText(_T("Copied to clipboard."));
	}
	else
	{
		SetStatusText(_T("Copy failed."));
	}
}

void LCD_VirtualDevice::Screenshots(void)
{
	uint32_t		uiFileCounter = 1;
	while(true == wxFileExists(SCREENSHOTS_FILE_FULLNAME(uiFileCounter)))
	{
		uiFileCounter++;
	}
	if(true == m_CtrlPaintPanel->SaveToFile(SCREENSHOTS_FILE_FULLNAME(uiFileCounter)))
	{
		SetStatusText(wxString::Format("Save screen to %s.", SCREENSHOTS_FILE_NAME(uiFileCounter)));
	}
	else
	{
		SetStatusText(_T("Save screen failed."));
	}
}

void LCD_VirtualDevice::OnUpdateUI(wxUpdateUIEvent& event)
{
	static bool bInitialized = false;

    if(false == bInitialized)
	{
		VTIF_LCDInitializeDisplay();
		bInitialized = true;
		m_CtrlPaintPanel->Paint();
		SetStatusText(_T("Initialzied."));
	}
}

void LCD_VirtualDevice::OnPaint(wxPaintEvent &event)
{
	m_CtrlPaintPanel->Paint();
}

void LCD_VirtualDevice::OpenScreenshotsFolder(void)
{
    wxExecute(wxString::Format(_T("explorer %s\\%s"), wxGetCwd(), _T(SCREENSHOTS_FOLDER_T)));
}
