/*                                                                              
 * PDFedit - free program for PDF document manipulation.                        
 * Copyright (C) 2006, 2007  PDFedit team:      Michal Hocko, 
 *                                              Miroslav Jahoda,       
 *                                              Jozef Misutka, 
 *                                              Martin Petricek                                             
 *
 * Project is hosted on http://sourceforge.net/projects/pdfedit                                                                      
 */ 
/*
 * =====================================================================================
 *        Filename:  selectpagesdialog.h
 *     Description:  
 *         Created:  03/12/2006 07:41:44 PM CET
 *          Author:  jmisutka ()
 * =====================================================================================
 */


#ifndef __SELECTPAGESDIALOG_H__
#define __SELECTPAGESDIALOG_H__

#include "qtcompat.h"
#include <vector>
#include <qvariant.h>
#include <qdialog.h>
#include <qfiledialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QPushButton;
class QFrame;
class Q_ListBox;
class Q_ListBoxItem;

// =====================================================================================
namespace gui {
// =====================================================================================


// =====================================================================================
//  SelectPagesDialog
// =====================================================================================

/** 
 * Select page dialog.
 * Used to select pages for PDF to XML export
 * \see MergeDialog
 */
class SelectPagesDialog : public QDialog 
{
    Q_OBJECT

public:
	typedef std::vector<size_t> Result;

	//
	// Variables
	//
protected:

    QGridLayout* SelectPagesDialogLayout;
    QVBoxLayout* layout48;
    QHBoxLayout* layout27;
    QHBoxLayout* layout47;
    QVBoxLayout* layout4;
    QSpacerItem* spacer3;
    QHBoxLayout* layout6;
    QSpacerItem* spacer5;
    QSpacerItem* spacer6;

	QLabel* textLabel1;
    Q_ListBox* originalList;
    Q_ListBox* selectedList;
    /** button to add current page from right (imported document) to the left (current document)*/
    QPushButton* addBtn;
    /** button to remove current page from left*/
    QPushButton* removeBtn;
    /** Cancel button - dismiss dialog without doing anything*/
    QPushButton* cancelBtn;
    /** Ok button - accept result of dialog and merge pages*/
    QPushButton* okBtn;

	//
	// Ctor
	//
public:
    SelectPagesDialog (const QString& filename);

	//
	// Interface
	//
public:
    /** 
	 * Returns result of selection.
     * 
     * Creates structure representing the results.
	 * Important: Caller is responsible for deallocation).
     */
	template<typename Container> void getResult (Container& cont) const;

	//
	// Helper functions
	//
protected:
    /** 
	 * Initializes page selection.
     * @param count Document page count.
     */
    void init (size_t count);

	/** 
	 * Init page selection from pdf file name.
     * @param filename Document file name.
     */
    bool init (const QString& filename);


	//
	// Event handlers
	//
public slots:
    // Events handlers
    /** Slot called when button "<<" to add page to current document is clicked */
    virtual void addBtn_clicked ();
    /** Slot called when button ">>" to remove page from current document is clicked */
    virtual void removeBtn_clicked ();
	// Other handlers
#ifdef QT3
    virtual void originalList_changed (QListBoxItem* item);
    virtual void selectedList_changed (QListBoxItem*);
#else
//MOC_SKIP_BEGIN (Qt3 moc will skip this. Qt4 moc won't and it is able to understande ifdef. Good)
    virtual void originalList_changed (Q3ListBoxItem* item);
    virtual void selectedList_changed (Q3ListBoxItem*);
//MOC_SKIP_END
#endif

protected slots:
    virtual void languageChange();
};


// =====================================================================================
} //namespace gui
// =====================================================================================

#endif // __SELECTPAGESDIALOG_H__
