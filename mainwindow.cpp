#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->listWidget->installEventFilter(this);
    vector = new QVector<float>;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete vector;
}


void MainWindow::on_lineEdit_returnPressed()
{
    if(!ui->lineEdit->text().isEmpty())
    {
        ui->listWidget->addItem(ui->lineEdit->text());
        vector->push_back(ui->lineEdit->text().toFloat());
        ui->lineEdit->clear();
    }
    for (int ii = 0; ii < ui->listWidget->count(); ii++) {
        ui->listWidget->item(ii)->setFlags(ui->listWidget->item(ii)->flags() | Qt::ItemIsEditable);
    }
    float sum = 0;
    for (int i = 0; i < vector->size(); i++)
    {
        sum += vector->at(i);
    }
    QString str;
    str = QString("%1").arg(sum);
    ui->label->setText(str);
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (target == ui->listWidget) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = (QKeyEvent*)event;
            if (keyEvent->key() == Qt::Key_Delete) {
              vector->removeAt(ui->listWidget->currentRow());
              QListWidgetItem *it = ui->listWidget->item(ui->listWidget->currentRow());
              delete it;
              float sum = 0;
              for (int i = 0; i < vector->size(); i++)
              {
                  sum += vector->at(i);
              }
              QString str;
              str = QString("%1").arg(sum);
              ui->label->setText(str);
              return true;}
        } else {
            return false;
        }
    }
        // pass the event on to the parent class
    return QMainWindow::eventFilter(target, event);
}

void MainWindow::on_listWidget_itemChanged(QListWidgetItem *item)
{
    if (item->isSelected())
    {
        vector->replace(ui->listWidget->currentRow(), item->text().toFloat());
        float sum = 0;
        for (int i = 0; i < vector->size(); i++)
        {
            sum += vector->at(i);
        }
        QString str;
        str = QString("%1").arg(sum);
        ui->label->setText(str);
    }
}
