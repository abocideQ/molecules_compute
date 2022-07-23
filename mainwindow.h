#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qclickqlabel.h"
#include "qcustomplot.h"
#include "brigde.h"
#include "qhandler.h"
#include <thread>
#include <QApplication>
#include <QtConcurrent/QtConcurrent>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void initWidgetTop();
    void initWidgetCenter();
    void initWidgetBottom();

private:
    Ui::MainWindow *ui;
    //top
    QWidget *m_pWidget_top;
    QClickQLabel *m_pLabel_file_Temperature;
    QClickQLabel *m_pLabel_file_Q;
    QClickQLabel *m_pLabel_file_Xul_Aul;
    QClickQLabel *m_pLabel_distribution_test;
    QClickQLabel *m_pLabel_baisc_build;
    QClickQLabel *m_pLabel_baisc_export;
    QClickQLabel *m_pLabel_build;
    //center
    QWidget *m_pWidget_center;
    QCustomPlot *m_pQCumstomPlot;
    //bottom
    QWidget *m_pWidget_bottom;
    QLabel *m_pLabel_data;
    //core
    Brigde *m_pBrigde = new Brigde();

    long double ENumber(std::string num_str);

private slots:
    void on_qcustomplot_selection();//qcustomplot selection
    void on_menu_file_Temperature();
    void on_menu_file_Xul_Aul();
    void on_menu_file_Q();
    void on_menu_distribution_test();
    void on_menu_basic_build();
    void on_menu_basic_export();
    void on_menu_build();
};
#endif // MAINWINDOW_H
