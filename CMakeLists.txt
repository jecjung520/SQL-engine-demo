cmake_minimum_required(VERSION 3.11)

project(
    sql_engine-demo
    VERSION 0.1
    DESCRIPTION "SQL Mini Engine"
    LANGUAGES CXX)

add_executable(queryEngine qe.cc)