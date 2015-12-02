#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QListWidgetItem>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <list>
#include <vector>
#include <array>
#include <algorithm>
#include <random>
#include <utility>
#include "boost/filesystem/fstream.hpp"
#include <QtDebug>
#include "readcsv.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void InitializeListWidget(std::vector<std::list<datavalue>> *vec);
    void RangeValues(std::list<datavalue> &list);
    int RosenbaumCriteria();
    int MannWhitney();
    int KruskalWallis();
    int Jonkir();
    int Pirson();

private slots:
    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_doubleSpinBox_editingFinished();

    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_pushButton_3_pressed();

    void on_pushButton_4_pressed();

    void on_pushButton_5_pressed();

    void on_pushButton_6_pressed();

    void on_pushButton_7_pressed();

protected:
    bool eventFilter(QObject *target, QEvent *event);
private:
    Ui::MainWindow *ui;
    std::list<datavalue> *list;
    std::vector<std::list<datavalue>> *vector;
    unsigned short global_counter = 0;
};

#endif // MAINWINDOW_H
