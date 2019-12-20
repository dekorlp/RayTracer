// base foudnation from https://stackoverflow.com/questions/55877790/wxwidgets-best-control-for-drawing-realtime-graphics
// and https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing/how-does-it-work
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
#include "Color.h"
#include "Sphere.h"
#include "Scene.h"
#include "Vector3.h"
#include "Ray.h"
#include "Camera.h"		
#include "Triangle.h"

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


#define WIDTH 640
#define HEIGHT 480
#define TITLE "RayTracing Demo"

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

	// Helper function
	void Render(int width, int height);
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
	Scene mWorld;
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
	m_width = size.GetWidth();
	m_height = size.GetHeight();

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
	

	// coordinate system:
	// +x -> left direction
	// -x -> right direction
	// +y -> near to cam
	// -y -> away from cam
	// +z -> down
	// -z -> top

	float R = cos(M_PI / 4);
	mWorld.Add(new Sphere(Vector3(-R-0.3, -0.8, -1), R, Vector3(1.00, 0.32, 0.36), 1));
	mWorld.Add(new Sphere(Vector3(R, -0, -1), R, Vector3(0.65, 0.77, 0.97), 0.0));
	//mWorld.Add(new Sphere(Vector3(-1, -4, -2), R, Vector3(0, 1, 0), 1.0));

	mWorld.AddPlane(Vector3(0, 0, 4), 5, 5, Vector3(0, 0, 1), 0.0);
	
	//mWorld.Add(new Triangle(Vector3(-0.3, -1, -1), Vector3(0.3, -1, -1), Vector3(0, -1, -1), Vector3(0, 1, 0)));

	mWorld.Add(new Light(Vector3(1.0, 1.0, 1.0), Vector3(10, 10, 10)));


	Render(m_width, m_height);

	FillBitmap();

	if (m_bitmapBuffer.IsOk())
	{
		dc.DrawBitmap(m_bitmapBuffer, 0, 0);
	}

	for (int i = 0; i < mWorld.PrimitiveCount(); i++)
	{
		delete mWorld.getPrimitive(i);
	}
	delete mWorld.GetLight();
	mWorld.ClearPrimitives();
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

void MyFrame::Render(int width, int height)
{
	Vector3 lower_left_coner(-2.0, -1.0, -1.0);
	Vector3 horizontal(4.0, 0.0, 0.0);
	Vector3 vertical(0.0, 2.0, 0.0);
	Vector3 origin(0.0, 0.0, 0.0);

	Camera cam(Vector3(0, 1, -2.5), Vector3(0,0, -1), Vector3(0,1,0), 90, float(width)/float(height));
	for (int j = height-1; j >= 0; j--)
	{
		for (int i = 0; i < width; i++)
		{
			float u = float(i) / float(width);
			float v = float(j) / float(height);
			//Ray ray(origin, lower_left_coner + u*horizontal + v*vertical);
			Ray ray = cam.getRay(u, v);
			//Vector3 col = colorGradient(ray);
			Vector3 col = mWorld.Trace(ray);
			float r = int(255.99 * col.r());
			float g = int(255.99 * col.g());
			float b = int(255.99 * col.b());
			SetPixel(i, j, Color(r, g, b));
		}
	}


	/*Vec3f *image = new Vec3f[width * height], *pixel = image;
	float invWidth = 1 / float(width), invHeight = 1 / float(height);
	float fov = 30, aspectratio = width / float(height);
	float angle = tan(M_PI * 0.5 * fov / 180.);
	// Trace rays
	for (unsigned y = 0; y < height; ++y) {
		for (unsigned x = 0; x < width; ++x, ++pixel) {
			float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
			float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
			Vec3f raydir(xx, yy, -1);
			raydir.normalize();
			*pixel = trace(Vec3f(0), raydir, spheres, 0);
			SetPixel(x, y, Color(std::min(float(1), pixel->x) * 255, std::min(float(1), pixel->y) * 255, std::min(float(1), pixel->z) * 255));
		}
	}*/
}

bool MyApp::OnInit()
{
	//MyFrame* frame = new MyFrame(NULL);
	MyFrame* frame = new MyFrame(NULL, -1, TITLE, { 0,0 }, {WIDTH, HEIGHT}, wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	frame->Show();
	return true;
}

wxIMPLEMENT_APP(MyApp);