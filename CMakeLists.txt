cmake_minimum_required(VERSION 3.25)

project(GuismusEngine VERSION 1.0.3)

# Définissez vos fichiers sources et d'en-tête ici
set(SOURCES "src/GameEngine.cpp")
set(HEADERS "headers/GameEngine.hpp" "headers/Utils.hpp" "headers/GameEngine")

# Créez votre bibliothèque partagée
add_library(GuismusEngine SHARED ${SOURCES} ${HEADERS})

# Configuration de votre bibliothèque (options de compilation, etc.)
target_compile_features(GuismusEngine PUBLIC cxx_std_20)
# Vous pouvez également ajouter d'autres options de compilation ici

# Créez votre bibliothèque statique
add_library(GuismusEngineStatic STATIC ${SOURCES} ${HEADERS})

# Configuration de votre bibliothèque statique (options de compilation, etc.)
target_compile_features(GuismusEngineStatic PUBLIC cxx_std_20)
# Vous pouvez également ajouter d'autres options de compilation ici

# Incluez les répertoires d'en-têtes pour les deux bibliothèques
target_include_directories(GuismusEngine
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/headers>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(GuismusEngineStatic
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/headers>
    $<INSTALL_INTERFACE:include>
)

# Définissez d'autres options de compilation ou de bibliothèque ici

# Exportez votre bibliothèque CPM
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/GuismusEngine/GuismusEngineConfigVersion.cmake"
    VERSION 1.0.3
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_LIST_DIR}/Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/GuismusEngine/GuismusEngineConfig.cmake"
    INSTALL_DESTINATION lib/cmake/GuismusEngine
)

install(TARGETS GuismusEngine GuismusEngineStatic
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

