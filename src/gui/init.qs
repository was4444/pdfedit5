//PDFedit init script
//This script will be run at start, or on creation of new window
//Each window have its own scripting context

/* ==== load various needed functions ==== */
run( "pdfoperator.qs" );	//Functions for manipulation with pdf operators
run( "callback.qs" );			//Callback handlers
run( "dialog_lib.qs" );			//Dialog helper functions
run( "dialogs.qs" );			//Dialogs
run( "menu.qs" );			//Functons activated from menu/toolbars
run( "page.qs" );			//Page manipulation functions
run( "test.qs" );			//Testing functions

/* ==== Other helper functions ==== */

/** Toggle on/off boolean setting with specified key */
function toggle(key) {
 val=settings.readBool(key);
 settings.write(key,!val);
}

/** Get dictionary from page number X */
function pageDict(x) {
 page=document.getPage(x);
 return page().getDictionary();
}

/** === Validate functions === */

/** Is argument a number */
function isNumber(x) {
	if (undefined == x || isNaN(parseFloat(x)))
		return false;
	else
		return true;
}

/** Are all numbers */
function isNumber2(x,y) {
	if (isNumber(x) && isNumber(y))
		return true;
	else
		return false;
}

/** Are all numbers */
function isNumber4(x,y,z,w) {
	if (isNumber(x) && isNumber(y) && isNumber(z) && isNumber(w))
		return true;
	else
		return false;
}

/** Validate current page */
function isPageAvaliable() {
 if (page()) {
	return true;
 }else
 	return false;
}

/** Validate item selection */
function isTreeItemSelected() {
 if (undefined == firstSelectedItem()) {
	return false;
 }else
 	return true;
}

/** Update menus to correctly show certain window shown/hidden state */
function toggleVisItem(item,menuitem) {
 vis=isVisible(item);
 checkItem(menuitem,vis);
// t=getItemText(menuitem);
}

/* ==== Code to run on start ==== */

//Pre-selected font sizes
setPredefs('fontface',getSystemFonts());
//Pre-selected font sizes
setPredefs('fontsize','8,9,10,12,14,16,18,24,36,72');
setNumber('fontsize',10);//default value
//Pre-selected line widths
setPredefs('linewidth','0.5,1,1.5,2,3,4,8,16');
setNumber('linewidth',1);//default value

//Print welcome message
print("PDFedit "+version());
onSelectMode_AllObjects();
checkMenus();

//Item visibility toggleboxes
toggleVisItem('commandline','hideCmd');
toggleVisItem('propertyeditor','hideProp');
toggleVisItem('tree','hideTree');
toggleVisItem('statusbar','hideStatus');

//Set tooltips for items
setTooltip("fontface",tr("Font face"));
setTooltip("fontsize",tr("Font size (in points)"));
setTooltip("linewidth",tr("Line width (in points)"));
