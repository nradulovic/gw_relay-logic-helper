#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/relay_logic_helper.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/relay_logic_helper.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=application/source/main.c application/source/support.c driver/source/intr.c driver/source/adc.c driver/source/systick.c driver/source/gpio.c driver/source/clock.c esolid-base/port/pic32-none-gcc/mips-m4k/intr.c esolid-base/port/pic32-none-gcc/mips-m4k/systimer.c esolid-base/port/pic32-none-gcc/mips-m4k/cpu.c esolid-base/src/prio_queue.c esolid-base/src/base.c esolid-base/src/debug.c esolid-base/src/error.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/application/source/main.o ${OBJECTDIR}/application/source/support.o ${OBJECTDIR}/driver/source/intr.o ${OBJECTDIR}/driver/source/adc.o ${OBJECTDIR}/driver/source/systick.o ${OBJECTDIR}/driver/source/gpio.o ${OBJECTDIR}/driver/source/clock.o ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/intr.o ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/systimer.o ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/cpu.o ${OBJECTDIR}/esolid-base/src/prio_queue.o ${OBJECTDIR}/esolid-base/src/base.o ${OBJECTDIR}/esolid-base/src/debug.o ${OBJECTDIR}/esolid-base/src/error.o
POSSIBLE_DEPFILES=${OBJECTDIR}/application/source/main.o.d ${OBJECTDIR}/application/source/support.o.d ${OBJECTDIR}/driver/source/intr.o.d ${OBJECTDIR}/driver/source/adc.o.d ${OBJECTDIR}/driver/source/systick.o.d ${OBJECTDIR}/driver/source/gpio.o.d ${OBJECTDIR}/driver/source/clock.o.d ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/intr.o.d ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/systimer.o.d ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/cpu.o.d ${OBJECTDIR}/esolid-base/src/prio_queue.o.d ${OBJECTDIR}/esolid-base/src/base.o.d ${OBJECTDIR}/esolid-base/src/debug.o.d ${OBJECTDIR}/esolid-base/src/error.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/application/source/main.o ${OBJECTDIR}/application/source/support.o ${OBJECTDIR}/driver/source/intr.o ${OBJECTDIR}/driver/source/adc.o ${OBJECTDIR}/driver/source/systick.o ${OBJECTDIR}/driver/source/gpio.o ${OBJECTDIR}/driver/source/clock.o ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/intr.o ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/systimer.o ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/cpu.o ${OBJECTDIR}/esolid-base/src/prio_queue.o ${OBJECTDIR}/esolid-base/src/base.o ${OBJECTDIR}/esolid-base/src/debug.o ${OBJECTDIR}/esolid-base/src/error.o

# Source Files
SOURCEFILES=application/source/main.c application/source/support.c driver/source/intr.c driver/source/adc.c driver/source/systick.c driver/source/gpio.c driver/source/clock.c esolid-base/port/pic32-none-gcc/mips-m4k/intr.c esolid-base/port/pic32-none-gcc/mips-m4k/systimer.c esolid-base/port/pic32-none-gcc/mips-m4k/cpu.c esolid-base/src/prio_queue.c esolid-base/src/base.c esolid-base/src/debug.c esolid-base/src/error.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/relay_logic_helper.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX250F128B
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/application/source/main.o: application/source/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/application/source 
	@${RM} ${OBJECTDIR}/application/source/main.o.d 
	@${RM} ${OBJECTDIR}/application/source/main.o 
	@${FIXDEPS} "${OBJECTDIR}/application/source/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/application/source/main.o.d" -o ${OBJECTDIR}/application/source/main.o application/source/main.c   
	
${OBJECTDIR}/application/source/support.o: application/source/support.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/application/source 
	@${RM} ${OBJECTDIR}/application/source/support.o.d 
	@${RM} ${OBJECTDIR}/application/source/support.o 
	@${FIXDEPS} "${OBJECTDIR}/application/source/support.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/application/source/support.o.d" -o ${OBJECTDIR}/application/source/support.o application/source/support.c   
	
${OBJECTDIR}/driver/source/intr.o: driver/source/intr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/driver/source 
	@${RM} ${OBJECTDIR}/driver/source/intr.o.d 
	@${RM} ${OBJECTDIR}/driver/source/intr.o 
	@${FIXDEPS} "${OBJECTDIR}/driver/source/intr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/driver/source/intr.o.d" -o ${OBJECTDIR}/driver/source/intr.o driver/source/intr.c   
	
${OBJECTDIR}/driver/source/adc.o: driver/source/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/driver/source 
	@${RM} ${OBJECTDIR}/driver/source/adc.o.d 
	@${RM} ${OBJECTDIR}/driver/source/adc.o 
	@${FIXDEPS} "${OBJECTDIR}/driver/source/adc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/driver/source/adc.o.d" -o ${OBJECTDIR}/driver/source/adc.o driver/source/adc.c   
	
${OBJECTDIR}/driver/source/systick.o: driver/source/systick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/driver/source 
	@${RM} ${OBJECTDIR}/driver/source/systick.o.d 
	@${RM} ${OBJECTDIR}/driver/source/systick.o 
	@${FIXDEPS} "${OBJECTDIR}/driver/source/systick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/driver/source/systick.o.d" -o ${OBJECTDIR}/driver/source/systick.o driver/source/systick.c   
	
${OBJECTDIR}/driver/source/gpio.o: driver/source/gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/driver/source 
	@${RM} ${OBJECTDIR}/driver/source/gpio.o.d 
	@${RM} ${OBJECTDIR}/driver/source/gpio.o 
	@${FIXDEPS} "${OBJECTDIR}/driver/source/gpio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/driver/source/gpio.o.d" -o ${OBJECTDIR}/driver/source/gpio.o driver/source/gpio.c   
	
${OBJECTDIR}/driver/source/clock.o: driver/source/clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/driver/source 
	@${RM} ${OBJECTDIR}/driver/source/clock.o.d 
	@${RM} ${OBJECTDIR}/driver/source/clock.o 
	@${FIXDEPS} "${OBJECTDIR}/driver/source/clock.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/driver/source/clock.o.d" -o ${OBJECTDIR}/driver/source/clock.o driver/source/clock.c   
	
${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/intr.o: esolid-base/port/pic32-none-gcc/mips-m4k/intr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k 
	@${RM} ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/intr.o.d 
	@${RM} ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/intr.o 
	@${FIXDEPS} "${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/intr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/intr.o.d" -o ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/intr.o esolid-base/port/pic32-none-gcc/mips-m4k/intr.c   
	
${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/systimer.o: esolid-base/port/pic32-none-gcc/mips-m4k/systimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k 
	@${RM} ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/systimer.o.d 
	@${RM} ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/systimer.o 
	@${FIXDEPS} "${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/systimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/systimer.o.d" -o ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/systimer.o esolid-base/port/pic32-none-gcc/mips-m4k/systimer.c   
	
${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/cpu.o: esolid-base/port/pic32-none-gcc/mips-m4k/cpu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k 
	@${RM} ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/cpu.o.d 
	@${RM} ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/cpu.o 
	@${FIXDEPS} "${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/cpu.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/cpu.o.d" -o ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/cpu.o esolid-base/port/pic32-none-gcc/mips-m4k/cpu.c   
	
${OBJECTDIR}/esolid-base/src/prio_queue.o: esolid-base/src/prio_queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/esolid-base/src 
	@${RM} ${OBJECTDIR}/esolid-base/src/prio_queue.o.d 
	@${RM} ${OBJECTDIR}/esolid-base/src/prio_queue.o 
	@${FIXDEPS} "${OBJECTDIR}/esolid-base/src/prio_queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/esolid-base/src/prio_queue.o.d" -o ${OBJECTDIR}/esolid-base/src/prio_queue.o esolid-base/src/prio_queue.c   
	
${OBJECTDIR}/esolid-base/src/base.o: esolid-base/src/base.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/esolid-base/src 
	@${RM} ${OBJECTDIR}/esolid-base/src/base.o.d 
	@${RM} ${OBJECTDIR}/esolid-base/src/base.o 
	@${FIXDEPS} "${OBJECTDIR}/esolid-base/src/base.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/esolid-base/src/base.o.d" -o ${OBJECTDIR}/esolid-base/src/base.o esolid-base/src/base.c   
	
${OBJECTDIR}/esolid-base/src/debug.o: esolid-base/src/debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/esolid-base/src 
	@${RM} ${OBJECTDIR}/esolid-base/src/debug.o.d 
	@${RM} ${OBJECTDIR}/esolid-base/src/debug.o 
	@${FIXDEPS} "${OBJECTDIR}/esolid-base/src/debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/esolid-base/src/debug.o.d" -o ${OBJECTDIR}/esolid-base/src/debug.o esolid-base/src/debug.c   
	
${OBJECTDIR}/esolid-base/src/error.o: esolid-base/src/error.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/esolid-base/src 
	@${RM} ${OBJECTDIR}/esolid-base/src/error.o.d 
	@${RM} ${OBJECTDIR}/esolid-base/src/error.o 
	@${FIXDEPS} "${OBJECTDIR}/esolid-base/src/error.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/esolid-base/src/error.o.d" -o ${OBJECTDIR}/esolid-base/src/error.o esolid-base/src/error.c   
	
else
${OBJECTDIR}/application/source/main.o: application/source/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/application/source 
	@${RM} ${OBJECTDIR}/application/source/main.o.d 
	@${RM} ${OBJECTDIR}/application/source/main.o 
	@${FIXDEPS} "${OBJECTDIR}/application/source/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/application/source/main.o.d" -o ${OBJECTDIR}/application/source/main.o application/source/main.c   
	
${OBJECTDIR}/application/source/support.o: application/source/support.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/application/source 
	@${RM} ${OBJECTDIR}/application/source/support.o.d 
	@${RM} ${OBJECTDIR}/application/source/support.o 
	@${FIXDEPS} "${OBJECTDIR}/application/source/support.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/application/source/support.o.d" -o ${OBJECTDIR}/application/source/support.o application/source/support.c   
	
${OBJECTDIR}/driver/source/intr.o: driver/source/intr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/driver/source 
	@${RM} ${OBJECTDIR}/driver/source/intr.o.d 
	@${RM} ${OBJECTDIR}/driver/source/intr.o 
	@${FIXDEPS} "${OBJECTDIR}/driver/source/intr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/driver/source/intr.o.d" -o ${OBJECTDIR}/driver/source/intr.o driver/source/intr.c   
	
${OBJECTDIR}/driver/source/adc.o: driver/source/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/driver/source 
	@${RM} ${OBJECTDIR}/driver/source/adc.o.d 
	@${RM} ${OBJECTDIR}/driver/source/adc.o 
	@${FIXDEPS} "${OBJECTDIR}/driver/source/adc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/driver/source/adc.o.d" -o ${OBJECTDIR}/driver/source/adc.o driver/source/adc.c   
	
${OBJECTDIR}/driver/source/systick.o: driver/source/systick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/driver/source 
	@${RM} ${OBJECTDIR}/driver/source/systick.o.d 
	@${RM} ${OBJECTDIR}/driver/source/systick.o 
	@${FIXDEPS} "${OBJECTDIR}/driver/source/systick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/driver/source/systick.o.d" -o ${OBJECTDIR}/driver/source/systick.o driver/source/systick.c   
	
${OBJECTDIR}/driver/source/gpio.o: driver/source/gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/driver/source 
	@${RM} ${OBJECTDIR}/driver/source/gpio.o.d 
	@${RM} ${OBJECTDIR}/driver/source/gpio.o 
	@${FIXDEPS} "${OBJECTDIR}/driver/source/gpio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/driver/source/gpio.o.d" -o ${OBJECTDIR}/driver/source/gpio.o driver/source/gpio.c   
	
${OBJECTDIR}/driver/source/clock.o: driver/source/clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/driver/source 
	@${RM} ${OBJECTDIR}/driver/source/clock.o.d 
	@${RM} ${OBJECTDIR}/driver/source/clock.o 
	@${FIXDEPS} "${OBJECTDIR}/driver/source/clock.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/driver/source/clock.o.d" -o ${OBJECTDIR}/driver/source/clock.o driver/source/clock.c   
	
${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/intr.o: esolid-base/port/pic32-none-gcc/mips-m4k/intr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k 
	@${RM} ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/intr.o.d 
	@${RM} ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/intr.o 
	@${FIXDEPS} "${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/intr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/intr.o.d" -o ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/intr.o esolid-base/port/pic32-none-gcc/mips-m4k/intr.c   
	
${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/systimer.o: esolid-base/port/pic32-none-gcc/mips-m4k/systimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k 
	@${RM} ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/systimer.o.d 
	@${RM} ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/systimer.o 
	@${FIXDEPS} "${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/systimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/systimer.o.d" -o ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/systimer.o esolid-base/port/pic32-none-gcc/mips-m4k/systimer.c   
	
${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/cpu.o: esolid-base/port/pic32-none-gcc/mips-m4k/cpu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k 
	@${RM} ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/cpu.o.d 
	@${RM} ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/cpu.o 
	@${FIXDEPS} "${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/cpu.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/cpu.o.d" -o ${OBJECTDIR}/esolid-base/port/pic32-none-gcc/mips-m4k/cpu.o esolid-base/port/pic32-none-gcc/mips-m4k/cpu.c   
	
${OBJECTDIR}/esolid-base/src/prio_queue.o: esolid-base/src/prio_queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/esolid-base/src 
	@${RM} ${OBJECTDIR}/esolid-base/src/prio_queue.o.d 
	@${RM} ${OBJECTDIR}/esolid-base/src/prio_queue.o 
	@${FIXDEPS} "${OBJECTDIR}/esolid-base/src/prio_queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/esolid-base/src/prio_queue.o.d" -o ${OBJECTDIR}/esolid-base/src/prio_queue.o esolid-base/src/prio_queue.c   
	
${OBJECTDIR}/esolid-base/src/base.o: esolid-base/src/base.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/esolid-base/src 
	@${RM} ${OBJECTDIR}/esolid-base/src/base.o.d 
	@${RM} ${OBJECTDIR}/esolid-base/src/base.o 
	@${FIXDEPS} "${OBJECTDIR}/esolid-base/src/base.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/esolid-base/src/base.o.d" -o ${OBJECTDIR}/esolid-base/src/base.o esolid-base/src/base.c   
	
${OBJECTDIR}/esolid-base/src/debug.o: esolid-base/src/debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/esolid-base/src 
	@${RM} ${OBJECTDIR}/esolid-base/src/debug.o.d 
	@${RM} ${OBJECTDIR}/esolid-base/src/debug.o 
	@${FIXDEPS} "${OBJECTDIR}/esolid-base/src/debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/esolid-base/src/debug.o.d" -o ${OBJECTDIR}/esolid-base/src/debug.o esolid-base/src/debug.c   
	
${OBJECTDIR}/esolid-base/src/error.o: esolid-base/src/error.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/esolid-base/src 
	@${RM} ${OBJECTDIR}/esolid-base/src/error.o.d 
	@${RM} ${OBJECTDIR}/esolid-base/src/error.o 
	@${FIXDEPS} "${OBJECTDIR}/esolid-base/src/error.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"application/include" -I"driver/include" -I"esolid-base/inc" -I"esolid-base/port/pic32-none-gcc/common" -I"esolid-base/port/pic32-none-gcc/mips-m4k" -I"esolid-base/port/pic32-none-gcc/pic32mx250f128d" -MMD -MF "${OBJECTDIR}/esolid-base/src/error.o.d" -o ${OBJECTDIR}/esolid-base/src/error.o esolid-base/src/error.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/relay_logic_helper.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/relay_logic_helper.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}           -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/relay_logic_helper.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/relay_logic_helper.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/relay_logic_helper.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
