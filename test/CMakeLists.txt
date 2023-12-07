set(RSL_BASE_TESTS
        container/StaticArray.cpp
        container/StaticList.cpp
        container/DynamicArray.cpp
        container/DynamicList.cpp
        stream/PipelineTest.cpp)

add_executable(RSLTest ${RSL_BASE_TESTS})

#RSL
include_directories(${CMAKE_SOURCE_DIR}/src)
target_link_libraries(RSLTest PRIVATE RSL)

#Catch2
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1 # or a later release
)
FetchContent_MakeAvailable(Catch2)
target_link_libraries(RSLTest PRIVATE Catch2::Catch2WithMain)