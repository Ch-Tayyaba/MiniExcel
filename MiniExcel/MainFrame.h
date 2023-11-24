#pragma once
#include <wx/wx.h>
#include <wx/grid.h>
#include"Node.h"
#include <wx/sizer.h>
#include <wx/event.h>

enum ID
{
   

    ID_DeleteCellOfRow = 401,
    ID_DeleteCellOfColumn,
    ID_DeleteRow,
    ID_DeleteColumn,
    ID_ClearRow,
    ID_ClearColumn,

    ID_FormulaSUM = 301,
    ID_FormulaMIN,
    ID_FormulaMAX,
    ID_FormulaCOUNT,
    ID_FormulaAVERAGE,

    ID_InsertRowAbove = 205,
    ID_InsertRowBelow,
    ID_InsertColumnRight,
    ID_InsertColumnLeft,
    ID_InsertValue,

    ID_CopyRow = 101,
    ID_CopyColumn,
    ID_CutRow,
    ID_CutColumn,
    ID_PasteRow,
    ID_PasteColumn,

    ID_GRID,
    ID_InsertAfter,
    ID_InsertBefore,
    ID_InsertAboveGrid,
    ID_InsertBelowGrid,
    ID_HelpItem
};

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);


private:
    wxGrid* grid;
    wxPanel* panel;
    wxSizer* currentSizer;
    wxSizer* newSizer;
    string prevCellPosition;

    void OnCellLeftClick(wxGridEvent& event);

    void OnInsertCellAfter(wxCommandEvent& event);
    void OnInsertCellBefore(wxCommandEvent& event);
    void OnInsertCellAbove(wxCommandEvent& event);
    void OnInsertCellBelow(wxCommandEvent& event);

    void OnInsertRowAbove(wxCommandEvent& event);
    void OnInsertRowBelow(wxCommandEvent& event);
    void OnInsertColumnRight(wxCommandEvent& event);
    void OnInsertColumnLeft(wxCommandEvent& event);
    void OnInsertValue(wxCommandEvent& event);

    void OnDeleteCellOfRow(wxCommandEvent& event);
    void OnDeleteCellOfColumn(wxCommandEvent& event);
    void OnDeleteRow(wxCommandEvent& event);
    void OnDeleteColumn(wxCommandEvent& event);
    void OnClearRow(wxCommandEvent& event);
    void OnClearColumn(wxCommandEvent& event);

    void OnFormulaSUM(wxCommandEvent& event);
    void OnFormulaMIN(wxCommandEvent& event);
    void OnFormulaMAX(wxCommandEvent& event);
    void OnFormulaCOUNT(wxCommandEvent& event);
    void OnFormulaAVERAGE(wxCommandEvent& event);

    void OnCopyRow(wxCommandEvent& WXUNUSED(event));
    void OnCopyColumn(wxCommandEvent& WXUNUSED(event));
    void OnCutRow(wxCommandEvent& WXUNUSED(event));
    void OnCutColumn(wxCommandEvent& WXUNUSED(event));
    void OnPasteRow(wxCommandEvent& WXUNUSED(event));
    void OnPasteColumn(wxCommandEvent& WXUNUSED(event));

    void OnFileSave(wxCommandEvent& event);
    void OnFileExit(wxCommandEvent& event);
   
    void OnHelp(wxCommandEvent& event);

    void CustomizeGrid();
    void UpdateGrid();
    void PrintValues();
    

    wxDECLARE_EVENT_TABLE();
};