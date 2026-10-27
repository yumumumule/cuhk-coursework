cmake_minimum_required(VERSION 3.16)
project(ESTR1002 LANGUAGES C)

foreach(lab L01 L02 L03 L04 L05 L06 L07 L08 L09 L10)
    add_subdirectory(${lab})
endforeach()

# The local-only Project directory is deliberately excluded from this build.
include(CTest)
if(BUILD_TESTING)
    include(cmake/Exercises.cmake)
    estr1002_exercise(l10_q3_boundary_test tests/l10_q3_max.c L10/Q3/func.c)
    target_include_directories(l10_q3_boundary_test PRIVATE L10/Q3)
    target_compile_definitions(l10_q3_boundary_test PRIVATE SIZE=5)
    find_package(Python3 COMPONENTS Interpreter QUIET)
    if(Python3_Interpreter_FOUND)
        add_test(NAME exercise_regression
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/regression.py
                --build-dir ${CMAKE_BINARY_DIR}
                --boundary-exe $<TARGET_FILE:l10_q3_boundary_test>)
        set_tests_properties(exercise_regression PROPERTIES TIMEOUT 180)
    else()
        message(STATUS "Python 3 not found: build succeeds; regression tests are unavailable.")
    endif()
endif()
