#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("QT Database Control");
    setMaximumSize(geometry().width(), geometry().height());
    setMinimumSize(geometry().width(), geometry().height());

    QStringList title;
    ui->tableWidget->setColumnCount(2);
    title << "ID" << "Content";
    ui->tableWidget->setHorizontalHeaderLabels(title);

    if(!db.createDatabase())
    {
        QMessageBox::warning(this,"Database Error","Database is not Created!");
    }
    db.init();

    //Read All Data to temp when Init
    temp_List = db.readAllData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_write_clicked()
{
    //Check wherther Unique key
    QString content = ui->w_content->text();
    if(!temp_List.contains(content))
    {
        db.insertData(content);
        temp_List.append(content);
        on_showData_clicked();
    }
    else
    {
        QMessageBox::about(this,"Entry Error","The Content must be Unique!");
    }

}

void MainWindow::on_delete_2_clicked()
{
    db.removeData(ui->d_content->text());
    on_showData_clicked();
}

void MainWindow::on_showData_clicked()
{
    ui->tableWidget->setRowCount(0);
    QStringList contentList = db.readAllData();
    foreach (QString content, contentList) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        int fila = ui->tableWidget->rowCount()-1;
        ui->tableWidget->setItem(fila,0,new QTableWidgetItem(QString::number(fila+1)));
        ui->tableWidget->setItem(fila,1,new QTableWidgetItem(content));
    }
}

void MainWindow::on_clearData_clicked()
{
    db.clearDatabase();
    temp_List.clear();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}

void MainWindow::on_close_clicked()
{
    this->close();
}
