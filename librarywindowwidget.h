#ifndef LIBRARYWINDOWWIDGET_H
#define LIBRARYWINDOWWIDGET_H

#include <QWidget>

namespace Ui {
class libraryWindowWidget;
}

class libraryWindowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit libraryWindowWidget(QWidget *parent = 0);
    ~libraryWindowWidget();

private:
    Ui::libraryWindowWidget *ui;
};

#endif // LIBRARYWINDOWWIDGET_H
