# Client/CMakeLists.txt

add_executable(${CLIENT_TARGET_NAME}
    # Client related source files
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Client.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/EntryPoint.cpp

    # Common source files
    ${CMAKE_SOURCE_DIR}/Common/Source/Interfaces/INetwork.cpp
    ${CMAKE_SOURCE_DIR}/Common/Source/Managers/EventSystem.cpp
    ${CMAKE_SOURCE_DIR}/Common/Source/Managers/NetworkManager.cpp
)

target_include_directories(${CLIENT_TARGET_NAME} PUBLIC
    # Client related includes
    ${CMAKE_CURRENT_SOURCE_DIR}/Source
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core

    # Common includes
    ${CMAKE_SOURCE_DIR}/Common/Source/Core
    ${CMAKE_SOURCE_DIR}/Common/Source/Interfaces
    ${CMAKE_SOURCE_DIR}/Common/Source/Network
    ${CMAKE_SOURCE_DIR}/Common/Source/Managers
)

#=========================================================================================
# Fetch external libraries
#=========================================================================================

include(FetchContent)

# Fetch SFML
set(SFML_LIB_NAME SFML)

FetchContent_Declare(
    ${SFML_LIB_NAME}
    GIT_REPOSITORY http://github.com/SFML/SFML
    GIT_TAG 2.6.0
    GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(${SFML_LIB_NAME})

# Link SFML
target_link_libraries(${CLIENT_TARGET_NAME} PUBLIC sfml-graphics)
target_link_libraries(${CLIENT_TARGET_NAME} PUBLIC sfml-window)
target_link_libraries(${CLIENT_TARGET_NAME} PUBLIC sfml-system)
target_link_libraries(${CLIENT_TARGET_NAME} PUBLIC sfml-audio)
target_link_libraries(${CLIENT_TARGET_NAME} PUBLIC sfml-network)

# Fetch EnTT
set(ENTT_LIB_NAME EnTT)
FetchContent_Declare(
    ${ENTT_LIB_NAME}
    GIT_REPOSITORY https://github.com/skypjack/entt
    GIT_TAG v3.12.2
    GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(${ENTT_LIB_NAME})

# Add EnTT include directories
target_include_directories(${CLIENT_TARGET_NAME} SYSTEM PUBLIC
    ${entt_SOURCE_DIR}/single_include
)

target_link_libraries(${CLIENT_TARGET_NAME} PUBLIC EnTT::EnTT)

set(RESOURCE_FOLDER_NAME "Assets")
set(RESOURCE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_FOLDER_NAME}")

#=========================================================================================
# Post Build
#=========================================================================================

function(CopyLibToTarget LIB_NAME TARGET_NAME)
    add_custom_command(TARGET ${TARGET_NAME}    
        POST_BUILD
        COMMAND
        ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${LIB_NAME}>
        $<TARGET_FILE_DIR:${TARGET_NAME}>
    )
endfunction()

CopyLibToTarget(sfml-graphics   ${CLIENT_TARGET_NAME})
CopyLibToTarget(sfml-window     ${CLIENT_TARGET_NAME})
CopyLibToTarget(sfml-system     ${CLIENT_TARGET_NAME})
CopyLibToTarget(sfml-audio      ${CLIENT_TARGET_NAME})
CopyLibToTarget(sfml-network    ${CLIENT_TARGET_NAME})

add_custom_command(
    TARGET ${CLIENT_TARGET_NAME}
    POST_BUILD
    COMMAND
    ${CMAKE_COMMAND} -E copy_directory
    ${RESOURCE_SRC_DIR}
    $<TARGET_FILE_DIR:${CLIENT_TARGET_NAME}>/${RESOURCE_FOLDER_NAME}
)

configure_file(
    "config.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Config.h" ESCAPE_QUOTES
)