#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QKeyEvent>
#include <QListWidgetItem>

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

protected:
    bool eventFilter(QObject *target, QEvent *event);
private:
    Ui::MainWindow *ui;
    QVector<float> *vector;
};

#endif // MAINWINDOW_H
