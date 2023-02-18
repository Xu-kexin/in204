//
//  WelcomePage.cpp
//  PaxBritannica
//
//  Created by Laurine Xu on 2022/12/08.
//

#include "WelcomePage.hpp"
#include "GamePage.hpp"

const char * w_soundFiles="res/music.mp3";
const char * w_backgoundFiles="res/background.png";
const char * w_titleFiles="res/logo.png";

using namespace std;

WelcomePage::WelcomePage() : wxFrame(nullptr, wxID_ANY, "Pax Britannica"), bg_music(w_soundFiles) {
    // Set the size and position of the frame
    SetSize(windowSize);
    Centre();
    
    wxLogNull AD;
    wxInitAllImageHandlers();
    // Load the background image
    m_bitmap.LoadFile(w_backgoundFiles, wxBITMAP_TYPE_ANY);
    // Load the title image
    m_titleBitmap.LoadFile(w_titleFiles, wxBITMAP_TYPE_ANY);
    // Bind the OnPaint method to the EVT_PAINT event
    Bind(wxEVT_PAINT, &WelcomePage::OnPaint, this);
    
    // Create the game mode choice widget
    gameModeChoice = new wxChoice(this, wxID_ANY);
    // Add the available game modes to the choice widget
    gameModeChoice->Append("One player");
    gameModeChoice->Append("Multiplayer");
    // Bind the EVT_CHOICE event to the OnGameModeChoice handler
    gameModeChoice->Bind(wxEVT_CHOICE, &WelcomePage::OnGameModeChoice, this);

    // Create the start and end buttons
    auto startButton = new wxButton(this, wxID_ANY, "Start game");
    auto endButton = new wxButton(this, wxID_ANY, "Exit game");
    soundButton = new wxButton(this, wxID_ANY, "Mute", wxPoint(20, windowSize.GetHeight()*17/20));

    // Put buttons in the bottom of my frame
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *bottomSizer = new wxBoxSizer(wxHORIZONTAL);
    
    sizer->AddStretchSpacer();
    sizer->Add(bottomSizer, 1, wxEXPAND, 10);
    bottomSizer->Add(startButton, 1, wxEXPAND|wxALL, 10);
    bottomSizer->Add(gameModeChoice, 1, wxEXPAND|wxALL, 10);
    bottomSizer->Add(endButton, 1, wxEXPAND|wxALL, 10);
    SetSizer(sizer);

    // Bind the buttons to event handlers
    startButton->Bind(wxEVT_BUTTON, &WelcomePage::OnStart, this);
    endButton->Bind(wxEVT_BUTTON, &WelcomePage::OnEnd, this);
    soundButton->Bind(wxEVT_BUTTON, &WelcomePage::OnMute, this);

    // Draw the text string
    CreateStatusBar(2); 
    SetStatusText("Credit: Kexin Xu, Amaury Lorin", 1);
    
    // Sound effect
    PlayMusic();
}

void WelcomePage::OnPaint(wxPaintEvent& event) 
{
    // Create a device context for drawing
    wxPaintDC dc(this);
    
    // Get the size of the frame
    windowSize = GetClientSize();
    
    if (windowSize.GetHeight()-40 > 0)
        soundButton->SetPosition(wxPoint(20, windowSize.GetHeight()-40));
    
    // Draw the background image
    wxBitmap bg(m_bitmap);
    wxBitmap::Rescale(bg, windowSize);
    dc.DrawBitmap(bg, 0, 0);
    
    // Calculate the x and y coordinates for the title image
    auto x = (windowSize.GetWidth() - m_titleBitmap.GetWidth()) / 2;
    auto y = (windowSize.GetHeight() - m_titleBitmap.GetHeight()) / 3;
    // Draw the title image at the bottom of the page
    dc.DrawBitmap(m_titleBitmap, x, y, true);
}

// Event handler for the game mode choice widget
void WelcomePage::OnGameModeChoice(wxCommandEvent& event)
{   
    // Get the selected game mode
    auto gameMode = gameModeChoice->GetStringSelection();
}

// Event handler for the start button
void WelcomePage::OnStart(wxCommandEvent& event)
{
    // Start the main program here
    auto gamePage = new GamePage();
    Close(true);
    gamePage->Show();
}

// Event handler for the end button
void WelcomePage::OnEnd(wxCommandEvent& event)
{
    // End the program here
    Close(true);
}

void WelcomePage::PlayMusic()
{
    bg_music.play();
}

void WelcomePage::OnMute(wxCommandEvent &event) {
    if (bg_music.isPlaying()) {
        bg_music.stop();
        soundButton->SetLabelText("Unmute");
    } else {
        bg_music.play();
        soundButton->SetLabelText("Mute");
    }
}
