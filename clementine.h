#ifndef CLEMENTINE_H
#define CLEMENTINE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPainter>
#include <QStackedLayout>
#include <QResizeEvent>
#include <QScrollArea>
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
    QScrollArea *scrollarea;

private:
    Ui::Clementine *ui;
    QList<QAction*> fileActions;
    void init();
    void initFileBar();
    void initButtons(QHBoxLayout *mainLayout);
    void initLeft(QHBoxLayout *mainLayout);
    void initRight(QHBoxLayout *mainLayout);

    void initSearchArea(QWidget* parent);

signals:
    void sizeChanged(const QSize &newSize);


private slots:

    void onActionTriggered();

protected:
    void resizeEvent(QResizeEvent *event) override ;

};
#endif // CLEMENTINE_H
