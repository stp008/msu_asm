cmake_minimum_required(VERSION 3.20)
project(area_calc LANGUAGES C ASM_NASM)

# -----------------------------------------------------------------------------
# Определяем формат объектных файлов NASM и нужные флаги компилятору
# -----------------------------------------------------------------------------
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # ---- macOS (x86_64) ----
    set(CMAKE_ASM_NASM_OBJECT_FORMAT macho64)
    set(CMAKE_ASM_NASM_FLAGS "-f macho64" CACHE STRING "" FORCE)
    # Чётко задаём архитектуру, чтобы не собрать arm64 по умолчанию
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
else()
    # ---- Linux/BSD ----
    set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
    set(CMAKE_ASM_NASM_FLAGS "-f elf64" CACHE STRING "" FORCE)
endif()

# -----------------------------------------------------------------------------
# Обычные флаги для clang/gcc (без -m32)
# -----------------------------------------------------------------------------
set(CMAKE_C_STANDARD 99)
add_compile_options(-O2 -Wall)

# -----------------------------------------------------------------------------
# Исходники
# -----------------------------------------------------------------------------
set(SRC_C
        main.c
        wrappers.c
        newton.c
        simpson.c)
set(SRC_ASM functions.asm)   # используем x87‑вариант; можно заменить на SSE–файл

add_executable(area_calc ${SRC_C} ${SRC_ASM})

# В 64‑битном мире PIE включён по умолчанию; для NASM‑кода это безопасно.
# Если нужно отключить, раскомментируйте:
# set_target_properties(area_calc PROPERTIES POSITION_INDEPENDENT_CODE OFF)

# -----------------------------------------------------------------------------
# Цель «clean-all» для IDE/CLI
# -----------------------------------------------------------------------------
add_custom_target(clean-all COMMAND ${CMAKE_COMMAND} --build . --target clean)