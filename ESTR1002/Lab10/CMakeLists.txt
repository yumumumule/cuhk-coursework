cmake_minimum_required(VERSION 3.16)
project(ESTR1002_L10 LANGUAGES C)

include(${CMAKE_CURRENT_LIST_DIR}/../cmake/Exercises.cmake)

estr1002_exercise(l10_q1_task1 Q1_task1.c)
estr1002_exercise(l10_q1_task2 Q1_task2.c)
estr1002_exercise(l10_q2_task1 Q2_task1.c)
estr1002_exercise(l10_q2_task2 Q2_task2.c)
estr1002_exercise(l10_q2_task3 Q2_task3.c)

add_subdirectory(Q3)
