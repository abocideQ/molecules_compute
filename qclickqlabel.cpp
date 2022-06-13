#include "qclickqlabel.h"
#include <QMouseEvent>

QClickQLabel::QClickQLabel(QWidget *parent): QLabel(parent)
{
    this->setAutoFillBackground(true);
    QFont font = this->font();
    font.setStyleStrategy(QFont::PreferAntialias);
    this->setFont(font);
}

QClickQLabel::QClickQLabel(const QString &text, QWidget *parent): QLabel(text, parent)
{
    this->setAutoFillBackground(true);
    QFont font = this->font();
    font.setStyleStrategy(QFont::PreferAntialias);
    this->setFont(font);
}

void QClickQLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton){
       emit clicked();
    }
}

void QClickQLabel::enterEvent(QEvent *)
{
    QPalette *palette = new QPalette;
    palette->setColor(QPalette::Background, QColor(0, 0, 0, 25));
    this->setPalette(*palette);
}

void QClickQLabel::leaveEvent(QEvent *)
{
    QPalette *palette = new QPalette;
    palette->setColor(QPalette::Background, Qt::white);
    this->setPalette(*palette);
}

