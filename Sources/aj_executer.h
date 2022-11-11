#ifndef AJ_EXECUTER_H
#define AJ_EXECUTER_H

#include "aj_win.h"
#include "aj_parser.h"
#include "aj_virt.h"

#define AJ_CHECK_FAILED  1
#define AJ_CHECK_SUCCESS 2


class AjExecuter
{
public:
    AjExecuter(QString script_path);

    int condition_flag;

private:
    void exec(AjCommand *cmd);
    int execOpen(AjCommand *cmd);

    QString conf_path;
    AjApplication app;
    AjParser parser; // value stored in parser
    AjVirt vi;
};


#endif // AJ_EXECUTER_H
