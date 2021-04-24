cmake_minimum_required(VERSION 3.13.0...3.20)
project(TND004-Lab-3 VERSION 1.0.0 DESCRIPTION "TND004 Lab 3" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(enable_warnings target)
target_compile_options(${target} PUBLIC 
$<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
$<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall -Wextra>
)
endfunction()

add_executable(Lab3 lab3.cpp BinarySearchTree.h node.h dsexceptions.h iterator.h test1.cpp test2.cpp test3.cpp frequency_table.cpp 
               test0_out.txt test1_out.txt words.txt text.txt text_long.txt frequency_table.txt frequency_table_long.txt)

enable_warnings(Lab3)