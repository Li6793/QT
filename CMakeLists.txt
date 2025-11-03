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

include_directories(include)


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
    Icons.qrc
    output/windows/Debug/bin/generic/qtuiotouchplugind.dll output/windows/Debug/bin/iconengines/qsvgicond.dll output/windows/Debug/bin/imageformats/qgifd.dll output/windows/Debug/bin/imageformats/qicnsd.dll output/windows/Debug/bin/imageformats/qicod.dll output/windows/Debug/bin/imageformats/qjpegd.dll output/windows/Debug/bin/imageformats/qpdfd.dll output/windows/Debug/bin/imageformats/qsvgd.dll output/windows/Debug/bin/imageformats/qtgad.dll output/windows/Debug/bin/imageformats/qtiffd.dll output/windows/Debug/bin/imageformats/qwbmpd.dll output/windows/Debug/bin/imageformats/qwebpd.dll output/windows/Debug/bin/networkinformation/qnetworklistmanagerd.dll output/windows/Debug/bin/platforms/qwindowsd.dll output/windows/Debug/bin/styles/qmodernwindowsstyled.dll output/windows/Debug/bin/tls/qcertonlybackendd.dll output/windows/Debug/bin/tls/qschannelbackendd.dll output/windows/Debug/bin/translations/qt_ar.qm output/windows/Debug/bin/translations/qt_bg.qm output/windows/Debug/bin/translations/qt_ca.qm output/windows/Debug/bin/translations/qt_cs.qm output/windows/Debug/bin/translations/qt_da.qm output/windows/Debug/bin/translations/qt_de.qm output/windows/Debug/bin/translations/qt_en.qm output/windows/Debug/bin/translations/qt_es.qm output/windows/Debug/bin/translations/qt_fa.qm output/windows/Debug/bin/translations/qt_fi.qm output/windows/Debug/bin/translations/qt_fr.qm output/windows/Debug/bin/translations/qt_gd.qm output/windows/Debug/bin/translations/qt_he.qm output/windows/Debug/bin/translations/qt_hr.qm output/windows/Debug/bin/translations/qt_hu.qm output/windows/Debug/bin/translations/qt_it.qm output/windows/Debug/bin/translations/qt_ja.qm output/windows/Debug/bin/translations/qt_ka.qm output/windows/Debug/bin/translations/qt_ko.qm output/windows/Debug/bin/translations/qt_lg.qm output/windows/Debug/bin/translations/qt_lv.qm output/windows/Debug/bin/translations/qt_nl.qm output/windows/Debug/bin/translations/qt_nn.qm output/windows/Debug/bin/translations/qt_pl.qm output/windows/Debug/bin/translations/qt_pt_BR.qm output/windows/Debug/bin/translations/qt_ru.qm output/windows/Debug/bin/translations/qt_sk.qm output/windows/Debug/bin/translations/qt_sv.qm output/windows/Debug/bin/translations/qt_tr.qm output/windows/Debug/bin/translations/qt_uk.qm output/windows/Debug/bin/translations/qt_zh_CN.qm output/windows/Debug/bin/translations/qt_zh_TW.qm output/windows/Debug/bin/Clementine.exe output/windows/Debug/bin/Clementine.ilk output/windows/Debug/bin/Clementine.pdb output/windows/Debug/bin/d3dcompiler_47.dll output/windows/Debug/bin/dxcompiler.dll output/windows/Debug/bin/dxil.dll output/windows/Debug/bin/opengl32sw.dll output/windows/Debug/bin/Qt6Cored.dll output/windows/Debug/bin/Qt6Guid.dll output/windows/Debug/bin/Qt6Networkd.dll output/windows/Debug/bin/Qt6Pdfd.dll output/windows/Debug/bin/Qt6Svgd.dll output/windows/Debug/bin/Qt6Widgetsd.dll
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

            if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR
               (DEFINED CMAKE_CONFIGURATION_TYPES AND "Debug" IN_LIST CMAKE_CONFIGURATION_TYPES))
                set(DEPLOY_MODE --debug)
            else()
                set(DEPLOY_MODE --release)
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


