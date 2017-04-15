#ifndef MYSIC_TOOL_FACTORY
#define MYSIC_TOOL_FACTORY


#include <KoToolFactoryBase.h>

class MyToolFactory : public KoToolFactoryBase
{
public:
    MyToolFactory();
    ~MyToolFactory();

    KoToolBase* createTool( KoCanvasBase* canvas );
};


#endif 
