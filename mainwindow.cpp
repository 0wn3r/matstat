#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->listWidget->installEventFilter(this);
    list = new std::list<float>;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete list;
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (target == ui->listWidget) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = (QKeyEvent*)event;
            if (keyEvent->key() == Qt::Key_Delete) {
              auto it = list->begin();
              for (int i = 0; i < ui->listWidget->currentRow(); i++)
                  it++;
              list->erase(it);
              QListWidgetItem *item = ui->listWidget->item(ui->listWidget->currentRow());
              delete item;
              float sum = 0;
              for (auto it = list->begin(); it != list->end(); ++it)
              {
                  sum += *it;
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
        auto it = list->begin();
        for (int i = 0; i < ui->listWidget->currentRow(); i++)
            it++;
        *it = item->text().toFloat();
        float sum = 0;
        for (auto it = list->begin(); it != list->end(); ++it)
        {
            sum += *it;
        }
        QString str;
        str = QString("%1").arg(sum);
        ui->label->setText(str);
    }
}

void MainWindow::on_doubleSpinBox_editingFinished()
{
    if (ui->doubleSpinBox->cleanText() == "")
        return;
    ui->listWidget->addItem(ui->doubleSpinBox->cleanText());
    list->push_back(ui->doubleSpinBox->value());
    ui->doubleSpinBox->clear();
    for (int ii = 0; ii < ui->listWidget->count(); ii++) {
        ui->listWidget->item(ii)->setFlags(ui->listWidget->item(ii)->flags() | Qt::ItemIsEditable);
    }
    float sum = 0;
    for (auto it = list->begin(); it != list->end(); ++it)
    {
        sum += *it;
    }
    QString str;
    str = QString("%1").arg(sum);
    ui->label->setText(str);
}
