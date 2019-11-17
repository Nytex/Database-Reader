#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTcpSocket>
#include <QTableWidget>
#include <QMessageBox>

#include "databasewrapper.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_write_clicked();
    void on_delete_2_clicked();
    void on_showData_clicked();
    void on_clearData_clicked();

    void on_close_clicked();

private:
    Ui::MainWindow *ui;
    DatabaseWrapper db;
    QStringList temp_List;
};

#endif // MAINWINDOW_H
