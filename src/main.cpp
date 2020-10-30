#include "connecting.h"
#include "creategame.h"
#include "determineroledialog.h"
#include "error.h"
#include "gamewidget.h"
#include "joinexistinggame.h"
#include "manageroom.h"
#include "waitingtostart.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWidget w;
    w.show();

    Connecting c;
    //c.show();

    CreateGame cg;
    //cg.show();

    DetermineRoleDialog d;
    //d.show();

    error e;
    //e.show();

    GameWidget g;
    //g.show();

    JoinExistingGame j;
    //j.show();

    ManageRoom m;
    //m.show();

    WaitingToStart t;
    //t.show();


    return a.exec();
}
