#include "mainwindow.h"
#include "ui_mainwindow.h"

const short rosenbaum_p005[16][16] = {{6, 6, 6, 7, 7, 8, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8},
                              {6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8},
                              {6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8},
                              {7, 7, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8},
                              {7, 7, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8},
                              {8, 7, 7, 7, 6, 6, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8},
                              {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8},
                              {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8},
                              {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8},
                              {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 7, 8},
                              {8, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
                              {8, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
                              {8, 8, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
                              {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7},
                              {8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7, 7},
                              {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7}};

const short rosenbaum_p001[16][16] = {{9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 12, 12, 12},
                              {9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12},
                              {9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 11, 11, 11},
                              {9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 11},
                              {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10},
                              {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10},
                              {10, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10},
                              {10, 10, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10},
                              {10, 10, 10, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10},
                              {10, 10, 10, 10, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
                              {11, 10, 10, 10, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
                              {11, 11, 10, 10, 10, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
                              {11, 11, 10, 10, 10, 10, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
                              {12, 11, 11, 10, 10, 10, 10, 9, 9, 9, 9, 9, 9, 9, 9, 9},
                              {12, 11, 11, 10, 10, 10, 10, 10, 9, 9, 9, 9, 9, 9, 9, 9},
                              {12, 12, 11, 11, 10, 10, 10, 10, 10, 9, 9, 9, 9, 9, 9, 9}};

const short mann_witney_005[18][18] = {{0, 0, 1, 2, 2, 3, 4, 4, 5, 5, 6, 7, 7, 8, 9, 9, 10, 11},
                           {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 17, 18},
                           {1, 2, 4, 5, 6, 8, 9, 11, 12, 13, 15, 16, 18, 19, 20, 22, 23, 25},
                           {2, 3, 5, 7, 8, 10, 12, 14, 16, 17, 19, 21, 23, 25, 26, 28, 30, 32},
                           {2, 4, 6, 8, 11, 13, 15, 17, 19, 21, 24, 26, 28, 30, 33, 35, 37, 39},
                           {3, 5, 8, 10, 13, 15, 18, 20, 23, 26, 28, 31, 33, 36, 39, 41, 44, 47},
                           {4, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48, 51, 54},
                           {4, 7, 11, 14, 17, 20, 24, 27, 31, 34, 37, 41, 44, 48, 51, 55, 58, 62},
                           {5, 8, 12, 16, 19, 23, 27, 31, 34, 38, 42, 46, 50, 54, 57, 61, 65, 69},
                           {5, 9, 13, 17, 21, 26, 30, 34, 38, 42, 47, 51, 55, 60, 64, 68, 72, 77},
                           {6, 10, 15, 19, 24, 28, 33, 37, 42, 47, 51, 56, 61, 65, 70, 75, 80, 84},
                           {7, 11, 16, 21, 26, 31, 36, 41, 46, 51, 56, 61, 66, 71, 77, 82, 87, 92},
                           {7, 12, 18, 23, 28, 33, 39, 44, 50, 55, 61, 66, 72, 77, 83, 88, 94, 100},
                           {8, 14, 19, 25, 30, 36, 42, 48, 54, 60, 65, 71, 77, 83, 89, 95, 101, 107},
                           {9, 15, 20, 26, 33, 39, 45, 51, 57, 64, 70, 77, 83, 89, 96, 102, 109, 115},
                           {9, 16, 22, 28, 35, 41, 48, 55, 61, 68, 75, 82, 88, 95, 102, 109, 116, 123},
                           {10, 17, 23, 30, 37, 44, 51, 58, 65, 72, 80, 87, 94, 101, 109, 116, 123, 130},
                           {11, 18, 25, 32, 39, 47, 54, 62, 69, 77, 84, 92, 100, 107, 115, 123, 130, 138}};
const short mann_witney_001[18][18] = {{-1, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 5},
                               {-1, -1, 0, 1, 1, 2, 3, 3, 4, 5, 5, 6, 7, 7, 8, 9, 9, 10},
                               {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
                               {-1, 1, 2, 3, 4, 6, 7, 8, 9, 11, 12, 13, 15, 16, 18, 19, 20, 22},
                               {0, 1, 3, 4, 6, 7, 9, 11, 12, 14, 16, 17, 19, 21, 23, 24, 26, 28},
                               {0, 2, 4, 6, 7, 9, 11, 13, 15, 17, 20, 22, 24, 26, 28, 30, 32, 34},
                               {1, 3, 5, 7, 9, 11, 14, 16, 18, 21, 23, 26, 28, 31, 33, 36, 38, 40},
                               {1, 3, 6, 8, 11, 13, 16, 19, 22, 24, 27, 30, 33, 36, 38, 41, 44, 47},
                               {1, 4, 7, 9, 12, 15, 18, 22, 25, 28, 31, 34, 37, 41, 44, 47, 50, 53},
                               {2, 5, 8, 11, 14, 17, 21, 24, 28, 31, 35, 38, 42, 46, 49, 53, 56, 60},
                               {2, 5, 9, 12, 16, 20, 23, 27, 31, 35, 39, 43, 47, 51, 55, 59, 63, 67},
                               {2, 6, 10, 13, 17, 22, 26, 30, 34, 38, 43, 47, 51, 56, 60, 65, 69, 73},
                               {3, 7, 11, 15, 19, 24, 28, 33, 37, 42, 47, 51, 56, 61, 66, 70, 75, 80},
                               {3, 7, 12, 16, 21, 26, 31, 36, 41, 46, 51, 56, 61, 66, 71, 76, 82, 87},
                               {4, 8, 13, 18, 23, 28, 33, 38, 44, 49, 55, 60, 66, 71, 77, 82, 88, 93},
                               {4, 9, 14, 19, 24, 30, 36, 41, 47, 53, 59, 65, 70, 76, 82, 88, 94, 100},
                               {4, 9, 15, 20, 26, 32, 38, 44, 50, 56, 63, 69, 75, 82, 88, 94, 101, 107},
                               {5, 10, 16, 22, 28, 34, 40, 47, 53, 60, 67, 73, 80, 87, 93, 100, 107, 114}};

const float pirson[2][80] = {{3.842, 5.992, 7.815, 9.488, 11.071, 12.593, 14.068, 15.509, 16.921, 18.309, 19.677, 21.028, 22.365, 23.688, 24.999, 26.299, 27.591, 28.873, 30.147, 31.415, 32.675, 33.929, 35.177, 36.420, 37.658, 38.891, 40.119, 41.343, 42.564, 43.780, 44.993, 46.202, 47.408, 48.610, 49.810, 51.007, 52.201, 53.393, 54.582, 55.768, 56.953, 58.135, 59.314, 60.492, 61.668, 62.841, 64.013, 65.183, 66.351, 67.518, 68.683, 69.846, 71.008, 72.168, 73.326, 74.484, 75.639, 76.794, 77.947, 79.099, 80.232, 81.381, 82.529, 83.675, 84.821, 85.965, 87.108, 88.250, 89.391, 90.531, 91.670, 92.808, 93.945, 95.081, 96.217, 97.351, 99.617, 100.749, 101.879},
                     {6.635, 9.211, 11.346, 13.278, 15.088, 16.814, 18.478, 20.093, 21.669, 23.213, 24.729, 26.221, 27.693, 29.146, 30.583, 32.006, 33.415, 34.812, 36.198, 37.574, 38.940, 40.298, 41.647, 42.989, 44.324, 45.652, 46.973, 48.289, 49.599, 50.904, 52.203, 53.498, 54.789, 56.074, 57.356, 58.634, 59.907, 61.177, 62.444, 63.707, 64.967, 66.224, 67.477, 68.728, 69.976, 71.221, 72.463, 73.703, 74.940, 76.175, 77.408, 78.638, 79.866, 81.092, 82.316, 83.538, 84.758, 85.976, 87.192, 88.406, 89.591, 90.802, 92.010, 93.217, 94.422, 95.626, 96.828, 98.028, 99.227, 100.425, 101.621, 102.816, 104.010, 105.202, 106.393, 107.582, 109.958, 111.144, 112.329}};

const short jonkir_005[4][9] = {{10, 17, 24, 33, 42, 53, 64, 76, 88},
                             {14, 26, 38, 51, 66, 82, 100, 118, 138},
                             {20, 34, 51, 71, 92, 115, 140, 166, 194},
                             {26, 44, 67, 93, 121, 151, 184, 219, 256}};
const short jonkir_001[4][9] = {{-1, 23, 32, 45, 59, 74, 90, 106, 124},
                              {20, 34, 50, 71, 92, 115, 140, 167, 195},
                              {26, 48, 72, 99, 129, 162, 197, 234, 274},
                              {34, 62, 94, 130, 170, 213, 260, 309, 361}};

bool compareVec(const std::list<datavalue> &a, const std::list<datavalue> &b)
{
    float sumA (0), sumB (0);
    for (auto it = a.begin(); it != a.end(); ++it)
    {
        sumA += it->num;
    }
    for (auto it = b.begin(); it != b.end(); ++it)
    {
        sumB += it->num;
    }
    return sumA < sumB;
}

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
    ui->doubleSpinBox->setMaximum(100000);
    ui->doubleSpinBox->clear();
    ui->doubleSpinBox->setFocus();
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
        it->num = item->text().toFloat();
    }
}

void MainWindow::on_doubleSpinBox_editingFinished()
{
    if (ui->doubleSpinBox->cleanText() == "")
        return;
    ui->listWidget->addItem(ui->doubleSpinBox->cleanText());
    datavalue temp = { ui->doubleSpinBox->value(), global_counter, 0, 0};
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
    if (list->size() > static_cast<size_t>(ui->tableWidget->columnCount()) || vector->size() == 1)
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
    ui->doubleSpinBox->setFocus();
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
            sum[i] += it->num;
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
    int Q001, Q005;
    if (vector->at(0).size() > 26 || vector->at(1).size() > 26)
    {
        Q001 = 10;
        Q005 = 8;
    }
    else
    {
        Q001 = rosenbaum_p001[vector->at(0).size() - 11][vector->at(1).size() - 11];
        Q005 = rosenbaum_p005[vector->at(0).size() - 11][vector->at(1).size() - 11];
    }
    QString str;
    str = QString("%1").arg(Q);
    ui->lineEdit->setText(str);
    str = QString("%1").arg(Q005);
    ui->lineEdit_2->setText(str);
    str = QString("%1").arg(Q001);
    ui->lineEdit_3->setText(str);

    return 1;
}

void MainWindow::on_pushButton_2_pressed()
{
    RosenbaumCriteria();
}

int MainWindow::MannWhitney()
{
    if (vector->size() != 2)
    {
        QMessageBox msgBox;
        msgBox.setText("1.");
        msgBox.exec();
        return 0;
    }
    if (vector->at(0).size() < 3 || vector->at(1).size() < 3)
    {
        QMessageBox msgBox;
        msgBox.setText("2.");
        msgBox.exec();
        return 0;
    }
    if (vector->at(0).size() > 20 || vector->at(1).size() > 20)
    {
        QMessageBox msgBox;
        msgBox.setText("3.");
        msgBox.exec();
        return 0;
    }
    std::list<datavalue> first(vector->at(0));
    std::list<datavalue> second(vector->at(1));
    first.merge(second);

    float summ[2] = {0,0};
    unsigned int mainIndex = 0;
    unsigned int sideIndex = 0;
    for (size_t i = 0; i < vector->size(); i++)
    {
        for (auto it = vector->at(i).begin(); it != vector->at(i).end(); ++it)
        {
            summ[i] += it->num;
        }
    }
    if (summ[0] < summ[1])
    {
       mainIndex = (*vector->at(1).begin()).set_number;
       sideIndex = (*vector->at(0).begin()).set_number;
    }
    else
    {
       mainIndex = (*vector->at(0).begin()).set_number;
       sideIndex = (*vector->at(1).begin()).set_number;
    }

    RangeValues(first);

    double sumranks[2] = {0,0};
    unsigned int maincount (0);
    unsigned int sidecount (0);
    for (auto it = first.begin(); it != first.end(); it++)
    {
        if (it->set_number == mainIndex)
        {
            sumranks[0] += it->rank;
            maincount++;
        }
        else if ((*it).set_number == sideIndex)
        {
            sumranks[1] += it->rank;
            sidecount++;
        }
    }
    float U;
    if (sumranks[0] > sumranks[1])
    {
        U = maincount*sidecount + (maincount*(maincount + 1))/2 - sumranks[0];
    }
    else
    {
        U = maincount*sidecount + (sidecount*(sidecount + 1))/2 - sumranks[1];
    }


    int U_crit_005 = mann_witney_005[maincount-3][sidecount-3];
    int U_crit_001 = mann_witney_001[maincount-3][sidecount-3];

    QString str;
    str = QString("%1").arg(U);
    ui->lineEdit_4->setText(str);
    str = QString("%1").arg(U_crit_001);
    ui->lineEdit_5->setText(str);
    str = QString("%1").arg(U_crit_005);
    ui->lineEdit_6->setText(str);

    return 0;
}

void MainWindow::on_pushButton_3_pressed()
{
    MannWhitney();
}

int MainWindow::KruskalWallis()
{
    if (vector->size() < 3)
    {
        QMessageBox msgBox;
        msgBox.setText("1.");
        msgBox.exec();
        return 0;
    }
    for (size_t i = 0; i < vector->size(); i++)
    {
        if (vector->at(i).size() < 3)
        {
            QMessageBox msgBox;
            msgBox.setText("2.");
            msgBox.exec();
            return 0;
        }
    }

    std::vector<std::list<datavalue>> *vec = new std::vector<std::list<datavalue>>(*vector);
    std::list<datavalue> temp;
    for (auto &x : *vec)
    {
        temp.merge(x);
    }
    vec->clear();

    RangeValues(temp);
    temp.sort([](const datavalue &a, const datavalue &b){return a.set_number < b.set_number;});
    int i (0);
    for (auto it = temp.begin(); it != temp.end(); ++it)
    {
        if (it->set_number != std::next(it, 1)->set_number || it == temp.end())
        {

            std::list<datavalue> temp(std::prev(it, i), std::next(it, 1));
            vec->push_back(temp);
            i = 0;
            continue;
        }
        i++;
    }

    float *ranksSum = new float[vec->size()];
    float sum (0);
    for (size_t i = 0; i < vec->size(); i++)
    {
        for (auto it = vec->at(i).begin(); it != vec->at(i).end(); ++it)
        {
            sum += it->rank;
        }
        ranksSum[i] = sum;
        sum = 0;
    }

    float partialSum (0);
    for (size_t i = 0; i < vec->size(); i++)
    {
        partialSum += ranksSum[i]*ranksSum[i]/vec->at(i).size();
    }

    float H_criteria = (12.0f/(temp.size()*(temp.size()+1)))*partialSum - 3*(temp.size()+1);
    float H_005 = pirson[0][vec->size()-2];
    float H_001 = pirson[1][vec->size()-2];

    QString str;
    str = QString("%1").arg(H_criteria);
    ui->lineEdit_7->setText(str);
    str = QString("%1").arg(H_005);
    ui->lineEdit_8->setText(str);
    str = QString("%1").arg(H_001);
    ui->lineEdit_9->setText(str);
    delete [] ranksSum;
    delete vec;
    return 0;

}

void MainWindow::on_pushButton_4_pressed()
{
    KruskalWallis();
}

int MainWindow::Jonkir()
{
    if (vector->size() < 3)
    {
        QMessageBox msgBox;
        msgBox.setText("1.");
        msgBox.exec();
        return 0;
    }

    std::vector<std::list<datavalue>> * vec = new std::vector<std::list<datavalue>> (*vector);
    size_t min = vec->at(0).size();
    for (size_t i = 0; i < vec->size(); i++)
    {
        min = std::min(min, vec->at(i).size());
    }
    std::default_random_engine generator;
    for (size_t i = 0; i < vec->size(); i++)
    {
        size_t diff = vec->at(i).size() - min;
        for (size_t j = 0; j < diff; j++)
        {
            std::uniform_int_distribution<int> distribution(0, vec->at(i).size());
            vec->at(i).erase(std::next(vec->at(i).begin(), distribution(generator)));
        }
    }

    std::sort(vec->begin(), vec->end(), compareVec);
    for (size_t i = 0; i < vec->size() - 1; i++)
    {
        for (auto it1 = vec->at(i).begin(); it1 != vec->at(i).end(); ++it1)
        {
            for (size_t j = i + 1; j < vec->size(); j++)
            {
                for (auto it2 = vec->at(j).begin(); it2 != vec->at(j).end(); ++it2)
                {
                    if(it2->num > it1->num)
                    {
                        it1->jonkir_count++;
                    }
                }
            }
        }
    }

    unsigned int jonkirSum (0);
    for (size_t i = 0; i < vec->size() - 1; i++)
    {
        for (auto it = vec->at(i).begin(); it != vec->at(i).end(); it++)
        {
            jonkirSum += it->jonkir_count;
        }
    }
    unsigned int maxJonkirSum = vec->size() * (vec->size() - 1) / 2 * vec->at(0).size() * vec->at(0).size();

    unsigned int S_emp = 2 * jonkirSum - maxJonkirSum;
    int S_005 = jonkir_005[vec->size()-2][vec->at(0).size()-3];
    int S_001 = jonkir_001[vec->size()-2][vec->at(0).size()-3];

    QString str;
    str = QString("%1").arg(S_emp);
    ui->lineEdit_10->setText(str);
    str = QString("%1").arg(S_005);
    ui->lineEdit_11->setText(str);
    str = QString("%1").arg(S_001);
    ui->lineEdit_12->setText(str);

    delete vec;
    return 0;
}

void MainWindow::on_pushButton_5_pressed()
{
    Jonkir();
}

void MainWindow::RangeValues(std::list<datavalue> &list)
{
    int i (0), k (1);
    float sum (0);
    for (auto it = list.begin(); it != list.end(); it++)
    {
        i++;
        if (it != list.end() && it->num == std::next(it, 1)->num)
        {
            k++;
        }
        else if (k != 1 && (it == list.end() || it->num != std::next(it, 1)->num))
        {
            for (int j = 0; j < k; j++)
            {
                sum += i-j;
            }
            sum /= k;
            for (int j = 0; j < k; j++)
            {
                std::prev(it, j)->rank = sum;
            }
            sum = 0;
            k = 1;
        }
        else
        {
            it->rank = i;
        }
    }
}
