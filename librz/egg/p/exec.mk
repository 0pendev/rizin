NEXEC=egg_exec
OBJ_EXEC=${NEXEC}.o
STATIC_OBJ+=${OBJ_EXEC}
TARGET_${NEXEC}=${NEXEC}.${EXT_SO}
CFLAGS+=-DRZ_PLUGIN_INCORE
LDFLAGS+=-L..

ALL_TARGETS+=${TARGET_${NEXEC}}

${TARGET_EXEC} ${TARGET_${NEXEC}}: ${P}${OBJ_EXEC}
	${CC} $(call libname,${NEXEC}) ${LDFLAGS} ${CFLAGS} -o ${TARGET_${NEXEC}} ${P}${OBJ_EXEC}
