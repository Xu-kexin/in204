//
//  GamePage.cpp
//  PaxBritannica
//
//  Created by Laurine Xu on 2022/12/08.
//
#ifndef GamePage_hpp
#define GamePage_hpp

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <thread>
#include <wx/dcbuffer.h>
#include <wx/toolbar.h>
#include "wx/timer.h"

#include "../objects/Environment.hpp"

class GamePage : public wxFrame
{
public:
    // The background image
    wxBitmap m_bitmap;
    GamePage();
private:
    Environment env;
    wxTimer m_timer;
    wxStaticText* score1 {nullptr};
    wxStaticText* score2 {nullptr};
    int key_pressed1 {0};
    std::chrono::steady_clock::time_point last_shoot;
    
    // Event handler for the painting
    void OnPaint(wxPaintEvent& event);
    // Event handler for replay
    void OnReplay(wxCommandEvent& event);
    // Event handler for exit
    void OnExit(wxCommandEvent& event);
    // Event handler for timer
    void OnTimer(wxTimerEvent& event);
    // Event handler for keyboard events key down
    void OnKeyDown(wxKeyEvent& event);
    // Event handler for keyboard events key up
    void OnKeyUp(wxKeyEvent& event);
};


#endif /* GamePage_hpp */
