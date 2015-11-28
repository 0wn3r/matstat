#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QKeyEvent>
#include <QListWidgetItem>
#include <QDesktopWidget>
#include <QMessageBox>
#include <list>
#include <vector>
#include <algorithm>
#include <QtDebug>

struct datavalue
{
    double num;
    unsigned int set_number;
    float rank;
    bool operator < (const datavalue &a)
    {
        return num < a.num;
    }
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void RangeValues(std::list<datavalue> &list);
    int RosenbaumCriteria();
    int MannWhitney();
    int KruskalWallis();

private slots:
    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_doubleSpinBox_editingFinished();

    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_pushButton_3_pressed();

    void on_pushButton_4_pressed();

protected:
    bool eventFilter(QObject *target, QEvent *event);
private:
    Ui::MainWindow *ui;
    std::list<datavalue> *list;
    std::vector<std::list<datavalue>> *vector;
    unsigned int global_counter = 0;
};

#endif // MAINWINDOW_H
