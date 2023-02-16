//
//  Myapp.cpp
//  PaxBritannica
//
//  Created by Laurine Xu on 2022/12/14.
//

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
