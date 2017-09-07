cmake_minimum_required(VERSION 3.8)
project(75_42_PEPAS_cliente)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        PEPAS/headers/com.pepas.controllers/clienteController.h
        PEPAS/headers/com.pepas.logger/Logger.h
        PEPAS/headers/com.pepas.model/cliente.h
        PEPAS/headers/com.pepas.model/usuario.h
        PEPAS/headers/com.pepas.parser/ClienteParser.h
        PEPAS/headers/com.pepas.view/consola.h
        PEPAS/headers/pugi/pugiconfig.hpp
        PEPAS/headers/pugi/pugixml.cpp
        PEPAS/headers/pugi/pugixml.hpp
        PEPAS/src/com.pepas.controllers/clienteController.cpp
        PEPAS/src/com.pepas.logger/Logger.cpp
        PEPAS/src/com.pepas.model/cliente.cpp
        PEPAS/src/com.pepas.model/turi.cpp
        PEPAS/src/com.pepas.model/usuario.cpp
        PEPAS/src/com.pepas.parser/ClienteParser.cpp
        PEPAS/src/com.pepas.view/consola.cpp
        PEPAS/src/main.cpp
        PEPAS/src/PEPAS.cpp
        PEPAS/cliente.xml
        PEPAS/PEPAS.xml
        PEPAS/Server.xml
        cliente.cpp
        cliente.h
        clienteController.cpp
        clienteController.h
        consola.cpp
        consola.h
        main.cpp
        PEPAS.cpp
        README.md
        socketCliente.cpp
        socketCliente.h
        turi.cpp
        usuario.cpp
        usuario.h)

add_executable(75_42_PEPAS_cliente ${SOURCE_FILES})