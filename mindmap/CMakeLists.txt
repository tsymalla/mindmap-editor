# CMakeList.txt: CMake-Projekt für "mindmap". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE INCLUDES "includes/*.hpp")
SOURCE_GROUP(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${INCLUDES})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES "src/*.cpp")
SOURCE_GROUP(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (mindmap ${INCLUDES} ${SOURCES})

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
