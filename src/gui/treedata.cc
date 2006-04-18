/** @file
 TreeItem - class holding Tree Data that need to be shared between tree window and its items
*/

#include "treedata.h"
#include "treewindow.h"
#include "treeitem.h"

namespace gui {

using namespace std;

/** Constructor of TreeData
 @param parent TreeWindow holding these data
 @param tree Tree holding list items
*/
TreeData::TreeData(TreeWindow *parent,QListView *tree) {
 _parent=parent;
 _tree=tree;
}

/** Add TreeItem that holds a CRef into list
 Will do nothing on TreeItems that do not hold a CRef.
 @param it TreeItem holding CRef
 */
void TreeData::add(TreeItem *it) {
 QString ref=it->getRef();
 if (ref.isNull()) return;
 //Remove any old data
 while (refs.remove(ref));
 //Add new data
 refs.insert(ref,it);
}

/** Remove TreeItem that holds a CRef from list
 Will do nothing on TreeItems that do not hold a CRef.
 @param it TreeItem with reference to remove
 */
void TreeData::remove(TreeItem *it) {
 remove(it->getRef());
}

/** Remove specific reference from the list
 (Useful to call after reference in object itself was changed to remove old reference))
 @param ref Reference to remove
 */
void TreeData::remove(const QString &ref) {
 if (ref.isNull()) return;
 while (refs.remove(ref));
}


/** Look in list for a treeItem with given reference and return it.
 @param ref Reference in string format
 @return TreeItem with given reference, or NULL if nothing found
*/
TreeItem* TreeData::find(const QString &ref) {
 return refs.find(ref);
}

/** Clear list of TreeItems with CRef*/
void TreeData::clear() {
 refs.clear();
}

/** Return parent of this TreeData
 @return parent TreeWindow */
TreeWindow* TreeData::parent() {
 return _parent;
}

/** Return tree from this TreeData
 @return QlistViewparent Tree */
QListView* TreeData::tree() {
 return _tree;
}

/** default destructor */
TreeData::~TreeData() {
}

} // namespace gui
