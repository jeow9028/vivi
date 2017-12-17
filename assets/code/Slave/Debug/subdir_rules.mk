################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
IRBeamsSv.obj: ../IRBeamsSv.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Brandon/workspace_v7/Slave" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="IRBeamsSv.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

bluetooth.obj: ../bluetooth.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Brandon/workspace_v7/Slave" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="bluetooth.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

buffer.obj: ../buffer.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Brandon/workspace_v7/Slave" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="buffer.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

gpio1.obj: ../gpio1.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Brandon/workspace_v7/Slave" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="gpio1.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main_s.obj: ../main_s.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Brandon/workspace_v7/Slave" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="main_s.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup_msp432p401r_ccs.obj: ../startup_msp432p401r_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Brandon/workspace_v7/Slave" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="startup_msp432p401r_ccs.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

system_msp432p401r.obj: ../system_msp432p401r.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Brandon/workspace_v7/Slave" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="system_msp432p401r.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

timer.obj: ../timer.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Brandon/workspace_v7/Slave" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="timer.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uart.obj: ../uart.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Brandon/workspace_v7/Slave" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="uart.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


