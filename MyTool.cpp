#include <QPainter>
#include <ktabwidget.h>

#include <kdebug.h>
#include <klocale.h>

#include <KoCanvasBase.h>
#include <KoSelection.h>

#include "MyShape.h"

#include "MyTool.h"
//#include <MyTool.moc>

#include "dialogs/PartsWidget.h"

MyTool::MyTool( KoCanvasBase* canvas )
    : KoToolBase( canvas ),
      m_myshape(0),
      view (new QGraphicsView)
{
}

MyTool::~MyTool()
{
}

void MyTool::activate(ToolActivation toolActivation, const QSet<KoShape*> &shapes)
{
    Q_UNUSED(toolActivation);

    foreach (KoShape *shape, shapes) {
        m_myshape = dynamic_cast<MyShape*>( shape );
        if ( m_myshape )
            break;
    }
    if ( !m_myshape )
    {
        emit done();
        return;
    }
    emit shapeChanged(m_myshape);
    view->setScene(m_myshape->getScene());
//    useCursor(Qt::ArrowCursor);
}

void MyTool::deactivate()
{
  m_myshape = 0;
  view->setScene(0);
  emit shape_changed(0);
}

void MyTool::paint( QPainter& painter, const KoViewConverter& viewConverter )
{
    Q_UNUSED( painter );
    Q_UNUSED( viewConverter );
}

void MyTool::mousePressEvent( KoPointerEvent* )
{
}

void MyTool::mouseMoveEvent( KoPointerEvent* )
{
}

void MyTool::mouseReleaseEvent( KoPointerEvent* )
{
}

void MyTool::addCommand(KUndo2Command* command)
{
    canvas()->addCommand(command);
}


QWidget * MyTool::createOptionWidget()
{
    KTabWidget *widget = new KTabWidget();

    PartsWidget *pw = new PartsWidget(this, widget);
    widget->addTab(pw, i18n("Parts"));

    connect(this, SIGNAL(shapeChanged(MyShape*)), pw, SLOT(setShape(MyShape*)));

    if (m_myshape) pw->setShape(m_myshape);

    return widget;

}

MyShape* MyTool::shape()
{
    return m_myshape;
}
    
