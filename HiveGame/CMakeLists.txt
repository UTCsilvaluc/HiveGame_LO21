cmake_minimum_required(VERSION 3.28)
project(HiveGame)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HiveGame
        GameMaster.cpp
        GameMaster.h
        Hexagon.cpp
        Hexagon.h
        Insecte.cpp
        Insecte.h
        Joueur.cpp
        Joueur.h
        main.cpp
        Plateau.cpp
        Plateau.h)
