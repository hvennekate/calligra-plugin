#ifndef MY_TOOL
#define MY_TOOL

#include <KoToolBase.h>
#include <QGraphicsView>
class MyShape;
class KUndo2Command;

class MyTool : public KoToolBase
{
  Q_OBJECT
public:
  explicit MyTool( KoCanvasBase* canvas );
  ~MyTool();

  virtual void paint( QPainter& painter, const KoViewConverter& converter ); // TODO Why paint here?

  virtual void mousePressEvent( KoPointerEvent* event ) ; // TODO
  virtual void mouseMoveEvent( KoPointerEvent* event ); // TODO
  virtual void mouseReleaseEvent( KoPointerEvent* event ); // TODO

    virtual void activate(ToolActivation toolActivation, const QSet<KoShape*> &shapes); // TODO
  void deactivate(); // TODO

  void addCommand(KUndo2Command* command); // TODO needed?
    MyShape* shape();
protected:
  /*
   * Create default option widget
   */
    virtual QWidget * createOptionWidget(); // TODO

protected Q_SLOTS:
Q_SIGNALS:
    void shapeChanged(MyShape* shape);
private:
   MyShape *m_myshape;
   QGraphicsView *view;
};

#endif
