#ifndef CLEMENTINE_H
#define CLEMENTINE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPainter>
#include <QList>
QT_BEGIN_NAMESPACE
namespace Ui {
class Clementine;
}
QT_END_NAMESPACE

class Clementine : public QMainWindow
{
    Q_OBJECT

public:
    Clementine(QWidget *parent = nullptr);
    ~Clementine();

private:
    Ui::Clementine *ui;
    QList<QAction*> fileActions;
    void init();
    void initFileBar();
    void initButtons(QHBoxLayout *mainLayout);
    void initLeft(QHBoxLayout *mainLayout);
    void initRight(QHBoxLayout *mainLayout);


private slots:

    void onActionTriggered();

};
#endif // CLEMENTINE_H
