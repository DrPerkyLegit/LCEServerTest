cmake_minimum_required(VERSION 3.24)

project(MinecraftConsoles LANGUAGES C CXX RC ASM_MASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT WIN32)
  message(FATAL_ERROR "This CMake build currently supports Windows only.")
endif()

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
  message(FATAL_ERROR "Use a 64-bit generator/toolchain (x64).")
endif()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

function(configure_msvc_target target)
  target_compile_options(${target} PRIVATE
    $<$<AND:$<NOT:$<CONFIG:Release>>,$<COMPILE_LANGUAGE:C,CXX>>:/W3>
    $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C,CXX>>:/W0>
    $<$<COMPILE_LANGUAGE:C,CXX>:/MP>
    $<$<COMPILE_LANGUAGE:C,CXX>:/FS>
    $<$<COMPILE_LANGUAGE:CXX>:/EHsc>
    $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C,CXX>>:/GL /O2 /Oi /GT /GF>
  )
endfunction()

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/WorldSources.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/ClientSources.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/ServerSources.cmake")

list(TRANSFORM MINECRAFT_WORLD_SOURCES PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/Minecraft.World/")
list(TRANSFORM MINECRAFT_CLIENT_SOURCES PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/Minecraft.Client/")
list(TRANSFORM MINECRAFT_SERVER_SOURCES PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/Minecraft.Server/")

add_library(MinecraftWorld STATIC ${MINECRAFT_WORLD_SOURCES})
target_include_directories(MinecraftWorld PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/Minecraft.World"
  "${CMAKE_CURRENT_SOURCE_DIR}/Minecraft.World/x64headers"
)
target_compile_definitions(MinecraftWorld PRIVATE
  $<$<CONFIG:Debug>:_LARGE_WORLDS;_DEBUG;_LIB;_CRT_NON_CONFORMING_SWPRINTFS;_CRT_SECURE_NO_WARNINGS;_WINDOWS64>
  $<$<NOT:$<CONFIG:Debug>>:_LARGE_WORLDS;_LIB;_CRT_NON_CONFORMING_SWPRINTFS;_CRT_SECURE_NO_WARNINGS;_WINDOWS64>
)
if(MSVC)
  configure_msvc_target(MinecraftWorld)
endif()

set(BUILDVER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/cmake/tools/GenerateBuildVer.cmake")
set(BUILDVER_OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/Minecraft.Client/Common/BuildVer.h")

add_custom_target(GenerateBuildVer
  COMMAND ${CMAKE_COMMAND}
    "-DOUTPUT_FILE=${BUILDVER_OUTPUT}"
    -P "${BUILDVER_SCRIPT}"
  COMMENT "Generating BuildVer.h..."
  VERBATIM
)

add_library(MinecraftClient STATIC ${MINECRAFT_CLIENT_SOURCES})
target_include_directories(MinecraftClient PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/Minecraft.Client"
  "${CMAKE_CURRENT_SOURCE_DIR}/Minecraft.Client/Xbox/Sentient/Include"
  "${CMAKE_CURRENT_SOURCE_DIR}/Minecraft.World/x64headers"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)
target_compile_definitions(MinecraftClient PRIVATE
  $<$<CONFIG:Debug>:_LARGE_WORLDS;_DEBUG;_CRT_NON_CONFORMING_SWPRINTFS;_CRT_SECURE_NO_WARNINGS;_WINDOWS64>
  $<$<NOT:$<CONFIG:Debug>>:_LARGE_WORLDS;_CRT_NON_CONFORMING_SWPRINTFS;_CRT_SECURE_NO_WARNINGS;_WINDOWS64>
)
if(MSVC)
  configure_msvc_target(MinecraftClient)
endif()

target_link_libraries(MinecraftClient PRIVATE
  MinecraftWorld
  d3d11
  XInput9_1_0
  wsock32
  legacy_stdio_definitions
  $<$<CONFIG:Debug>:
    "${CMAKE_CURRENT_SOURCE_DIR}/Minecraft.Client/Windows64/4JLibs/libs/4J_Input_d.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/Minecraft.Client/Windows64/4JLibs/libs/4J_Storage_d.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/Minecraft.Client/Windows64/4JLibs/libs/4J_Render_PC_d.lib"
  >
  $<$<NOT:$<CONFIG:Debug>>:
    "${CMAKE_CURRENT_SOURCE_DIR}/Minecraft.Client/Windows64/4JLibs/libs/4J_Input.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/Minecraft.Client/Windows64/4JLibs/libs/4J_Storage.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/Minecraft.Client/Windows64/4JLibs/libs/4J_Render_PC.lib"
  >
)

add_executable(MinecraftServer WIN32 ${MINECRAFT_SERVER_SOURCES})
target_link_options(MinecraftServer PRIVATE "/SUBSYSTEM:CONSOLE")
target_include_directories(MinecraftServer PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/Minecraft.Server"
)
target_compile_definitions(MinecraftServer PRIVATE
  $<$<CONFIG:Debug>:_LARGE_WORLDS;_DEBUG;_CRT_NON_CONFORMING_SWPRINTFS;_CRT_SECURE_NO_WARNINGS;_WINDOWS64>
  $<$<NOT:$<CONFIG:Debug>>:_LARGE_WORLDS;_CRT_NON_CONFORMING_SWPRINTFS;_CRT_SECURE_NO_WARNINGS;_WINDOWS64>
)
if(MSVC)
  configure_msvc_target(MinecraftServer)
  target_link_options(MinecraftServer PRIVATE
    $<$<CONFIG:Release>:/LTCG /INCREMENTAL:NO>
  )
endif()

set_target_properties(MinecraftServer PROPERTIES
  VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:MinecraftServer>"
)

target_link_libraries(MinecraftServer PRIVATE
  MinecraftClient
)

add_dependencies(MinecraftClient GenerateBuildVer)
add_dependencies(MinecraftWorld GenerateBuildVer)
add_dependencies(MinecraftServer GenerateBuildVer)

add_custom_command(TARGET MinecraftServer POST_BUILD
  COMMAND powershell.exe -ExecutionPolicy Bypass -File "${CMAKE_CURRENT_SOURCE_DIR}/Minecraft.Client/postbuild.ps1"
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Minecraft.Client/"
  COMMENT "Running postbuild.ps1"
)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT MinecraftServer)
