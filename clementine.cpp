#include "clementine.h"
#include "./ui_clementine.h"
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
Clementine::Clementine(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Clementine)
{
    ui->setupUi(this);

    QMenuBar*menuBar=this->menuBar();

    QMenu *fileMenu = menuBar->addMenu("文件");

    addFileAction = new QAction("添加文件", this);
    removeFileAction = new QAction("删除文件", this);
    exitAction = new QAction("退出", this);

    addFileAction->setShortcut(tr("Ctrl+N"));
    exitAction->setShortcut(tr("Ctrl+Q"));

    fileMenu->addAction(addFileAction);
    fileMenu->addAction(removeFileAction);
    fileMenu->addSeparator(); // 添加分隔线
    fileMenu->addAction(exitAction);

    connect(addFileAction, &QAction::triggered, this, &Clementine::onAddFile);
    connect(removeFileAction, &QAction::triggered, this, &Clementine::onRemoveFile);
    connect(exitAction, &QAction::triggered, this, &Clementine::onExit);


}

Clementine::~Clementine()
{
    delete ui;
}

// 点击“添加文件”触发
void Clementine::onAddFile()
{
    QMessageBox::information(this, "提示", "执行添加文件操作");
}

// 点击“删除文件”触发
void Clementine::onRemoveFile()
{
    QMessageBox::information(this, "提示", "执行删除文件操作");
}

// 点击“退出”触发
void Clementine::onExit()
{
    close(); // 关闭窗口
}

