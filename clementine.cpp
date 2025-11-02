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

    // QMenuBar*menuBar=this->menuBar();


    initFileBar();


}

Clementine::~Clementine()
{
    delete ui;
}

void Clementine::initFileBar(){
    QMenuBar*menuBar=this->menuBar();

    menuBar->setStyleSheet("QMenuBar {"
                           "    min-height: 20px;"
                           "    max-height: 20px;"
                           "    background-color: #f0f0f0;"
                           "    border-bottom: 1px solid #ccc;"
                           "}"
                           "QMenuBar::item {"
                           "    padding: 0 10px;"
                           "}"
                           "QMenuBar::item:selected {"
                           "    background-color: #e0e0e0;"
                           "}");

    struct ActionInfo {
        QString text;       // 动作文本
        QKeySequence shortcut; // 快捷键
        QString tooltip;    // 提示文本
        QString Icon;
    };

    QList<ActionInfo> actionInfos = {
        {"Open File", QKeySequence(), "open file",":/fileicons/QT-Icons/open-folder.png"},
        {"打开音频", QKeySequence(), "video",":/fileicons/QT-Icons/video.png"},
        {"Add podcast", QKeySequence(), "new podcast",":/fileicons/QT-Icons/podcast.png"},
        {"上一首", QKeySequence(Qt::Key_F5), "previous",":/fileicons/QT-Icons/prev.png"},
        {"播放", QKeySequence(Qt::Key_F6), "play",":/fileicons/QT-Icons/play.png"},
        {"停止", QKeySequence(Qt::Key_F7), "stop",":/fileicons/QT-Icons/stop.png"},
        {"下一首", QKeySequence(Qt::Key_F8), "next",":/fileicons/QT-Icons/next.png"},
        {"静音", QKeySequence(Qt::CTRL | Qt::Key_M), "silence",":/fileicons/QT-Icons/silence.png"},
        {"喜欢", QKeySequence(Qt::CTRL | Qt::Key_Q), "prefer",":/fileicons/QT-Icons/prefer.png"},
        {"退出", QKeySequence(Qt::CTRL | Qt::Key_L), "exit",":/fileicons/QT-Icons/exit.png"}
    };



    for (const auto &info : actionInfos) {
        QAction *action = new QAction(info.text, this);
        action->setShortcut(info.shortcut);
        action->setToolTip(info.tooltip);
        action->setIcon(QIcon(info.Icon));
        fileActions.append(action);
    }

    QMenu *fileMenu = menuBar->addMenu("音乐(M)");
    for (QAction *action : fileActions) {
        QString str=action->text();
        if (str == "退出" || str == "上一首" || str == "喜欢" || str == "静音") {
            fileMenu->addSeparator();
        }
        fileMenu->addAction(action);
    }

    for (QAction *action : fileActions) {
        connect(action, &QAction::triggered, this, &Clementine::onActionTriggered);
    }

}

void Clementine::onActionTriggered()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if (!action) return;

    QString text = action->text();
    if (text == "新建") {
        QMessageBox::information(this, "提示", "执行新建操作");
    } else if (text == "打开") {
        QMessageBox::information(this, "提示", "执行打开操作");
    } else if (text == "保存") {
        QMessageBox::information(this, "提示", "执行保存操作");
    } else if (text == "另存为") {
        QMessageBox::information(this, "提示", "执行另存为操作");
    } else if (text == "退出") {
        close();
    }
}

