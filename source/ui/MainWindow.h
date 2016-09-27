
#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QMainWindow>
#include <QPointer>

class TextArea;
class DocumentWidget;
class DialogReplace;

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
	Q_OBJECT
	friend class DocumentWidget;

public:
	MainWindow (QWidget *parent = 0, Qt::WindowFlags flags = 0);
	virtual ~MainWindow();
	
private:
	void setupMenuGroups();
	void setupMenuStrings();
	void setupTabBar();
	void setupMenuAlternativeMenus();
    void CreateLanguageModeSubMenu();
    void updateLanguageModeSubmenu();

public:
	void UpdateWindowTitle(DocumentWidget *doc);
	DialogReplace *getDialogReplace() const;
	void InvalidateWindowMenus();
	void UpdateWindowReadOnly(DocumentWidget *doc);
	void ShowTabBar(bool state);
	bool GetShowTabBar();
	void SortTabBar();
	int TabCount();
    void CheckCloseDim();
    QList<DocumentWidget *> openDocuments() const;
    int updateLineNumDisp();
    int updateGutterWidth();
    void TempShowISearch(bool state);

public:
    static QList<MainWindow *> allWindows();
    static QList<DocumentWidget *> allDocuments();

public:
	DocumentWidget *CreateDocument(QString name);

public Q_SLOTS:
	// internal variants
    void action_New(const QString &mode = QString());
    void action_Shift_Left_Tabs();
    void action_Shift_Right_Tabs();

public Q_SLOTS:
	void on_action_New_triggered();
	void on_action_New_Window_triggered();
	void on_action_Open_triggered();
	void on_action_About_triggered();
	void on_action_Select_All_triggered();
#if 0

	void on_action_Open_Selected_triggered();
	void on_action_Open_Previous_triggered();
	void on_action_Close_triggered();
	void on_action_Save_triggered();
	void on_action_Save_As_triggered();
	void on_action_Revert_to_Saved_triggered();
	void on_action_Include_File_triggered();
	void on_action_Load_Macro_File_triggered();
	void on_action_Load_Tags_File_triggered();
	void on_action_Unload_Tags_File_triggered();
	void on_action_Load_Calltips_File_triggered();
	void on_action_Unload_Calltips_File_triggered();
	void on_action_Print_triggered();
	void on_action_Print_Selection_triggered();
	void on_action_Exit_triggered();
	void on_action_Undo_triggered();
	void on_action_Redo_triggered();
#endif
	void on_action_Cut_triggered();
	void on_action_Copy_triggered();
	void on_action_Paste_triggered();
	void on_action_Execute_Command_Line_triggered();

#if 0
	void on_action_Paste_Column_triggered();
	void on_action_Delete_triggered();	
	void on_action_Shift_Left_triggered();
	void on_action_Shift_Right_triggered();
	void on_action_Lower_case_triggered();
	void on_action_Upper_case_triggered();
	void on_action_Fill_Paragraph_triggered();
	void on_action_Insert_Form_Feed_triggered();
	void on_action_Insert_Ctrl_Code_triggered();
	void on_action_Find_triggered();
	void on_action_Find_Again_triggered();
	void on_action_Find_Selection_triggered();
	void on_action_Find_Incremental_triggered();
	void on_action_Replace_triggered();
	void on_action_Replace_Find_Again_triggered();
	void on_action_Replace_Again_triggered();
	void on_action_Goto_Line_Number_triggered();
	void on_action_Goto_Selected_triggered();
	void on_action_Mark_triggered();
	void on_action_Goto_Mark_triggered();
	void on_action_Goto_Matching_triggered();
	void on_action_Find_Definition_triggered();
	void on_action_Show_Calltip_triggered();
	void on_action_Execute_Command_triggered();	
	void on_action_Filter_Selection_triggered();
	void on_action_Cancel_Shell_Command_triggered();
	void on_action_Split_Pane_triggered();
	void on_action_Close_Pane_triggered();
	void on_action_Detach_Tab_triggered();
	void on_action_Move_Tab_To_triggered();
	void on_action_About_Qt_triggered();
	void on_action_Indent_triggered();
	void on_action_Unindent_triggered();
	void on_action_Save_Defaults_triggered();
	void on_action_Statistics_Line_triggered();
	void on_action_Incremental_Search_Line_triggered();
	void on_action_Show_Line_Numbers_triggered();
	void on_action_Language_Mode_triggered();
	void on_action_Tab_Stops_triggered();
	void on_action_Text_Fonts_triggered();
	void on_action_Highlight_Syntax_triggered();
	void on_action_Apply_Backlighting_triggered();
	void on_action_Make_Backup_Copy_triggered();
	void on_action_Incremental_Backup_triggered();
	void on_action_Overtype_triggered();
	void on_action_Read_Only_triggered();
	void on_action_Matching_Off_triggered();
	void on_action_Matching_Delimiter_triggered();
	void on_action_Matching_Range_triggered();
	void on_action_Matching_Syntax_triggered();
	void on_action_Wrap_None_triggered();
	void on_action_Wrap_Auto_Newline_triggered();
	void on_action_Wrap_Continuous_triggered();
	void on_action_Wrap_Margin_triggered();
	void on_action_Indent_Off_triggered();
	void on_action_Indent_On_triggered();
	void on_action_Indent_Smart_triggered();
	void on_action_Learn_Keystrokes_triggered();
	void on_action_Finish_Learn_triggered();
	void on_action_Cancel_Learn_triggered();
	void on_action_Replay_Keystrokes_triggered();
	void on_action_Repeat_triggered();
	void on_action_Complete_Word_triggered();	
	void on_action_Find_Again_Backwards_triggered();
	void on_action_Find_Selection_Backwards_triggered();
	void on_action_Highlight_To_Matching_triggered();
	void on_action_Find_Backwards_triggered();
	void on_action_Replace_Backwards_triggered();
	void on_action_Replace_Again_Backwards_triggered();
	void on_action_Replace_Find_Again_Backwards_triggered();
	void on_action_Default_Language_Modes_triggered();
	void on_action_Default_Command_Shell_triggered();
	void on_action_Default_Tab_Stops_triggered();
	void on_action_Default_Text_Fonts_triggered();
	void on_action_Default_Colors_triggered();
	void on_action_Default_Customize_Window_Title_triggered();
	void on_action_Default_Apply_Backlighting_triggered();
	void on_action_Default_Show_Tooltips_triggered();
	void on_action_Default_Statistics_Line_triggered();
	void on_action_Default_Incremental_Search_Line_triggered();
	void on_action_Default_Make_Backup_Copy_triggered();
	void on_action_Default_Incremental_Backup_triggered();
	void on_action_Default_Terminate_with_Line_Break_on_Save_triggered();
	void on_action_Default_Popups_Under_Pointer_triggered();
	void on_action_Default_Auto_Scroll_Near_Window_Top_Bottom_triggered();
	void on_action_Default_Indent_Off_triggered();
	void on_action_Default_Indent_On_triggered();
	void on_action_Default_Indent_Smart_triggered();
	void on_action_Default_Program_Smart_Indent_triggered();
	void on_action_Default_Wrap_None_triggered();
	void on_action_Default_Wrap_Auto_Newline_triggered();
	void on_action_Default_Wrap_Continuous_triggered();
	void on_action_Default_Wrap_Margin_triggered();
	void on_action_Default_Tag_Show_All_triggered();
	void on_action_Default_Tag_Smart_triggered();
	void on_action_Default_Shell_Menu_triggered();
	void on_action_Default_Macro_Menu_triggered();
	void on_action_Default_Window_Background_Menu_triggered();
	void on_action_Default_Sort_Open_Prev_Menu_triggered();
	void on_action_Default_Show_Path_In_Windows_Menu_triggered();
	void on_action_Default_Search_Verbose_triggered();
	void on_action_Default_Search_Wrap_Around_triggered();
	void on_action_Default_Search_Beep_On_Search_Wrap_triggered();
	void on_action_Default_Search_Keep_Dialogs_Up_triggered();
	void on_action_Default_Search_Literal_triggered();
	void on_action_Default_Search_Literal_Case_Sensitive_triggered();
	void on_action_Default_Search_Literal_Whole_Word_triggered();
	void on_action_Default_Search_Literal_Case_Sensitive_Whole_Word_triggered();
	void on_action_Default_Search_Regular_Expression_triggered();
	void on_action_Default_Search_Regular_Expresison_Case_Insensitive_triggered();
	void on_action_Default_Syntax_Off_triggered();
	void on_action_Default_Syntax_On_triggered();
	void on_action_Default_Syntax_Recognition_Patterns_triggered();
	void on_action_Default_Syntax_Text_Drawing_Styles_triggered();
	void on_action_Default_Tab_Open_File_In_New_Tab_triggered();
	void on_action_Default_Tab_Show_Tab_Bar_triggered();
	void on_action_Default_Tab_Hide_Tab_Bar_When_Only_One_Document_is_Open_triggered();
	void on_action_Default_Tab_Next_Prev_Tabs_Across_Windows_triggered();
	void on_action_Default_Tab_Sort_Tabs_Alphabetically_triggered();
	void on_action_Default_Show_Line_Numbers_triggered();
	void on_action_Default_Matching_Off_triggered();
	void on_action_Default_Matching_Delimiter_triggered();
	void on_action_Default_Matching_Range_triggered();
	void on_action_Default_Matching_Syntax_Based_triggered();
	void on_action_Default_Warnings_Files_Modified_Externally_triggered();
	void on_action_Default_Warnings_Check_Modified_File_Contents_triggered();
	void on_action_Default_Warnings_On_Exit_triggered();
	void on_action_Default_Size_24_x_24_triggered();
	void on_action_Default_Size_40_x_80_triggered();
	void on_action_Default_Size_60_x_80_triggered();
	void on_action_Default_Size_80_x_80_triggered();
	void on_action_Default_Size_Custom_triggered();
#endif

private Q_SLOTS:
	void deleteTabButtonClicked();
    void raiseCB();
    void setLangModeCB();

private:
	QPointer<QDialog>  dialogFind_;
	QPointer<QDialog>  dialogReplace_;
	QPointer<TextArea> lastFocus_;
	bool               showLineNumbers_; // is the line number display shown
	bool               showStats_;       // is stats line supposed to be shown
	bool               showISearchLine_; // is incr. search line to be shown
    bool               modeMessageDisplayed_;

public:
	Ui::MainWindow ui;
};

#endif
