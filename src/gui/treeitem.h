#ifndef __TREEITEM_H__
#define __TREEITEM_H__

#include <iproperty.h>
#include <qlistview.h>

using namespace pdfobjects;

class TreeItem : public QListViewItem {
public:
 TreeItem(QListView *parent,IProperty *pdfObj,const QString name=QString::null);
 TreeItem(QListViewItem *parent,IProperty *pdfObj,const QString name=QString::null);
 ~TreeItem();
 IProperty* getObject();
private:
 void init(IProperty *pdfObj,const QString name);
 /** CObject stored in this TreeItem */
 IProperty *obj;
};

#endif
