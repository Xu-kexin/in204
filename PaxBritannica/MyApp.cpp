#include "MyApp.hpp"
#include "pages/WelcomePage.hpp"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    // Create an instance of the welcome page
    auto welcomePage = new WelcomePage();
    welcomePage->Show();
    return true;
}
