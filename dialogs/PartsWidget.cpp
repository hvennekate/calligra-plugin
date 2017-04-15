#include "PartsWidget.h"

#include "../MyTool.h"
#include "../MyShape.h"

#include <KoIcon.h>

#include <QToolBar>
#include <actions/drawaction.h>
#include <molscene.h>

PartsWidget::PartsWidget(MyTool *tool, QWidget *parent)
    : QWidget(parent),
    m_tool(tool)
{
    widget.setupUi(this);

    widget.addPart->setIcon(koIcon("list-add"));
    widget.removePart->setIcon(koIcon("list-remove"));
    widget.editPart->setIcon(koIcon("document-properties"));

    connect(widget.partsList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(partDoubleClicked(QModelIndex)));
    //connect(widget.partsList, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(selectionChanged(QListWidgetItem*,QListWidgetItem*)));
    connect(widget.addPart, SIGNAL(clicked()), this, SLOT(addPart()));
    connect(widget.removePart, SIGNAL(clicked()), this, SLOT(removePart()));
    connect(widget.editPart, SIGNAL(clicked()), this, SLOT(editPart()));

    QToolBar *bar = new QToolBar(this);
    widget.hboxlayout->addWidget(bar);
    draw = new Molsketch::drawAction(0);
    bar->addAction(draw);
}

void PartsWidget::setShape(MyShape* shape)
{
    m_shape = shape;
    draw->setParent(shape->getScene());
}

void PartsWidget::partDoubleClicked(const QModelIndex & index)
{
    int row = index.row();
}

void PartsWidget::selectionChanged(const QModelIndex& current, const QModelIndex& prev)
{
    Q_UNUSED( prev );
    widget.editPart->setEnabled(current.isValid());
    widget.removePart->setEnabled(current.isValid());
}

void PartsWidget::addPart()
{
//     m_tool->addCommand(new AddPartCommand(m_shape));
}

void PartsWidget::removePart()
{
//     Part* part = m_sheet->part(widget.partsList->currentIndex().row());

//     m_tool->addCommand(new RemovePartCommand(m_shape, part));
}

void PartsWidget::editPart()
{
//     int row = widget.partsList->currentIndex().row();
//     PartDetailsDialog::showDialog(m_tool, m_sheet->part(row), this);
}

//#include <PartsWidget.moc>
