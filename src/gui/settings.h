#ifndef __SETTINGS_H__
#define __SETTINGS_H__
#include "config.h"
#include <qapplication.h>
#include <qsettings.h>
#include <qsplitter.h>
#include <qstringlist.h> 
#include <qmenudata.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qstring.h>
#include <qpixmap.h>
#include "toolbar.h"

typedef QMap<QString, int> ActionMap;
typedef QMap<int, QString> ActionMapInverse;
typedef QMap<QString, QPixmap*> IconCache;
typedef QValueList<ToolBar*> ToolBarList;

/** Class managing settings and also loading configurable menus, toolbars and keyboard shortcuts */

class Settings : public QObject {
 Q_OBJECT
public:
 ~Settings();
 /** get Instance of Settings. Ensures only one instance of Settings is avalable */
 static Settings* getInstance() {
  static Settings* globalSettings=NULL;
  if (!globalSettings) globalSettings=new Settings();
  return globalSettings;
 }
// static Settings* getInstance();
 QMenuBar *loadMenu(QWidget *parent);
 QString getAction(int index);
 ToolBarList loadToolBars(QMainWindow *parent);
 void saveWindow(QWidget *win,const QString name); 
 void restoreWindow(QWidget *win,const QString name);
 void saveSplitter(QSplitter *spl,const QString name);
 void restoreSplitter(QSplitter *spl,const QString name);
 QString getIconFile(const QString &name);
 QStringList readPath(const QString &name);
 QStringList readList(const QString &name,const QString separator=",");
public slots:
 void flushSettings();
 QString readExpand(const QString &key,const QString defValue=QString::null);
 QString read(const QString &key,const QString defValue=QString::null);
 bool readBool(const QString &key,bool defValue=false);
 void write(const QString &key,const QString &value);
 QString expand(QString s);
signals:
 /** Signal emitted when any setting is changed. Key of changed settings is sent.
     Can be used to monitor settings changes */
 void settingChanged(QString);
private:
 //Constructor is private, use getInstance
 Settings();
 /** List with paths to application icons */
 QStringList iconPath;
 /** Cache storing loaded icons */
 IconCache iconCache;
 /** Settings object used to load configuration
  These settings takle precedence before staticSettings */
 QSettings *set;
 /** Settings object used to load static configuration (menu, etc ...)
  These settings are never changed (and never written) */
 QSettings *staticSet;
 /** Mapping between menu IDs and actions */
 ActionMap action_map;
 /** Inverse mapping between menu IDs and actions */
 ActionMapInverse action_map_i;
 /** Incrementing action index for menu items */
 int action_index;

 int addAction(const QString action);
 void init();
 QString readItem(const QString name,const QString root="gui/items/");
 void loadItem(const QString name,QMenuData *parent=NULL,bool isRoot=FALSE);
 void initSettings();
 void initPaths();
 QPixmap *getIcon(const QString name);
 ToolBar *loadToolbar(const QString name,QMainWindow *parent);
 void loadToolBarItem(ToolBar *tb,QString item);

};

/** One object for application, holding all global settings. */
extern Settings *globalSettings;

#endif
