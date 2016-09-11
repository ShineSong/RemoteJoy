get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(APP_NAME ${DIR_NAME})
FILE(GLOB ${APP_NAME}_HDR *.h)
FILE(GLOB ${APP_NAME}_SRC *.cpp)
FILE(GLOB ${APP_NAME}_UIS *.ui)

qt5_wrap_ui(${APP_NAME}_UI ${${APP_NAME}_UIS})
qt5_wrap_cpp(${APP_NAME}_MOC ${${APP_NAME}_HDR})
add_executable(${APP_NAME} ${${APP_NAME}_SRC} ${${APP_NAME}_MOC} ${${APP_NAME}_UI} )
target_link_libraries(${APP_NAME} IWindows)

qt5_use_modules(${APP_NAME} Widgets Network)

if (WIN32)
    target_link_libraries(${APP_NAME} Qt5::WinMain )
endif()
