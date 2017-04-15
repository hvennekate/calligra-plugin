#include "MyShape.h"

#include <limits.h>

#include <QPainter>
#include <QBuffer>
#include <QByteArray>
#include <QSvgGenerator>

#include <kdebug.h>
#include <klocalizedstring.h>

#include <KoViewConverter.h>
#include <KoShapeSavingContext.h>
#include <KoXmlWriter.h>
#include <KoXmlReader.h>
#include <KoEmbeddedDocumentSaver.h>

#include <QDebug>
#include <molscene.h>
#include <molecule.h>
#include <atom.h>

//static MyShape* firstShape = 0;

using namespace Molsketch;

MyShape::MyShape()
    : KoFrameShape("http://www.calligra.org/my", "shape"),
      scene(new MolScene)
{
	Atom *a = new Atom(QPointF(0,0), "C"),
			*b = new Atom(QPointF(50,0), "C"),
			*c = new Atom(QPoint(0,50), "C"),
			*d = new Atom(QPointF(50,50),"Si");
	Molecule *m = new Molecule(QSet<Atom*>() << a << b << c << d,
				   QSet<Bond*>() << new Bond(a,b)
						 << new Bond(a,c)
						 << new Bond(b,d)
						 << new Bond(c,d));
	scene->addItem(m);
}

MyShape::~MyShape()
{
}

void MyShape::setSize( const QSizeF &newSize )
{
    KoShape::setSize(newSize);
}

void MyShape::paint( QPainter& painter, const KoViewConverter& converter, KoShapePaintingContext &)
{
    constPaint( painter, converter );
}

void MyShape::constPaint( QPainter& painter, const KoViewConverter& converter ) const
{
    applyConversion( painter, converter );

    painter.setClipping(true);
    QRectF drawingRect(0, 0, size().width(), size().height());
    painter.setClipRect(drawingRect, Qt::IntersectClip);

    qDebug() << "Painting: " << size();
//    painter.drawImage(QPoint(0,0), scene->renderImage(QRectF(0,0,50,50)));
    QRectF sceneRect;
    foreach (QGraphicsItem* item, scene->items()) // TODO this should be a scene function
    {
	sceneRect |= item->boundingRect();
    }
    scene->render(&painter, drawingRect, sceneRect);
}

void MyShape::saveOdf( KoShapeSavingContext & context ) const
{
//     // The name of this object in the ODF file.
//     KoEmbeddedDocumentSaver &fileSaver = context.embeddedSaver();
//     QString objectName = fileSaver.getFilename("Object");
// 
//     KoXmlWriter& writer = context.xmlWriter();
//     writer.startElement("draw:frame");
//     saveOdfAttributes(context, OdfAllAttributes);
// 
//     writer.startElement("music:shape");
//     writer.addAttribute("xmlns:music", "http://www.calligra.org/music");
// //     MyXmlWriter().writeSheet(writer, m_sheet, false);
//     writer.endElement(); // music:shape
// 
//     const qreal previewZoom = 150 / 72.; // 150 DPI
//     QSizeF imgSize = size(); // in points
//     imgSize *= previewZoom;
//     KoViewConverter converter;
//     
//     // Save a preview SVG image.
//     // -------------------------
// 
//     // 1. Set up the svg renderer.
//     QByteArray svgContents;           // The contents
//     QBuffer svgBuffer(&svgContents);  // The corresponding QIODevice
//     QSvgGenerator svg;
//     svg.setOutputDevice(&svgBuffer);  // Write to the buffer
//     svg.setSize(imgSize.toSize());
//     svg.setViewBox(QRect(0, 0, boundingRect().width(), boundingRect().height()));
//         
//     // 2. Paint the svg preview image.
//     //
//     // We need to create all text as paths, because otherwise it
//     // will be difficult for most people to preview the SVG
//     // image. Not many people have music fonts installed.
//     QPainter svgPainter;
//     svgPainter.begin(&svg);
//     svgPainter.setRenderHint(QPainter::Antialiasing);
//     svgPainter.setRenderHint(QPainter::TextAntialiasing);
// //     m_style->setTextAsPath(true);
//     constPaint(svgPainter, converter);
// //     m_style->setTextAsPath(false);
//     svgPainter.end();
// 
//     // 3. Create the xml to embed the svg image and the contents to the file.
//     writer.startElement("draw:image");
//     QString name = QString("ObjectReplacements/") + objectName + ".svg";
//     writer.addAttribute("xlink:type", "simple" );
//     writer.addAttribute("xlink:show", "embed" );
//     writer.addAttribute("xlink:actuate", "onLoad");
//     writer.addAttribute("xlink:href", name);
//     writer.endElement(); // draw:image
//     fileSaver.saveFile(name, "image/svg+xml", svgContents);
// 
//     // Save a preview bitmap image.
//     // ----------------------------
// 
//     // 1. Create the image.
//     QImage img(imgSize.toSize(), QImage::Format_ARGB32);
//     QPainter painter(&img);
//     painter.setRenderHint(QPainter::Antialiasing);
//     painter.setRenderHint(QPainter::TextAntialiasing);
//     converter.setZoom(previewZoom);
//     constPaint(painter, converter);
// 
//     // 2. Create the xml to embed the svg image and the contents to the file.
//     writer.startElement("draw:image");
//     name = context.imageHref(img);
//     // FIXME: Find out how to save a picture using the embeddedSaver and saveFile()
//     //name = QString("ObjectReplacements/") + objectName + ".png";
//     writer.addAttribute("xlink:type", "simple" );
//     writer.addAttribute("xlink:show", "embed" );
//     writer.addAttribute("xlink:actuate", "onLoad");
//     writer.addAttribute("xlink:href", name);
//     writer.endElement(); // draw:image
// 
//     saveOdfCommonChildElements(context);
//     writer.endElement(); // draw:frame
}

bool MyShape::loadOdf( const KoXmlElement & element, KoShapeLoadingContext &context ) {
    loadOdfAttributes(element, context, OdfAllAttributes);
    return loadOdfFrame(element, context);
}

MolScene *MyShape::getScene() const
{
	return scene;
}

bool MyShape::loadOdfFrameElement( const KoXmlElement & element, KoShapeLoadingContext & /*context*/ )
{
//     KoXmlElement score = KoXml::namedItemNS(element, "http://www.calligra.org/music", "score-partwise");
//     if (score.isNull()) {
//         kWarning() << "no music:score-partwise element as first child";
//         return false;
//     }
//     Sheet* sheet = MyXmlReader().loadSheet(score);
//     if (sheet) {
//         if (!m_predecessor && !m_successor) {
//             delete m_sheet;
//         }
//         m_sheet = sheet;
//         m_engraver->engraveSheet(m_sheet, m_firstSystem, size(), true, &m_lastSystem);
        return true;
//     }
//     return false;
}
