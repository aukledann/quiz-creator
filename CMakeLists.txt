cmake_minimum_required(VERSION 3.24)
project(Quizz_Creator)

set(CMAKE_CXX_STANDARD 20)

add_executable(Quizz_Creator main.cpp New_Quiz.cpp Question.cpp True_Or_False_Question.cpp Type_in_Question.cpp Single_Answer_Question.h Single_Answer_Question.cpp Multiple_Answer_Question.h Multiple_Answer_Question.cpp Match_Question.h Match_Question.cpp Essay_Question.h Essay_Question.cpp Button.h Button.cpp TextBox.h TextBox.cpp)


set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.6.2/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics  network REQUIRED)
include_directories(C:/SFML-2.6.2/include)
target_link_libraries(Quizz_Creator sfml-system sfml-window sfml-graphics )