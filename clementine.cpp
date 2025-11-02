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
    ui->centralwidget->setContentsMargins(0,0,0,0);
    //ui->centralwidget->setStyleSheet("background-color: grey;");

    init();
    initFileBar();

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    initButtons(mainLayout);
    initLeft(mainLayout);
    connect(this,&Clementine::sizeChanged,[&](){
        auto new_width=(this->width()-70)/8*3;
        auto new_height=this->height();
        scrollarea->resize(new_width,new_height);
    });
    initRight(mainLayout);

    ui->centralwidget->setLayout(mainLayout);
}

Clementine::~Clementine()
{
    delete ui;
}

void Clementine::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    emit sizeChanged(event->size());
}

void Clementine::init(){
    this->statusBar()->hide();
    this->setStatusBar(nullptr);
    setWindowIcon(QIcon(":/fileicons/QT-Icons/clementine.png"));
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
        QString text;
        QKeySequence shortcut;
        QString tooltip;
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

void Clementine::initButtons(QHBoxLayout *mainLayout){
    QWidget*ButtonBox=new QWidget(this);
    ButtonBox->setFixedWidth(70);
    mainLayout->addWidget(ButtonBox,0);
    ButtonBox->setObjectName("BB");
    ButtonBox->setStyleSheet(R"(
        #BB {
            background-image: url(:/background/QT-Icons/ButtonBackground.webp);
            background-repeat: no-repeat;
            background-position: center;
        }
        QPushButton {
            background-color: rgba(255, 255, 255, 150); /* 半透明白色背景 */
            border: 1px solid #ccc;
        }
    )");

    struct ButtonInfo{
        QString icon;
        QString text;
    };

    QVBoxLayout *ButtonBoxLayout = new QVBoxLayout(ButtonBox);
    ButtonBoxLayout->setSpacing(0);
    ButtonBoxLayout->setContentsMargins(0, 0, 0, 0);
    QVector<ButtonInfo>buttons={
        {":/buttonicons/QT-Icons/search.png","搜索"},
        {":/buttonicons/QT-Icons/media-repo.png","媒体库"},
        {":/fileicons/QT-Icons/open-folder.png","文件"},
        {":/buttonicons/QT-Icons/playlist.png","Play-lists"},
        {":/buttonicons/QT-Icons/internet.png","互联网"},
        {":/buttonicons/QT-Icons/device.png","设备"},
        {":/buttonicons/QT-Icons/music-info.png","歌曲信息"},
        {":/buttonicons/QT-Icons/player-info.png","音乐人信息"}
    };
    for(const auto& button:buttons){
        QPushButton* b = new QPushButton(this);
        b->setFixedSize(70,55);
        b->setStyleSheet("background-color:transparent");
        QVBoxLayout* innerLayout = new QVBoxLayout(b);
        innerLayout->setSpacing(5);
        innerLayout->setContentsMargins(0, 5, 0, 5);
        QLabel* iconLabel = new QLabel;





        iconLabel->setPixmap(QIcon(button.icon).pixmap(32, 32));
        iconLabel->setAlignment(Qt::AlignCenter);

        QLabel* textLabel = new QLabel(button.text);
        textLabel->setAlignment(Qt::AlignCenter);
        textLabel->setStyleSheet(
            "color: white;"
            "font-weight: bold;"
            "font-size: 14px;"
            );

        innerLayout->addWidget(iconLabel);
        innerLayout->addWidget(textLabel);
        b->setLayout(innerLayout);
        ButtonBoxLayout->addWidget(b, 0, Qt::AlignTop);
    }

    ButtonBox->setLayout(ButtonBoxLayout);
}

void Clementine::initLeft(QHBoxLayout *mainLayout){
    QWidget *Left = new QWidget();
    Left->setStyleSheet("background-color: white;");
    Left->setMinimumWidth(0);       // 允许最小宽度为0
    Left->setMaximumWidth(QWIDGETSIZE_MAX); // 允许最大宽度无限
    Left->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
     qDebug() << Left->width() << Qt::endl;
    //QStackedLayout *LeftStackedLayout = new QStackedLayout;
    this->initSearchArea(Left);


    //Left->setLayout(LeftStackedLayout);
    mainLayout->addWidget(Left,3);
}

void Clementine::initRight(QHBoxLayout *mainLayout){
    QWidget *Right = new QWidget();
    Right->setStyleSheet("background-color: blue;");
    mainLayout->addWidget(Right,5);
}

void Clementine::initSearchArea(QWidget* parent){
    scrollarea=new QScrollArea(parent);
    auto new_width=(this->width()-70)/8*3;
    auto new_height=this->height();
    scrollarea->resize(new_width,new_height);

    QWidget* contentWidget =new QWidget(parent);
    QVBoxLayout *sLayout=new QVBoxLayout(contentWidget);

    for (int i = 0; i < 20; ++i) {
        sLayout->addWidget(new QPushButton(QString("按钮 %1").arg(i + 1)));
    }


    contentWidget->setLayout(sLayout);
    scrollarea->setWidget(contentWidget);
    scrollarea->show();


}
