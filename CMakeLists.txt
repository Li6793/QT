cmake_minimum_required(VERSION 3.16)

project(Clementine VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Network
    Sql
    SerialPort
)


set(OUTPUT_ROOT ${CMAKE_SOURCE_DIR}/output)

if(WIN32)
    set(PLATFORM_DIR "windows")
elseif(UNIX AND NOT APPLE)
    set(PLATFORM_DIR "linux")
elseif(APPLE)
    set(PLATFORM_DIR "macos")
endif()


if(DEFINED CMAKE_BUILD_TYPE AND NOT CMAKE_BUILD_TYPE STREQUAL "")
    set(BUILD_TYPE_DIR ${CMAKE_BUILD_TYPE})
else()

    set(BUILD_TYPE_DIR "release")
endif()

set(OUTPUT_DIR ${OUTPUT_ROOT}/${PLATFORM_DIR}/${BUILD_TYPE_DIR})


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib)


set(SOURCES
    main.cpp
    clementine.cpp
)

set(HEADERS
    clementine.h
)

set(UIS
    clementine.ui
)

set(RESOURCES

)


qt_add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UIS}
    ${RESOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
    Qt6::Sql
    Qt6::SerialPort
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)




function(qt_deploy_target target)
    if(WIN32)
        find_program(WINDEPLOYQT_EXE windeployqt
            HINTS
                "C:/Qt/6.9.2/msvc2022_64/bin"
                "${QT_BIN_DIR}"
                "$ENV{QTDIR}/bin"
        )
        if(WINDEPLOYQT_EXE)
            # message(STATUS "找到64位windeployqt: ${WINDEPLOYQT_EXE}")

            if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR
               (DEFINED CMAKE_CONFIGURATION_TYPES AND "Debug" IN_LIST CMAKE_CONFIGURATION_TYPES))
                set(DEPLOY_MODE --debug)
                # message(STATUS "64位Debug模式：部署带d后缀的Qt库")
            else()
                set(DEPLOY_MODE --release)
                # message(STATUS "64位Release模式：部署不带d后缀的Qt库")
            endif()

            add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${WINDEPLOYQT_EXE}
                    --verbose 1
                    ${DEPLOY_MODE}
                    --no-compiler-runtime
                    --dir $<TARGET_FILE_DIR:${target}>
                    $<TARGET_FILE:${target}>
                VERBATIM
                COMMENT "64位Qt依赖部署完成：$<TARGET_FILE_DIR:${target}>"
            )
        else()
            message(FATAL_ERROR "未找到64位windeployqt，请检查Qt 64位版本是否安装")
        endif()
    endif()
endfunction()


qt_deploy_target(${PROJECT_NAME})


