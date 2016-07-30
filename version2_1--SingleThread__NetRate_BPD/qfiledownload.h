#ifndef QFILEDOWNLOAD
#define QFILEDOWNLOAD
#include<mainwindow.h>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QFile>
#include<QFileInfo>
#include<QUrl>
#include<QTimer>
#include<QMessageBox>
#include<QEventLoop>

class MainWindow;

class QFileDownload:public QWidget
{
    Q_OBJECT

public:
    QFileDownload(QUrl url,MainWindow * window);
  //  ~QFileDownload();
    void startDeal();
    void stop();
    void startAgain();

private:
    QNetworkAccessManager *manager;
    QNetworkReply * reply;
    QNetworkRequest * qheader;
    QUrl url;
    QFile * file;
    QTimer *timer;
    QTimer *timer_15s;
    MainWindow * _window;
    qint64 totalSize,oldSize,newSize,leftBytes,startBytes;
    qint64 last_15s_Ssiz;//超时30s则出现网络异常，则暂停下载。
    qint64 speed,time_left;

private slots:
    void httpFinished();
    void httpReadyRead();
    void updateDataReadProgress(qint64,qint64);
    void updateSpeedTime();
    void timeOut();
};


#endif // QFILEDOWNLOAD

