cmake_minimum_required(VERSION 3.10)
project(language_gen)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(language_gen
    utils/list.c
    utils/list.h
    utils/node.h
    utils/string.c
    utils/string.h
    initList.c
    initList.h
    lang-gen.c
    lang-gen.h
    langstructs.h
    ortho.c ortho.h)
