#include "highscoredb.h"
#include <QtSql>
#include <QTableView>
#include <QtDebug>

highScoreDb::highScoreDb() {
  qDebug() << "start";

  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("/home/student/eal0010/high_score.db");

  if (!db.open()) {
    qDebug() << db.lastError();
    qDebug() << "Error: Unable to connect";
    // return 1;
  }

  // QSqlQueryModel model;
  // model.setQuery("SELECT * FROM highScore");
  QSqlTableModel* model = new QSqlTableModel;
  model->setTable("High Score Mode");
  model->select();
  model->setEditStrategy(QSqlTableModel::OnFieldChange);

  QTableView* view = new QTableView;
  view->setModel(model);
  view->show();

  db.close();
  // return a.exec();
}

// }
