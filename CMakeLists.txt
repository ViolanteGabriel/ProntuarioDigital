cmake_minimum_required(VERSION 3.21)
project(ProntuarioDigital LANGUAGES C)

set(CMAKE_C_STANDARD 11 CACHE STRING "Padrao da linguagem C (11 ou 17)")
set_property(CACHE CMAKE_C_STANDARD PROPERTY STRINGS 11 17)
if(NOT CMAKE_C_STANDARD MATCHES "^(11|17)$")
    message(FATAL_ERROR "Escolha CMAKE_C_STANDARD=11 ou 17")
endif()
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(estruturas "Trabalho Trimestral 1/estruturas.c")
target_include_directories(estruturas PUBLIC "Trabalho Trimestral 1")
add_executable(prontuario "Trabalho Trimestral 1/main.c")
target_link_libraries(prontuario PRIVATE estruturas)

include(CTest)
if(BUILD_TESTING)
    add_executable(test_estruturas tests/test_estruturas.c)
    target_link_libraries(test_estruturas PRIVATE estruturas)
    set(CASOS
        data_mes_31_dias data_mes_30_dias data_fevereiro
        data_bissexto data_seculo data_dia_invalido
        data_mes_invalido data_ano_invalido
        lista_vazia lista_primeira_consulta lista_varias_consultas
        lista_nula lista_copia_consulta arvore_vazia no_com_consulta
        libera_estruturas)
    foreach(caso IN LISTS CASOS)
        add_test(NAME ${caso} COMMAND test_estruturas ${caso})
        set_tests_properties(${caso} PROPERTIES TIMEOUT 10)
    endforeach()
endif()

if(MSVC)
    # As funcoes padrao de C sao utilizadas para manter a portabilidade.
    target_compile_definitions(estruturas PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_definitions(prontuario PRIVATE _CRT_SECURE_NO_WARNINGS)
else()
    target_compile_options(estruturas PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(prontuario PRIVATE -Wall -Wextra -Wpedantic)
    if(BUILD_TESTING)
        target_compile_options(test_estruturas PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()
