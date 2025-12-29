cmake_minimum_required(VERSION 3.16)

project(QtTelemetryDashboard VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Quick
    WebSockets
)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appQtTelemetryDashboard
    src/main.cpp
)

qt_add_qml_module(appQtTelemetryDashboard
    URI QtTelemetryDashboard
    VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
    QML_FILES
        qml/Main.qml
        qml/screens/DashboardScreen.qml
        qml/screens/ErrorScreen.qml
        qml/components/TelemetryCard.qml
        qml/components/StatusBar.qml
    SOURCES
        src/app/AppController.cpp
        src/app/AppController.h
        src/app/AppState.h src/app/AppState.cpp
        src/models/TelemetryModel.h src/models/TelemetryModel.cpp
        src/models/TelemetryItem.h
        src/services/TelemetryService.h src/services/TelemetryService.cpp
        src/services/ConnectionService.h src/services/ConnectionService.cpp
        src/utils/Logger.h src/utils/Logger.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appQtTelemetryDashboard PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appQtTelemetryDashboard
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appQtTelemetryDashboard
    PRIVATE Qt6::Quick
    PRIVATE Qt6::WebSockets
)

include(GNUInstallDirs)
install(TARGETS appQtTelemetryDashboard
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
