#ifndef AJ_UIA_PROP_H
#define AJ_UIA_PROP_H

#include "aj_uia.h"

class AjUiaProp
{
public:
    explicit AjUiaProp(AjUia *u);
    ~AjUiaProp();

    void setValue(HWND hwnd, QString path, QString val);
    QString getValue(HWND hwnd, QString path);
    void toggle(HWND hwnd, QString path);
    QString getToggle(HWND hwnd, QString path);
    QString getName(HWND hwnd, QString path);
    QString getState(HWND hwnd, QString path);
    QString getType(HWND hwnd, QString path);
    QString getParent(QString path);
    QString getChildPath(HWND hwnd, QString path, QString name);

private:
    AjUia *uia;
};

#endif // AJ_UIA_PROP_H
