#ifndef MY_SHAPE
#define MY_SHAPE

#include <KoShape.h>
#include <KoFrameShape.h>

#define MyShapeId "MyShape"

namespace Molsketch {
	class MolScene;
}

class MyShape : public KoShape, public KoFrameShape
{
public:
    MyShape();
    virtual ~MyShape();
    /// reimplemented
    virtual void paint( QPainter& painter, const KoViewConverter& converter, KoShapePaintingContext &paintcontext); // TODO reimplement
    void constPaint( QPainter& painter, const KoViewConverter& converter ) const; // TODO really needed?

    /// reimplemented
    virtual void setSize( const QSizeF &newSize ); // TODO options: a) keep resolution constant and reveal/hide scene, or b) keep view excerpt constant and change resolution

    /// reimplemented
    virtual void saveOdf( KoShapeSavingContext & context ) const; // TODO -> xml
    // reimplemented
    virtual bool loadOdf( const KoXmlElement & element, KoShapeLoadingContext &context ); //TOOD -> xml

    Molsketch::MolScene* getScene() const;
protected:
    // reimplemented
    virtual bool loadOdfFrameElement( const KoXmlElement & element, KoShapeLoadingContext & context ); // TODO ???
private:
    Molsketch::MolScene *scene;
};


#endif // MUSIC_SHAPE
