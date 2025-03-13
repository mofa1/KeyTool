cmake_minimum_required(VERSION 3.16)

project(KeyTool VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Svg SerialPort Core Quick3D)

qt_standard_project_setup(REQUIRES 6.5)

set(CMAKE_AUTORCC ON)  # 加载QRC
qt_add_executable(appKeyTool
    main.cpp img_source.qrc
)

qt_add_qml_module(appKeyTool
    URI KeyTool
    VERSION 1.0
    QML_FILES
        Main.qml
    SOURCES winmsg.h
    SOURCES customizetitle.h customizetitle.cpp
    RESOURCES resource/GameToll/meshes/defaultobject_mesh.mesh
    RESOURCES resource/GameToll/meshes/___mesh.mesh
    QML_FILES resource/GameToll/GameToll.qml
    QML_FILES resource/GameToll/Keym.qml
    QML_FILES import_qm_file/window_qml/TitleBar.qml
    QML_FILES import_qm_file/app_qml/AppInterface.qml
    QML_FILES import_qm_file/app_qml/LeftToggle.qml
    QML_FILES import_qm_file/app_qml/ModelShow.qml
    QML_FILES import_qm_file/app_qml/BottomFunc.qml
    QML_FILES import_qm_file/app_qml/ConnectIndications.qml
    QML_FILES import_qm_file/app_qml/SetPage.qml
    QML_FILES import_qm_file/app_qml/BottomFunc_page/BFpage1.qml
    QML_FILES import_qm_file/app_qml/BottomFunc_page/BFpage1_keyshow.qml
    QML_FILES import_qm_file/app_qml/BottomFunc_page/BFpage2.qml
    QML_FILES import_qm_file/app_qml/BottomFunc_page/BFpage2_keyset.qml
    QML_FILES import_qm_file/app_qml/BottomFunc_page/ConversionTable.qml
    SOURCES myserial.h myserial.cpp
    SOURCES keymapping.h
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appKeyTool PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appKeyTool
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appKeyTool
    PRIVATE Qt6::Quick Qt6::Svg Qt6::SerialPort Qt6::Core Qt6::Quick3D
    dwmapi user32
)

include(GNUInstallDirs)
install(TARGETS appKeyTool
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
