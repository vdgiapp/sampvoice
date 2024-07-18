set(PROJECT_NAME server)

################################################################################
# Source groups
################################################################################
set(___auxiliary
    "Makefile"
    "plugin.def"
    "sampvoice.inc"
)
source_group("Исходные файлы\\auxiliary" FILES ${___auxiliary})

set(___include
    "include/MPMCQueue.h"
    "include/SPSCQueue.h"
)
source_group("Исходные файлы\\include" FILES ${___include})

set(___include__pawn
    "include/pawn/amxplugin.cpp"
    "include/pawn/plugincommon.h"
)
source_group("Исходные файлы\\include\\pawn" FILES ${___include__pawn})

set(___include__pawn__amx
    "include/pawn/amx/amx.h"
    "include/pawn/amx/getch.h"
    "include/pawn/amx/sclinux.h"
)
source_group("Исходные файлы\\include\\pawn\\amx" FILES ${___include__pawn__amx})

set(___include__raknet
    "include/raknet/bitstream.cpp"
    "include/raknet/bitstream.h"
    "include/raknet/networktypes.h"
)
source_group("Исходные файлы\\include\\raknet" FILES ${___include__raknet})

set(___include__util
    "include/util/logger.cpp"
    "include/util/logger.h"
    "include/util/memory.hpp"
    "include/util/raknet.cpp"
    "include/util/raknet.h"
    "include/util/timer.cpp"
    "include/util/timer.h"
)
source_group("Исходные файлы\\include\\util" FILES ${___include__util})

set(___include__ysf
    "include/ysf/addresses.h"
    "include/ysf/globals.h"
    "include/ysf/structs.h"
    "include/ysf/ysf.cpp"
)
source_group("Исходные файлы\\include\\ysf" FILES ${___include__ysf})

set(___include__ysf__utils
    "include/ysf/utils/cvector.h"
    "include/ysf/utils/cvector2d.h"
    "include/ysf/utils/memory.h"
)
source_group("Исходные файлы\\include\\ysf\\utils" FILES ${___include__ysf__utils})

set(___source
    "Header.h"
    "main.cpp"
    "Worker.h"
)
source_group("Исходные файлы\\source" FILES ${___source})

set(___source__audio__effects
    "Effect.cpp"
    "Effect.h"
)
source_group("Исходные файлы\\source\\audio\\effects" FILES ${___source__audio__effects})

set(___source__audio__parameters
    "Parameter.cpp"
    "Parameter.h"
)
source_group("Исходные файлы\\source\\audio\\parameters" FILES ${___source__audio__parameters})

set(___source__audio__streams
    "DynamicStream.cpp"
    "DynamicStream.h"
    "GlobalStream.cpp"
    "GlobalStream.h"
    "LocalStream.cpp"
    "LocalStream.h"
    "PointStream.cpp"
    "PointStream.h"
    "Stream.cpp"
    "Stream.h"
)
source_group("Исходные файлы\\source\\audio\\streams" FILES ${___source__audio__streams})

set(___source__audio__streams__dynamic
    "DynamicLocalStreamAtObject.cpp"
    "DynamicLocalStreamAtObject.h"
    "DynamicLocalStreamAtPlayer.cpp"
    "DynamicLocalStreamAtPlayer.h"
    "DynamicLocalStreamAtPoint.cpp"
    "DynamicLocalStreamAtPoint.h"
    "DynamicLocalStreamAtVehicle.cpp"
    "DynamicLocalStreamAtVehicle.h"
)
source_group("Исходные файлы\\source\\audio\\streams\\dynamic" FILES ${___source__audio__streams__dynamic})

set(___source__audio__streams__static
    "StaticLocalStreamAtObject.cpp"
    "StaticLocalStreamAtObject.h"
    "StaticLocalStreamAtPlayer.cpp"
    "StaticLocalStreamAtPlayer.h"
    "StaticLocalStreamAtPoint.cpp"
    "StaticLocalStreamAtPoint.h"
    "StaticLocalStreamAtVehicle.cpp"
    "StaticLocalStreamAtVehicle.h"
)
source_group("Исходные файлы\\source\\audio\\streams\\static" FILES ${___source__audio__streams__static})

set(___source__network
    "ControlPacket.cpp"
    "ControlPacket.h"
    "Network.cpp"
    "Network.h"
    "VoicePacket.cpp"
    "VoicePacket.h"
)
source_group("Исходные файлы\\source\\network" FILES ${___source__network})

set(___source__pawn
    "Pawn.cpp"
    "Pawn.h"
)
source_group("Исходные файлы\\source\\pawn" FILES ${___source__pawn})

set(___source__store
    "PlayerInfo.h"
    "PlayerStore.cpp"
    "PlayerStore.h"
)
source_group("Исходные файлы\\source\\store" FILES ${___source__store})

set(ALL_FILES
    ${___auxiliary}
    ${___include}
    ${___include__pawn}
    ${___include__pawn__amx}
    ${___include__raknet}
    ${___include__util}
    ${___include__ysf}
    ${___include__ysf__utils}
    ${___source}
    ${___source__audio__effects}
    ${___source__audio__parameters}
    ${___source__audio__streams}
    ${___source__audio__streams__dynamic}
    ${___source__audio__streams__static}
    ${___source__network}
    ${___source__pawn}
    ${___source__store}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE server)

################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_RELEASE "sampvoice"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION         "TRUE"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "_WINDLL;"
    "NDEBUG;"
    "_MBCS"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /std:c++17;
        /Oi;
        /sdl-;
        /GF;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        /Ot;
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        /SUBSYSTEM:WINDOWS;
        /OPT:REF;
        /OPT:ICF
    )
endif()

