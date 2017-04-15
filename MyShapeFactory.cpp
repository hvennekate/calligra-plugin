#include <QStringList>
#include <QFontDatabase>

#include <kpluginfactory.h>
#include <klocale.h>
#include <kdebug.h>
#include <kstandarddirs.h>
#include <KoIcon.h>
#include <KoToolRegistry.h>
#include <KoShapeRegistry.h>
#include <KoShapeLoadingContext.h>

#include "MyShape.h"
#include "MyToolFactory.h"
// #include "SimpleEntryToolFactory.h"

#include "MyShapeFactory.h"

K_PLUGIN_FACTORY(MyShapePluginFactory, registerPlugin<MyShapePlugin>();)
K_EXPORT_PLUGIN(MyShapePluginFactory( "calligra_shape_myshape" ))

MyShapePlugin::MyShapePlugin( QObject *,  const QVariantList& )
{
    KoShapeRegistry::instance()->add( new MyShapeFactory() );
    KoToolRegistry::instance()->add( new MyToolFactory() );
//     KoToolRegistry::instance()->add( new SimpleEntryToolFactory() );
}


MyShapeFactory::MyShapeFactory()
    : KoShapeFactoryBase(MyShapeId, i18n( "My Shape" ) )
{
    setToolTip( i18n( "A sample shape which provides no real editor" ) );
    setIconName(koIconNameCStrNeededWithSubs("icon for the My Shape","myshape", "my-note-16th"));
    setXmlElementNames( "http://www.calligra.org/my", QStringList("shape") );
    setLoadingPriority( 1 );
}

KoShape *MyShapeFactory::createDefaultShape(KoDocumentResourceManager *) const
{
    static bool loadedFont = false;
    MyShape* shape = new MyShape();
    shape->setSize(QSizeF(400, 300));
    shape->setShapeId(MyShapeId);
    return shape;
}

bool MyShapeFactory::supports(const KoXmlElement & e, KoShapeLoadingContext &context) const
{
    Q_UNUSED(context);
    return ( e.localName() == "shape" ) && ( e.namespaceURI() == "http://www.calligra.org/my" );
}
