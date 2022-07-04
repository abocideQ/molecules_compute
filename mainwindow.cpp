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
    //    initWidgetMenu();
    //addwidget
    QGridLayout *layout_root = new QGridLayout();
    ui->centralwidget->setLayout(layout_root);
    layout_root->addWidget(m_pWidget_top, 0, 0);
    layout_root->addWidget(m_pWidget_center, 1, 0);
    layout_root->addWidget(m_pWidget_bottom, 2, 0);
}

void MainWindow::initWidgetTop(){
    m_pWidget_top = new QWidget();
    m_pWidget_top->setMaximumHeight(36);
    QHBoxLayout *layout_top = new QHBoxLayout(m_pWidget_top);
    //    layout_top->setSizeConstraint(QLayout::SetMaximumSize);
    //    layout_top->setMargin(10);
    //    layout_top->setSpacing(0);
    m_pLabel_file_Q = new QClickQLabel("Q");
    m_pLabel_file_Q->setMinimumWidth(80);
    m_pLabel_file_Q->setMaximumHeight(36);
    m_pLabel_file_Q->setAlignment(Qt::AlignmentFlag::AlignCenter);
    m_pLabel_file_Xul_Aul = new QClickQLabel("λul & Aul");
    m_pLabel_file_Xul_Aul->setMinimumWidth(80);
    m_pLabel_file_Xul_Aul->setMaximumHeight(36);
    m_pLabel_file_Xul_Aul->setAlignment(Qt::AlignmentFlag::AlignCenter);
    m_pLabel_distribution_test = new QClickQLabel("分布数据");
    m_pLabel_distribution_test->setMinimumWidth(80);
    m_pLabel_distribution_test->setMaximumHeight(36);
    m_pLabel_distribution_test->setAlignment(Qt::AlignmentFlag::AlignCenter);
    m_pLabel_baisc_build = new QClickQLabel("基准数据");
    m_pLabel_baisc_build->setMinimumWidth(80);
    m_pLabel_baisc_build->setMaximumHeight(36);
    m_pLabel_baisc_build->setAlignment(Qt::AlignmentFlag::AlignCenter);
    m_pLabel_build = new QClickQLabel("Build");
    m_pLabel_build->setMinimumWidth(80);
    m_pLabel_build->setMaximumHeight(36);
    m_pLabel_build->setAlignment(Qt::AlignmentFlag::AlignCenter);
    layout_top->addWidget(m_pLabel_file_Q);
    layout_top->addWidget(m_pLabel_file_Xul_Aul);
    layout_top->addWidget(m_pLabel_distribution_test);
    layout_top->addWidget(m_pLabel_baisc_build);
    layout_top->addWidget(m_pLabel_build);
    layout_top->addSpacerItem(new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Fixed));
    //信号槽
    connect(m_pLabel_file_Q, &QClickQLabel::clicked, this, &MainWindow::on_menu_file_Q);
    connect(m_pLabel_file_Xul_Aul, &QClickQLabel::clicked, this, &MainWindow::on_menu_file_Xul_Aul);
    connect(m_pLabel_distribution_test, &QClickQLabel::clicked, this, &MainWindow::on_menu_distribution_test);
    connect(m_pLabel_baisc_build, &QClickQLabel::clicked, this, &MainWindow::on_menu_basic_build);
    connect(m_pLabel_build, &QClickQLabel::clicked, this, &MainWindow::on_menu_build);
}

void MainWindow::initWidgetCenter(){
    m_pWidget_center = new QWidget();
    QGridLayout *layout_center = new QGridLayout(m_pWidget_center);
    m_pQCumstomPlot = new QCustomPlot;
    m_pQCumstomPlot->clearGraphs();
    m_pQCumstomPlot->addGraph();
    // 1、轴拖动 2、轴缩放 3、图可选 4、 多选
    m_pQCumstomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    // 数据点显示图案
    m_pQCumstomPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ScatterShape::ssDisc, 3));
    m_pQCumstomPlot->graph(0)->setSelectable(QCP::SelectionType::stMultipleDataRanges);
    // 设置颜色/宽度等
    QPen *pen = new QPen;
    pen->setWidth(1);
    pen->setColor(Qt::red);
    m_pQCumstomPlot->graph(0)->setPen(*pen);
    // 设置x轴，y轴 label
    m_pQCumstomPlot->xAxis->setLabel("x");
    m_pQCumstomPlot->yAxis->setLabel("y");
    layout_center->addWidget(m_pQCumstomPlot, 0, 0);
    //信号槽
    connect(m_pQCumstomPlot, &QCustomPlot::selectionChangedByUser, this, &MainWindow::on_qcustomplot_selection);
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

void MainWindow::on_menu_file_Q()
{
    try {
        while(1){
            bool ret_ok;
            //A态
            QString file_q_g = QInputDialog::getText(this, tr("态名称"), tr("请输入名称"), QLineEdit::Normal, 0, &ret_ok);
            if (!ret_ok || file_q_g.isEmpty()){
                goto __Exit;
            }
            float file_q_Te = QInputDialog::getText(this, file_q_g , "请输入跃迁值", QLineEdit::Normal, 0, &ret_ok).toFloat();
            if (!ret_ok || file_q_Te < 0){
                return;
            }
            QString file_q_url = QFileDialog::getOpenFileName(this, file_q_g + "文件", "", "All files(*.*)");
            if (file_q_url.isEmpty()){
                goto __Exit;
            }
            //gne
            float const_gne = QInputDialog::getText(this, file_q_g, tr("请输入偶数时的值gne"), QLineEdit::Normal, 0, &ret_ok).toFloat();
            if (!ret_ok || const_gne < 0){
                goto __Exit;
            }
            //gno
            float const_gno = QInputDialog::getText(this, file_q_g, tr("请输入奇数时的值gno"), QLineEdit::Normal, 0, &ret_ok).toFloat();
            if (!ret_ok || const_gno < 0){
                goto __Exit;
            }
            //gbase
            float const_gbase = QInputDialog::getText(this, file_q_g, tr("请输入gj倍数"), QLineEdit::Normal, 0, &ret_ok).toFloat();
            if (!ret_ok || const_gbase < 0){
                goto __Exit;
            }
            //常量h
            long double const_h = 6.63 * pow(10, -34);
            //常量c
            long double const_c = 2.99792458 * pow(10, 10);
            //常量K
            long double const_K = (1.38 * pow(10, -23));
            //Tex Tvib Trot
            float const_Tssss = QInputDialog::getText(this, "温度", tr("请输入温度"), QLineEdit::Normal, 0, &ret_ok).toFloat();
            if (!ret_ok || const_Tssss < 0){
                goto __Exit;
            }
            //======================save
            QByteArray bytes = file_q_url.toLocal8Bit();//.toLatin1().data() 无效
            char *file_url_char = new char[1024];
            //        memcpy(file_url_char, bytes.data(), bytes.size()+1);  //存放结束符
            strcpy(file_url_char ,bytes.data());
            m_pBrigde->add_q_info(file_q_g.toStdString(), file_q_Te, file_url_char,
                                  const_h, const_c, const_K, const_Tssss, const_Tssss,const_Tssss,
                                  const_gne, const_gno, const_gbase);
        }
__Exit:
        qDebug()<< "done";
    } catch (QException e) {
        qDebug("%s", e.what());
    }
}

void MainWindow::on_menu_file_Xul_Aul()
{
    try {
        bool ret_ok;
        //A态
        QString file_1_g = QInputDialog::getText(this, tr("低能态"),tr("请输入名称"), QLineEdit::Normal, 0, &ret_ok);
        if (!ret_ok || file_1_g.isEmpty()){
            return;
        }
        float file_1_t = QInputDialog::getText(this, tr("低能态"),tr("请输入跃迁值"), QLineEdit::Normal, 0, &ret_ok).toFloat();
        if (!ret_ok || file_1_t < 0){
            return;
        }
        QString file_1_url = QFileDialog::getOpenFileName(this, "低能态文件", "", "All files(*.*)");
        if (file_1_url.isEmpty()){
            return;
        }
        qDebug()<< file_1_url;
        //B态
        QString file_2_g = QInputDialog::getText(this, tr("高能态"),tr("请输入名称"), QLineEdit::Normal,0, &ret_ok);
        if (!ret_ok || file_2_g.isEmpty()){
            return;
        }
        float file_2_t = QInputDialog::getText(this, tr("高能态"),tr("请输入跃迁值"), QLineEdit::Normal,0, &ret_ok).toFloat();
        if (!ret_ok || file_2_t < 0){
            return;
        }
        QString file_2_url = QFileDialog::getOpenFileName(this, "高能态文件", "", "All files(*.*)");
        if (file_2_url.isEmpty()){
            return;
        }
        qDebug()<< file_2_url;
        //gne
        float const_gne = QInputDialog::getText(this, tr("高能态"),tr("请输入偶数时的值gne"), QLineEdit::Normal, 0, &ret_ok).toFloat();
        if (!ret_ok || const_gne < 0){
            return;
        }
        //gno
        float const_gno = QInputDialog::getText(this, tr("高能态"),tr("请输入奇数时的值gno"), QLineEdit::Normal, 0, &ret_ok).toFloat();
        if (!ret_ok || const_gno < 0){
            return;
        }
        //gbase
        float const_gbase = QInputDialog::getText(this, tr("高能态"),tr("请输入gj倍数"), QLineEdit::Normal, 0, &ret_ok).toFloat();
        if (!ret_ok || const_gbase < 0){
            return;
        }
        //常量h
        long double const_h = 6.63 * pow(10, -34);
        //常量c
        long double const_c = 2.99792458 * pow(10, 10);
        //常量K
        long double const_K = (1.38 * pow(10, -23));
        //Aul
        QString file_a_url = QFileDialog::getOpenFileName(this, "请选择Aul文件", "", "All files(*.*)");
        if (file_a_url.isEmpty()){
            return;
        }
        //Tex Tvib Trot
        float const_Tssss = QInputDialog::getText(this, tr("温度"),tr("请输入温度"), QLineEdit::Normal, 0, &ret_ok).toFloat();
        if (!ret_ok || const_Tssss < 0){
            return;
        }
        //======================save
        QByteArray bytes_1 = file_1_url.toLocal8Bit();//.toLatin1().data() 无效
        QByteArray bytes_2 = file_2_url.toLocal8Bit();
        QByteArray bytes_a = file_a_url.toLocal8Bit();
        char *file_1_url_char = new char[1024];
        char *file_2_url_char = new char[1024];
        char *file_a_url_char = new char[1024];
        //        memcpy(file_1_url_char, bytes_1.data(), bytes_1.size()+1);  //存放结束符
        //        memcpy(file_2_url_char, bytes_2.data(), bytes_2.size()+1);
        //        memcpy(file_a_url_char, bytes_a.data(), bytes_a.size()+1);
        strcpy(file_1_url_char ,bytes_1.data());
        strcpy(file_2_url_char ,bytes_2.data());
        strcpy(file_a_url_char ,bytes_a.data());
        m_pBrigde->set_x_a_info(file_1_g.toStdString(),
                                file_1_t,
                                file_1_url_char,
                                file_2_g.toStdString(),
                                file_2_t,
                                file_2_url_char,
                                const_h, const_c, const_K,
                                const_Tssss, const_Tssss,const_Tssss,
                                const_gne, const_gno, const_gbase,
                                file_a_url_char);
    } catch (QException e) {
        qDebug("%s", e.what());
    }
}

void MainWindow::on_menu_distribution_test()
{
    // 曲线测试
    vector<CoordinateModel> vec_coordinate = vector<CoordinateModel>();
    std::thread t(&ComputePlot::computTestPlots, ComputePlot(), 14.0f, 15000, &vec_coordinate);
    t.join();
    // plot
    QVector<double> m_x(vec_coordinate.size()), m_y(vec_coordinate.size());
    for (size_t i = 0; i < vec_coordinate.size(); i++)
    {
        m_x[i] = vec_coordinate[i].x;
        m_y[i] = vec_coordinate[i].y;
    }
    m_pQCumstomPlot->graph(0)->setData(m_x, m_y);
    m_pQCumstomPlot->graph(0)->rescaleAxes();
    m_pQCumstomPlot->replot();
}

void MainWindow::on_menu_basic_build()
{
    //基准测试
    std::thread t(&Brigde::compute, m_pBrigde, 0, 100, 0.1, 14);
    t.join();
    vector<CoordinateModel> vec_coordinate = m_pBrigde->getBasicData();
    // plot
    QVector<double> m_x(vec_coordinate.size()), m_y(vec_coordinate.size());
    for (size_t i = 0; i < vec_coordinate.size(); i++)
    {
        m_x[i] = vec_coordinate[i].x;
        m_y[i] = vec_coordinate[i].y;
    }
    m_pQCumstomPlot->graph(0)->setData(m_x, m_y);
    m_pQCumstomPlot->graph(0)->rescaleAxes();
    m_pQCumstomPlot->replot();
}

void MainWindow::on_menu_build()
{

    // compute
    bool ret_ok;
    float min = QInputDialog::getText(this, tr("min"),tr("min"), QLineEdit::Normal, 0, &ret_ok).toFloat();
    if (!ret_ok || min < 0){
        return;
    }
    float max = QInputDialog::getText(this, tr("max"),tr("max"), QLineEdit::Normal, 0, &ret_ok).toFloat();
    if (!ret_ok || max < 0){
        return;
    }
    std::thread t(&Brigde::compute, m_pBrigde, min, max, 0.02, 14);
    t.join();
    vector<CoordinateModel> vec_coordinate = m_pBrigde->getData();
    // plot
    QVector<double> m_x(vec_coordinate.size()), m_y(vec_coordinate.size());
    for (size_t i = 0; i < vec_coordinate.size(); i++)
    {
        m_x[i] = vec_coordinate[i].x;
        m_y[i] = vec_coordinate[i].y;
    }
    m_pQCumstomPlot->graph(0)->setData(m_x, m_y);
    m_pQCumstomPlot->graph(0)->rescaleAxes();
    m_pQCumstomPlot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//科学计数法
long double MainWindow::ENumber(std::string num_str){
    long double ret_ = 0;
    int index_E_base = 1;
    int index_E = -1;
    if (num_str.find("E-") != num_str.npos) {
        index_E_base = -1;
        index_E = num_str.find("E-");
    } else if (num_str.find("E+") != num_str.npos){
        index_E_base = 1;
        index_E = num_str.find("E+");
    }
    if (index_E == -1){
        ret_ = std::stold(num_str);
        return ret_;
    }
    std::string num_a = num_str.substr(0, index_E);
    std::string num_b = num_str.substr(index_E + 2, num_str.length() - (index_E + 2));
    ret_ = std::stold(num_a) * (std::pow(10, index_E_base * std::stoi(num_b)));
    return ret_;
}
