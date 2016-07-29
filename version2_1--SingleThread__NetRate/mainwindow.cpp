#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progressBar->hide();
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButton_clicked()
{
    QUrl url = ui->lineEdit->text();
    fd = new QFileDownload(url,this);
    fd->startDeal();

}
void MainWindow::upDateProgressBar(qint64 bytesRead,qint64 totalBytes)
{
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesRead);



}
void MainWindow::ShowProgressBar()
{
    ui->progressBar->show();
}
void MainWindow::HideProgressBar()
{
    ui->progressBar->hide();
}
void MainWindow::upDateSpeedLabel(QString speed){
    ui->label->setText(speed);
}

void MainWindow::upDateTimeLabel(QString _time_left){
    ui->label_2->setText(_time_left);
}


















/*
void MainWindow::startRequest(QUrl url){
    reply = manager->get(QNetworkRequest(url));
    connect(reply,SIGNAL(finished()),this,SLOT(httpFinished()));
    connect(reply,SIGNAL(readyRead()),this,SLOT(httpReadyRead()));
    connect(reply,SIGNAL(downloadProgress(qint64 ,qint64 )),this
            ,SLOT(updateDataReadProgress(qint64,qint64)));

}

void MainWindow::httpReadyRead()
{
    if(file)
        file->write(reply->readAll());
}
void MainWindow::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes){
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesRead);
}
void MainWindow::httpFinished(){
    ui->progressBar->hide();
    file->flush();
    file->close();
    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;
}
MainWindow* MainWindow::shared_ui(){
     return ui;
 }
*/
