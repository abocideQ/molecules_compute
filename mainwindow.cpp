#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    //ui
    ui->setupUi(this);
    this->setWindowTitle("? Chart");
    ui->menubar->setPalette(QPalette(Qt::white));
    ui->menubar->setAutoFillBackground(true);
    ui->statusbar->setPalette(QPalette(Qt::white));
    ui->statusbar->setAutoFillBackground(true);
    ui->centralwidget->setPalette(QPalette(Qt::white));
    ui->centralwidget->setAutoFillBackground(true);
    //widget
    initWidgetTop();
    initWidgetCenter();
    initWidgetBottom();
    initWidgetMenu();
    //addwidget
    QGridLayout *layout_root = new QGridLayout();
    ui->centralwidget->setLayout(layout_root);
    layout_root->addWidget(m_pWidget_top, 0, 0);
    layout_root->addWidget(m_pWidget_center, 1, 0);
    layout_root->addWidget(m_pWidget_bottom, 2, 0);
    //信号槽
    connect(m_pQCumstomPlot, &QCustomPlot::selectionChangedByUser, this, &MainWindow::on_qcustomplot_selection);
}

void MainWindow::initWidgetTop(){
    m_pWidget_top = new QWidget();
    m_pWidget_top->setMaximumHeight(36);
    QHBoxLayout *layout_top = new QHBoxLayout(m_pWidget_top);
    //    layout_top->setSizeConstraint(QLayout::SetMaximumSize);
    //    layout_top->setMargin(10);
    //    layout_top->setSpacing(0);
    m_pLabel_file_basic = new QClickQLabel("基态");
    m_pLabel_file_basic->setMinimumWidth(60);
    m_pLabel_file_basic->setMaximumHeight(36);
    m_pLabel_file_basic->setAlignment(Qt::AlignmentFlag::AlignCenter);
    m_pLabel_file_excitation = new QClickQLabel("激发态");
    m_pLabel_file_excitation->setMinimumWidth(60);
    m_pLabel_file_excitation->setMaximumHeight(36);
    m_pLabel_file_excitation->setAlignment(Qt::AlignmentFlag::AlignCenter);
    m_pLabel_file_aul = new QClickQLabel("Aul");
    m_pLabel_file_aul->setMinimumWidth(60);
    m_pLabel_file_aul->setMaximumHeight(36);
    m_pLabel_file_aul->setAlignment(Qt::AlignmentFlag::AlignCenter);
    m_pLabel_build = new QClickQLabel("构建");
    m_pLabel_build->setMinimumWidth(60);
    m_pLabel_build->setMaximumHeight(36);
    m_pLabel_build->setAlignment(Qt::AlignmentFlag::AlignCenter);
    layout_top->addWidget(m_pLabel_file_basic);
    layout_top->addWidget(m_pLabel_file_excitation);
    layout_top->addWidget(m_pLabel_file_aul);
    layout_top->addWidget(m_pLabel_build);
    layout_top->addSpacerItem(new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Fixed));
    //信号槽
    connect(m_pLabel_file_basic, &QClickQLabel::clicked, this, &MainWindow::on_menu_file_show);
    connect(m_pLabel_build, &QClickQLabel::clicked, this, &MainWindow::on_menu_build_show);
}

void MainWindow::initWidgetCenter(){
    m_pWidget_center = new QWidget();
    QGridLayout *layout_center = new QGridLayout(m_pWidget_center);
    m_pQCumstomPlot = new QCustomPlot;
    m_pQCumstomPlot->clearGraphs();
    m_pQCumstomPlot->addGraph();
    // 1、轴拖动 2、轴缩放 3、图可选 4、 多选
    m_pQCumstomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    //    m_pQCumstomPlot->setMultiSelectModifier(Qt::KeyboardModifier::ControlModifier);
    //    m_pQCumstomPlot->setSelectionRectMode(QCP::SelectionRectMode::srmSelect);
    // 数据点显示图案
    m_pQCumstomPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ScatterShape::ssDisc, 5));
    m_pQCumstomPlot->graph(0)->setSelectable(QCP::SelectionType::stMultipleDataRanges);
    // 设置颜色/宽度等
    QPen *pen = new QPen;
    pen->setWidth(1);
    pen->setColor(Qt::red);
    m_pQCumstomPlot->graph(0)->setPen(*pen);
    // 设置x轴，y轴 label
    m_pQCumstomPlot->xAxis->setLabel("x");
    m_pQCumstomPlot->yAxis->setLabel("y");
    // 设置图形中的数据m_x和m_y是两个QVector容器
    QVector<double> m_x(1000), m_y(1000);
    for (int i = 0; i < 251; ++i)
    {
        m_x[i] = i;
        m_y[i] = qExp(-i/150.0) * qCos(i/10.0);
    }
    m_pQCumstomPlot->graph(0)->setData(m_x, m_y);
    m_pQCumstomPlot->graph(0)->rescaleAxes();
    // 刷新m_CustomPlot中数据
    m_pQCumstomPlot->replot();
    layout_center->addWidget(m_pQCumstomPlot, 0, 0);
}

void MainWindow::initWidgetBottom(){
    m_pWidget_bottom = new QWidget();
    m_pWidget_bottom->setMaximumHeight(40);
    QGridLayout *layout_bottom = new QGridLayout(m_pWidget_bottom);
    m_pLabel_data = new QLabel("g:g, x:x, y:y, t:t, e,e, .....数据");
    m_pLabel_data->setMaximumHeight(40);
    m_pLabel_data->setAlignment(Qt::AlignmentFlag::AlignCenter);
    layout_bottom->addWidget(m_pLabel_data, 0, 0);
}

void MainWindow::initWidgetMenu()
{
    m_pMenu_file = new QMenu();
    m_pAction_file_ground_state = new QAction("基态文件");
    m_pAction_file_excitation_state = new QAction("激发态文件");
    m_pAction_file_a_ul = new QAction("Aul文件");
    m_pMenu_file->addAction(m_pAction_file_ground_state);
    m_pMenu_file->addAction(m_pAction_file_excitation_state);
    m_pMenu_file->addAction(m_pAction_file_a_ul);
    m_pMenu_build = new QMenu();
    m_pAction_build = new QAction("开始构建");
    m_pMenu_build->addAction(m_pAction_build);
    connect(m_pMenu_file, &QMenu::triggered, this, &MainWindow::slot_action_triggered);
    connect(m_pMenu_build, &QMenu::triggered, this, &MainWindow::slot_action_triggered);
}

//qcustomplot 数据点选择回调
void MainWindow::on_qcustomplot_selection()
{
    for(int i=0;i<m_pQCumstomPlot->graphCount();i++)
    {
        //遍历有被选中的graph
        if(m_pQCumstomPlot->graph(i)->selected())
        {
            QCPDataSelection selection =m_pQCumstomPlot->graph(i)->selection();
            //遍历选中范围
            for(int j=0;j<selection.dataRangeCount();j++)
            {
                QCPDataRange dataRange = selection.dataRange(j);
                //遍历数据
                for(int k=dataRange.begin();k<dataRange.end();k++)
                {
                    QString str_key = QString::number(m_pQCumstomPlot->graph(i)->data()->at(k)->key);
                    QString str_value = QString::number(m_pQCumstomPlot->graph(i)->data()->at(k)->value);
                    QString str_at= QString::number(i);
                    //text
                    m_pLabel_data->setText("x=" + str_key + ", y=" + str_value);
                }
            }
        }
    }
}

void MainWindow::on_menu_file_show()
{
    //    QWidget *pwindow = this->window();
    //    int x = pwindow->geometry().x() + 10;
    //    int y = pwindow->geometry().y() + 30;
    //    QPoint pos(x, y);
    //    m_pMenu_file->exec(pos);
    //    m_pMenu_file->popup(cursor().pos());
}

void MainWindow::on_menu_build_show()
{
    //    QWidget *pwindow = this->window();
    //    int x = pwindow->geometry().x() + m_pLabel_file_basic->width() + 18;
    //    int y = pwindow->geometry().y() + 30;
    //    QPoint pos(x, y);
    //    m_pMenu_build->exec(pos);
    //    m_pMenu_build->popup(cursor().pos());
}

void MainWindow::slot_action_triggered(QAction *action)
{
    if(action == m_pAction_file_ground_state)
    {
        QString fileName = QFileDialog::getOpenFileName(this,"基态文件","C:/","All files(*.*)");
    }
    else if(action == m_pAction_file_excitation_state)
    {
        QString fileName = QFileDialog::getOpenFileName(this,"激发态文件","C:/","All files(*.*)");
    }
    else if(action == m_pAction_file_a_ul)
    {
        QString fileName = QFileDialog::getOpenFileName(this,"Aul文件","C:/","All files(*.*)");
    }
    else if(action == m_pAction_build)
    {

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

