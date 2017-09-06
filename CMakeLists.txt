cmake_minimum_required(VERSION 3.8)
project(75_42_PEPAS)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        PEPAS/headers/Controller/servidorController.h
        PEPAS/headers/Model/baseDeDatos.h
        PEPAS/headers/Model/logger.h
        PEPAS/headers/Model/pugiconfig.hpp
        PEPAS/headers/Model/pugixml.hpp
        PEPAS/headers/Model/servidor.h
        PEPAS/headers/Model/servidorBuilder.h
        PEPAS/headers/Model/usuario.h
        PEPAS/headers/Vista/consola.h
        PEPAS/headers/Auto.h
        PEPAS/src/Controller/servidorController.cpp
        PEPAS/src/Model/baseDeDatos.cpp
        PEPAS/src/Model/logger.cpp
        PEPAS/src/Model/main.cpp
        PEPAS/src/Model/pugixml.cpp
        PEPAS/src/Model/servidor.cpp
        PEPAS/src/Model/servidorBuilder.cpp
        PEPAS/src/Model/usuario.cpp
        PEPAS/src/Vista/consola.cpp
        PEPAS/src/Auto.cpp
        PEPAS/makefile PEPAS/src/Model/socket.cpp PEPAS/headers/Model/socket.h)

add_executable(75_42_PEPAS ${SOURCE_FILES})