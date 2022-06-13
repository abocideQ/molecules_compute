#ifndef CLICKQLABEL_H
#define CLICKQLABEL_H

#include <QWidget>
#include <QLabel>

class QClickQLabel : public QLabel
{
    Q_OBJECT

public:
    explicit  QClickQLabel(QWidget *parent = 0);
    QClickQLabel(const QString &text, QWidget *parent=0);

protected:
    void mouseReleaseEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

signals:
    void clicked();
};

#endif // CLICKQLABEL_H
