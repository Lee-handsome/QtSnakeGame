#ifndef RANKLIST_H
#define RANKLIST_H

#include <QWidget>
#include <QFile>
#include <QDebug>

namespace Ui {
class RankList;
}

class RankList : public QWidget
{
    Q_OBJECT

public:
    explicit RankList(QWidget *parent = 0);
    ~RankList();
private:
    Ui::RankList *ui;
};

#endif // RANKLIST_H
