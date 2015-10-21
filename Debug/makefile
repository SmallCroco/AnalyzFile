################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm

# All of the sources participating in the build are defined here
-include sources.mk
-include Rule/RegularRule/PatternUnit/subdir.mk
-include Rule/RegularRule/subdir.mk
-include Rule/KeywordsRule/subdir.mk
-include Rule/subdir.mk
-include Result/RegularResult/subdir.mk
-include Result/KeywordsResult/subdir.mk
-include Result/subdir.mk
-include Content/ZipFile/subdir.mk
-include Content/XmlFile/subdir.mk
-include Content/TxtFile/subdir.mk
-include Content/TarFile/subdir.mk
-include Content/RtfFile/subdir.mk
-include Content/RarFile/subdir.mk
-include Content/PdfFile/subdir.mk
-include Content/OffFile/subdir.mk
-include Content/HtmlFile/subdir.mk
-include Content/GzFile/subdir.mk
-include Content/7zipFile/subdir.mk
-include Content/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: AnalyzFile.exe

# Tool invocations
AnalyzFile.exe: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -L/usr/lib -L/usr/lib/pcre8.37 -o "AnalyzFile.exe" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) AnalyzFile.exe
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
