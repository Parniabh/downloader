#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ProcessJson->setEnabled(false);
    downloader = new Downloader();
    connect(downloader, SIGNAL(download_finished_sgnl()), this, SLOT(enable_button()));
    connect(ui->ProcessJson, SIGNAL(clicked()),this, SLOT(show_json()));
    downloader->execute();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enable_button()
{
    ui->ProcessJson->setEnabled(true);
}

void MainWindow::show_json()
{
    QJsonObject jsonobject = downloader->loadedJson.object();
    qDebug()<<jsonobject;
    int j = 0;
    foreach(const QString& key, jsonobject.keys()) {
        QJsonValue value = jsonobject.value(key);
        qDebug() << "Key = " << key << ", Value = " << value;
        ui->listWidget->insertItem(j, key);
        j++;
    }
    QString forcast_url = jsonobject.value("properties").toObject().value("forecast").toString();
    qDebug()<<"url: " << forcast_url;


}
