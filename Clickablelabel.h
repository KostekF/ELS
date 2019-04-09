#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickableLabel();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);
    void enterEvent(QEvent *ev) override
    {
        setStyleSheet("QLabel {  font: bold; }");
    }

    void leaveEvent(QEvent *ev) override
    {
        setStyleSheet("QLabel {  font: normal }");
    }

};

#endif // CLICKABLELABEL_H
