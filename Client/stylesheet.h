#ifndef STYLESHEET_H
#define STYLESHEET_H

#include <QString>


class Stylesheet
{
public:

    ///Master header stylesheets
    static QString masterHeaderParentStylesheetOn;
    static QString masterHeaderParentStylesheetOff;

    static QString masterHeaderLabelStylesheetOn;
    static QString masterHeaderLabelStylesheetOff;

    static QString masterHeaderLineStylesheetOn;
    static QString masterHeaderLineStylesheetOff;


    ///Master items stylesheets
    static QString masterItemsParentStylesheetOn;

    static QString masterItemsLabelStylesheetOn;
    static QString masterItemsLabelStylesheetOff;




    static QString scrollAreaStylesheet;





public:
    Stylesheet();
    ~Stylesheet();

};

#endif
