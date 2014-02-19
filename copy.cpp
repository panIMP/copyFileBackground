#include "copy.h"

Copy::Copy(QWidget *parent) :QWidget(parent)
{
    /*********************************/
    selectSrcFolder = new QPushButton("srcFolder", this);
    connect(selectSrcFolder, SIGNAL(clicked()), this, SLOT(FindSrcFolder()));

    selectDstFolder = new QPushButton("dstFolder", this);
    connect(selectDstFolder, SIGNAL(clicked()), this, SLOT(FindDstFolder()));

    dstFolder = new QLineEdit(this);
    srcFolder = new QLineEdit(this);

    startMove = new QPushButton("Start Moving", this);
    connect(startMove, SIGNAL(clicked()), this, SLOT(copyFile()));

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
    trayIcon->show();
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
        QFile::copy(fileName.absoluteFilePath(), dstFolderPath + "/" + fileName.fileName());
    }

    return true;
}

