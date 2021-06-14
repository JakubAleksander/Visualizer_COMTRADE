#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QDateTimeAxis>
#include <QValueAxis>
#include <QFileDialog>
#include <QMessageBox>

#include <chart.h>
#include <chartview.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setData();
    void clearTabs();

private:
    Ui::MainWindow *ui;
    QTabWidget *tabWidget;
};

#endif // MAINWINDOW_H
