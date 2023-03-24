//
//  GamePage.cpp
//  PaxBritannica
//
//  Created by Laurine Xu on 2022/12/08.
//
#include "WelcomePage.hpp"
#include "GamePage.hpp"

#define TIMER_ID 1000
const char* g_backgoundFiles="res/background.png";

#define W(s)    s.GetWidth()
#define H(s)    s.GetHeight()

#define FONT_SIZE     20
#define FONT_HEIGHT   FONT_SIZE*1.2

#define BUTTON_PADDING  10

GamePage::GamePage(bool multi) : wxFrame(nullptr, wxID_ANY, "Pax Britannica"), env(wxSize(W(windowSize), H(windowSize)*4/5-FONT_HEIGHT-BUTTON_PADDING), wxPoint(0, H(windowSize)/20+FONT_HEIGHT)), m_timer(this, TIMER_ID), multiplayer(multi)
{
    // Set the size and position of the frame
    SetSize(windowSize);
    Centre();
    
    wxLogNull AD;
    wxInitAllImageHandlers();
    // Load the background image
    m_bitmap.LoadFile(g_backgoundFiles, wxBITMAP_TYPE_ANY);
    wxBitmap::Rescale(m_bitmap, windowSize);
   
    // Bind the OnPaint method to the EVT_PAINT event
    Bind(wxEVT_PAINT, &GamePage::OnPaint, this);
    
    wxPanel* panel = new wxPanel(this);
    panel->Bind(wxEVT_KEY_DOWN, &GamePage::OnKeyDown, this);
    panel->Bind(wxEVT_KEY_UP, &GamePage::OnKeyUp, this);
    
    // Pose the return and replay buttons
    auto exitButton = new wxButton(this, wxID_ANY, "Exit");
    auto replayButton = new wxButton(this, wxID_ANY, "Replay");
    // Bind the buttons to event handlers
    exitButton->Bind(wxEVT_BUTTON, &GamePage::OnExit, this);
    replayButton->Bind(wxEVT_BUTTON, &GamePage::OnReplay, this);
    exitButton->SetPosition(wxPoint(W(windowSize)*4/6, H(windowSize)*17/20));
    replayButton->SetPosition(wxPoint(W(windowSize)/6, H(windowSize)*17/20));
    
    wxFont font(FONT_SIZE, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxPoint p(0, H(windowSize)/40);
    score_text1 = new wxStaticText(this, wxID_ANY, "", p, wxSize(W(windowSize)/2, FONT_HEIGHT), wxALIGN_CENTRE);
    score_text1->SetFont(font);
    score_text1->SetForegroundColour(RED);
    if (multiplayer){
        wxPoint p2(W(windowSize)/2, H(windowSize)/40);
        score_text2 = new wxStaticText(this, wxID_ANY, "", p2, wxSize(W(windowSize)/2, FONT_HEIGHT), wxALIGN_CENTRE);
        score_text2->SetFont(font);
        score_text2->SetForegroundColour(BLUE);
    }
    
    // Draw the text string
    CreateStatusBar(2);
    SetStatusText("Credit: Kexin Xu, Amaury Lorin", 1);
    
    env.AddPlayer();
    if (multiplayer){
        // Add the second player
        env.AddPlayer();
    }
    
    // Set a timer for updating every 1s
    Bind(wxEVT_TIMER, &GamePage::OnTimer, this);
    m_timer.Start(100);
}

void GamePage::OnPaint(wxPaintEvent& event)
{
    // Create a device context for drawing
    wxPaintDC dc(this);
    
    // prevent window size from changing
    SetSize(windowSize);
    
    // Draw the background image
    dc.DrawBitmap(m_bitmap, 0, 0);
    
    wxPen p(wxColour(255, 255, 255));
    dc.SetPen(p);
    dc.DrawLine(0, H(windowSize)/20+FONT_HEIGHT, W(windowSize), H(windowSize)/20+FONT_HEIGHT);
    dc.DrawLine(W(windowSize)/2, 0, W(windowSize)/2, H(windowSize)/20+FONT_HEIGHT);
    
    // Show the health and score value
    if (env.IsPlayerAlive(1))
        score1 = env.GetScore(1);
    score_text1->SetLabel(wxString::Format("Player1: Score: %08d  Health: %d", score1, env.GetHp(1)));
    if (multiplayer) {
        if (env.IsPlayerAlive(2))
            score2 = env.GetScore(2);
        score_text2->SetLabel(wxString::Format("Player2: Score: %08d  Health: %d", score2, env.GetHp(2)));
    }
    
    env.Draw(dc);
}

void GamePage::OnReplay(wxCommandEvent& event)
{
    m_timer.Stop();
    auto NewGame = new GamePage(multiplayer);
    Close(true);
    NewGame->Show();
}

void GamePage::OnExit(wxCommandEvent& event)
{
    exit(0);
}

void GamePage::OnTimer(wxTimerEvent &event) {
    if (key_pressed1 & 1) {
        auto now = std::chrono::steady_clock::now();
        if ((now - last_shoot1).count() > 500 * 1000000) {   // ns
            env.Shoot(1);
            last_shoot1 = now;
        }
    }
    if (key_pressed2 & 1) {
        auto now = std::chrono::steady_clock::now();
        if ((now - last_shoot2).count() > 500 * 1000000) {   // ns
            env.Shoot(2);
            last_shoot2 = now;
        }
    }
    if (key_pressed1 & UP) {
        env.MovePlayer(1, UP);
    }
    if (key_pressed1 & DOWN) {
        env.MovePlayer(1, DOWN);
    }
    if (key_pressed1 & LEFT) {
        env.MovePlayer(1, LEFT);
    }
    if (key_pressed1 & RIGHT) {
        env.MovePlayer(1, RIGHT);
    }
    if (key_pressed2 & UP) {
        env.MovePlayer(2, UP);
    }
    if (key_pressed2 & DOWN) {
        env.MovePlayer(2, DOWN);
    }
    if (key_pressed2 & LEFT) {
        env.MovePlayer(2, LEFT);
    }
    if (key_pressed2 & RIGHT) {
        env.MovePlayer(2, RIGHT);
    }
    int r = rand()%100;
    if (r < 10)
        env.AddBot(r >= 8);
    if (!env.Step()) {
        wxFont font(40, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
        wxStaticText* gameover = new wxStaticText(this, wxID_ANY, "Game over!");
        gameover->SetFont(font);
        gameover->SetForegroundColour(wxColour(255, 255, 255));
        wxSize s = (windowSize - gameover->GetSize())/2;
        gameover->SetPosition(wxPoint(W(s), H(s)));
        m_timer.Stop();
    }
    Refresh();
}

void GamePage::OnKeyDown(wxKeyEvent &event) {
    switch (event.GetKeyCode()) {
        //TODO: -> french kbd
        case 'W':
            key_pressed1 |=UP;
            break;
        case 'S':
            key_pressed1 |=DOWN;
            break;
        case 'A':
            key_pressed1 |=LEFT;
            break;
        case 'D':
            key_pressed1 |=RIGHT;
            break;
        case ' ':
            key_pressed1 |=1;
            break;
        case 315:
            key_pressed2 |=UP;
            break;
        case 317:
            key_pressed2 |=DOWN;
            break;
        case 314:
            key_pressed2 |=LEFT;
            break;
        case 316:
            key_pressed2 |=RIGHT;
            break;
        case 13:
            key_pressed2 |=1;
            break;
        default:
            break;
    }
}

void GamePage::OnKeyUp(wxKeyEvent &event) {
    switch (event.GetKeyCode()) {
        //TODO: -> french kbd
        case 'W':
            key_pressed1 &=~UP;
            break;
        case 'S':
            key_pressed1 &=~DOWN;
            break;
        case 'A':
            key_pressed1 &=~LEFT;
            break;
        case 'D':
            key_pressed1 &=~RIGHT;
            break;
        case ' ':
            key_pressed1 &=~1;
            break;
        case 315:
            key_pressed2 &=~UP;
            break;
        case 317:
            key_pressed2 &=~DOWN;
            break;
        case 314:
            key_pressed2 &=~LEFT;
            break;
        case 316:
            key_pressed2 &=~RIGHT;
            break;
        case 13:
            key_pressed2 &=~1;
            break;
        default:
            break;
    }
}
