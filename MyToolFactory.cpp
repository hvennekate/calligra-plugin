#include "MyToolFactory.h"

#include "MyShape.h"
#include "MyTool.h"

#include <KoIcon.h>
#include <klocale.h>


MyToolFactory::MyToolFactory()
    : KoToolFactoryBase("MyToolFactoryId")
{
    setToolTip( i18n( "My editing, parts" ) );
    setIconName(koIconNameCStr("myshape"));
    setToolType( dynamicToolType() );
    setPriority( 2 );
    setActivationShapeId( MyShapeId );
}

MyToolFactory::~MyToolFactory()
{
}

KoToolBase* MyToolFactory::createTool( KoCanvasBase* canvas )
{
    return new MyTool( canvas );
}
