#include "copy.h"

Copy::Copy(QWidget *parent) :QWidget(parent)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));

    /*********************************/
    selectSrcFolder = new QPushButton("srcFolder", this);
    connect(selectSrcFolder, SIGNAL(clicked()), this, SLOT(FindSrcFolder()));

    selectDstFolder = new QPushButton("dstFolder", this);
    connect(selectDstFolder, SIGNAL(clicked()), this, SLOT(FindDstFolder()));

    dstFolder = new QLineEdit(this);
    srcFolder = new QLineEdit(this);

    // 1. create a button for manual operation to start copying files
    startMove = new QPushButton("Start Moving", this);
    connect(startMove, SIGNAL(clicked()), this, SLOT(copyFile()));

    // 2. create a button for automatic operation to start copying files
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(copyFile()));
    timer->start(60000);

    CreateActions();

    QVBoxLayout* vLay1 = new QVBoxLayout;
    vLay1->addWidget(srcFolder);
    vLay1->addWidget(selectSrcFolder);
    QVBoxLayout* vLay2 = new QVBoxLayout;
    vLay2->addWidget(dstFolder);
    vLay2->addWidget(selectDstFolder);
    QHBoxLayout* hLay1 = new QHBoxLayout;
    hLay1->addLayout(vLay1);
    hLay1->addLayout(vLay2);
    QVBoxLayout* vLay3 = new QVBoxLayout;
    vLay3->addLayout(hLay1);
    vLay3->addWidget(startMove);
    setLayout(vLay3);

    setWindowIcon(QIcon(":/icons/copyFile.ico"));

    /*********************************/
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setToolTip("Copy File - by pan");
    trayIcon->setIcon(QIcon(":/icons/copyFile.ico"));
    CreateTrayIconActions();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    trayIcon->show();

}


void Copy::CreateActions(){
     minimizeAction = new QAction(tr("minimize"), this);
     connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
     maximizeAction = new QAction(tr("maxmize"), this);
     connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));
     restoreAction = new QAction(tr("restore"), this);
     connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
     quitAction = new QAction(tr("exit"), this);
     connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}


void Copy::CreateTrayIconActions(){
     trayIconMenu = new QMenu(this);
     trayIconMenu->addAction(minimizeAction);
     trayIconMenu->addAction(maximizeAction);
     trayIconMenu->addAction(restoreAction);
     trayIconMenu->addSeparator();
     trayIconMenu->addAction(quitAction);
     trayIcon->setContextMenu(trayIconMenu);
}


void Copy::FindSrcFolder(){
    srcFolderPath = QFileDialog::getExistingDirectory(this, "Select the source folder", "C:/");

    if (srcFolderPath != NULL){
        srcFolder->setText(srcFolderPath);
    }
}


void Copy::FindDstFolder(){
    dstFolderPath = QFileDialog::getExistingDirectory(this, "Select the destination folder", "C:/");

    if (dstFolderPath != NULL){
        dstFolder->setText(dstFolderPath);
    }
}


bool Copy::copyFile(){
    QDir dir;
    dir.setPath(srcFolderPath);
    srcFileList = dir.entryInfoList();
    QFileInfo fileName;
    for (int i = 0; i < srcFileList.size(); i++){
        fileName = srcFileList.at(i);
        if (QFile::exists(dstFolderPath + "/" + fileName.fileName())) {
            QFile::remove(dstFolderPath + "/" + fileName.fileName());
        }
        QFile::copy(fileName.absoluteFilePath(), dstFolderPath + "/" + fileName.fileName());
    }

    return true;
}

void Copy::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::DoubleClick:
            this->show();
            this->setWindowState(Qt::WindowNoState);
            break;
        default:
            break;
    }
}


void Copy::changeEvent(QEvent *event){
    if(this->isMinimized())
    {
        QTimer::singleShot(0, this, SLOT(hide()));
        this->setWindowState(Qt::WindowNoState);
        event->ignore();
    }
}

void Copy::closeEvent(QCloseEvent *event){
    if (this->trayIcon->isVisible()){
        this->hide();
        this->setWindowState(Qt::WindowNoState);
        event->ignore();
    }
}












