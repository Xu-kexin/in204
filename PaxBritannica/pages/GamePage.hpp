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
    GamePage(bool mult);
private:
    // The background image
    wxBitmap m_bitmap;
    bool multiplayer;
    Environment env;
    wxTimer m_timer;
    wxStaticText* score_text1 {nullptr};
    wxStaticText* score_text2 {nullptr};
    int key_pressed1 {0};
    int key_pressed2 {0};
    std::chrono::steady_clock::time_point last_shoot1;
    std::chrono::steady_clock::time_point last_shoot2;
    int score1 {0};
    int score2 {0};
    
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
