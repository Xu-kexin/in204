#ifndef GamePage_hpp
#define GamePage_hpp

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/dcbuffer.h>
#include "wx/toolbar.h"

class GamePage : public wxFrame
{
public:
    // The background image
    wxBitmap m_bitmap;
    // Buttons
    wxButton* returnButton {nullptr};
    wxButton* replayButton {nullptr};
    GamePage();
private:
    // Event handler for the painting
    void OnPaint(wxPaintEvent& event);
    // Event handler for replay
    void OnReplay(wxCommandEvent& event);
    // Event handler for exit
    void OnReturn(wxCommandEvent& event);
};


#endif /* GamePage_hpp */
