#include<qfiledownload.h>

QFileDownload::QFileDownload(QUrl url, MainWindow * _window){
    this->url = url;
    this->_window = _window;
    oldSize = newSize = 0; //初始化大小都为0
    last_15s_Ssiz =0;

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
    // 启动测速定时，1s。
    timer = new QTimer(this);
    timer->start(1000);
    //启动超时定时，30s。
    timer_15s = new QTimer(this);
    if(timer_15s->isActive())
        timer_15s->stop();
    timer_15s->start(15000);

    connect(timer,SIGNAL(timeout()),this,SLOT(updateSpeedTime()));
    connect(timer_15s,SIGNAL(timeout()),this,SLOT(timeOut()));
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

//    _window->HideProgressBar();

    totalSize = oldSize = newSize =  0;
    //disconnect(timer,SIGNAL(timeout()),this,SLOT(updateSpeedTime()));

    _window->upDateSpeedLabel("");
    _window->upDateTimeLabel("下载完成");
    //如果还在定时，就停止
    if(timer_15s->isActive())
        timer_15s->stop();
    //将缓冲区内的数据全部刷到文件中并关闭文件。
    file->flush();
    file->close();
    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;
    delete this;
}

void QFileDownload::updateDataReadProgress(qint64 _bytesRead, qint64 _totalBytes){

    totalSize = _totalBytes;
    newSize = _bytesRead;
    leftBytes = _totalBytes - _bytesRead;

    _window->upDateProgressBar(_bytesRead,_totalBytes);
}

void QFileDownload::updateSpeedTime(){

    speed =  newSize - oldSize;
    oldSize = newSize;
    QString str1,str2;
    str1 = QString::number(speed/1024,10)+" K/s";


    if(speed != 0){
         time_left = leftBytes/speed;
         str2 = QString::number(time_left,10)+" s";
    }
    else  if(leftBytes != 0 ){
            str2 = "暂无网络.";
        }

    _window->upDateSpeedLabel(str1);
    _window->upDateTimeLabel(str2);
}
void QFileDownload::timeOut(){
    if(newSize != last_15s_Ssiz)
        last_15s_Ssiz = newSize;
    else {
       QMessageBox::warning(this,tr("Error!"),tr("Network fault,wait or stop?"),QMessageBox::Yes);
    }
}
