#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QKeyEvent>
#include <QListWidgetItem>
#include <QDesktopWidget>
#include <list>
#include <vector>

struct datavalue
{
    double num;
    unsigned int set_number;
    int rank;
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

private slots:
    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_doubleSpinBox_editingFinished();

    void on_pushButton_pressed();

protected:
    bool eventFilter(QObject *target, QEvent *event);
private:
    Ui::MainWindow *ui;
    std::list<datavalue> *list;
    std::vector<std::list<datavalue> *> *vector;
    unsigned int global_counter = 0;
};

#endif // MAINWINDOW_H
