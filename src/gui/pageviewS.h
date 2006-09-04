#ifndef __PAGEVIEWS_H__
#define __PAGEVIEWS_H__

#include <qscrollview.h>
#include <qevent.h>
#include <qpainter.h>
#include <qcursor.h>

#include <boost/smart_ptr.hpp>

#include "cpage.h"

class OutputDev;

namespace gui {

#ifdef __PAINTER_TO_MODE_ACTION
#undef __PAINTER_TO_MODE_ACTION
#endif

class PageViewMode;


/** QWidget's class for viewing a page.
 *
 */
class PageViewS : public QScrollView {
	Q_OBJECT
	public:
		/** Default constructor of pageView.
		 * @param parent widget containing this control
		 *
		 * It sets 
		 *	selection mode to FillRectRectSelection
		 **/
		PageViewS (QWidget *parent);
		/** Deconstructor of pageView.
		 */
		virtual ~PageViewS ();

		/** Method show defined page \a page.
		 * @param page Page for show.
		 */
		void showPage ( boost::shared_ptr<pdfobjects::CPage> page );
	signals:
		/** Signal generated by moving process after move cursor
		 * @param  x New horizontal position of the cursor
		 * @param  y New vertical position of the cursor
		 */
		void changeMousePosition( double x, double y );
	protected:
		/** Method set correct width and height of viewport for actual page \a actualPage. */
		void setCorrectSize ();
		/** Method update display parameters \a displayParams for output devices \a output
		 * and actual page \a actualPage.
		 * @param output Initialized output device.
		 */
		virtual void updateDisplayParameters ( OutputDev & output );

		/** Method for process mouse press events (see QScrollView's method).
		 * @param  e press event
		 */
		virtual void contentsMousePressEvent ( QMouseEvent * e );

		/** Method for process mouse release events (see QScrollView's method).
		 * @param  e release event
		 */
		virtual void contentsMouseReleaseEvent ( QMouseEvent * e );

		/** Method for process mouse double click events (see QScrollView's method).
		 * @param  e double-click event
		 */
		virtual void contentsMouseDoubleClickEvent ( QMouseEvent * e );

		/** Method for process mouse move events (see QScrollView's method).
		 * @param  e move event
		 */
		virtual void contentsMouseMoveEvent ( QMouseEvent * e );
		
		/** Method for process wheel event (see QWidget's method).
		 * @param  e wheel event
		 */
		virtual void wheelEvent ( QWheelEvent * e );

		/** Method for process key press event (see QWidget's method).
		 * @param  e press event
		 */
		virtual void keyPressEvent ( QKeyEvent * e );

		/** Method for process key release event (see QWidget's method).
		 * @param  e release event
		 */
		virtual void keyReleaseEvent ( QKeyEvent * e );

		/** Method for process focus in event (see QWidget's method).
		 * @param  e focus event
		 */
		virtual void focusInEvent ( QFocusEvent * e );

		/** Method for process focus out event (see QWidget's method).
		 * @param  e focus event
		 */
		virtual void focusOutEvent ( QFocusEvent * e );

		/** Method for process drawing contents (see QScrollView's method).
		 * @param  p painter
		 * @param  cx content's x
		 * @param  cy content's y
		 * @param  cw content's width
		 * @param  ch content's hight
		 */
		virtual void drawContents(QPainter* p, int cx, int cy, int cw, int ch);

		/** Method set left-top position of page on viewport (set \a movedPageToCenter).
		 * Set x = 0 if page's width is greatter then visible viewport's width. Otherwise set x to
		 * half of ( visible viewport's width  minus  page's width ).
		 * Set y = 0 if page's height is ...
		 */
		void centerPage( );

		/** Method is call if viewport is resized (\see Qt::QWidget::viewportResizeEvent).
		 * @param e Resiaze event structure.
		 *
		 * Center actual page for new size of viewport.
		 * @see centerPage
		 */
		virtual void viewportResizeEvent ( QResizeEvent * e );

		/** Method send all operators in page to mode and initialize him. */
		void initializeWorkOperatorsInMode();
	public slots:
		/** Function return actual zoom factor of viewed page.
		 * @return Return zoom factor (1.0 = 100%)
		 *
		 * @see setZoomFactor
		 */
		float getZoomFactor ( );
		/** Set zoom factor of viewed page.
		 * @param set_zoomFactor Zoom factor (1.0 = 100%)
		 *
		 * @return Return zoom factor which is set (1.0 = 100%)
		 *
		 * @see getZoomFactor
		 */
		float setZoomFactor ( float set_zoomFactor );

		/** Method set selection mode.
		 * @param m Shared pointer to new selection mode
		 */
		void setSelectionMode ( const boost::shared_ptr<PageViewMode> & m );
		/** Method set pixmap image of slice of page.
		 * @param r rectangle define slice of page
		 */
		virtual void setPixmap ( const QRect & r );

		/** Method save image to file
		 * @param file output file name
		 * @param format format output file (see QImageIO::outputFormats()
		 * @param quality quality factor must be in the range [0,100] or -1. Specify 0 to obtain small compressed files.
		 * @param onlySelectedArea specify TRUE to save only selected area, or FALSE to save all page
		 *
		 * @return  returns TRUE if successful; otherwise FALSE
		 */
		bool saveImage ( const QString & file, const char * format, int quality = -1, bool onlySelectedArea = false);
		/** Method repaint pixmap and selected region */
		void needRepaint ( );

		/** Converting position from pixmap of viewed page to pdf position.
		 * @param fromX	X position on viewed page.
		 * @param fromY	Y position on viewed page.
		 *
		 * @param toX	return X position in pdf page.
		 * @param toY	return Y position in pdf page.
		 *
		 * @see convertPdfPosToPixmapPos
		 * @see DisplayParams::convertPixmapPosToPdfPos
		 */
		void convertPixmapPosToPdfPos( double fromX, double fromY, double & toX, double & toY );
		/** Converting pdf position to position on pixmap of viewed page.
		 * @param fromX	X position in pdf page.
		 * @param fromY	Y position in pdf page.
		 *
		 * @param toX	return X position on viewed page.
		 * @param toY	return Y position on viewed page.
		 *
		 * @see convertPixmapPosToPdfPos
		 * @see DisplayParams::convertPdfPosToPixmapPos
		 */
		void convertPdfPosToPixmapPos( double fromX, double fromY, double & toX, double & toY );
	protected:
		/** Region for repaint */
		QRegion regionForRepaint;

		/** Working mode (selecting, ...) */
		boost::shared_ptr<PageViewMode> mode;

		/** aktual mouse position */
		QPoint  mousePos;

		/** position of left-top position of page on viewport (is not [0,0] when page is smaller then space for view) */
		QPoint  movedPageToCenter;
		/** original part of viewed page */
		QPixmap	* pagePixmap;
		/** Size of all viewed page */
		QSize	sizeOfPage;
		/** Rectangle saved in pagePixmap */
		QRect	croppedPage;

		/** Display parameters ( hDpi, vDpi, rotate, ... ) */
		pdfobjects::DisplayParams	displayParams;

		/** Smart pointer to actual viewed page. */
		boost::shared_ptr<pdfobjects::CPage>	actualPage;

		/** Pixels per point when zoom is 100 % */
		float		basePpP;
		/** Zoom factor requirement by user */
		float		zoomFactor;

};

} // namespace gui

#endif
