#ifndef COPY_H
#define COPY_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QFileDialog>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <Filter.h>
#include <QFileInfoList>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QTextCodec>
#include <QApplication>
#include <QTimer>
#include <QCloseEvent>

class Copy : public QWidget
{
    Q_OBJECT
public:
    explicit Copy(QWidget *parent = 0);

    void CreateActions();
    void CreateTrayIconActions();

signals:

public slots:
    void FindSrcFolder();
    void FindDstFolder();
    bool copyFile();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    //void showMessage(char* msg);


protected:
    void changeEvent(QEvent *event);
    void closeEvent(QCloseEvent *event);


private:
    QString srcFolderPath;
    QString dstFolderPath;
    QFileInfoList srcFileList;
    QString dstFileList;
    QPushButton* selectSrcFolder;
    QPushButton* selectDstFolder;
    QPushButton* startMove;
    QLineEdit* srcFolder;
    QLineEdit* dstFolder;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;
};

#endif // COPY_H
