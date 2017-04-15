#include <QPainter>
#include <ktabwidget.h>

#include <kdebug.h>
#include <klocale.h>

#include <KoCanvasBase.h>
#include <KoSelection.h>

#include "MyShape.h"

#include "MyTool.h"
#include <MyTool.moc>

#include "dialogs/PartsWidget.h"

MyTool::MyTool( KoCanvasBase* canvas )
    : KoToolBase( canvas ),
      m_musicshape(0)
{
}

MyTool::~MyTool()
{
}

void MyTool::activate(ToolActivation toolActivation, const QSet<KoShape*> &shapes)
{
    Q_UNUSED(toolActivation);
    //kDebug() ;

    foreach (KoShape *shape, shapes) {
        m_musicshape = dynamic_cast<MyShape*>( shape );
        if ( m_musicshape )
            break;
    }
    if ( !m_musicshape )
    {
        emit done();
        return;
    }
    emit shapeChanged(m_musicshape);
    useCursor(Qt::ArrowCursor);
}

void MyTool::deactivate()
{
  m_musicshape = 0;
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

    if (m_musicshape) pw->setShape(m_musicshape);

    return widget;

}

MyShape* MyTool::shape()
{
    return m_musicshape;
}
    
