#ifndef MyApp_hpp
#define MyApp_hpp

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

#endif
