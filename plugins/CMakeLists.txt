project(plugins)

set(plasmoidplugin_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PlasmoidPlugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ApplicationLauncher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/QProcessWrapperImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ShortcutHandler.cpp
)

set(plasmoidplugin_DEPS
    Qt5::Quick KF5::Plasma KF5::ConfigCore KF5::GlobalAccel KF5::Package KF5::I18n
)

find_package(KF5Config)
find_package(KF5GlobalAccel)
find_package(KF5I18n)
find_package(KF5Package)

add_library(plasmoidplugin SHARED ${plasmoidplugin_SRCS})

target_link_libraries(plasmoidplugin ${plasmoidplugin_DEPS})

install(TARGETS plasmoidplugin DESTINATION ${QML_INSTALL_DIR}/dscheffer/krunnerplasmoidplugin)

install(FILES qmldir DESTINATION ${QML_INSTALL_DIR}/dscheffer/krunnerplasmoidplugin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(test_MAIN ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/tests/GTestWidget.cpp)

add_executable(applicationLauncherTest ${test_MAIN} ${CMAKE_CURRENT_SOURCE_DIR}/tests/ApplicationLauncherTest.cpp ${plasmoidplugin_SRCS})
target_link_libraries(applicationLauncherTest gmock ${Qt5Widgets_LIBRARIES} ${plasmoidplugin_DEPS} -lpthread -lm)

add_test(ApplicationLauncherTest applicationLauncherTest)
