#include "MainFrame.h"
#include"Node.h"
#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/gbsizer.h>
#include <wx/event.h>
#include <sstream>
#include "LinkedList.h"


wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)

EVT_GRID_CELL_LEFT_CLICK(MainFrame::OnCellLeftClick)

EVT_MENU(ID_InsertAfter, MainFrame::OnInsertCellAfter)
EVT_MENU(ID_InsertBefore, MainFrame::OnInsertCellBefore)
EVT_MENU(ID_InsertAboveGrid, MainFrame::OnInsertCellAbove)
EVT_MENU(ID_InsertBelowGrid, MainFrame::OnInsertCellBelow)


EVT_MENU(ID_InsertRowAbove, MainFrame::OnInsertRowAbove)
EVT_MENU(ID_InsertRowBelow, MainFrame::OnInsertRowBelow)

EVT_MENU(ID_InsertColumnRight, MainFrame::OnInsertColumnRight)
EVT_MENU(ID_InsertColumnLeft, MainFrame::OnInsertColumnLeft)
EVT_MENU(ID_InsertColumnLeft, MainFrame::OnInsertValue)

EVT_MENU(ID_DeleteCellOfRow, MainFrame::OnDeleteCellOfRow)
EVT_MENU(ID_DeleteCellOfColumn, MainFrame::OnDeleteCellOfColumn)
EVT_MENU(ID_DeleteRow, MainFrame::OnDeleteRow)
EVT_MENU(ID_DeleteColumn, MainFrame::OnDeleteColumn)
EVT_MENU(ID_ClearRow, MainFrame::OnClearRow)
EVT_MENU(ID_ClearColumn, MainFrame::OnClearColumn)

EVT_MENU(ID_FormulaSUM, MainFrame::OnFormulaSUM)
EVT_MENU(ID_FormulaMIN, MainFrame::OnFormulaMIN)
EVT_MENU(ID_FormulaMAX, MainFrame::OnFormulaMAX)
EVT_MENU(ID_FormulaCOUNT, MainFrame::OnFormulaCOUNT)
EVT_MENU(ID_FormulaAVERAGE, MainFrame::OnFormulaAVERAGE)

EVT_MENU(ID_CopyRow, MainFrame::OnCopyRow)
EVT_MENU(ID_CopyColumn, MainFrame::OnCopyColumn)
EVT_MENU(ID_CutRow, MainFrame::OnCutRow)
EVT_MENU(ID_CutColumn, MainFrame::OnCutColumn)
EVT_MENU(ID_PasteRow, MainFrame::OnPasteRow)
EVT_MENU(ID_PasteColumn, MainFrame::OnPasteColumn)

EVT_MENU(ID_HelpItem, MainFrame::OnHelp)

wxEND_EVENT_TABLE()

void GetAddressFromUser(string& start, string& end, string& destination);
Node* CreateInitiallyLinkedList();
string cellPosition;
LinkedList Excel;
vector<string> copied;


MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), grid(new wxGrid(this, wxID_ANY))
{
    CreateInitiallyLinkedList();
    //Excel.LoadFromFile("excel.txt");
    

   

    PrintValues();
   
    // Create the menu bar
    wxMenuBar* menuBar = new wxMenuBar;

    // Create the File menu
    wxMenu* fileMenu = new wxMenu;
    fileMenu->Append(wxID_SAVE, "Save");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, "Exit");
    menuBar->Append(fileMenu, "File");

    // Create the Home menu
    wxMenu* homeMenu = new wxMenu;
    wxMenu* copySubMenu = new wxMenu;
    copySubMenu->Append(101, "Row");
    copySubMenu->Append(102, "Column");
    homeMenu->AppendSubMenu(copySubMenu, "Copy");
    wxMenu* cutSubMenu = new wxMenu;
    cutSubMenu->Append(103, "Row");
    cutSubMenu->Append(104, "Column");
    homeMenu->AppendSubMenu(cutSubMenu, "Cut");
    wxMenu* pasteSubMenu = new wxMenu;
    pasteSubMenu->Append(105, "Row");
    pasteSubMenu->Append(106, "Column");
    homeMenu->AppendSubMenu(pasteSubMenu, "Paste");
    menuBar->Append(homeMenu, "Home");

    // Create the Insert menu
    wxMenu* insertMenu = new wxMenu;
    wxMenu* insertCellSubMenu = new wxMenu;
    insertCellSubMenu->Append(201, "After");
    insertCellSubMenu->Append(202, "Before");
    insertCellSubMenu->Append(203, "Above");
    insertCellSubMenu->Append(204, "Below");
    insertMenu->AppendSubMenu(insertCellSubMenu, "Cell");
    wxMenu* insertRowSubMenu = new wxMenu;
    insertRowSubMenu->Append(205, "Above");
    insertRowSubMenu->Append(206, "Below");
    insertMenu->AppendSubMenu(insertRowSubMenu, "Row");
    wxMenu* insertColumnSubMenu = new wxMenu;
    insertColumnSubMenu->Append(207, "Right");
    insertColumnSubMenu->Append(208, "Left");
    insertMenu->AppendSubMenu(insertColumnSubMenu, "Column");
    insertMenu->Append(209, "Value");
    menuBar->Append(insertMenu, "Insert");

    // Create the Formulas menu
    wxMenu* formulasMenu = new wxMenu;
    formulasMenu->Append(301, "SUM");
    formulasMenu->Append(302, "MIN");
    formulasMenu->Append(303, "MAX");
    formulasMenu->Append(304, "COUNT");
    formulasMenu->Append(305, "AVERAGE");
    menuBar->Append(formulasMenu, "Formulas");

    // Create the Deletion menu
    wxMenu* deletionMenu = new wxMenu;
    wxMenu* deletionSubMenu = new wxMenu;
    wxMenu* cellSubMenu = new wxMenu;
    cellSubMenu->Append(401, "Of Row");
    cellSubMenu->Append(402, "Of Column");
    deletionMenu->AppendSubMenu(cellSubMenu, "Cell");
    deletionSubMenu->Append(403, "Row");
    deletionSubMenu->Append(404, "Column");
    deletionMenu->AppendSubMenu(deletionSubMenu, "Delete");
    wxMenu* clearSubMenu = new wxMenu;
    clearSubMenu->Append(405, "Row");
    clearSubMenu->Append(406, "Column");
    deletionMenu->AppendSubMenu(clearSubMenu, "Clear");
    menuBar->Append(deletionMenu, "Deletion");

    wxMenu* helpMenu = new wxMenu;
    helpMenu->Append(ID_HelpItem, "Help");
    menuBar->Append(helpMenu, "Help");
    // Set the menu bar
    SetMenuBar(menuBar);

    Bind(wxEVT_SIZE, &MainFrame::OnSize, this);
    Bind(wxEVT_GRID_CELL_LEFT_CLICK, &MainFrame::OnCellLeftClick, this, ID_GRID);

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnFileSave, this, wxID_SAVE);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnFileExit, this, wxID_EXIT);

    //Bind(wxEVT_MENU, &MainFrame::OnInsertCellAfter, this, ID_InsertAfter);
    //Bind(wxEVT_MENU, &MainFrame::OnInsertCellBefore, this, ID_InsertBefore);
    //Bind(wxEVT_MENU, &MainFrame::OnInsertCellAbove, this, ID_InsertAboveGrid);
    //Bind(wxEVT_MENU, &MainFrame::OnInsertCellBelow, this, ID_InsertBelowGrid);

    Bind(wxEVT_MENU, &MainFrame::OnInsertCellAfter, this, 201);
    Bind(wxEVT_MENU, &MainFrame::OnInsertCellBefore, this, 202);
    Bind(wxEVT_MENU, &MainFrame::OnInsertCellAbove, this, 203);
    Bind(wxEVT_MENU, &MainFrame::OnInsertCellBelow, this, 204);


    Bind(wxEVT_MENU, &MainFrame::OnInsertRowAbove, this, ID_InsertRowAbove);
    Bind(wxEVT_MENU, &MainFrame::OnInsertRowBelow, this, ID_InsertRowBelow);
    Bind(wxEVT_MENU, &MainFrame::OnInsertColumnRight, this, ID_InsertColumnRight);
    Bind(wxEVT_MENU, &MainFrame::OnInsertColumnLeft, this, ID_InsertColumnLeft);
    Bind(wxEVT_MENU, &MainFrame::OnInsertValue, this, ID_InsertValue);

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnFormulaSUM, this, ID_FormulaSUM);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnFormulaMIN, this, ID_FormulaMIN);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnFormulaMAX, this, ID_FormulaMAX);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnFormulaCOUNT, this, ID_FormulaCOUNT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnFormulaAVERAGE, this, ID_FormulaAVERAGE);

    Bind(wxEVT_MENU, &MainFrame::OnCopyRow, this, ID_CopyRow);
    Bind(wxEVT_MENU, &MainFrame::OnCopyColumn, this, ID_CopyColumn);
    Bind(wxEVT_MENU, &MainFrame::OnCutRow, this, ID_CutRow);
    Bind(wxEVT_MENU, &MainFrame::OnCutColumn, this, ID_CutColumn);
    Bind(wxEVT_MENU, &MainFrame::OnPasteRow, this, ID_PasteRow);
    Bind(wxEVT_MENU, &MainFrame::OnPasteColumn, this, ID_PasteColumn);
    Bind(wxEVT_MENU, &MainFrame::OnHelp, this, ID_HelpItem);

}

// Event handling methods in MainFrame class
void MainFrame::OnInsertCellAfter(wxCommandEvent& event) {
    wxString value;
    string Svalue;
    value = wxGetTextFromUser("Enter Value:", "Input", "", NULL);
    Svalue = value.ToStdString();
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.InsertAfter(current, Svalue);
    UpdateGrid();

}
void MainFrame::OnInsertCellBefore(wxCommandEvent& event) {
    wxString value;
    string Svalue;
    value = wxGetTextFromUser("Enter Value:", "Input", "", NULL);
    Svalue = value.ToStdString();
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.InsertBefore(current, Svalue);
    UpdateGrid();
}

void MainFrame::OnInsertCellAbove(wxCommandEvent& event) {
    wxString value;
    string Svalue;
    value = wxGetTextFromUser("Enter Value:", "Input", "", NULL);
    Svalue = value.ToStdString();
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.InsertAbove(current, Svalue);
    UpdateGrid();
}

void MainFrame::OnInsertCellBelow(wxCommandEvent& event) {
    wxString value;
    string Svalue;
    value = wxGetTextFromUser("Enter Value:", "Input", "", NULL);
    Svalue = value.ToStdString();
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.InsertBelow(current, Svalue);
    UpdateGrid();
}

void MainFrame::OnInsertRowAbove(wxCommandEvent& event)
{
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.InsertRowAbove(current);
    UpdateGrid();
}

void MainFrame::OnInsertRowBelow(wxCommandEvent& event)
{
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.InsertRowBelow(current);
    UpdateGrid();
}

void MainFrame::OnInsertColumnRight(wxCommandEvent& event)
{
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.InsertColumnAfter(current);
    UpdateGrid();
}

void MainFrame::OnInsertColumnLeft(wxCommandEvent& event)
{
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.InsertColumnBefore(current);
    UpdateGrid();
}

void MainFrame::OnInsertValue(wxCommandEvent& event)
{
    wxString value;
    string Svalue;
    value = wxGetTextFromUser("Enter Value:", "Input", "", NULL);
    Svalue = value.ToStdString();
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.SetValue(current,Svalue);
    UpdateGrid();
}

void MainFrame::OnDeleteCellOfRow(wxCommandEvent& event)
{
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.DeleteCellOfRow(current);
    UpdateGrid();
}

void MainFrame::OnDeleteCellOfColumn(wxCommandEvent& event)
{
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.DeleteCellOfColumn(current);
    UpdateGrid();
}

void MainFrame::OnDeleteRow(wxCommandEvent& event)
{
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.DeleteRow(current);
    UpdateGrid();
}

void MainFrame::OnDeleteColumn(wxCommandEvent& event)
{
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.DeleteColumn(current);
    UpdateGrid();
}

void MainFrame::OnClearRow(wxCommandEvent& event)
{
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.ClearRow(current);
    UpdateGrid();
}

void MainFrame::OnClearColumn(wxCommandEvent& event)
{
    Node* current = Excel.GetNodeByPosition(cellPosition);
    Excel.ClearColumn(current);
    UpdateGrid();
}

void MainFrame::OnFormulaSUM(wxCommandEvent& event)
{   
    string start , end, destination;
    GetAddressFromUser(start, end, destination);
    string ans = Excel.Sum(start, end);
    Node* forAns = Excel.GetNodeByPosition(destination);
    Excel.SetValue(forAns, ans);
    UpdateGrid();
}

void MainFrame::OnFormulaMIN(wxCommandEvent& event)
{
    string start, end, destination;
    GetAddressFromUser(start, end, destination);
    string ans = Excel.Min(start, end);
    Node* forAns = Excel.GetNodeByPosition(destination);
    Excel.SetValue(forAns, ans);
    UpdateGrid();
}

void MainFrame::OnFormulaMAX(wxCommandEvent& event)
{
    string start, end, destination;
    GetAddressFromUser(start, end, destination);
    string ans = Excel.Max(start, end);
    Node* forAns = Excel.GetNodeByPosition(destination);
    Excel.SetValue(forAns, ans);
    UpdateGrid();
}

void MainFrame::OnFormulaCOUNT(wxCommandEvent& event)
{
    string start, end, destination;
    GetAddressFromUser(start, end, destination);
    string ans = Excel.Count(start, end);
    Node* forAns = Excel.GetNodeByPosition(destination);
    Excel.SetValue(forAns, ans);
    UpdateGrid();
}

void MainFrame::OnFormulaAVERAGE(wxCommandEvent& event)
{
    string start, end, destination;
    GetAddressFromUser(start, end, destination);
    string ans = Excel.Average(start, end);
    Node* forAns = Excel.GetNodeByPosition(destination);
    Excel.SetValue(forAns, ans);
    UpdateGrid();
}

void MainFrame::OnCopyRow(wxCommandEvent& WXUNUSED(event)) {
   
    copied = Excel.CopyRow(cellPosition);
}

void MainFrame::OnCopyColumn(wxCommandEvent& WXUNUSED(event)) {

    copied = Excel.CopyColumn(cellPosition);
}

void MainFrame::OnCutRow(wxCommandEvent& WXUNUSED(event)) {

    copied = Excel.CutRow(cellPosition);
    UpdateGrid();
}

void MainFrame::OnCutColumn(wxCommandEvent& WXUNUSED(event)) {

    copied = Excel.CutColumn(cellPosition);
    UpdateGrid();
}

void MainFrame::OnPasteRow(wxCommandEvent& WXUNUSED(event)) {
    
    Excel.PasteRow(cellPosition, copied);
    UpdateGrid();
}
void MainFrame::OnPasteColumn(wxCommandEvent& WXUNUSED(event)) {

    Excel.PasteColumn(cellPosition, copied);
    UpdateGrid();
}

void MainFrame::OnFileSave(wxCommandEvent& event)
{
    //Excel.StoreToFile("excel.txt");
}
void MainFrame::OnFileExit(wxCommandEvent& event)
{
    Close(true);
}

void MainFrame::OnHelp(wxCommandEvent& event)
{
    wxMessageBox("Before every function/task implementation you have to select cell every time.The cel will be selected with left click of mouse.\n Every thing should be done by mouse and there is no funtion which is imolemented by keyboard. ", "Help Menu", wxOK | wxICON_INFORMATION, this);
}


void MainFrame::CustomizeGrid() {
    // Set row labels (1, 2, 3, ...)
    for (int row = 0; row < grid->GetNumberRows(); ++row) {
        grid->SetRowLabelValue(row, wxString::Format("%d", row + 1));
    }

    // Set column labels (A, B, C, ...)
    for (int col = 0; col < grid->GetNumberCols(); ++col) {
        grid->SetColLabelValue(col, wxString::Format("%d", col + 1));
        grid->SetColSize(col, 80);  // Set the width of each column
    }

    // Set the height of each row
    for (int row = 0; row < grid->GetNumberRows(); ++row) {
        grid->SetRowSize(row, 30);  // Set the height of each row
    }
    // Enable row and column labels
    grid->SetRowLabelSize(wxGRID_AUTOSIZE);
    grid->SetColLabelSize(wxGRID_AUTOSIZE);
}

void MainFrame::OnCellLeftClick(wxGridEvent& event) {
    string previousPosition;
    previousPosition = cellPosition;
    size_t cPos = previousPosition.find('C');
    size_t rPos = previousPosition.find('R');

    // Extract column and row substrings
    string colStr = previousPosition.substr(cPos + 1, rPos - cPos - 1);
    string rowStr = previousPosition.substr(rPos + 1);

    // Convert strings to integers
    int Pcol, Prow;
    istringstream(colStr) >> Pcol;
    istringstream(rowStr) >> Prow;
    Pcol--;
    Prow--;

    int row = event.GetRow();
    int col = event.GetCol();

    wxString position = wxString::Format("C%dR%d", col + 1, row + 1);
    cellPosition = position.ToStdString();
    if (grid) {
        // Set the background color of the clicked cell to baby pink
        grid->SetCellBackgroundColour(Prow, Pcol, wxColour(255, 255, 255));
        grid->SetCellBackgroundColour(row, col, wxColour(255, 182, 193));  // RGB for baby pink
        grid->Refresh();  // Refresh the grid to apply the color change
    }


    
}

void MainFrame::UpdateGrid()
{
    grid->ClearGrid();
    PrintValues();
    grid->Refresh();
}

void MainFrame::PrintValues()
{
    
    // Assuming you have these member variables in your class
    panel = nullptr;
    currentSizer = nullptr; 
    newSizer = nullptr;      
    grid = nullptr;

    // Set up your grid and other initialization code here
    grid = new wxGrid(this, ID_GRID);  // Use the frame as the parent, and assign an ID
    grid->CreateGrid(20, 16);
    grid->AutoSizeColumns();
    grid->AutoSizeRows();

    // Set the height of each row
    for (int row = 0; row < grid->GetNumberRows(); ++row) {
        grid->SetRowSize(row, 30);  // Set the height of each row
    }

    // Set the width of each column
    for (int col = 0; col < grid->GetNumberCols(); ++col) {
        grid->SetColSize(col, 80);  // Set the width of each column
    }

    Node* temp = Excel.TopLeft;
    int row = 0;
    while (temp != nullptr)
    {
        Node* rowStart = temp;
        int col = 0;
        while (temp != nullptr)
        {
            grid->SetCellValue(row, col, wxString::FromUTF8(temp->data.c_str()));
            temp = temp->next;
            col++;
        }
        temp = rowStart->bottom;
        row++;
    }
    grid->GetCellValue(0, 0);
    for (int row = 0; row < grid->GetNumberRows(); ++row)
    {
        for (int col = 0; col < grid->GetNumberCols(); ++col)
        {
            wxString value = grid->GetCellValue(row, col);
            wxPrintf(value);
        }
    }


    // Customize the grid
    CustomizeGrid();

    // Set up the layout with wxGridSizer
    wxGridSizer* sizer = new wxGridSizer(0, 0, 0, 0);
    sizer->Add(grid, 1, wxEXPAND | wxALL, 0);

    if (!panel)
    {
        panel = new wxPanel(this, wxID_ANY);
    }

    if (panel->GetContainingSizer()) {
        wxSizer* currentContainingSizer = panel->GetContainingSizer();
        currentContainingSizer->Detach(panel);
    }

    panel->SetSizerAndFit(sizer);

    // Add the panel to the current sizer
    if (!currentSizer) {
        currentSizer = new wxBoxSizer(wxHORIZONTAL);  
    }
    currentSizer->Add(panel, 1, wxEXPAND);

    panel->SetSizerAndFit(newSizer);

    wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
    frameSizer->Add(currentSizer, 1, wxEXPAND);
    SetSizerAndFit(frameSizer);

    // Show the frame
    Show(true);

}

void GetAddressFromUser(string& start, string& end, string& destination)
{
    wxString starting, ending, final;

    starting = wxGetTextFromUser("Location Of Starting Cell:", "Input", "", NULL);
    ending = wxGetTextFromUser("Location Of Ending Cell:", "Input", "", NULL);
    final = wxGetTextFromUser("Location for Answer:", "Input", "", NULL);
    start = starting.ToStdString();
    end = ending.ToStdString();
    destination = final.ToStdString();

}
Node* CreateInitiallyLinkedList()
{
    Excel.InsertAfter(Excel.TopLeft, "1");
    Excel.InsertAfter(Excel.TopLeft, "2");
    Excel.InsertAfter(Excel.TopLeft, "3");
    Excel.InsertAfter(Excel.TopLeft, "4");
    Excel.InsertAfter(Excel.TopLeft, "5");
    Excel.InsertBelow(Excel.TopLeft, "6");
    Excel.InsertBelow(Excel.TopLeft, "7");
    Excel.InsertBelow(Excel.TopLeft, "8");
    return Excel.TopLeft;
}
