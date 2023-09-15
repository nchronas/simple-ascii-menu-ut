# CMakeLists.txt

find_package(GTest REQUIRED)

# Add the directory containing your test file
add_executable(MyTest test_simple_menu.cpp)

# Link against Google Test and Google Mock
target_link_libraries(MyTest PRIVATE GTest::GTest GTest::Main)

# Add any additional dependencies or source files for your tests
target_sources(MyTest PRIVATE
    CommandProcessor.cpp 
)
