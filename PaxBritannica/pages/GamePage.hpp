#ifndef GamePage_hpp
#define GamePage_hpp

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/dcbuffer.h>

class GamePage : public wxFrame
{
public:
    // The background image
    wxBitmap m_bitmap;
    // The bitmap for the ship
    wxBitmap m_titleBitmap;
    GamePage();
private:
    // Event handler for the painting
    void OnPaint(wxPaintEvent& event);
    void OnStart(wxCommandEvent& event);
    // Event handler for the end button
    void OnEnd(wxCommandEvent& event);
};


#endif /* GamePage_hpp */
