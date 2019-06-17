cmake_minimum_required (VERSION 2.8)
project (ScapeNet)
find_package (OpenCV REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/inc")

add_executable (ocr src/ocr.cpp)
target_link_libraries (ocr ${OpenCV_LIBS})

add_executable (mouse examples/mouse.cpp)
target_link_libraries (mouse ${OpenCV_LIBS} X11 Xtst)

add_executable (mini-map examples/mini-map.cpp)
target_link_libraries (mini-map ${OpenCV_LIBS})

add_executable (features examples/features.cpp)
target_link_libraries (features ${OpenCV_LIBS})

add_executable (health examples/health.cpp)
target_link_libraries (health ${OpenCV_LIBS})

add_executable (agent 
	src/main.cpp 
	src/control/mouse.cpp 
	src/control/keyboard.cpp
	src/client.cpp
	src/player.cpp
)
target_link_libraries (agent ${OpenCV_LIBS} pthread X11 Xtst)
