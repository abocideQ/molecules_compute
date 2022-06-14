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
    m_pLabel_file_x_a = new QClickQLabel("X & A");
    m_pLabel_file_x_a->setMinimumWidth(60);
    m_pLabel_file_x_a->setMaximumHeight(36);
    m_pLabel_file_x_a->setAlignment(Qt::AlignmentFlag::AlignCenter);
    m_pLabel_file_q = new QClickQLabel("Q");
    m_pLabel_file_q->setMinimumWidth(60);
    m_pLabel_file_q->setMaximumHeight(36);
    m_pLabel_file_q->setAlignment(Qt::AlignmentFlag::AlignCenter);
    m_pLabel_build = new QClickQLabel("构建");
    m_pLabel_build->setMinimumWidth(60);
    m_pLabel_build->setMaximumHeight(36);
    m_pLabel_build->setAlignment(Qt::AlignmentFlag::AlignCenter);
    layout_top->addWidget(m_pLabel_file_x_a);
    layout_top->addWidget(m_pLabel_file_q);
    layout_top->addWidget(m_pLabel_build);
    layout_top->addSpacerItem(new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Fixed));
    //信号槽
    connect(m_pLabel_file_x_a, &QClickQLabel::clicked, this, &MainWindow::on_menu_file_x_a);
    connect(m_pLabel_file_q, &QClickQLabel::clicked, this, &MainWindow::on_menu_file_q);
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

void MainWindow::on_menu_file_x_a()
{
    try {
        bool ret_ok;
        //A态
        QString file_1_g = QInputDialog::getText(this, tr("A态名称"),tr("请输入A态的名称"), QLineEdit::Normal, 0, &ret_ok);
        if (!ret_ok || file_1_g.isEmpty()){
            return;
        }
        float file_1_t = QInputDialog::getText(this, tr("A态跃迁值"),tr("请输入A态的跃迁值Te（请输入数字）"), QLineEdit::Normal, 0, &ret_ok).toFloat();
        if (!ret_ok || file_1_t < 0){
            return;
        }
        QString file_1_url = QFileDialog::getOpenFileName(this, "请选择A态文件", "", "All files(*.*)");
        if (file_1_url.isEmpty()){
            return;
        }
        qDebug()<< file_1_url;
        //B态
        QString file_2_g = QInputDialog::getText(this, tr("B态名称"),tr("请输入B态的名称"), QLineEdit::Normal,0, &ret_ok);
        if (!ret_ok || file_2_g.isEmpty()){
            return;
        }
        float file_2_t = QInputDialog::getText(this, tr("B态跃迁值"),tr("请输入B态的跃迁值T（请输入数字）"), QLineEdit::Normal,0, &ret_ok).toFloat();
        if (!ret_ok || file_2_t < 0){
            return;
        }
        QString file_2_url = QFileDialog::getOpenFileName(this, "请选择B态文件", "", "All files(*.*)");
        if (file_2_url.isEmpty()){
            return;
        }
        qDebug()<< file_2_url;
        //Aul
        QString file_a_url = QFileDialog::getOpenFileName(this, "选择Aul文件", "", "All files(*.*)");
        if (file_a_url.isEmpty()){
            return;
        }
        //save
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
                                file_a_url_char);
    } catch (QException e) {
        qDebug("%s", e.what());
    }
}

void MainWindow::on_menu_file_q()
{
    try {
        while(1){
            bool ret_ok;
            //A态
            QString file_q_g = QInputDialog::getText(this, tr("X态名称"),tr("请输入X态的名称"), QLineEdit::Normal, 0, &ret_ok);
            if (!ret_ok || file_q_g.isEmpty()){
                goto __Exit;
            }
            float file_q_Te = QInputDialog::getText(this, tr("X态跃迁值"),tr("请输入X态的跃迁值Te（请输入数字）"), QLineEdit::Normal, 0, &ret_ok).toFloat();
            if (!ret_ok || file_q_Te < 0){
                return;
            }
            QString file_q_url = QFileDialog::getOpenFileName(this, "请选择A态文件", "", "All files(*.*)");
            if (file_q_url.isEmpty()){
                goto __Exit;
            }
            //常量h
            long double const_h = 0;
            string const_h_str = QInputDialog::getText(this, tr("常量h"),tr("请输入常量h(例 11或1.1E±1)"), QLineEdit::Normal, 0, &ret_ok).toStdString();
            if (!ret_ok || const_h_str.empty()){
                goto __Exit;
            }
            const_h = ENumber(const_h_str);
            qDebug()<< "h: " << QString::number(const_h, 2, 50);
            //常量c
            long double const_c = 0;
            string const_c_str = QInputDialog::getText(this, tr("常量c"),tr("请输入常量c(例 11或1.1E±1)"), QLineEdit::Normal, 0, &ret_ok).toStdString();
            if (!ret_ok || const_c_str.empty()){
                goto __Exit;
            }
            const_c = ENumber(const_c_str);
            //常量K
            long double const_K = 0;
            string const_K_str = QInputDialog::getText(this, tr("常量K"),tr("请输入常量K(例 11或1.1E±1)"), QLineEdit::Normal, 0, &ret_ok).toStdString();
            if (!ret_ok || const_K_str.empty()){
                goto __Exit;
            }
            const_K = ENumber(const_K_str);
            //Tex Tvib Trot
            float const_Tssss = QInputDialog::getText(this, tr("温度"),tr("请输入温度（请输入数字）"), QLineEdit::Normal, 0, &ret_ok).toFloat();
            if (!ret_ok || const_Tssss < 0){
                return;
            }
            //gne
            float const_gne = QInputDialog::getText(this, tr("偶数时的值"),tr("请输入偶数时的值(gne)"), QLineEdit::Normal, 0, &ret_ok).toFloat();
            if (!ret_ok || const_gne < 0){
                return;
            }
            //gno
            float const_gno = QInputDialog::getText(this, tr("奇数时的值"),tr("请输入奇数时的值(gno)"), QLineEdit::Normal, 0, &ret_ok).toFloat();
            if (!ret_ok || const_gno < 0){
                return;
            }
            //gbase
            float const_gbase = QInputDialog::getText(this, tr("gj倍数"),tr("请输入gj倍数"), QLineEdit::Normal, 0, &ret_ok).toFloat();
            if (!ret_ok || const_gbase < 0){
                return;
            }
            QByteArray bytes = file_q_url.toLocal8Bit();//.toLatin1().data() 无效
            char *file_url_char = new char[1024];
    //        memcpy(file_url_char, bytes.data(), bytes.size()+1);  //存放结束符
            strcpy(file_url_char ,bytes.data());
            m_pBrigde->add_q_info(file_q_g.toStdString(), file_q_Te, file_url_char,
                                  const_h, const_c, const_K, const_Tssss, const_Tssss,const_Tssss,
                                  const_gne, const_gno, const_gbase);
            qDebug()<< "c: " << QString::number(const_c, 10, 50);
        }
        __Exit:
         qDebug()<< "done";
    } catch (QException e) {
        qDebug("%s", e.what());
    }
}

void MainWindow::on_menu_build()
{
    vector<XModel> vec_x = m_pBrigde->compute_x_a();
    //x & a
    QVector<double> m_x(vec_x.size()), m_y(vec_x.size());
    for (size_t i = 0; i < vec_x.size(); i++)
    {
        m_x[i] = vec_x[i].x;
        m_y[i] = vec_x[i].x;
    }
    m_pQCumstomPlot->graph(0)->setData(m_x, m_y);
    m_pQCumstomPlot->graph(0)->rescaleAxes();
    m_pQCumstomPlot->replot();
    //Q
    m_pBrigde->compute_q();
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

//void MainWindow::initWidgetMenu()
//{
//    m_pMenu_file = new QMenu();
//    m_pAction_file_ground_state = new QAction("基态文件");
//    m_pAction_file_excitation_state = new QAction("激发态文件");
//    m_pAction_file_a_ul = new QAction("Aul文件");
//    m_pMenu_file->addAction(m_pAction_file_ground_state);
//    m_pMenu_file->addAction(m_pAction_file_excitation_state);
//    m_pMenu_file->addAction(m_pAction_file_a_ul);
//    m_pMenu_build = new QMenu();
//    m_pAction_build = new QAction("开始构建");
//    m_pMenu_build->addAction(m_pAction_build);
//    connect(m_pMenu_file, &QMenu::triggered, this, &MainWindow::slot_action_triggered);
//    connect(m_pMenu_build, &QMenu::triggered, this, &MainWindow::slot_action_triggered);
//}

//void MainWindow::on_menu_file_show()
//{
//    //    QWidget *pwindow = this->window();
//    //    int x = pwindow->geometry().x() + 10;
//    //    int y = pwindow->geometry().y() + 30;
//    //    QPoint pos(x, y);
//    //    m_pMenu_file->exec(pos);
//    //    m_pMenu_file->popup(cursor().pos());
//}

//void MainWindow::on_menu_build_show()
//{
//    //    QWidget *pwindow = this->window();
//    //    int x = pwindow->geometry().x() + m_pLabel_file_basic->width() + 18;
//    //    int y = pwindow->geometry().y() + 30;
//    //    QPoint pos(x, y);
//    //    m_pMenu_build->exec(pos);
//    //    m_pMenu_build->popup(cursor().pos());
//}

//void MainWindow::slot_action_triggered(QAction *action)
//{
//    if(action == m_pAction_file_ground_state)
//    {
//        QString fileName = QFileDialog::getOpenFileName(this,"基态文件","C:/","All files(*.*)");
//    }
//    else if(action == m_pAction_file_excitation_state)
//    {
//        QString fileName = QFileDialog::getOpenFileName(this,"激发态文件","C:/","All files(*.*)");
//    }
//    else if(action == m_pAction_file_a_ul)
//    {
//        QString fileName = QFileDialog::getOpenFileName(this,"Aul文件","C:/","All files(*.*)");
//    }
//    else if(action == m_pAction_build)
//    {

//    }
//}
