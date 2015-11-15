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
    vector = new std::vector<std::list<datavalue>>;
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
    datavalue temp = { ui->doubleSpinBox->value(), global_counter, 0};
    list->push_back(temp);
    ui->doubleSpinBox->clear();
    for (int i = 0; i < ui->listWidget->count(); i++) {
        ui->listWidget->item(i)->setFlags(ui->listWidget->item(i)->flags() | Qt::ItemIsEditable);
    }
}

void MainWindow::on_pushButton_pressed()
{
    if (!list->size())
        return;
    list->sort([](const datavalue &a, const datavalue &b){return a.num < b.num;});
    vector->push_back(*list);
    if (list->size() > static_cast<size_t>(ui->tableWidget->columnCount()) || list->size() == 1)
    {
        ui->tableWidget->setColumnCount(list->size());
    }
    ui->tableWidget->setRowCount(vector->size());
    for (auto it = list->begin(); it != list->end(); ++it)
    {
        QString str = QString("%1").arg((*it).num);
        ui->tableWidget->setItem(vector->size()-1, std::distance(list->begin(), it), new QTableWidgetItem(str));
    }
    list->clear();
    ui->listWidget->clear();
    global_counter++;
}

int MainWindow::RosenbaumCriteria()
{
    if (vector->size() != 2)
    {
        QMessageBox msgBox;
        msgBox.setText("1.");
        msgBox.exec();
        return 0;
    }
    if (vector->at(0).size() < 11 || vector->at(1).size() < 11)
    {
        QMessageBox msgBox;
        msgBox.setText("2.");
        msgBox.exec();
        return 0;
    }
    if (vector->at(0).size() <= 50 && vector->at(1).size() <= 50 && abs(vector->at(0).size() - vector->at(1).size()) > 10)
    {
        QMessageBox msgBox;
        msgBox.setText("3.");
        msgBox.exec();
        return 0;
    }
    if (vector->at(0).size() > 50 && vector->at(0).size() <= 100 && vector->at(1).size() > 50 && vector->at(1).size() <= 100 && abs(vector->at(0).size() - vector->at(1).size()) > 20)
    {
        QMessageBox msgBox;
        msgBox.setText("4.");
        msgBox.exec();
        return 0;
    }
    if (vector->at(0).size() > 100 && vector->at(1).size() > 100 && ((float)vector->at(0).size() / (float)vector->at(1).size() < 0.5 || (float)vector->at(0).size() / (float)vector->at(1).size() > 2.0))
    {
        QMessageBox msgBox;
        msgBox.setText("5.");
        msgBox.exec();
        return 0;
    }
    double sum[2] = {0,0};
    int mainIndex = 0;
    for (size_t i = 0; i < vector->size(); i++)
    {
        for (auto it = vector->at(i).begin(); it != vector->at(i).end(); ++it)
        {
            sum[i] += (*it).num;
        }
    }
    if (sum[0] < sum[1])
    {
       mainIndex = 1;
    }
    double maxFromSideSet = (*std::max_element(vector->at(!mainIndex).begin(), vector->at(!mainIndex).end(), [](const datavalue &a, const datavalue &b){return a.num < b.num;})).num;
    int S1 = count_if(vector->at(mainIndex).begin(), vector->at(mainIndex).end(), [maxFromSideSet](const datavalue &a){return a.num > maxFromSideSet;});
    double minFromMainSet = (*std::min_element(vector->at(mainIndex).begin(), vector->at(mainIndex).end(), [](const datavalue &a, const datavalue &b){return a.num < b.num;})).num;
    int S2 = count_if(vector->at(!mainIndex).begin(), vector->at(!mainIndex).end(), [minFromMainSet](const datavalue &a){return a.num < minFromMainSet;});
    int Q = S1 + S2;
    QString str;
    str = QString("maxFromSideSet %1").arg(maxFromSideSet);
    ui->label->setText(str);
    str = QString("S1 %1").arg(S1);
    ui->label_2->setText(str);
    str = QString("minFromMainSet %1").arg(minFromMainSet);
    ui->label_3->setText(str);
    str = QString("S2 %1").arg(S2);
    ui->label_4->setText(str);
    str = QString("Q %1").arg(Q);
    ui->label_5->setText(str);

    return 1;
}

void MainWindow::on_pushButton_2_pressed()
{
    RosenbaumCriteria();
}
