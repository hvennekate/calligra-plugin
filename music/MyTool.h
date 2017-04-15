#ifndef MY_TOOL
#define MY_TOOL

#include <KoToolBase.h>
class MyShape;
class KUndo2Command;

class MyTool : public KoToolBase
{
  Q_OBJECT
public:
  explicit MyTool( KoCanvasBase* canvas );
  ~MyTool();

  virtual void paint( QPainter& painter, const KoViewConverter& converter );

  virtual void mousePressEvent( KoPointerEvent* event ) ;
  virtual void mouseMoveEvent( KoPointerEvent* event );
  virtual void mouseReleaseEvent( KoPointerEvent* event );

    virtual void activate(ToolActivation toolActivation, const QSet<KoShape*> &shapes);
  void deactivate();

  void addCommand(KUndo2Command* command);
    MyShape* shape();
protected:
  /*
   * Create default option widget
   */
    virtual QWidget * createOptionWidget();

protected Q_SLOTS:
Q_SIGNALS:
    void shapeChanged(MyShape* shape);
private:
   MyShape *m_musicshape;
};

#endif
