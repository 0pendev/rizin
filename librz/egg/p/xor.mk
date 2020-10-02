NXOR=egg_xor
OBJ_XOR=${NXOR}.o
STATIC_OBJ+=${OBJ_XOR}
TARGET_${NXOR}=${NXOR}.${EXT_SO}
CFLAGS+=-DRZ_PLUGIN_INCORE

ALL_TARGETS+=${TARGET_${NXOR}}

${TARGET_XOR} ${TARGET_${NXOR}}: ${OBJ_XOR}
	${CC} $(call libname,${NXOR}) ${LDFLAGS} ${CFLAGS} -o ${TARGET_${NXOR}} ${OBJ_XOR}
