cmake_minimum_required(VERSION 3.30)
project(Projet2025)

set(CMAKE_CXX_STANDARD 20)

add_executable(Projet2025 main.cpp
    include/Badge.h
    src/Badge.cpp
    include/LecteurBadge.h
    src/LecteurBadge.cpp
    include/Personne.h
    src/Personne.cpp
    include/Scheduler.h
    src/Scheduler.cpp
    include/Serveur.h
    src/Serveur.cpp
    include/HeritageBadge.h
    include/HeritagePersonne.h
    src/HeritageBadge.cpp
    include/HeritageLecteur.h
)
