#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qclickqlabel.h"
#include "qcustomplot.h"
#include "brigde.h"

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
//    void initWidgetMenu();
    long double ENumber(std::string num_str);

private:
    Ui::MainWindow *ui;
    //top
    QWidget *m_pWidget_top;
    QClickQLabel *m_pLabel_file_x_a;
    QClickQLabel *m_pLabel_file_q;
    QClickQLabel *m_pLabel_build;
    //center
    QWidget *m_pWidget_center;
    QCustomPlot *m_pQCumstomPlot;
    //bottom
    QWidget *m_pWidget_bottom;
    QLabel *m_pLabel_data;
    //menu
    QMenu *m_pMenu_file;
    QAction *m_pAction_file_ground_state;
    QAction *m_pAction_file_excitation_state;
    QAction *m_pAction_file_a_ul;
    QMenu *m_pMenu_build;
    QAction *m_pAction_build;
    //core
    Brigde *m_pBrigde = new Brigde();

private slots:
    void on_qcustomplot_selection();//qcustomplot selection
    void on_menu_file_x_a();
    void on_menu_file_q();
    void on_menu_build();
//    void on_menu_file_show();//qmenu show
//    void on_menu_build_show();//qmenu show
//    void slot_action_triggered(QAction *action);//qmenu item click
};
#endif // MAINWINDOW_H
