#FixMath:
set(FIXMATH_SRC
    ./fixmath/fix16_exp.c
    ./fixmath/fix16_fft.c
    ./fixmath/fix16_sqrt.c
    ./fixmath/fix16_str.c
    ./fixmath/fix16_trig.c
    ./fixmath/fix16.c
    ./fixmath/fract32.c
    ./fixmath/uint32.c
)

add_library(fixmath STATIC ${FIXMATH_SRC})
target_include_directories(fixmath INTERFACE ./fixmath)
target_compile_definitions(fixmath PUBLIC FIXMATH_NO_64BIT FIXMATH_FAST_SIN)
