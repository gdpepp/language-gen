cmake_minimum_required(VERSION 3.10)
project(language-gen)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(language-gen
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
    ortho.c ortho.h
    utils/random.c
    utils/random.h
        word.c
        word.h
        utils/fileFunctions.c
        utils/fileFunctions.h
        shuffle.c
        shuffle.h
        morpheme.h
        morpheme.c
        construct.h
        construct.c
        )

target_link_libraries(language-gen m)