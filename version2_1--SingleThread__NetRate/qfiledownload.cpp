#include<qfiledownload.h>

QFileDownload::QFileDownload(QUrl url, MainWindow * _window){
    this->url = url;
    this->_window = _window;
    manager = new QNetworkAccessManager(this);
}
/*
QFileDownload::~FileDownload(){
}
*/
void QFileDownload::startDeal()
{
    QFileInfo info(url.path());
    QString fileName(info.fileName());
    if(fileName.isEmpty())
        fileName = "index.html";
    file = new QFile(fileName);
    if(!file->open(QIODevice::WriteOnly))
    {
        qDebug()<<"file open error !";
        delete file;
        file = 0;
        return ;
    }
    reply = manager->get(QNetworkRequest(url));
    _window->upDateProgressBar(0,0);
    _window->ShowProgressBar();

    connect(reply,SIGNAL(finished()),this,SLOT(httpFinished()));
    connect(reply,SIGNAL(readyRead()),this,SLOT(httpReadyRead()));
    connect(reply,SIGNAL(downloadProgress(qint64 ,qint64 )),this
            ,SLOT(updateDataReadProgress(qint64,qint64)));
}

void QFileDownload::httpReadyRead()
{
    if(file)
        file->write(reply->readAll());
}
void QFileDownload::httpFinished(){
//    ui->progressBar->hide();
    _window->HideProgressBar();

    file->flush();
    file->close();
    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;
}

void QFileDownload::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes){

    _window->upDateProgressBar(bytesRead,totalBytes);
}



