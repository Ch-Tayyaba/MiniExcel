#include "App.h"
#include "MainFrame.h"
#include "Node.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    MainFrame* mainFrame = new MainFrame("MiniExcel", wxPoint(50, 50), wxSize(800, 600));
    mainFrame->Center();
    mainFrame->Show();

    return true;
}
