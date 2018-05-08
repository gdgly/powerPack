################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Example_2806xSci_FFDLB_int.obj: ../Example_2806xSci_FFDLB_int.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/home/eunwho/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="/home/eunwho/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.3.LTS/include" --include_path="/home/eunwho/f28069/f2806x/headers/include" --include_path="/home/eunwho/f28069/f2806x/common/include" --include_path="/home/eunwho/f28069/libraries/math/IQmath/c28/lib" --include_path="/home/eunwho/f28069/libraries/math/FPUfastRTS/c28/lib" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="Example_2806xSci_FFDLB_int.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_CodeStartBranch.obj: /home/eunwho/f28069/f2806x/common/source/F2806x_CodeStartBranch.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/home/eunwho/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="/home/eunwho/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.3.LTS/include" --include_path="/home/eunwho/f28069/f2806x/headers/include" --include_path="/home/eunwho/f28069/f2806x/common/include" --include_path="/home/eunwho/f28069/libraries/math/IQmath/c28/lib" --include_path="/home/eunwho/f28069/libraries/math/FPUfastRTS/c28/lib" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="F2806x_CodeStartBranch.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_DefaultIsr.obj: /home/eunwho/f28069/f2806x/common/source/F2806x_DefaultIsr.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/home/eunwho/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="/home/eunwho/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.3.LTS/include" --include_path="/home/eunwho/f28069/f2806x/headers/include" --include_path="/home/eunwho/f28069/f2806x/common/include" --include_path="/home/eunwho/f28069/libraries/math/IQmath/c28/lib" --include_path="/home/eunwho/f28069/libraries/math/FPUfastRTS/c28/lib" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="F2806x_DefaultIsr.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_GlobalVariableDefs.obj: /home/eunwho/f28069/f2806x/headers/source/F2806x_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/home/eunwho/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="/home/eunwho/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.3.LTS/include" --include_path="/home/eunwho/f28069/f2806x/headers/include" --include_path="/home/eunwho/f28069/f2806x/common/include" --include_path="/home/eunwho/f28069/libraries/math/IQmath/c28/lib" --include_path="/home/eunwho/f28069/libraries/math/FPUfastRTS/c28/lib" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="F2806x_GlobalVariableDefs.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_PieCtrl.obj: /home/eunwho/f28069/f2806x/common/source/F2806x_PieCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/home/eunwho/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="/home/eunwho/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.3.LTS/include" --include_path="/home/eunwho/f28069/f2806x/headers/include" --include_path="/home/eunwho/f28069/f2806x/common/include" --include_path="/home/eunwho/f28069/libraries/math/IQmath/c28/lib" --include_path="/home/eunwho/f28069/libraries/math/FPUfastRTS/c28/lib" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="F2806x_PieCtrl.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_PieVect.obj: /home/eunwho/f28069/f2806x/common/source/F2806x_PieVect.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/home/eunwho/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="/home/eunwho/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.3.LTS/include" --include_path="/home/eunwho/f28069/f2806x/headers/include" --include_path="/home/eunwho/f28069/f2806x/common/include" --include_path="/home/eunwho/f28069/libraries/math/IQmath/c28/lib" --include_path="/home/eunwho/f28069/libraries/math/FPUfastRTS/c28/lib" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="F2806x_PieVect.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_Sci.obj: /home/eunwho/f28069/f2806x/common/source/F2806x_Sci.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/home/eunwho/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="/home/eunwho/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.3.LTS/include" --include_path="/home/eunwho/f28069/f2806x/headers/include" --include_path="/home/eunwho/f28069/f2806x/common/include" --include_path="/home/eunwho/f28069/libraries/math/IQmath/c28/lib" --include_path="/home/eunwho/f28069/libraries/math/FPUfastRTS/c28/lib" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="F2806x_Sci.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_SysCtrl.obj: /home/eunwho/f28069/f2806x/common/source/F2806x_SysCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/home/eunwho/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="/home/eunwho/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.3.LTS/include" --include_path="/home/eunwho/f28069/f2806x/headers/include" --include_path="/home/eunwho/f28069/f2806x/common/include" --include_path="/home/eunwho/f28069/libraries/math/IQmath/c28/lib" --include_path="/home/eunwho/f28069/libraries/math/FPUfastRTS/c28/lib" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="F2806x_SysCtrl.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_usDelay.obj: /home/eunwho/f28069/f2806x/common/source/F2806x_usDelay.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/home/eunwho/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="/home/eunwho/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.3.LTS/include" --include_path="/home/eunwho/f28069/f2806x/headers/include" --include_path="/home/eunwho/f28069/f2806x/common/include" --include_path="/home/eunwho/f28069/libraries/math/IQmath/c28/lib" --include_path="/home/eunwho/f28069/libraries/math/FPUfastRTS/c28/lib" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="F2806x_usDelay.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


