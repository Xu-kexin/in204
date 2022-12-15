#include "WelcomePage.hpp"
#include "GamePage.hpp"

WelcomePage::WelcomePage() : wxFrame(nullptr, wxID_ANY, "Pax Britannica")
{
    // Set the size and position of the frame
    SetSize(windowSize);
    Centre();
    
    wxInitAllImageHandlers();
    // Load the background image
    m_bitmap.LoadFile("res/background.png", wxBITMAP_TYPE_ANY);
    // Load the title image
    m_titleBitmap.LoadFile("res/logo.png", wxBITMAP_TYPE_PNG);
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
    
    // Put buttons in the bottom of my frame
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);
    wxBoxSizer *bottomSizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->AddStretchSpacer();
    sizer->Add(bottomSizer, 1, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 10);
    bottomSizer->Add(startButton, 1, wxEXPAND|wxALL, 10);
    bottomSizer->Add(gameModeChoice, 1, wxEXPAND|wxALL, 10);
    bottomSizer->Add(endButton, 1, wxEXPAND|wxALL, 10);
    SetSizer(sizer);

    // Bind the buttons to event handlers
    startButton->Bind(wxEVT_BUTTON, &WelcomePage::OnStart, this);
    endButton->Bind(wxEVT_BUTTON, &WelcomePage::OnEnd, this);

    // Draw the text string
    CreateStatusBar(2); 
    SetStatusText("Credit: Amaury Lorin, Kexin Xu", 1);
}

void WelcomePage::OnPaint(wxPaintEvent& event) 
{
    // Create a device context for drawing
    wxPaintDC dc(this);
    
    // Get the size of the frame
    auto size = GetClientSize();
    
    // Draw the background image
    m_bitmap.Rescale(m_bitmap, size);
    dc.DrawBitmap(m_bitmap, 0, 0, true);
    
    // Calculate the x and y coordinates for the title image
    auto x = (size.GetWidth() - m_titleBitmap.GetWidth()) / 2;
    auto y = (size.GetHeight() - m_titleBitmap.GetHeight()) / 3;
    
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
    gamePage->Show(true);
    Close(true);
    
}

// Event handler for the end button
void WelcomePage::OnEnd(wxCommandEvent& event)
{
    // End the program here
    Close(true);
}
