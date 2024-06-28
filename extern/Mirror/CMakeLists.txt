cmake_minimum_required(VERSION 3.15)
project("Mirror" LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SCRIPTX_BACKEND V8)

#add_subdirectory(ScriptX)

set(V8_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/v8/win64/include")

include(ScriptX/CMakeLists.txt)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/v8/win64/include/"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/v8)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/v8/win64/dll/"
        DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/v8/win64/v8.dll.lib
    ${CMAKE_CURRENT_SOURCE_DIR}/v8/win64/v8_libbase.dll.lib
    ${CMAKE_CURRENT_SOURCE_DIR}/v8/win64/v8_libplatform.dll.lib
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)