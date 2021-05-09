#include "stylesheet.h"

QString Stylesheet::masterHeaderParentStylesheetOn = "border-radius:10px; background-color: rgb(30, 33, 36);";
QString Stylesheet::masterHeaderParentStylesheetOff = "border-radius:10px; background-color: rgb(40, 46, 51); ";

QString Stylesheet::masterHeaderLabelStylesheetOn = "background-color: rgb(30, 33, 36); border:solid";
QString Stylesheet::masterHeaderLabelStylesheetOff = "background-color: rgb(40, 46, 51);";

QString Stylesheet::masterHeaderLineStylesheetOn = "background-color: #ff006c; max-height:1px; min-height:1px;";
QString Stylesheet::masterHeaderLineStylesheetOff = "background-color: rgb(127, 127, 127); max-height:1px; min-height:1px;";


QString Stylesheet::masterItemsParentStylesheetOn = "QWidget{ border-style: solid; background-color:rgb(35, 38, 41); border-radius:12px; max-width:370px; max-height:50px; min-width:370px; min-height:50px; }";

QString Stylesheet::masterItemsLabelStylesheetOn = "background-color: rgb(30, 33, 36);  max-width:320px; max-height:20px; min-width:320px; min-height:20px;";
QString Stylesheet::masterItemsLabelStylesheetOff = "background-color: rgb(35, 38, 41);  max-width:320px; max-height:20px; min-width:320px; min-height:20px;";




QString Stylesheet::scrollAreaStylesheet = "QScrollBar:vertical { background-color: #2A2929;  width: 12px; margin: 15px 3px 15px 3px; border: 1px transparent #2A2929; border-radius: 3px; }"
                               "QScrollBar::handle:vertical { background-color:  rgb(255, 0, 127); min-height: 5px; border-radius: 3px; }"
                               "QScrollBar::sub-line:vertical { margin: 3px 0px 3px 0px; border-image: url(:/images/up_arrow_disabled.png); height: 10px; width: 10px; subcontrol-position: top; subcontrol-origin: margin; }"
                               "QScrollBar::add-line:vertical { margin: 3px 0px 3px 0px; border-image: url(:/images/down_arrow_disabled.png); height: 10px; width: 10px; subcontrol-position: bottom; subcontrol-origin: margin; }"
                               "QScrollBar::sub-line:vertical:hover,QScrollBar::sub-line:vertical:on { border-image: url(:/images/up_arrow.png); height: 10px; width: 10px; subcontrol-position: top; subcontrol-origin: margin; }"
                               "QScrollBar::add-line:vertical:hover, QScrollBar::add-line:vertical:on { border-image: url(:/images/down_arrow.png); height: 10px; width: 10px; subcontrol-position: bottom; subcontrol-origin: margin; }"
                               "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical { background: none; }"
                               "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: none; }";




Stylesheet::Stylesheet(){ }
