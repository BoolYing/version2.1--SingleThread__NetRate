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

class MainWindow;

class QFileDownload:public QObject
{
    Q_OBJECT

public:
    QFileDownload(QUrl url,MainWindow * window);
  //  ~QFileDownload();
    void startDeal();

private:
    QNetworkAccessManager *manager;
    QNetworkReply * reply;
    QUrl url;
    QFile * file;
    QTimer *timer;
    MainWindow * _window;
private slots:
    void httpFinished();
    void httpReadyRead();
    void updateDataReadProgress(qint64,qint64);

};


#endif // QFILEDOWNLOAD

