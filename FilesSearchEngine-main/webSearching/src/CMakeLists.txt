set(ENGINE_SRCS 
    "converterJSON.cpp"
    "main.cpp"
)

add_library(engine_lib ${ENGINE_SRCS})

target_include_directories(engine_lib PUBLIC "../include" "../jsonFiles")

add_executable(webSearching_app "main.cpp") 
target_link_libraries(webSearching_app PRIVATE engine_lib)