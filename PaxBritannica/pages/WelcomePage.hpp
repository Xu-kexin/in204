//
//  WelcomePage.hpp
//  PaxBritannica
//
//  Created by Laurine Xu on 2022/12/08.
//

#ifndef WelcomePage_hpp
#define WelcomePage_hpp

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include "../utils/SoundPlayer.hpp"

static wxSize windowSize(800, 600);

class WelcomePage : public wxFrame
{
public:
    WelcomePage();
private:
    SoundPlayer bg_music;
    wxButton* soundButton {nullptr};
    // The background image
    wxBitmap m_bitmap;
    // The bitmap for the title image
    wxBitmap m_titleBitmap;
    wxChoice* gameModeChoice {nullptr};
    
    // Event handler for the painting
    void OnPaint(wxPaintEvent& event);
    // Event handler for the start button
    void OnStart(wxCommandEvent& event);
    // Event handler for the end button
    void OnEnd(wxCommandEvent& event);
    // Event handler for the mute button
    void OnMute(wxCommandEvent& event);
    // Event handler for the sound effect
    void PlayMusic();
};

#endif
