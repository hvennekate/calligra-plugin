#ifndef PARTSWIDGET_H
#define PARTSWIDGET_H

#include <ui_PartsWidget.h>

#include <QWidget>

class MyTool;
class MyShape;
class QAction;

class PartsWidget : public QWidget {
    Q_OBJECT
public:
    explicit PartsWidget(MyTool *tool, QWidget *parent = 0);

public Q_SLOTS:
    void setShape(MyShape* shape);
private Q_SLOTS:
    void partDoubleClicked(const QModelIndex & index);
    void selectionChanged(const QModelIndex& current, const QModelIndex& prev);
    void addPart();
    void removePart();
    void editPart();
private:
    Ui::PartsWidget widget;
    MyTool *m_tool;
    MyShape *m_shape;
    QAction *draw;
};

#endif // PARTSWIDGET_H
