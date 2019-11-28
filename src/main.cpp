// base foudnation from https://stackoverflow.com/questions/55877790/wxwidgets-best-control-for-drawing-realtime-graphics
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
#include "Color.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/timer.h>
#include <wx/dcclient.h>
#include <wx/rawbmp.h>
#include "Vector3.h"
#include "Matrix.h"
#include "Ray.h"

///////////// Declarations

class MyFrame : public wxFrame
{
public:
	MyFrame(wxWindow* parent, int id = wxID_ANY, wxString title = "Demo",
		wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize,
		int style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	~MyFrame();

private:
	// Event Handlers
	void OnPaint(wxPaintEvent& event);
	void OnTimer(wxTimerEvent& event);

	// Helper function
	void Render();
	void SetPixel(int x, int y, Color c);
	void FillBitmap();

	// Private data
	wxWindow* m_renderSurface;
	int m_width;
	int m_height;
	int m_stride;
	wxBitmap m_bitmapBuffer;
	wxTimer m_timer;
	unsigned int m_curRGB;
	unsigned char* m_pixelData;
};

class MyApp : public wxApp
{
public:
	virtual bool OnInit() wxOVERRIDE;
};

wxDECLARE_APP(MyApp);


///////////// Implementation

MyFrame::MyFrame(wxWindow* parent, int id, wxString title, wxPoint pos,
	wxSize size, int style)
	:wxFrame(parent, id, title, pos, size, style)
{
	m_width = 200;
	m_height = 200;

	int validBitsPerLine = m_width * 24;
	m_stride = ((validBitsPerLine + 31) / 32) * 4;

	//m_pixelData = new unsigned char[3 * m_width*m_height];
	m_pixelData = new unsigned char[m_stride * m_height];

	m_renderSurface = new wxWindow(this, wxID_ANY, wxDefaultPosition,
		wxSize(m_width, m_height));
	m_renderSurface->SetBackgroundStyle(wxBG_STYLE_PAINT);
	m_renderSurface->Bind(wxEVT_PAINT, &MyFrame::OnPaint, this);

	wxBoxSizer* bSizer = new wxBoxSizer(wxVERTICAL);
	bSizer->Add(m_renderSurface, 0);
	this->SetSizer(bSizer);
	Layout();

	m_timer.SetOwner(this);
	m_timer.Start(17);
	this->Bind(wxEVT_TIMER, &MyFrame::OnTimer, this);
	m_curRGB = 0;
}

MyFrame::~MyFrame()
{
	m_timer.Stop();
	delete[] m_pixelData;
}

// Draw Bitmap to Rect
void MyFrame::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(m_renderSurface);
	if (m_bitmapBuffer.IsOk())
	{
		dc.DrawBitmap(m_bitmapBuffer, 0, 0);
	}
}

// Call Render every 17 ms
void MyFrame::OnTimer(wxTimerEvent& event)
{
	Render();
}

// Set Pixel
void MyFrame::SetPixel(int x, int y, Color c)
{
	int idx = y * m_stride + x * 3;
	m_pixelData[idx] = c.GetRComponent();
	m_pixelData[idx+1] = c.GetGComponent();
	m_pixelData[idx+2] = c.GetBComponent();
}

// Copy Raw Color Buffer (m_pixelData) to Bitmap
void MyFrame::FillBitmap()
{
	wxBitmap b(m_width, m_height, 24);
	wxNativePixelData data(b);

	if (!data)
	{
		// ... raw access to bitmap data unavailable, do something else ...
		return;
	}

	wxNativePixelData::Iterator p(data);

	int curPixelDataLoc = 0;
	for (int y = 0; y < m_height; ++y)
	{
		wxNativePixelData::Iterator rowStart = p;
		for (int x = 0; x < m_width; ++x, ++p)
		{
			p.Red() = m_pixelData[curPixelDataLoc++];
			p.Green() = m_pixelData[curPixelDataLoc++];
			p.Blue() = m_pixelData[curPixelDataLoc++];
		}
		p = rowStart;
		p.OffsetY(data, 1);
	}

	m_bitmapBuffer = b;
}

// Render Function
void MyFrame::Render()
{
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; ++x)
		{
			SetPixel(x, y, Color(m_curRGB, m_curRGB, m_curRGB));
		}
	}

	++m_curRGB;
	if (m_curRGB>255)
	{
		m_curRGB = 0;
	}

	FillBitmap();

	m_renderSurface->Refresh();
	m_renderSurface->Update();
}


bool MyApp::OnInit()
{
	MyFrame* frame = new MyFrame(NULL);
	frame->Show();
	return true;
}

wxIMPLEMENT_APP(MyApp);