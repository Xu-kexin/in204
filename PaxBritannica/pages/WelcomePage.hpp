#ifndef WelcomePage_hpp
#define WelcomePage_hpp

#include "../parameters.h"

class WelcomePage : public wxFrame
{
public:
    // The background image
    wxBitmap m_bitmap;
    // The bitmap for the title image
    wxBitmap m_titleBitmap;
    // The game mode choice widget
    wxChoice* gameModeChoice;
    WelcomePage();
private:
    // Event handler for the painting
    void OnPaint(wxPaintEvent& event);
    // Event handler for the game mode choice widget
    void OnGameModeChoice(wxCommandEvent& event);
    // Event handler for the start button
    void OnStart(wxCommandEvent& event);
    // Event handler for the end button
    void OnEnd(wxCommandEvent& event);
};

#endif
