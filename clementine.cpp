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

    init();
    initFileBar();

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    initButtons(mainLayout);


    connect(bts[0],&QPushButton::clicked,[&](){
        this->LeftStackedLayout->setCurrentIndex(0);
    });
    connect(bts[1],&QPushButton::clicked,[&](){
        this->LeftStackedLayout->setCurrentIndex(1);
    });


    initLeft(mainLayout);

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


    QVBoxLayout *ButtonBoxLayout = new QVBoxLayout(ButtonBox);
    ButtonBoxLayout->setSpacing(0);
    ButtonBoxLayout->setContentsMargins(0, 0, 0, 0);
    buttons={
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
        bts.push_back(b);
        ButtonBoxLayout->addWidget(b, 0, Qt::AlignTop);
    }

    ButtonBox->setLayout(ButtonBoxLayout);
}

void Clementine::initLeft(QHBoxLayout *mainLayout){
    Left = new QWidget();
    Left->setStyleSheet("background-color: rgb(240,240,240);");
    Left->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QVBoxLayout* searchLayout=new QVBoxLayout(Left);
    auto new_width=(this->width()-70)/8*3;
    auto new_height=this->height();
    searchBox=new QLineEdit(this);
    searchBox->setPlaceholderText("请在此输入关键词");
    searchBox->resize(new_width-50,20);

    searchKB=new QWidget(this);
    QHBoxLayout* par=new QHBoxLayout(searchKB);
    QPushButton*consearch=new QPushButton(searchKB);
    consearch->setIcon(QIcon(":/background/QT-Icons/right-search.png"));
    consearch->setFixedSize(20,20);
    par->addWidget(searchBox);
    par->addWidget(consearch);
    searchKB->resize(new_width,30);
    searchKB->setLayout(par);
    searchLayout->addWidget(searchKB);

    //searchLayout->addWidget(searchBox);

    nosearch=new QWidget(Left);
    nosearch->resize(new_width,new_height-40);
    nosearch->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    LeftStackedLayout = new QStackedLayout(nosearch);
    this->initSearchArea(LeftStackedLayout);
    this->initMediaRepo(LeftStackedLayout);//------------------------
    nosearch->setLayout(LeftStackedLayout);
    searchLayout->addWidget(nosearch);
    Left->setLayout(searchLayout);
    mainLayout->addWidget(Left,3);
}

void Clementine::initRight(QHBoxLayout *mainLayout){
    QWidget *Right = new QWidget();
    Right->setStyleSheet("background-color: blue;");
    mainLayout->addWidget(Right,5);
}

void Clementine::initSearchArea(QStackedLayout *layout){
    scrollarea=new QScrollArea(nosearch);
    scrollarea->setWidgetResizable(true);
    scrollarea->setMaximumHeight(600);
    scrollarea->setStyleSheet(R"(
        QScrollBar:vertical {
            border: none;
            background: #f0f0f0;
            width: 8px;
            margin: 0px;
        }

        QScrollBar::handle:vertical {
            background: #c0c0c0;
            border-radius: 4px;
            min-height: 40px;
        }

        QScrollBar::handle:vertical:hover {
            background: #a0a0a0;
        }

        QScrollBar::handle:vertical:pressed {
            background: #808080;
        }

        QScrollBar::sub-line:vertical {
            border: none;
            background: none;
        }

        QScrollBar::add-line:vertical {
            border: none;
            background: none;
        }

        QScrollBar::background:vertical {
            background: #f0f0f0;
        }

        QScrollBar:horizontal {
            height: 0px;
            visibility: hidden;
        }
    )");

    auto new_width=(this->width()-70)/8*3;
    auto new_height=this->height();
    scrollarea->resize(new_width,new_height-40);

    QWidget* contentWidget =new QWidget(scrollarea);
    contentWidget->setStyleSheet("background-color:white");
    QVBoxLayout *sLayout=new QVBoxLayout(contentWidget);
    sLayout->setContentsMargins(0, 0, 0, 0);

    //文字介绍

    QWidget*recommend=new QWidget(scrollarea);
    QVBoxLayout *relayout = new QVBoxLayout(recommend);
    recommend->setStyleSheet("background-color:white;");
    recommend->setFixedHeight(150);
    relabel = new QLabel("Enter search terms above to find music on your computer and on the internet", recommend);
    relabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    relabel->setWordWrap(true);
    relayout->addWidget(relabel);
    recommend->setLayout(relayout);

    relabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    sLayout->addWidget(recommend);
    //文字介绍 end

    //寻找乐曲
    QWidget* linkarea=new QWidget(scrollarea);
    linkarea->setMinimumHeight(100);
    QVBoxLayout* linkLayout=new QVBoxLayout(linkarea);
    QLabel *findmusic=new QLabel("Clementine will find music in:",linkarea);
    findmusic->setWordWrap(true);
    linkLayout->addWidget(findmusic);
    labels={
        {":/findmusics/QT-Icons/mediarepo.png","媒体库"},
        {":/findmusics/QT-Icons/classicalradio.png","ClassicalRadio"},
        {":/findmusics/QT-Icons/digitallyimported.png","DigitallyImported"},
        {":/findmusics/QT-Icons/intergalactic.png","Intergalactic FM"},
        {":/findmusics/QT-Icons/jazzradio.png","JazzRadio"},
        {":/findmusics/QT-Icons/magnatune.png","Magnatune"},
        {":/findmusics/QT-Icons/radiobrowser.png","Radio-Browser.info"},
        {":/findmusics/QT-Icons/Radiotunes.png","RadioTunes"},
        {":/findmusics/QT-Icons/Rockradio.png","RockRadio"},
        {":/findmusics/QT-Icons/流媒体.png","您的电台流媒体"},
        {":/findmusics/QT-Icons/Soma.png","SomaFM"},
        {":/findmusics/QT-Icons/subsonic.png","Subsonic"}
    };

    for(const auto &label:labels){
        QWidget *itemWidget = new QWidget(linkarea);
        QHBoxLayout *itemLayout = new QHBoxLayout(itemWidget);
        itemLayout->setContentsMargins(0, 0, 0, 0);
        itemLayout->setSpacing(8);
        QLabel *iconLabel = new QLabel(itemWidget);
        QPixmap pixmap(label.icon);
        if (pixmap.isNull()) {
            iconLabel->setText("?");
        } else {
            pixmap = pixmap.scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            iconLabel->setPixmap(pixmap);
        }
        QLabel *textLabel = new QLabel(label.text, itemWidget);
        textLabel->setAlignment(Qt::AlignVCenter);
        textLabel->setWordWrap(true);
        itemLayout->addWidget(iconLabel);
        itemLayout->addWidget(textLabel);
        itemLayout->addStretch();
        linkLayout->addWidget(itemWidget);
    }

    QLabel *lost=new QLabel("But these sources are disabled:",linkarea);
    lost->setWordWrap(true);
    linkLayout->addWidget(lost);



    list={
        {"Box",":/nameicons/QT-Icons/Box.png","Not logged in"},
        {"Seafile",":/nameicons/QT-Icons/seafile.png","Not logged in"},
        {"Dropbox",":/nameicons/QT-Icons/dropbox.png","Not logged in"},
        {"Google Drive",":/nameicons/QT-Icons/google-drive.png","Not logged in"},
        {"Icecast",":/nameicons/QT-Icons/ice-cast.png","已禁用"},
        {"Jamendo",":/nameicons/QT-Icons/jamendo.png","已禁用"},
        {"OneDrive",":/nameicons/QT-Icons/onedrive.png","Not logged in"}
    };

    QWidget*disabled=new QWidget(linkarea);
    QHBoxLayout *separate=new QHBoxLayout(disabled);
    QWidget*namelist=new QWidget(disabled);
    namelist->setStyleSheet("background-color:white");
    QVBoxLayout *leftLayout=new QVBoxLayout(namelist);

    QWidget*logstatuslist=new QWidget(disabled);
    logstatuslist->setStyleSheet("background-color:white");
    QVBoxLayout *rightLayout=new QVBoxLayout(logstatuslist);
    for(const auto&info:list){
        QWidget*webname=new QWidget(namelist);
        QHBoxLayout *nameLayout=new QHBoxLayout(webname);
        nameLayout->setContentsMargins(0, 0, 0, 0);
        nameLayout->setSpacing(8);
        QLabel *iconLabel = new QLabel(webname);
        QPixmap pixmap(info.icon);
        if (pixmap.isNull()) {
            iconLabel->setText("?");
        } else {
            pixmap = pixmap.scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            iconLabel->setPixmap(pixmap);
        }
        QLabel *textLabel = new QLabel(info.name, webname);
        textLabel->setAlignment(Qt::AlignVCenter);
        textLabel->setWordWrap(true);
        nameLayout->addWidget(iconLabel);
        nameLayout->addWidget(textLabel);
        nameLayout->addStretch();

        webname->setLayout(nameLayout);
        leftLayout->addWidget(webname);
    }

    for(const auto&info:list){
        QWidget*status=new QWidget(namelist);
        QHBoxLayout *statusLayout=new QHBoxLayout(status);
        statusLayout->setContentsMargins(0, 0, 0, 0);
        statusLayout->setSpacing(8);
        QLabel *iconLabel = new QLabel(status);
        QPixmap pixmap(":/nameicons/QT-Icons/warning.png");
        if (pixmap.isNull()) {
            iconLabel->setText("?");
        } else {
            pixmap = pixmap.scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            iconLabel->setPixmap(pixmap);
        }
        QLabel *textLabel = new QLabel(info.logstatus, status);
        textLabel->setAlignment(Qt::AlignVCenter);
        textLabel->setWordWrap(true);
        statusLayout->addWidget(iconLabel);
        statusLayout->addWidget(textLabel);
        statusLayout->addStretch();

        status->setLayout(statusLayout);
        rightLayout->addWidget(status);
    }
    namelist->setLayout(leftLayout);
    logstatuslist->setLayout(rightLayout);
    separate->addWidget(namelist);
    separate->addWidget(logstatuslist);
    disabled->setLayout(separate);

    linkLayout->addWidget(disabled);
    linkarea->setLayout(linkLayout);
    sLayout->addWidget(linkarea);

    //寻找乐曲 end

    contentWidget->setLayout(sLayout);
    scrollarea->setWidget(contentWidget);
    layout->addWidget(scrollarea);
    scrollarea->show();
}

void Clementine::initMediaRepo(QStackedLayout *layout){
    QWidget*MediaRepo=new QWidget(nosearch);
    MediaRepo->setStyleSheet("background-color:white;");
    layout->addWidget(MediaRepo);
}
