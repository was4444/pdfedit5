#ifndef __PAGEVIEW_H__
#define __PAGEVIEW_H__

#include <qlabel.h>
#include <qevent.h>
#include <qpainter.h>
#include <qcursor.h>

#include <boost/smart_ptr.hpp>

namespace gui {

class PageViewMode;


/** QWidget's class for viewing a page.
 *
 */
class PageView : public QLabel {
	Q_OBJECT
	public:
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
	signals:
		/** Signal generated by moving process after move cursor
		 * @param  p new position of the cursor
		 */
		void changeMousePosition( const QPoint & p);
	protected:
		/** Method for process mouse press events (see QWidget's method).
		 * @param  e press event
		 */
		virtual void mousePressEvent ( QMouseEvent * e );

		/** Method for process mouse release events (see QWidget's method).
		 * @param  e release event
		 */
		virtual void mouseReleaseEvent ( QMouseEvent * e );

		/** Method for process mouse double click events (see QWidget's method).
		 * @param  e double-click event
		 */
		virtual void mouseDoubleClickEvent ( QMouseEvent * e );

		/** Method for process mouse move events (see QWidget's method).
		 * @param  e move event
		 */
		virtual void mouseMoveEvent ( QMouseEvent * e );
		
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
	public slots:
		/** Method set selection mode.
		 * @param m Shared pointer to new selection mode
		 */
		void setSelectionMode ( const boost::shared_ptr<PageViewMode> & m );
		/** Method set pixmap image of page.
		 * @param qp image of page as QPixmap
		 */
		virtual void setPixmap ( const QPixmap & qp );
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
	private:
		/** Region for repaint */
		QRegion regionForRepaint;

		/** Painter for painting to pixmap */
		QPainter painter;

		/** Working mode (selecting, ...) */
		boost::shared_ptr<PageViewMode> mode;

		/** aktual mouse position */
		QPoint  mousePos;
};

} // namespace gui

#endif
