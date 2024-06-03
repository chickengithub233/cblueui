

set(CBLUEUI_FOUND TRUE)

if(0)
  find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core Multimedia REQUIRED)
  if(QT_FOUND)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Multimedia REQUIRED)
  endif()
endif()

if(0)
  find_package(wxWidgets CONFIG COMPONENTS core base REQUIRED)
  message("wxWidgets_USE_FILE=${wxWidgets_USE_FILE}")
  message("wxWidgets_LIBRARIES=${wxWidgets_LIBRARIES}")
  message("wxWidgets_INCLUDE_DIRS=${wxWidgets_INCLUDE_DIRS}")
endif()

include("${CMAKE_CURRENT_LIST_DIR}/CBlueUITargets.cmake")
