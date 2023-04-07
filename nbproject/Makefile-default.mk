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
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ACCM_GasSyetem_MCU-HMI.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ACCM_GasSyetem_MCU-HMI.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/iosetting.c src/main.c src/EXT_ACD_DAC_Driver.c src/SYS_Driver.c src/IO_Driver.c src/User_ISR.c src/UART_Driver.c src/Data_API.c src/PWM_Setting.c src/Encoder_Driver.c src/SystemControl.c src/StorageDev.c src/InputPortScan.c src/HMI_Control.c src/COM3_RX_Parsing.c src/uC_HMI_Control.c src/uC_HMI_Sending.c src/uC_HMI_Parsing.c src/uC_HMI_Utility.c src/Machine_uC_HMI_Sending.c src/Machine_uC_HMI_Parsing.c src/Machine_uC_HMI_Control.c src/InitialSystemTestParameter.c src/SystemParameterInputProcess.c src/COM3_TX.c src/RunTimeDisplayControl.c src/COM2_RX_ParsingExtDevice.c src/COM2_TX_ToExtDevice.c src/Android_HMI_Parsing.c src/Android_HMI_Sending.c src/Android_HMI_AlarmPacket_Generator.c src/Android_HMI_GetParameterResponsePacketGenerator.c src/Android_HMI_WriteParameters.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/iosetting.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/EXT_ACD_DAC_Driver.o ${OBJECTDIR}/src/SYS_Driver.o ${OBJECTDIR}/src/IO_Driver.o ${OBJECTDIR}/src/User_ISR.o ${OBJECTDIR}/src/UART_Driver.o ${OBJECTDIR}/src/Data_API.o ${OBJECTDIR}/src/PWM_Setting.o ${OBJECTDIR}/src/Encoder_Driver.o ${OBJECTDIR}/src/SystemControl.o ${OBJECTDIR}/src/StorageDev.o ${OBJECTDIR}/src/InputPortScan.o ${OBJECTDIR}/src/HMI_Control.o ${OBJECTDIR}/src/COM3_RX_Parsing.o ${OBJECTDIR}/src/uC_HMI_Control.o ${OBJECTDIR}/src/uC_HMI_Sending.o ${OBJECTDIR}/src/uC_HMI_Parsing.o ${OBJECTDIR}/src/uC_HMI_Utility.o ${OBJECTDIR}/src/Machine_uC_HMI_Sending.o ${OBJECTDIR}/src/Machine_uC_HMI_Parsing.o ${OBJECTDIR}/src/Machine_uC_HMI_Control.o ${OBJECTDIR}/src/InitialSystemTestParameter.o ${OBJECTDIR}/src/SystemParameterInputProcess.o ${OBJECTDIR}/src/COM3_TX.o ${OBJECTDIR}/src/RunTimeDisplayControl.o ${OBJECTDIR}/src/COM2_RX_ParsingExtDevice.o ${OBJECTDIR}/src/COM2_TX_ToExtDevice.o ${OBJECTDIR}/src/Android_HMI_Parsing.o ${OBJECTDIR}/src/Android_HMI_Sending.o ${OBJECTDIR}/src/Android_HMI_AlarmPacket_Generator.o ${OBJECTDIR}/src/Android_HMI_GetParameterResponsePacketGenerator.o ${OBJECTDIR}/src/Android_HMI_WriteParameters.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/iosetting.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/EXT_ACD_DAC_Driver.o.d ${OBJECTDIR}/src/SYS_Driver.o.d ${OBJECTDIR}/src/IO_Driver.o.d ${OBJECTDIR}/src/User_ISR.o.d ${OBJECTDIR}/src/UART_Driver.o.d ${OBJECTDIR}/src/Data_API.o.d ${OBJECTDIR}/src/PWM_Setting.o.d ${OBJECTDIR}/src/Encoder_Driver.o.d ${OBJECTDIR}/src/SystemControl.o.d ${OBJECTDIR}/src/StorageDev.o.d ${OBJECTDIR}/src/InputPortScan.o.d ${OBJECTDIR}/src/HMI_Control.o.d ${OBJECTDIR}/src/COM3_RX_Parsing.o.d ${OBJECTDIR}/src/uC_HMI_Control.o.d ${OBJECTDIR}/src/uC_HMI_Sending.o.d ${OBJECTDIR}/src/uC_HMI_Parsing.o.d ${OBJECTDIR}/src/uC_HMI_Utility.o.d ${OBJECTDIR}/src/Machine_uC_HMI_Sending.o.d ${OBJECTDIR}/src/Machine_uC_HMI_Parsing.o.d ${OBJECTDIR}/src/Machine_uC_HMI_Control.o.d ${OBJECTDIR}/src/InitialSystemTestParameter.o.d ${OBJECTDIR}/src/SystemParameterInputProcess.o.d ${OBJECTDIR}/src/COM3_TX.o.d ${OBJECTDIR}/src/RunTimeDisplayControl.o.d ${OBJECTDIR}/src/COM2_RX_ParsingExtDevice.o.d ${OBJECTDIR}/src/COM2_TX_ToExtDevice.o.d ${OBJECTDIR}/src/Android_HMI_Parsing.o.d ${OBJECTDIR}/src/Android_HMI_Sending.o.d ${OBJECTDIR}/src/Android_HMI_AlarmPacket_Generator.o.d ${OBJECTDIR}/src/Android_HMI_GetParameterResponsePacketGenerator.o.d ${OBJECTDIR}/src/Android_HMI_WriteParameters.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/iosetting.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/EXT_ACD_DAC_Driver.o ${OBJECTDIR}/src/SYS_Driver.o ${OBJECTDIR}/src/IO_Driver.o ${OBJECTDIR}/src/User_ISR.o ${OBJECTDIR}/src/UART_Driver.o ${OBJECTDIR}/src/Data_API.o ${OBJECTDIR}/src/PWM_Setting.o ${OBJECTDIR}/src/Encoder_Driver.o ${OBJECTDIR}/src/SystemControl.o ${OBJECTDIR}/src/StorageDev.o ${OBJECTDIR}/src/InputPortScan.o ${OBJECTDIR}/src/HMI_Control.o ${OBJECTDIR}/src/COM3_RX_Parsing.o ${OBJECTDIR}/src/uC_HMI_Control.o ${OBJECTDIR}/src/uC_HMI_Sending.o ${OBJECTDIR}/src/uC_HMI_Parsing.o ${OBJECTDIR}/src/uC_HMI_Utility.o ${OBJECTDIR}/src/Machine_uC_HMI_Sending.o ${OBJECTDIR}/src/Machine_uC_HMI_Parsing.o ${OBJECTDIR}/src/Machine_uC_HMI_Control.o ${OBJECTDIR}/src/InitialSystemTestParameter.o ${OBJECTDIR}/src/SystemParameterInputProcess.o ${OBJECTDIR}/src/COM3_TX.o ${OBJECTDIR}/src/RunTimeDisplayControl.o ${OBJECTDIR}/src/COM2_RX_ParsingExtDevice.o ${OBJECTDIR}/src/COM2_TX_ToExtDevice.o ${OBJECTDIR}/src/Android_HMI_Parsing.o ${OBJECTDIR}/src/Android_HMI_Sending.o ${OBJECTDIR}/src/Android_HMI_AlarmPacket_Generator.o ${OBJECTDIR}/src/Android_HMI_GetParameterResponsePacketGenerator.o ${OBJECTDIR}/src/Android_HMI_WriteParameters.o

# Source Files
SOURCEFILES=src/iosetting.c src/main.c src/EXT_ACD_DAC_Driver.c src/SYS_Driver.c src/IO_Driver.c src/User_ISR.c src/UART_Driver.c src/Data_API.c src/PWM_Setting.c src/Encoder_Driver.c src/SystemControl.c src/StorageDev.c src/InputPortScan.c src/HMI_Control.c src/COM3_RX_Parsing.c src/uC_HMI_Control.c src/uC_HMI_Sending.c src/uC_HMI_Parsing.c src/uC_HMI_Utility.c src/Machine_uC_HMI_Sending.c src/Machine_uC_HMI_Parsing.c src/Machine_uC_HMI_Control.c src/InitialSystemTestParameter.c src/SystemParameterInputProcess.c src/COM3_TX.c src/RunTimeDisplayControl.c src/COM2_RX_ParsingExtDevice.c src/COM2_TX_ToExtDevice.c src/Android_HMI_Parsing.c src/Android_HMI_Sending.c src/Android_HMI_AlarmPacket_Generator.c src/Android_HMI_GetParameterResponsePacketGenerator.c src/Android_HMI_WriteParameters.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/ACCM_GasSyetem_MCU-HMI.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP512MU814
MP_LINKER_FILE_OPTION=,--script=p33EP512MU814.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/iosetting.o: src/iosetting.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/iosetting.o.d 
	@${RM} ${OBJECTDIR}/src/iosetting.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/iosetting.c  -o ${OBJECTDIR}/src/iosetting.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/iosetting.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/iosetting.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/EXT_ACD_DAC_Driver.o: src/EXT_ACD_DAC_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/EXT_ACD_DAC_Driver.o.d 
	@${RM} ${OBJECTDIR}/src/EXT_ACD_DAC_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EXT_ACD_DAC_Driver.c  -o ${OBJECTDIR}/src/EXT_ACD_DAC_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/EXT_ACD_DAC_Driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/EXT_ACD_DAC_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/SYS_Driver.o: src/SYS_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/SYS_Driver.o.d 
	@${RM} ${OBJECTDIR}/src/SYS_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/SYS_Driver.c  -o ${OBJECTDIR}/src/SYS_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/SYS_Driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/SYS_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/IO_Driver.o: src/IO_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/IO_Driver.o.d 
	@${RM} ${OBJECTDIR}/src/IO_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/IO_Driver.c  -o ${OBJECTDIR}/src/IO_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/IO_Driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/IO_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/User_ISR.o: src/User_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/User_ISR.o.d 
	@${RM} ${OBJECTDIR}/src/User_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/User_ISR.c  -o ${OBJECTDIR}/src/User_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/User_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/User_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/UART_Driver.o: src/UART_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/UART_Driver.o.d 
	@${RM} ${OBJECTDIR}/src/UART_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/UART_Driver.c  -o ${OBJECTDIR}/src/UART_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/UART_Driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/UART_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Data_API.o: src/Data_API.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Data_API.o.d 
	@${RM} ${OBJECTDIR}/src/Data_API.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Data_API.c  -o ${OBJECTDIR}/src/Data_API.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Data_API.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/Data_API.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/PWM_Setting.o: src/PWM_Setting.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/PWM_Setting.o.d 
	@${RM} ${OBJECTDIR}/src/PWM_Setting.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/PWM_Setting.c  -o ${OBJECTDIR}/src/PWM_Setting.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/PWM_Setting.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/PWM_Setting.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Encoder_Driver.o: src/Encoder_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Encoder_Driver.o.d 
	@${RM} ${OBJECTDIR}/src/Encoder_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Encoder_Driver.c  -o ${OBJECTDIR}/src/Encoder_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Encoder_Driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/Encoder_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/SystemControl.o: src/SystemControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/SystemControl.o.d 
	@${RM} ${OBJECTDIR}/src/SystemControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/SystemControl.c  -o ${OBJECTDIR}/src/SystemControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/SystemControl.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/SystemControl.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/StorageDev.o: src/StorageDev.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/StorageDev.o.d 
	@${RM} ${OBJECTDIR}/src/StorageDev.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/StorageDev.c  -o ${OBJECTDIR}/src/StorageDev.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/StorageDev.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/StorageDev.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/InputPortScan.o: src/InputPortScan.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/InputPortScan.o.d 
	@${RM} ${OBJECTDIR}/src/InputPortScan.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/InputPortScan.c  -o ${OBJECTDIR}/src/InputPortScan.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/InputPortScan.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/InputPortScan.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/HMI_Control.o: src/HMI_Control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/HMI_Control.o.d 
	@${RM} ${OBJECTDIR}/src/HMI_Control.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/HMI_Control.c  -o ${OBJECTDIR}/src/HMI_Control.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/HMI_Control.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/HMI_Control.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/COM3_RX_Parsing.o: src/COM3_RX_Parsing.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/COM3_RX_Parsing.o.d 
	@${RM} ${OBJECTDIR}/src/COM3_RX_Parsing.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/COM3_RX_Parsing.c  -o ${OBJECTDIR}/src/COM3_RX_Parsing.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/COM3_RX_Parsing.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/COM3_RX_Parsing.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/uC_HMI_Control.o: src/uC_HMI_Control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uC_HMI_Control.o.d 
	@${RM} ${OBJECTDIR}/src/uC_HMI_Control.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uC_HMI_Control.c  -o ${OBJECTDIR}/src/uC_HMI_Control.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/uC_HMI_Control.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/uC_HMI_Control.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/uC_HMI_Sending.o: src/uC_HMI_Sending.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uC_HMI_Sending.o.d 
	@${RM} ${OBJECTDIR}/src/uC_HMI_Sending.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uC_HMI_Sending.c  -o ${OBJECTDIR}/src/uC_HMI_Sending.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/uC_HMI_Sending.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/uC_HMI_Sending.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/uC_HMI_Parsing.o: src/uC_HMI_Parsing.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uC_HMI_Parsing.o.d 
	@${RM} ${OBJECTDIR}/src/uC_HMI_Parsing.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uC_HMI_Parsing.c  -o ${OBJECTDIR}/src/uC_HMI_Parsing.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/uC_HMI_Parsing.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/uC_HMI_Parsing.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/uC_HMI_Utility.o: src/uC_HMI_Utility.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uC_HMI_Utility.o.d 
	@${RM} ${OBJECTDIR}/src/uC_HMI_Utility.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uC_HMI_Utility.c  -o ${OBJECTDIR}/src/uC_HMI_Utility.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/uC_HMI_Utility.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/uC_HMI_Utility.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Machine_uC_HMI_Sending.o: src/Machine_uC_HMI_Sending.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Machine_uC_HMI_Sending.o.d 
	@${RM} ${OBJECTDIR}/src/Machine_uC_HMI_Sending.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Machine_uC_HMI_Sending.c  -o ${OBJECTDIR}/src/Machine_uC_HMI_Sending.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Machine_uC_HMI_Sending.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/Machine_uC_HMI_Sending.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Machine_uC_HMI_Parsing.o: src/Machine_uC_HMI_Parsing.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Machine_uC_HMI_Parsing.o.d 
	@${RM} ${OBJECTDIR}/src/Machine_uC_HMI_Parsing.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Machine_uC_HMI_Parsing.c  -o ${OBJECTDIR}/src/Machine_uC_HMI_Parsing.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Machine_uC_HMI_Parsing.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/Machine_uC_HMI_Parsing.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Machine_uC_HMI_Control.o: src/Machine_uC_HMI_Control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Machine_uC_HMI_Control.o.d 
	@${RM} ${OBJECTDIR}/src/Machine_uC_HMI_Control.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Machine_uC_HMI_Control.c  -o ${OBJECTDIR}/src/Machine_uC_HMI_Control.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Machine_uC_HMI_Control.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/Machine_uC_HMI_Control.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/InitialSystemTestParameter.o: src/InitialSystemTestParameter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/InitialSystemTestParameter.o.d 
	@${RM} ${OBJECTDIR}/src/InitialSystemTestParameter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/InitialSystemTestParameter.c  -o ${OBJECTDIR}/src/InitialSystemTestParameter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/InitialSystemTestParameter.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/InitialSystemTestParameter.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/SystemParameterInputProcess.o: src/SystemParameterInputProcess.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/SystemParameterInputProcess.o.d 
	@${RM} ${OBJECTDIR}/src/SystemParameterInputProcess.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/SystemParameterInputProcess.c  -o ${OBJECTDIR}/src/SystemParameterInputProcess.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/SystemParameterInputProcess.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/SystemParameterInputProcess.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/COM3_TX.o: src/COM3_TX.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/COM3_TX.o.d 
	@${RM} ${OBJECTDIR}/src/COM3_TX.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/COM3_TX.c  -o ${OBJECTDIR}/src/COM3_TX.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/COM3_TX.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/COM3_TX.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/RunTimeDisplayControl.o: src/RunTimeDisplayControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/RunTimeDisplayControl.o.d 
	@${RM} ${OBJECTDIR}/src/RunTimeDisplayControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RunTimeDisplayControl.c  -o ${OBJECTDIR}/src/RunTimeDisplayControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/RunTimeDisplayControl.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/RunTimeDisplayControl.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/COM2_RX_ParsingExtDevice.o: src/COM2_RX_ParsingExtDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/COM2_RX_ParsingExtDevice.o.d 
	@${RM} ${OBJECTDIR}/src/COM2_RX_ParsingExtDevice.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/COM2_RX_ParsingExtDevice.c  -o ${OBJECTDIR}/src/COM2_RX_ParsingExtDevice.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/COM2_RX_ParsingExtDevice.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/COM2_RX_ParsingExtDevice.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/COM2_TX_ToExtDevice.o: src/COM2_TX_ToExtDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/COM2_TX_ToExtDevice.o.d 
	@${RM} ${OBJECTDIR}/src/COM2_TX_ToExtDevice.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/COM2_TX_ToExtDevice.c  -o ${OBJECTDIR}/src/COM2_TX_ToExtDevice.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/COM2_TX_ToExtDevice.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/COM2_TX_ToExtDevice.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Android_HMI_Parsing.o: src/Android_HMI_Parsing.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Android_HMI_Parsing.o.d 
	@${RM} ${OBJECTDIR}/src/Android_HMI_Parsing.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Android_HMI_Parsing.c  -o ${OBJECTDIR}/src/Android_HMI_Parsing.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Android_HMI_Parsing.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/Android_HMI_Parsing.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Android_HMI_Sending.o: src/Android_HMI_Sending.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Android_HMI_Sending.o.d 
	@${RM} ${OBJECTDIR}/src/Android_HMI_Sending.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Android_HMI_Sending.c  -o ${OBJECTDIR}/src/Android_HMI_Sending.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Android_HMI_Sending.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/Android_HMI_Sending.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Android_HMI_AlarmPacket_Generator.o: src/Android_HMI_AlarmPacket_Generator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Android_HMI_AlarmPacket_Generator.o.d 
	@${RM} ${OBJECTDIR}/src/Android_HMI_AlarmPacket_Generator.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Android_HMI_AlarmPacket_Generator.c  -o ${OBJECTDIR}/src/Android_HMI_AlarmPacket_Generator.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Android_HMI_AlarmPacket_Generator.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/Android_HMI_AlarmPacket_Generator.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Android_HMI_GetParameterResponsePacketGenerator.o: src/Android_HMI_GetParameterResponsePacketGenerator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Android_HMI_GetParameterResponsePacketGenerator.o.d 
	@${RM} ${OBJECTDIR}/src/Android_HMI_GetParameterResponsePacketGenerator.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Android_HMI_GetParameterResponsePacketGenerator.c  -o ${OBJECTDIR}/src/Android_HMI_GetParameterResponsePacketGenerator.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Android_HMI_GetParameterResponsePacketGenerator.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/Android_HMI_GetParameterResponsePacketGenerator.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Android_HMI_WriteParameters.o: src/Android_HMI_WriteParameters.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Android_HMI_WriteParameters.o.d 
	@${RM} ${OBJECTDIR}/src/Android_HMI_WriteParameters.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Android_HMI_WriteParameters.c  -o ${OBJECTDIR}/src/Android_HMI_WriteParameters.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Android_HMI_WriteParameters.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/Android_HMI_WriteParameters.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/src/iosetting.o: src/iosetting.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/iosetting.o.d 
	@${RM} ${OBJECTDIR}/src/iosetting.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/iosetting.c  -o ${OBJECTDIR}/src/iosetting.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/iosetting.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/iosetting.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/EXT_ACD_DAC_Driver.o: src/EXT_ACD_DAC_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/EXT_ACD_DAC_Driver.o.d 
	@${RM} ${OBJECTDIR}/src/EXT_ACD_DAC_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EXT_ACD_DAC_Driver.c  -o ${OBJECTDIR}/src/EXT_ACD_DAC_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/EXT_ACD_DAC_Driver.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/EXT_ACD_DAC_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/SYS_Driver.o: src/SYS_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/SYS_Driver.o.d 
	@${RM} ${OBJECTDIR}/src/SYS_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/SYS_Driver.c  -o ${OBJECTDIR}/src/SYS_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/SYS_Driver.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/SYS_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/IO_Driver.o: src/IO_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/IO_Driver.o.d 
	@${RM} ${OBJECTDIR}/src/IO_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/IO_Driver.c  -o ${OBJECTDIR}/src/IO_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/IO_Driver.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/IO_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/User_ISR.o: src/User_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/User_ISR.o.d 
	@${RM} ${OBJECTDIR}/src/User_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/User_ISR.c  -o ${OBJECTDIR}/src/User_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/User_ISR.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/User_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/UART_Driver.o: src/UART_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/UART_Driver.o.d 
	@${RM} ${OBJECTDIR}/src/UART_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/UART_Driver.c  -o ${OBJECTDIR}/src/UART_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/UART_Driver.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/UART_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Data_API.o: src/Data_API.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Data_API.o.d 
	@${RM} ${OBJECTDIR}/src/Data_API.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Data_API.c  -o ${OBJECTDIR}/src/Data_API.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Data_API.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/Data_API.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/PWM_Setting.o: src/PWM_Setting.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/PWM_Setting.o.d 
	@${RM} ${OBJECTDIR}/src/PWM_Setting.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/PWM_Setting.c  -o ${OBJECTDIR}/src/PWM_Setting.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/PWM_Setting.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/PWM_Setting.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Encoder_Driver.o: src/Encoder_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Encoder_Driver.o.d 
	@${RM} ${OBJECTDIR}/src/Encoder_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Encoder_Driver.c  -o ${OBJECTDIR}/src/Encoder_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Encoder_Driver.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/Encoder_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/SystemControl.o: src/SystemControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/SystemControl.o.d 
	@${RM} ${OBJECTDIR}/src/SystemControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/SystemControl.c  -o ${OBJECTDIR}/src/SystemControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/SystemControl.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/SystemControl.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/StorageDev.o: src/StorageDev.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/StorageDev.o.d 
	@${RM} ${OBJECTDIR}/src/StorageDev.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/StorageDev.c  -o ${OBJECTDIR}/src/StorageDev.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/StorageDev.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/StorageDev.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/InputPortScan.o: src/InputPortScan.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/InputPortScan.o.d 
	@${RM} ${OBJECTDIR}/src/InputPortScan.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/InputPortScan.c  -o ${OBJECTDIR}/src/InputPortScan.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/InputPortScan.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/InputPortScan.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/HMI_Control.o: src/HMI_Control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/HMI_Control.o.d 
	@${RM} ${OBJECTDIR}/src/HMI_Control.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/HMI_Control.c  -o ${OBJECTDIR}/src/HMI_Control.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/HMI_Control.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/HMI_Control.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/COM3_RX_Parsing.o: src/COM3_RX_Parsing.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/COM3_RX_Parsing.o.d 
	@${RM} ${OBJECTDIR}/src/COM3_RX_Parsing.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/COM3_RX_Parsing.c  -o ${OBJECTDIR}/src/COM3_RX_Parsing.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/COM3_RX_Parsing.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/COM3_RX_Parsing.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/uC_HMI_Control.o: src/uC_HMI_Control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uC_HMI_Control.o.d 
	@${RM} ${OBJECTDIR}/src/uC_HMI_Control.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uC_HMI_Control.c  -o ${OBJECTDIR}/src/uC_HMI_Control.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/uC_HMI_Control.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/uC_HMI_Control.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/uC_HMI_Sending.o: src/uC_HMI_Sending.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uC_HMI_Sending.o.d 
	@${RM} ${OBJECTDIR}/src/uC_HMI_Sending.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uC_HMI_Sending.c  -o ${OBJECTDIR}/src/uC_HMI_Sending.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/uC_HMI_Sending.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/uC_HMI_Sending.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/uC_HMI_Parsing.o: src/uC_HMI_Parsing.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uC_HMI_Parsing.o.d 
	@${RM} ${OBJECTDIR}/src/uC_HMI_Parsing.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uC_HMI_Parsing.c  -o ${OBJECTDIR}/src/uC_HMI_Parsing.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/uC_HMI_Parsing.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/uC_HMI_Parsing.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/uC_HMI_Utility.o: src/uC_HMI_Utility.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uC_HMI_Utility.o.d 
	@${RM} ${OBJECTDIR}/src/uC_HMI_Utility.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uC_HMI_Utility.c  -o ${OBJECTDIR}/src/uC_HMI_Utility.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/uC_HMI_Utility.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/uC_HMI_Utility.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Machine_uC_HMI_Sending.o: src/Machine_uC_HMI_Sending.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Machine_uC_HMI_Sending.o.d 
	@${RM} ${OBJECTDIR}/src/Machine_uC_HMI_Sending.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Machine_uC_HMI_Sending.c  -o ${OBJECTDIR}/src/Machine_uC_HMI_Sending.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Machine_uC_HMI_Sending.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/Machine_uC_HMI_Sending.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Machine_uC_HMI_Parsing.o: src/Machine_uC_HMI_Parsing.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Machine_uC_HMI_Parsing.o.d 
	@${RM} ${OBJECTDIR}/src/Machine_uC_HMI_Parsing.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Machine_uC_HMI_Parsing.c  -o ${OBJECTDIR}/src/Machine_uC_HMI_Parsing.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Machine_uC_HMI_Parsing.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/Machine_uC_HMI_Parsing.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Machine_uC_HMI_Control.o: src/Machine_uC_HMI_Control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Machine_uC_HMI_Control.o.d 
	@${RM} ${OBJECTDIR}/src/Machine_uC_HMI_Control.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Machine_uC_HMI_Control.c  -o ${OBJECTDIR}/src/Machine_uC_HMI_Control.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Machine_uC_HMI_Control.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/Machine_uC_HMI_Control.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/InitialSystemTestParameter.o: src/InitialSystemTestParameter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/InitialSystemTestParameter.o.d 
	@${RM} ${OBJECTDIR}/src/InitialSystemTestParameter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/InitialSystemTestParameter.c  -o ${OBJECTDIR}/src/InitialSystemTestParameter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/InitialSystemTestParameter.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/InitialSystemTestParameter.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/SystemParameterInputProcess.o: src/SystemParameterInputProcess.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/SystemParameterInputProcess.o.d 
	@${RM} ${OBJECTDIR}/src/SystemParameterInputProcess.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/SystemParameterInputProcess.c  -o ${OBJECTDIR}/src/SystemParameterInputProcess.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/SystemParameterInputProcess.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/SystemParameterInputProcess.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/COM3_TX.o: src/COM3_TX.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/COM3_TX.o.d 
	@${RM} ${OBJECTDIR}/src/COM3_TX.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/COM3_TX.c  -o ${OBJECTDIR}/src/COM3_TX.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/COM3_TX.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/COM3_TX.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/RunTimeDisplayControl.o: src/RunTimeDisplayControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/RunTimeDisplayControl.o.d 
	@${RM} ${OBJECTDIR}/src/RunTimeDisplayControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RunTimeDisplayControl.c  -o ${OBJECTDIR}/src/RunTimeDisplayControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/RunTimeDisplayControl.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/RunTimeDisplayControl.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/COM2_RX_ParsingExtDevice.o: src/COM2_RX_ParsingExtDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/COM2_RX_ParsingExtDevice.o.d 
	@${RM} ${OBJECTDIR}/src/COM2_RX_ParsingExtDevice.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/COM2_RX_ParsingExtDevice.c  -o ${OBJECTDIR}/src/COM2_RX_ParsingExtDevice.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/COM2_RX_ParsingExtDevice.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/COM2_RX_ParsingExtDevice.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/COM2_TX_ToExtDevice.o: src/COM2_TX_ToExtDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/COM2_TX_ToExtDevice.o.d 
	@${RM} ${OBJECTDIR}/src/COM2_TX_ToExtDevice.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/COM2_TX_ToExtDevice.c  -o ${OBJECTDIR}/src/COM2_TX_ToExtDevice.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/COM2_TX_ToExtDevice.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/COM2_TX_ToExtDevice.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Android_HMI_Parsing.o: src/Android_HMI_Parsing.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Android_HMI_Parsing.o.d 
	@${RM} ${OBJECTDIR}/src/Android_HMI_Parsing.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Android_HMI_Parsing.c  -o ${OBJECTDIR}/src/Android_HMI_Parsing.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Android_HMI_Parsing.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/Android_HMI_Parsing.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Android_HMI_Sending.o: src/Android_HMI_Sending.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Android_HMI_Sending.o.d 
	@${RM} ${OBJECTDIR}/src/Android_HMI_Sending.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Android_HMI_Sending.c  -o ${OBJECTDIR}/src/Android_HMI_Sending.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Android_HMI_Sending.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/Android_HMI_Sending.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Android_HMI_AlarmPacket_Generator.o: src/Android_HMI_AlarmPacket_Generator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Android_HMI_AlarmPacket_Generator.o.d 
	@${RM} ${OBJECTDIR}/src/Android_HMI_AlarmPacket_Generator.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Android_HMI_AlarmPacket_Generator.c  -o ${OBJECTDIR}/src/Android_HMI_AlarmPacket_Generator.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Android_HMI_AlarmPacket_Generator.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/Android_HMI_AlarmPacket_Generator.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Android_HMI_GetParameterResponsePacketGenerator.o: src/Android_HMI_GetParameterResponsePacketGenerator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Android_HMI_GetParameterResponsePacketGenerator.o.d 
	@${RM} ${OBJECTDIR}/src/Android_HMI_GetParameterResponsePacketGenerator.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Android_HMI_GetParameterResponsePacketGenerator.c  -o ${OBJECTDIR}/src/Android_HMI_GetParameterResponsePacketGenerator.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Android_HMI_GetParameterResponsePacketGenerator.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/Android_HMI_GetParameterResponsePacketGenerator.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Android_HMI_WriteParameters.o: src/Android_HMI_WriteParameters.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Android_HMI_WriteParameters.o.d 
	@${RM} ${OBJECTDIR}/src/Android_HMI_WriteParameters.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Android_HMI_WriteParameters.c  -o ${OBJECTDIR}/src/Android_HMI_WriteParameters.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Android_HMI_WriteParameters.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -mlarge-data -mlarge-scalar -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/Android_HMI_WriteParameters.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/ACCM_GasSyetem_MCU-HMI.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/ACCM_GasSyetem_MCU-HMI.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/ACCM_GasSyetem_MCU-HMI.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/ACCM_GasSyetem_MCU-HMI.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"h" -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/ACCM_GasSyetem_MCU-HMI.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
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

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
