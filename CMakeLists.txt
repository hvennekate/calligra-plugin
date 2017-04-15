
## CMake
cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)
if(${CMAKE_VERSION} VERSION_GREATER 2.8.3)
    cmake_policy(SET CMP0017 NEW)
endif()

if(${CMAKE_VERSION} VERSION_GREATER 2.8.12)
    cmake_policy(SET CMP0022 OLD)
endif()

if(${CMAKE_VERSION} VERSION_GREATER 3.0.0)
    cmake_policy(SET CMP0026 OLD)
    cmake_policy(SET CMP0046 OLD)
endif()

## KDE
set(KDE_MIN_VERSION "4.3.0")
find_package(KDE4 4.3.0 REQUIRED)

find_package(Qt4 4.6.0 REQUIRED QtCore QtGui QtXml QtScript QtSvg QtTest QtWebKit QtDBus)

include_directories(/usr/include/QtCore /usr/include/Qt /usr/include/QtGui /usr/include/QtSvg /usr/include/QtXml ~/calligra/install/include/calligra ~/calligra/calligra-2.9.11/libs/flake ~/calligra/calligra-2.9.11)

link_directories(~/calligra/install/lib64)

include (KDE4Defaults)
include (MacroLibrary)
include (MacroAdditionalCleanFiles)
include (MacroAddFileDependencies)



## actual plugin
include_directories(
    ${FLAKE_INCLUDES}
)

########### Flake Plugin library ###############

set (myshape_LIB_SRCS
    MyShape.cpp
    MyShapeFactory.cpp
    MyTool.cpp
    MyToolFactory.cpp
    
    dialogs/PartsWidget.cpp
)

kde4_add_ui_files(myshape_LIB_SRCS
    dialogs/PartsWidget.ui
)

kde4_add_plugin(calligra_shape_myshape ${myshape_LIB_SRCS})

target_link_libraries(calligra_shape_myshape flake ${KDE4_KFILE_LIBS})
install(TARGETS calligra_shape_myshape DESTINATION ${PLUGIN_INSTALL_DIR})

########### install files ###############

install( FILES calligra_shape_myshape.desktop DESTINATION ${SERVICES_INSTALL_DIR}/calligra)
kde4_install_icons( ${DATA_INSTALL_DIR}/calligra/icons )
