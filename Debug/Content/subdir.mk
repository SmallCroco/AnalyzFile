################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Content/CBaseFile.cpp 

OBJS += \
./Content/CBaseFile.o 

CPP_DEPS += \
./Content/CBaseFile.d 


# Each subdirectory must supply rules for building sources it contributes
Content/%.o: ../Content/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/smallcroco/workspace/AnalyzFile -I/home/smallcroco/workspace/AnalyzFile/Rule -I/home/smallcroco/workspace/AnalyzFile/Rule/RegularRule -I/home/smallcroco/workspace/AnalyzFile/Rule/KeywordsRule -I/home/smallcroco/workspace/AnalyzFile/Rule/RegularRule/PatternUnit -I/home/smallcroco/workspace/AnalyzFile/Result -I/home/smallcroco/workspace/AnalyzFile/Result/RegularResult -I/home/smallcroco/workspace/AnalyzFile/Result/KeywordsResult -I/home/smallcroco/workspace/AnalyzFile/Content -I/home/smallcroco/workspace/AnalyzFile/Content/XmlFile -I/home/smallcroco/workspace/AnalyzFile/Content/RtfFile -I/home/smallcroco/workspace/AnalyzFile/Content/HtmlFile -I/home/smallcroco/workspace/AnalyzFile/Content/ZipFile -I/home/smallcroco/workspace/AnalyzFile/Content/TxtFile -I/home/smallcroco/workspace/AnalyzFile/Content/TarFile -I/home/smallcroco/workspace/AnalyzFile/Content/RarFile -I/home/smallcroco/workspace/AnalyzFile/Content/PdfFile -I/home/smallcroco/workspace/AnalyzFile/Content/OffFile -I/home/smallcroco/workspace/AnalyzFile/Content/GzFile -I/home/smallcroco/workspace/AnalyzFile/Content/7zipFile -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


