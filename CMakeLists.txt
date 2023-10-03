cmake_minimum_required(VERSION 3.25)

project(GuismusEngine VERSION 1.0)

# Définissez vos fichiers sources et d'en-tête ici
set(SOURCES
    src/file1.cpp
    src/file2.cpp
    # Ajoutez ici tous les fichiers source de votre bibliothèque
)

set(HEADERS
    headers/file1.hpp
    headers/file2.hpp
    # Ajoutez ici tous les fichiers d'en-tête de votre bibliothèque
)

# Créez votre bibliothèque
add_library(GuismusEngine ${SOURCES} ${HEADERS})

# Configuration de votre bibliothèque (options de compilation, etc.)
target_compile_features(GuismusEngine PUBLIC cxx_std_11)
# Vous pouvez également ajouter d'autres options de compilation ici

# Incluez les répertoires d'en-têtes
target_include_directories(GuismusEngine
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/headers>
    $<INSTALL_INTERFACE:include>
)

# Définissez d'autres options de compilation ou de bibliothèque ici

# Exportez votre bibliothèque CPM
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/GuismusEngine/GuismusEngineConfigVersion.cmake"
    VERSION 1.0
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_LIST_DIR}/Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/GuismusEngine/GuismusEngineConfig.cmake"
    INSTALL_DESTINATION lib/cmake/GuismusEngine
)

install(TARGETS GuismusEngine
    EXPORT GuismusEngineTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(EXPORT GuismusEngineTargets
    FILE GuismusEngineTargets.cmake
    NAMESPACE GuismusEngine::
    DESTINATION lib/cmake/GuismusEngine
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/GuismusEngine/GuismusEngineConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/GuismusEngine/GuismusEngineConfigVersion.cmake"
    DESTINATION lib/cmake/GuismusEngine
)

install(DIRECTORY headers/ DESTINATION include)
