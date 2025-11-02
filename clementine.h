#ifndef CLEMENTINE_H
#define CLEMENTINE_H

#include <QMainWindow>
#include <QMessageBox>
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
    QAction *addFileAction;
    QAction *removeFileAction;
    QAction *exitAction;


private slots:
    void onAddFile();
    void onRemoveFile();
    void onExit();

};
#endif // CLEMENTINE_H
