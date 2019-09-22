set(SOURCE
    main.cpp
    )

# you must add unit test libraries here
set(TEST_LIBS
    HelloWorld-test
    )

set(LIB_DEPS
    boost_unit_test_framework
    )

add_executable(unittests ${SOURCE})
# test archives must be included as whole (means all symbols are added, even if
# not needed), else tests contained inside will not be registered in boost.test
target_link_libraries(unittests -Wl,--whole-archive)
target_link_libraries(unittests ${TEST_LIBS})
target_link_libraries(unittests -Wl,--no-whole-archive)
target_link_libraries(unittests ${LIB_DEPS})
