cmake_minimum_required(VERSION 3.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTORCC ON)

find_package(Qt5 5.4.0 REQUIRED Widgets Network Xml PrintSupport)
find_package(Boost 1.35 REQUIRED)
find_package(Qt5LinguistTools)

set(TRANSLATIONS
    res/translations/nedit-ng_fr.ts
)

qt5_add_translation(QM_FILES ${TRANSLATIONS})
set(QM_FILES ${QM_FILES} PARENT_SCOPE)
add_custom_target (translations ALL DEPENDS ${QM_FILES})

# Create translations QRC file - ts.qrc
set(TRANSLATIONS_QRC "${CMAKE_CURRENT_BINARY_DIR}/translations.qrc")

file(WRITE ${TRANSLATIONS_QRC} "<RCC>\n\t<qresource prefix=\"/translations\">")
foreach(QM_FILE ${QM_FILES})
	get_filename_component(QM_FILE_NAME ${QM_FILE} NAME)
	file(APPEND ${TRANSLATIONS_QRC} "\n\t\t<file>${QM_FILE_NAME}</file>")
endforeach()

file(APPEND ${TRANSLATIONS_QRC} "\n\t</qresource>\n</RCC>")
list(APPEND QRC_FILES ${TRANSLATIONS_QRC})


qt5_add_resources(QRC_SOURCES
	nedit.qrc
	${TRANSLATIONS_QRC}
)

qt5_wrap_cpp(MOC_SOURCES
	CallTipWidget.h
	CommandRecorder.h
	Dialog.h
	DialogAbout.h
	DialogColors.h
	DialogDrawingStyles.h
	DialogDuplicateTags.h
	DialogExecuteCommand.h
	DialogFilter.h
	DialogFind.h
	DialogFonts.h
	DialogLanguageModes.h
	DialogMacros.h
	DialogMoveDocument.h
	DialogMultiReplace.h
	DialogOutput.h
	DialogPrint.h
	DialogPrompt.h
	DialogPromptList.h
	DialogPromptString.h
	DialogRepeat.h
	DialogReplace.h
	DialogShellMenu.h
	DialogSmartIndent.h
	DialogSmartIndentCommon.h
	DialogSyntaxPatterns.h
	DialogTabs.h
	DialogWindowBackgroundMenu.h
	DialogWindowSize.h
	DialogWindowTitle.h
	DialogWrapMargin.h
	DocumentModel.h
	DocumentWidget.h
	ElidedLabel.h
	FixedFontSelector.h
	HighlightPatternModel.h
	HighlightStyleModel.h
	KeySequenceEdit.h
	LanguageModeModel.h
	MainWindow.h
	MenuItemModel.h
	NeditServer.h
	TabWidget.h
	TextArea.h
)

qt5_wrap_ui(UIC_SOURCES
	FixedFontSelector.ui
	CallTipWidget.ui
	DialogAbout.ui
	DialogColors.ui
	DialogDrawingStyles.ui
	DialogDuplicateTags.ui
	DialogExecuteCommand.ui
	DialogFilter.ui
	DialogFind.ui
	DialogFonts.ui
	DialogLanguageModes.ui
	DialogMacros.ui
	DialogMoveDocument.ui
	DialogMultiReplace.ui
	DialogOutput.ui
	DialogPrint.ui
	DialogPromptList.ui
	DialogPromptString.ui
	DialogPrompt.ui
	DialogRepeat.ui
	DialogReplace.ui
	DialogShellMenu.ui
	DialogSmartIndentCommon.ui
	DialogSmartIndent.ui
	DialogSyntaxPatterns.ui
	DialogTabs.ui
	DialogWindowBackgroundMenu.ui
	DialogWindowSize.ui
	DialogWindowTitle.ui
	DialogWrapMargin.ui
	DocumentWidget.ui
	MainWindow.ui
)

add_executable(nedit-ng

	${MOC_SOURCES}
	${QRC_SOURCES}
	${UIC_SOURCES}

	BlockDragTypes.h
	Bookmark.h
	CallTip.h
	CallTipWidget.cpp
	CallTipWidget.h
	CloseMode.h
	CommandRecorder.cpp
	CommandRecorder.h
	CommandSource.h
	CursorStyles.h
	Dialog.cpp
	Dialog.h
	DialogAbout.cpp
	DialogAbout.h
	DialogColors.cpp
	DialogColors.h
	DialogDrawingStyles.cpp
	DialogDrawingStyles.h
	DialogDuplicateTags.cpp
	DialogDuplicateTags.h
	DialogExecuteCommand.cpp
	DialogExecuteCommand.h
	DialogFilter.cpp
	DialogFilter.h
	DialogFind.cpp
	DialogFind.h
	DialogFonts.cpp
	DialogFonts.h
	DialogLanguageModes.cpp
	DialogLanguageModes.h
	DialogMacros.cpp
	DialogMacros.h
	DialogMoveDocument.cpp
	DialogMoveDocument.h
	DialogMultiReplace.cpp
	DialogMultiReplace.h
	DialogOutput.cpp
	DialogOutput.h
	DialogPrint.cpp
	DialogPrint.h
	DialogPrompt.cpp
	DialogPrompt.h
	DialogPromptList.cpp
	DialogPromptList.h
	DialogPromptString.cpp
	DialogPromptString.h
	DialogRepeat.cpp
	DialogRepeat.h
	DialogReplace.cpp
	DialogReplace.h
	DialogShellMenu.cpp
	DialogShellMenu.h
	DialogSmartIndent.cpp
	DialogSmartIndent.h
	DialogSmartIndentCommon.cpp
	DialogSmartIndentCommon.h
	DialogSyntaxPatterns.cpp
	DialogSyntaxPatterns.h
	DialogTabs.cpp
	DialogTabs.h
	DialogWindowBackgroundMenu.cpp
	DialogWindowBackgroundMenu.h
	DialogWindowSize.cpp
	DialogWindowSize.h
	DialogWindowTitle.cpp
	DialogWindowTitle.h
	DialogWrapMargin.cpp
	DialogWrapMargin.h
	Direction.h
	DocumentModel.cpp
	DocumentModel.h
	DocumentWidget.cpp
	DocumentWidget.h
	DragEndEvent.h
	DragStates.h
	EditFlags.h
	ElidedLabel.cpp
	ElidedLabel.h
	FixedFontSelector.cpp
	FixedFontSelector.h
	Font.cpp
	Font.h
	FontType.h
	Help.cpp
	Help.h
	HighlightData.h
	HighlightPattern.cpp
	HighlightPattern.h
	HighlightPatternModel.cpp
	HighlightPatternModel.h
	HighlightStyle.h
	HighlightStyleModel.cpp
	HighlightStyleModel.h
	KeySequenceEdit.cpp
	KeySequenceEdit.h
	LanguageMode.h
	LanguageModeModel.cpp
	LanguageModeModel.h
	LockReasons.h
	Main.cpp
	Main.h
	MainWindow.cpp
	MainWindow.h
	MenuData.h
	MenuItem.h
	MenuItemModel.cpp
	MenuItemModel.h
	MultiClickStates.h
	NeditServer.cpp
	NeditServer.h
	NewMode.h
	PatternSet.cpp
	PatternSet.h
	Rangeset.cpp
	Rangeset.h
	RangesetTable.cpp
	RangesetTable.h
	ReparseContext.h
	ShiftDirection.h
	SignalBlocker.h
	SmartIndent.cpp
	SmartIndent.h
	SmartIndentEntry.cpp
	SmartIndentEntry.h
	SmartIndentEvent.h
	Style.h
	StyleTableEntry.h
	TabWidget.cpp
	TabWidget.h
	Tags.cpp
	Tags.h
	TextArea.cpp
	TextArea.h
	TextBuffer.cpp
	TextBuffer.h
	TextBuffer.tcc
	TextBufferFwd.h
	TextEditEvent.cpp
	TextEditEvent.h
	TextSelection.cpp
	TextSelection.h
	UndoInfo.cpp
	UndoInfo.h
	Verbosity.h
	WindowHighlightData.cpp
	WindowHighlightData.h
	WindowMenuEvent.cpp
	WindowMenuEvent.h
	WrapMode.h
	X11Colors.cpp
	X11Colors.h
	gap_buffer.h
	gap_buffer_fwd.h
	gap_buffer_iterator.h
	Highlight.cpp
	Highlight.h
	macro.cpp
	macro.h
	nedit.cpp
	nedit.h
	preferences.cpp
	preferences.h
	Search.cpp
	Search.h
	shift.cpp
	shift.h
	userCmds.cpp
	userCmds.h	
)

target_include_directories (nedit-ng PRIVATE
	${Boost_INCLUDE_DIR}
)

target_link_libraries(nedit-ng LINK_PUBLIC
	Util
	Regex
	Settings
	Interpreter
	GSL
	Qt5::Widgets
	Qt5::Network
	Qt5::Xml
	Qt5::PrintSupport
)

set_property(TARGET nedit-ng PROPERTY CXX_EXTENSIONS OFF)
set_property(TARGET nedit-ng PROPERTY CXX_STANDARD 14)

set_target_properties(nedit-ng
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

install (TARGETS nedit-ng DESTINATION bin)
