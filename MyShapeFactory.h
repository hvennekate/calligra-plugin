#ifndef MY_SHAPE_FACTORY
#define MY_SHAPE_FACTORY


#include <KoShapeFactoryBase.h>
#include <QVariantList>

class KoShape;

class MyShapePlugin : public QObject
{
    Q_OBJECT

public:

    MyShapePlugin( QObject * parent,  const QVariantList& );
    ~MyShapePlugin() {}

};

class MyShapeFactory : public KoShapeFactoryBase
{
public:
    MyShapeFactory();
    ~MyShapeFactory() {}

    virtual KoShape *createDefaultShape(KoDocumentResourceManager *documentResources = 0) const; // TODO
    virtual bool supports(const KoXmlElement & e, KoShapeLoadingContext &context) const; // TODO
};

#endif
