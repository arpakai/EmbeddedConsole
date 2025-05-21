# INCLUDE GUARD
include_guard()

message("EmbeddedConsole lib is included")

target_sources(${PROJECT_NAME} PRIVATE

)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/cli
        ${CMAKE_CURRENT_LIST_DIR}/cli/inc
        ${CMAKE_CURRENT_LIST_DIR}/cli/inc/character_encodings
)


