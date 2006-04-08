#ifndef __PROPERTYEDITOR_H__
#define __PROPERTYEDITOR_H__

#include <qstringlist.h>
#include <qobjectlist.h>
#include <qscrollview.h>
#include <qdict.h>
#include <qmap.h>
#include <qwidget.h>
#include <qgrid.h>
#include <qlabel.h>
#include <qlayout.h>
#include <iproperty.h>
#include "property.h"

/** property editor widget */
class PropertyEditor : public QWidget {
 Q_OBJECT
public:
 PropertyEditor(QWidget *parent=0, const char *name=0);
 virtual ~PropertyEditor();
 void resizeEvent (QResizeEvent *e);
 void clear();
public slots:
 void setObject(const QString &message);
 void setObject(IProperty *pdfObject);
 void update(Property *p);
private:
 void addProperty(const QString &name,boost::shared_ptr<IProperty> value);
 void addProperty(Property *prop,boost::shared_ptr<IProperty> value);
 void deleteLayout();
 void createLayout();
private:
 /** Object currently edited */
 IProperty *obj;
 /** Number of objects in proiperty editor */
 int nObjects;
 /** Grid holding all property editing widgets*/
 QFrame *grid;
 /** Layout used for the grid */
 QGridLayout *gridl;
 /** Scrollview holding the grid */
 QScrollView *scroll;
 /** List of property names */
 QStringList *list;
 /** Dictionary with property items */
 QDict<Property> *items;
 /** Dictionary with IProperty items */
 QMap<QString,boost::shared_ptr<IProperty> > *props;
 /** Dictionary with property labels */
 QDict<QLabel> *labels;
};

#endif
