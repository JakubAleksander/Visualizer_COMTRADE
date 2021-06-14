#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Visualizer");

    tabWidget = new QTabWidget();
    setCentralWidget(tabWidget);

    connect(ui->actionLoad_file, SIGNAL(triggered()), this, SLOT(setData()));
    connect(ui->actionClear_tabs, SIGNAL(triggered()), this, SLOT(clearTabs()));
    connect(ui->actionExit, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setData()
{
    QString path = QFileDialog::getOpenFileName(this, "Choose file", "", tr("File (*.DAT)"));

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox msgBox;
        msgBox.setText("Can not open file \"" + path + "\"");
        msgBox.exec();
        return;
    }
    if(tabWidget->count() != 0) clearTabs();

    for(int i=0; i<6; i++){
        QScatterSeries *series = new QScatterSeries();
        series->setName("Sample " + QString::number(i));
        series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
        series->setMarkerSize(1.0);

        while(!file.atEnd()){
            QString line = file.readLine();
            QStringList data = line.split(',', QString::SkipEmptyParts);
            *series << QPoint(data.at(1).toInt()/1000, data.at(i+2).toInt());
        }

        Chart *chart = new Chart();
        chart->addSeries(series);
        chart->setTitle("Chart " + QString::number(i+1));

        QDateTimeAxis *axisX = new QDateTimeAxis();
        axisX->setTickCount(10);
        axisX->setFormat("mm:ss.z");
        axisX->setTitleText("Time [m:s.z]");
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setLabelFormat("%i");
        axisY->setTitleText("Value");
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        ChartView *chartView = new ChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        tabWidget->addTab(chartView, "Chart " + QString::number(i+1));

        file.seek(0);
    }
    file.close();
}

void MainWindow::clearTabs()
{
    for(int i = tabWidget->count(); i>0; i--){
        tabWidget->widget(i-1)->deleteLater();
        tabWidget->removeTab(i-1);
    }
}
