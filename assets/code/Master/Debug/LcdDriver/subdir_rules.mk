################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
LcdDriver/Crystalfontz128x128_ST7735.obj: ../LcdDriver/Crystalfontz128x128_ST7735.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/Users/Brandon/workspace_v7/Master/driverlib/MSP432P4xx" --include_path="C:/Users/Brandon/workspace_v7/Master/GrLib/fonts" --include_path="C:/Users/Brandon/workspace_v7/EmbeddedFinal/GrLib/grlib" --include_path="C:/Users/Brandon/workspace_v7/Master/LcdDriver" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Brandon/workspace_v7/Master" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="LcdDriver/Crystalfontz128x128_ST7735.d" --obj_directory="LcdDriver" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.obj: ../LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/Users/Brandon/workspace_v7/Master/driverlib/MSP432P4xx" --include_path="C:/Users/Brandon/workspace_v7/Master/GrLib/fonts" --include_path="C:/Users/Brandon/workspace_v7/EmbeddedFinal/GrLib/grlib" --include_path="C:/Users/Brandon/workspace_v7/Master/LcdDriver" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Brandon/workspace_v7/Master" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.d" --obj_directory="LcdDriver" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

LcdDriver/lcdconfig.obj: ../LcdDriver/lcdconfig.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/Users/Brandon/workspace_v7/Master/driverlib/MSP432P4xx" --include_path="C:/Users/Brandon/workspace_v7/Master/GrLib/fonts" --include_path="C:/Users/Brandon/workspace_v7/EmbeddedFinal/GrLib/grlib" --include_path="C:/Users/Brandon/workspace_v7/Master/LcdDriver" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Brandon/workspace_v7/Master" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="LcdDriver/lcdconfig.d" --obj_directory="LcdDriver" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


