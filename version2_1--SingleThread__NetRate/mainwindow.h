#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>

#include<qfiledownload.h>
class QFileDownload;
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void upDateProgressBar(qint64,qint64);
    void upDateSpeedLabel(QString);
    void upDateTimeLabel(QString);
    void HideProgressBar();
    void ShowProgressBar();

//    MainWindow* shared_ui();


private:
    Ui::MainWindow *ui;
    QFileDownload * fd;

private slots:
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
