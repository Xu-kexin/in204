//
//  GamePage.cpp
//  PaxBritannica
//
//  Created by Laurine Xu on 2022/12/08.
//
#include "WelcomePage.hpp"
#include "GamePage.hpp"

const char* g_backgoundFiles="res/background.png";

GamePage::GamePage() : wxFrame(nullptr, wxID_ANY, "Pax Britannica"), env(windowSize)
{
    // Set the size and position of the frame
    SetSize(windowSize);
    Centre();
    
    wxLogNull AD;
    wxInitAllImageHandlers();
    // Load the background image
    m_bitmap.LoadFile(g_backgoundFiles, wxBITMAP_TYPE_ANY);
   
    // Bind the OnPaint method to the EVT_PAINT event
    Bind(wxEVT_PAINT, &GamePage::OnPaint, this);
    
    // Pose the return and replay buttons
    returnButton = new wxButton(this, wxID_ANY, "Return");
    replayButton = new wxButton(this, wxID_ANY, "Replay");
    // Bind the buttons to event handlers
    returnButton->Bind(wxEVT_BUTTON, &GamePage::OnReturn, this);
    replayButton->Bind(wxEVT_BUTTON, &GamePage::OnReplay, this);
    
    // Draw the text string
    CreateStatusBar(2);
    SetStatusText("Credit: Amaury Lorin, Kexin Xu", 1);
    
    env.AddPlayer(1);
    for (int i=0; i<5; i++)
        env.AddBot();
    
    // Timer for updating every 1s
    std::thread timer([this]{
        while(true){
            if (stopped) return;
            this->env.Step();
            this->Refresh();
            usleep(2048);
        }
    });
    timer.detach();
    
}

void GamePage::OnPaint(wxPaintEvent& event)
{
    // Create a device context for drawing
    wxPaintDC dc(this);
    
    // prevent window size from changing
    SetSize(windowSize);
    
    // Draw the background image
    wxBitmap bg(m_bitmap);
    wxBitmap::Rescale(bg, windowSize);
    dc.DrawBitmap(bg, 0, 0, true);
    
    returnButton->SetPosition(wxPoint(windowSize.GetWidth()*4/6, windowSize.GetHeight()*5/6));
    replayButton->SetPosition(wxPoint(windowSize.GetWidth()/6, windowSize.GetHeight()*5/6));
    
    env.DrawShips(dc);
}


// Event handler for replay
void GamePage::OnReplay(wxCommandEvent& event)
{
    auto NewGame = new GamePage();
    Close(true);
    NewGame->Show();
}

// Event handler for return
void GamePage::OnReturn(wxCommandEvent& event)
{
    auto Welcome = new WelcomePage();
    Close(true);
    Welcome->Show();
}


