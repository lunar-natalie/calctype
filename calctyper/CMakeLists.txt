cmake_minimum_required(VERSION 3.10)

# Project initialisation
project(calctyper VERSION 0.1)
set(calctyper_VERSION_YEAR 2022)

# Libraries
find_package(Boost
             1.79.0
             REQUIRED
             COMPONENTS
                log
                program_options)

# Build configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

set(calctyper_CODE_SOURCE_DIR ${calctyper_SOURCE_DIR}/src)

configure_file(${calctyper_CODE_SOURCE_DIR}/config.h.in
               ${calctyper_CODE_SOURCE_DIR}/config.h)

set(calctyper_SOURCES
    logger.cc
    main.cc
    options.cc)

list(TRANSFORM calctyper_SOURCES
     PREPEND "${calctyper_CODE_SOURCE_DIR}/")

add_executable(${CMAKE_PROJECT_NAME} ${calctyper_SOURCES})

set(calctyper_CXX_LIBRARIES
    ${Boost_LIBRARIES})

target_link_libraries(${CMAKE_PROJECT_NAME} ${calctyper_CXX_LIBRARIES})

# Internationalization
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/intl.cmake)

# Install
install(TARGETS calctyper
    RUNTIME
    DESTINATION bin)

file(GLOB PO_LANGS LIST_DIRECTORIES true ${CMAKE_LOCALE_BINARY_DIR}/*)
foreach(PO_LANG IN ITEMS ${PO_LANGS})
    if(IS_DIRECTORY ${PO_LANG})
        message(STATUS ${PO_LANG})
        install(DIRECTORY ${PO_LANG}
                DESTINATION locale)
    endif()
endforeach()

# Uninstall
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND
            ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake)
endif()
