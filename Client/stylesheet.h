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

    ///Master items stylesheets


    static QString masterItemsLabelStylesheetOn;
    static QString masterItemsLabelStylesheetOff;



public:
    Stylesheet();
    ~Stylesheet();

};

#endif // STYLESHEET_H
