cmake_minimum_required(VERSION 3.25)

project(GuismusEngine VERSION 1.0)

# Définissez vos fichiers sources et d'en-tête ici
set(SOURCES "src/GameEngine.cpp")
set(HEADERS "headers/GameEngine.hpp" "headers/Utils.hpp" "headers/GameEngine")

# Créez votre bibliothèque statique ou partagée en fonction du système d'exploitation
if(WIN32)
    add_library(GuismusEngine STATIC ${SOURCES} ${HEADERS})
else()
    add_library(GuismusEngine SHARED ${SOURCES} ${HEADERS})
endif()

# Configuration de votre bibliothèque (options de compilation, etc.)
target_compile_features(GuismusEngine PUBLIC cxx_std_20)
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
    VERSION 1.0.2
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
