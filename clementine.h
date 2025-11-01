#ifndef CLEMENTINE_H
#define CLEMENTINE_H

#include <QMainWindow>

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
};
#endif // CLEMENTINE_H
