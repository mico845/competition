#THIS FILE IS AUTO GENERATED FROM THE TEMPLATE! DO NOT CHANGE!
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.17)

# specify cross compilers and tools
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# project settings
project(HEllOWORLD CXX C ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

#Uncomment for hardware floating point
add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)

#Uncomment for software floating point
#add_compile_options(-mfloat-abi=soft)

add_compile_options(-mcpu=cortex-m4 -mthumb -mthumb-interwork)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

# uncomment to mitigate c++17 absolute addresses warnings
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif ()

include_directories(Core/Inc Drivers/STM32F4xx_HAL_Driver/Inc Drivers/STM32F4xx_HAL_Driver/Inc/Legacy Drivers/CMSIS/Device/ST/STM32F4xx/Include Drivers/CMSIS/Include)

add_definitions(-DUSE_HAL_DRIVER -DSTM32F407xx)

include_directories(
        UserApp
        System/sys
        System/usart
        System/delay

        Platform
        Platform/Gpio
        Platform/Peripheral
        Platform/Adc
        Platform/Dac
        Platform/Pwm
        Platform/SignalProcess
        Platform/SignalProcess/BasicMeasure
        Platform/SignalProcess/AdvancedMeasure
        Platform/SignalProcess/FFT
        Platform/SignalProcess/Filter
        Platform/SignalProcess/Filter/fdacoefs
        Platform/SignalProcess/PwmMeasure

        Screen/ScreenBase
        Screen
        Task

        HardWare/config
        HardWare/lcd
        HardWare/key
        HardWare/touch
        HardWare/w25qxx

        #       HardWare/matrix_key
        #       HardWare/dac8563
        #       HardWare/oled
        #       HardWare/myiic
        #       HardWare/ad9834

        # DSP库
        ARM_DSP/Include/dsp
        ARM_DSP/Include
        ARM_DSP/PrivateInclude

)

file(
        GLOB_RECURSE SOURCES
        "startup/*.*"
        "Drivers/*.*"
        "Core/*.*"
        "UserApp/*.*"
        "System/*.*"
        "Platform/*.*"
        "HardWare/lcd/*"
        "Screen/*.*"
        "HardWare/key/*"
        "HardWare/config/*"
        "HardWare/touch/*"
        "HardWare/w25qxx/*"

        # "HardWare/matrix_key/*"
        #  "HardWare/oled/*"
        #  "HardWare/myiic/*"
        #  "HardWare/ad9834/*"

        "Task/*"

        # DSP库
        "ARM_DSP/Source/BasicMathFunctions/BasicMathFunctions.c"
        "ARM_DSP/Source/BayesFunctions/BayesFunctions.c"
        "ARM_DSP/Source/CommonTables/CommonTables.c"
        "ARM_DSP/Source/ComplexMathFunctions/ComplexMathFunctions.c"
        "ARM_DSP/Source/ControllerFunctions/ControllerFunctions.c"
        "ARM_DSP/Source/DistanceFunctions/DistanceFunctions.c"
        "ARM_DSP/Source/FastMathFunctions/FastMathFunctions.c"
        "ARM_DSP/Source/FilteringFunctions/FilteringFunctions.c"
        "ARM_DSP/Source/InterpolationFunctions/InterpolationFunctions.c"
        "ARM_DSP/Source/MatrixFunctions/MatrixFunctions.c"
        "ARM_DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.c"
        "ARM_DSP/Source/StatisticsFunctions/StatisticsFunctions.c"
        "ARM_DSP/Source/SupportFunctions/SupportFunctions.c"
        "ARM_DSP/Source/SVMFunctions/SVMFunctions.c"
        "ARM_DSP/Source/TransformFunctions/TransformFunctions.c"
        "ARM_DSP/Source/WindowFunctions/WindowFunctions.c"

)

# 排除Platform/Hrtim文件夹及其子文件夹中的文件
file(
        GLOB_RECURSE EXCLUDED_SOURCES
        "Platform/Hrtim/*.*"
)

# 从SOURCES中移除排除的文件
list(REMOVE_ITEM SOURCES ${EXCLUDED_SOURCES})

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F407VETx_FLASH.ld)

add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-mcpu=cortex-m4 -mthumb -mthumb-interwork)
add_link_options(-T ${LINKER_SCRIPT})

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")
