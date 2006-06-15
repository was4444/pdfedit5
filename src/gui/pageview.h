#ifndef __PAGEVIEW_H__
#define __PAGEVIEW_H__

#include <qlabel.h>
#include <qevent.h>
#include <qpainter.h>
#include <qcursor.h>

namespace gui {

class Rect2DArray;
class BBoxOfObjectOnPage;

/** QWidget's class for viewing a page.
 *
 */
class PageView : public QLabel {
	Q_OBJECT
	public:
		/** Enum type for setting selection mode for select all object. */
		enum SelectionAllMode {
				/** the selected area will be bounded thin rectangle */						RectSelection,
				/** the selected area will be filled rectangle */							FillRectSelection,
				/** moving or creating selected area -> FillRectSelection.
				 *							Otherwise -> RectSelection */					RectFillRectSelection,
				/** FillRectRectSelection	moving or creating selected area -> RectSelection.
				 *							Otherwise -> FillRectSelection */				FillRectRectSelection };

		/** Enum type for setting selection mode. */
		enum SelectionMode {
				/** choosing point or rectangle for select objects */	SelectAllObjects,
				/** choosing text bboxes */								SelectText,
				/** choosing point or rectangle for select */			SelectRect };

		/** Default constructor of pageView.
		 * @param parent widget containing this control
		 *
		 * It sets 
		 *	selection mode to FillRectRectSelection
		 **/
		PageView (QWidget *parent);
		/** Deconstructor of pageView.
		 */
		virtual ~PageView ();
		/** Method for escape from creating or moving selected area.
		 *
		 * @return  if was terminated creating or moving process, return true
		 */
		bool escapeSelection ();	// return true if escaped from selection or moving mode
	signals:
		/** Signal generated by selection process after the selected area
		 * @param r the selected area
		 */
		void leftClicked ( const QRect & r);
		/** Signal generated by mouse right release event
		 * @param  p page position of mouse right release event
		 * @param  r contains rectangle of the selected area on the page (if mouse event is out of selected area 
		 * 	on the page, than parameter will be NULL)
		 */
		void rightClicked ( const QPoint & p, const QRegion * r);
		/** Signal generated by selection process after move the selected area or if user clicked on selected area
		 * @param  r relativ position of move of selected area on the page
		 * @param  p position of release button
		 * @param  objects objects which are moved
		 */
		void selectionMoved ( const QPoint & r, const QPoint & p, const QPtrList<BBoxOfObjectOnPage> & objects );
		/** Signal generated by selection process after resize the selected area
		 * @param  oldRect old selected rectangle
		 * @param  newRect new selected rectangle
		 * @param  objects objects which are resized
		 */
		void selectionResized( const QRect & oldRect, const QRect & newRect, const QPtrList<BBoxOfObjectOnPage> & objects );
		/** Signal generated by new selection known objects
		 * @param  objects Objects which are selected.
		 */
		void newSelectedObjects( const QPtrList<BBoxOfObjectOnPage> & objects );
		/** Signal generated by moving process after move cursor
		 * @param  p new position of the cursor
		 */
		void changeMousePosition( const QPoint & p);
	protected:
		/** Method for process mouse press events (see QWidget's method).
		 * @param  e press event
		 *
		 * Start creating or moving process with selected area.
		 */
		virtual void mousePressEvent ( QMouseEvent * e );
		/** Method for process mouse release events (see QWidget's method).
		 * @param  e release event
		 *
		 * Finish creating or moving process with selected area.
		 *   ( emits leftClicked, rightClicked, selectionMovedTo signals )
		 */
		virtual void mouseReleaseEvent ( QMouseEvent * e );

//		virtual void mouseDoubleClickEvent ( QMouseEvent * e );

		/** Method for process mouse move events (see QWidget's method).
		 * @param  e move event
		 *
		 * If is started creating or moving process, process changes.
		 */
		virtual void mouseMoveEvent ( QMouseEvent * e );
	public slots:
		/** Method set selection mode.
		 * @param m selection mode (see 'enum SelectionMode')
		 *
		 * @return return FALSE if something is bad (e.g. want set SelectText and bboxes of text don't set), otherwise return TRUE
		 *
		 * Selection mode is dafault sets to SelectAllObjects .
		 */
		bool setSelectionMode ( enum SelectionMode m );				// default SelectAllObjects
		/** Method set selection mode for select all objects.
		 * @param m selection mode (see 'enum SelectionAllMode')
		 *
		 * Selection mode is dafault sets to FillRectRectSelection .
		 */
		void setSelectionAllMode ( enum SelectionAllMode m );		// default FillRectRectSelection
		/** Method clear objects with bbox for special selection mode (e.g. SelectText)
		 */
		void clearObjectsBBox ();
		/** Method add objects bbox for special selection mode (e.g. SelectText)
		 * @param bbox ref to rectangle's bbox
		 * @param ptr_object pointer to object with this bboxes (this pointer will return at end of selection)
		 */
		void addObjectsBBox ( const QRect & bbox, const void * ptr_object = NULL );
		/** Method set selected area.
		 * @param newRect rectangle to select area on page
		 * @param ptr_object pointer to object with this bboxes (this pointer will return at end of resizing, or moving)
		 */
		void setSelectedRegion ( QRect & newRect, const void * ptr_object = NULL );
		/** Method set selected area.
		 * @param newReg region to select area on page
		 * @param ptr_object pointer to object with this bboxes (this pointer will return at end of resizing, or moving)
		 */
		void setSelectedRegion ( QRegion & newReg, const void * ptr_object = NULL );
		/** Method add object to selected area.
		 * @param newRect rectangle to select area on page
		 * @param ptr_object pointer to object with this bboxes (this pointer will return at end of resizing, or moving)
		 */
		void addSelectedRegion ( QRect & newRect, const void * ptr_object = NULL );
		/** Method add object to selected area.
		 * @param newReg region to select area on page
		 * @param ptr_object pointer to object with this bboxes (this pointer will return at end of resizing, or moving)
		 */
		void addSelectedRegion ( QRegion & newReg, const void * ptr_object = NULL );
		/** Method unset selected area
		 */
		void unSelect ( );
		/** Method set pixmap image of page.
		 * @param qp image of page as QPixmap
		 */
		virtual void setPixmap ( const QPixmap & qp );
		/** Method set width of resizing zone
		 * @param width width in pixels
		 *
		 * Default is set to 2.
		 */
		void setResizingZone ( unsigned int width );
		/** Method save image to file
		 * @param file output file name
		 * @param format format output file (see QImageIO::outputFormats()
		 * @param quality quality factor must be in the range [0,100] or -1. Specify 0 to obtain small compressed files.
		 * @param onlySelectedArea specify TRUE to save only selected area, or FALSE to save all page
		 *
		 * @return  returns TRUE if successful; otherwise FALSE
		 */
		bool saveImage ( const QString & file, const char * format, int quality = -1, bool onlySelectedArea = false);
	protected:
		/** Set cursors for viewing on the page for actual selection mode */
		void setMappingCursor();
	private:
		/** enum of resizing parts */
		enum resizingParts	{ none = 0, left = 1, right = 2, top = 4, bottom = 8, onUnselectedObject = 16 };
		/** Method for calculation resizing mode
		 * @param r rectsngle for resizing
		 * @param p cursor position
		 * 
		 * @return combination of enum resizingParts
		 */
		int theNeerestResizingMode ( QRegion * r, const QPoint & p );
		/** Method for search and return the nearest Objects to point.
		 * @param point Search object to this point.
		 * 
		 * @return Pointer to the nearest object.
		 */
		BBoxOfObjectOnPage * getNearestObject( QPoint & point );
		/** enum of selection variant
		 * 	KeepSelection	= kepp actual selection variant 
		 */
		enum SelectionSet { KeepSelection, IsSelected, IsSelecting };
		/** Method for change selection variant
		 * @param ss selection variant (see enum SelectionSet)
		 */
		void changeSelection ( enum SelectionSet ss );
		/** Method for undraw selected area on the page
		 */
		void unDrawSelection ( void );
		/** Method for (un)block repainting widget
		 * @param block TRUE block repainting and FALSE unblock repainting and repaint widget
		 */
		void blockRepaint ( bool block = true );
		/** Method for draw region on page.
		 * @param newReg region to draw
		 * @param unDraw if region have been draw or undraw
		 *
		 * See also: changeSelection, setSelectionAllMode.
		 */
		void drawRect ( QRegion * newReg, bool unDraw = false );
		/** Method for undraw old rectangle and draw new region on page.
		 * @param oldReg old region to undraw
		 * @param newReg new region to draw
		 * @param ss selection variant to draw new region
		 */
		void drawRect ( QRegion * oldReg, QRegion * newReg, enum SelectionSet ss = KeepSelection );
		/** Method for redraw region with old rectangle to region with new rectangle on page.
		 * @param reg region selected on page
		 * @param oldRect old rectangle to undraw
		 * @param toPoint point of right bottom point of new rectangle to draw (left top point is same as have old rectangle)
		 * 		if toPoint is NULL, only undraw old selected region and rectangle
		 */
		void drawRect ( const QRegion * reg, QRect * oldRect, const QPoint * toPoint = NULL);
	private:
		/** original page image */
//		QPixmap * pageImage;

		/** temporary selected area */
		QRect * mouseRectSelected;
		/** selected area  ( must be normalized rectangle ) */
//		QRect * rectSelected;
		/** selected area  ( must be normalized rectangle ) */
//		QRect * oldRectSelected;

		/** temporary selected area */
		QRegion * mouseSelectedRegion;
		/** selected area - all selected bboxes */
		QRegion * selectedRegion;
		/** selected area - all selected bboxes */
		QRegion * oldSelectedRegion;

		/** Region for repaint */
		QRegion regionForRepaint;
		/** is true if repainting is blocked */
		bool	isRepaintingBlocked;

		/** is true if selected area is moving or creating new */
		bool	isPress;
		/** is true if selected area is moving */
		bool	isMoving;
		/** is true if selected area is resizing */
		bool	isResizing;
		/** is true if is set 'IsSelecting' selection variant */
		bool	quickSelection;
		/** selection mode */
		enum SelectionMode	selectionMode;
		/** selection mode which is set for selecting objects */
		enum SelectionAllMode	selectionAllMode;
		/** last selection mode which is set for selecting objects */
		enum SelectionAllMode	oldSelectionAllMode;
		/** moving mode - point is relative position mouse cursor from left top selected rectangle which is moving
		 *  resizing mode - point is right bottom position of selected area befor the area was resizing
		 */
		QPoint	pointInRect;
		/** aktual mouse position */
		QPoint	mousePos;
		/** mouse position in last left click */
		QPoint	mousePosInLeftClick;
		/** coefficient of X and Y in resizing (is eq. 0 or 1) */
		int	resizeCoefficientX,
			resizeCoefficientY;
		/** mapping array resizing mode to cursor shape */
		int mappingResizingModeToCursor [17];
		/** is combination of enum resizingParts */
		int cursorIsSetTo;
		/** width of resizing zone */
		int resizingCursorZone;

		/** 2D array of bboxes objects for special selection */
		Rect2DArray * arrayOfBBoxes;
		/** list of all selected objects */
		QPtrList<BBoxOfObjectOnPage> selectedObjects;
		/** Region of all objects for select */
		QRegion regionOfAllObjects;

		/** first selected objects */
		BBoxOfObjectOnPage * firstSelectedObject;
		/** last selected objects */
		BBoxOfObjectOnPage * lastSelectedObject;
		/** The nearest left objects on the line, if exist.
		 *  If doesn't exist left object on the line, it is the nearest right objects on the line.
		 */
		BBoxOfObjectOnPage * nearestObjectToClick;
};

} // namespace gui

#endif
