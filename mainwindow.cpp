#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->listWidget->installEventFilter(this);
    ui->tableWidget->installEventFilter(this);
    ui->tableWidget->horizontalHeader()->setVisible(0);
    ui->tableWidget->verticalHeader()->setVisible(0);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    list = new std::list<datavalue>;
    vector = new std::vector<std::list<datavalue> *>;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete list;
    delete vector;
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (target == ui->listWidget) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = (QKeyEvent*)event;
            if (keyEvent->key() == Qt::Key_Delete) {
              auto it = std::next(list->begin(), ui->listWidget->currentRow());
              list->erase(it);
              QListWidgetItem *item = ui->listWidget->item(ui->listWidget->currentRow());
              delete item;
              return true;}
        } else {
            return false;
        }
    }
    else if (target == ui->tableWidget) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = (QKeyEvent*)event;
            if (keyEvent->key() == Qt::Key_Delete) {
              vector->erase(vector->begin() + ui->tableWidget->currentRow());
              ui->tableWidget->removeRow(ui->tableWidget->currentRow());
              ui->tableWidget->setRowCount(vector->size());
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
        auto it = std::next(list->begin(), ui->listWidget->currentRow());
        (*it).num = item->text().toFloat();
    }
}

void MainWindow::on_doubleSpinBox_editingFinished()
{
    if (ui->doubleSpinBox->cleanText() == "")
        return;
    ui->listWidget->addItem(ui->doubleSpinBox->cleanText());
    datavalue temp;
    temp.num = ui->doubleSpinBox->value();
    temp.set_number = global_counter;
    temp.rank = 0;
    list->push_back(temp);
    ui->doubleSpinBox->clear();
    for (int ii = 0; ii < ui->listWidget->count(); ii++) {
        ui->listWidget->item(ii)->setFlags(ui->listWidget->item(ii)->flags() | Qt::ItemIsEditable);
    }
}

void MainWindow::on_pushButton_pressed()
{
    list->sort([](const datavalue &a, const datavalue &b){return a.num < b.num;});
    vector->push_back(list);
    if (list->size() > static_cast<size_t>(ui->tableWidget->columnCount()) || list->size() == 1)
    {
        ui->tableWidget->setColumnCount(list->size());
    }
    ui->tableWidget->setRowCount(vector->size());
    int i = 0;
    for (auto it = list->begin(); it != list->end(); ++it, i++)
    {
        QString str;
        str = QString("%1").arg((*it).num);
        ui->tableWidget->setItem(vector->size()-1, i, new QTableWidgetItem(str));
    }
    list->clear();
    ui->listWidget->clear();
    global_counter++;
}
