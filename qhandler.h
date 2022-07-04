#ifndef QHANDLER_H
#define QHANDLER_H

#include <QObject>
#include <iostream>
#include <functional>
#include <QThread>
#include <vector>
#include "core/XYModel.h"

class qhandler: public QThread {
    Q_OBJECT
//public:
//    void post(std::vector<CoordinateModel> (*threadRunnable)(float,float, float,float) , void (*mainRunnable)());
//protected:
//    virtual void run() override;
//private:
//    std::vector<CoordinateModel> (*mThreadRunnable)(float,float, float,float);
//    void (*m_pMainRunable)();
//signals:
//    void callUi();
//private slots:
//    void runOnUi();
};

#endif // QHANDLER_H
