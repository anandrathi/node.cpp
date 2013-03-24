##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=jsppnodejs
ConfigurationName      :=Release
WorkspacePath          := "/home/anandrathi/sre/jsppnodejs"
ProjectPath            := "/home/anandrathi/sre/jsppnodejs"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=anandrathi
Date                   :=03/24/2013
CodeLitePath           :="/home/anandrathi/.codelite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="jsppnodejs.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)/home/anandrathi/sre/node-v0.10.0/deps/http_parser 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -O2 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_tcp_wrap$(ObjectSuffix) $(IntermediateDirectory)/http_parser_test$(ObjectSuffix) $(IntermediateDirectory)/src_stream_wrap$(ObjectSuffix) $(IntermediateDirectory)/libjspp_http_parser$(ObjectSuffix) 

Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_tcp_wrap$(ObjectSuffix): ../node-v0.10.0/src/tcp_wrap.cc $(IntermediateDirectory)/src_tcp_wrap$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anandrathi/sre/node-v0.10.0/src/tcp_wrap.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_tcp_wrap$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_tcp_wrap$(DependSuffix): ../node-v0.10.0/src/tcp_wrap.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_tcp_wrap$(ObjectSuffix) -MF$(IntermediateDirectory)/src_tcp_wrap$(DependSuffix) -MM "../node-v0.10.0/src/tcp_wrap.cc"

$(IntermediateDirectory)/src_tcp_wrap$(PreprocessSuffix): ../node-v0.10.0/src/tcp_wrap.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_tcp_wrap$(PreprocessSuffix) "../node-v0.10.0/src/tcp_wrap.cc"

$(IntermediateDirectory)/http_parser_test$(ObjectSuffix): ../node-v0.10.0/deps/http_parser/test.c $(IntermediateDirectory)/http_parser_test$(DependSuffix)
	$(CXX) $(SourceSwitch) "/home/anandrathi/sre/node-v0.10.0/deps/http_parser/test.c" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/http_parser_test$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/http_parser_test$(DependSuffix): ../node-v0.10.0/deps/http_parser/test.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/http_parser_test$(ObjectSuffix) -MF$(IntermediateDirectory)/http_parser_test$(DependSuffix) -MM "../node-v0.10.0/deps/http_parser/test.c"

$(IntermediateDirectory)/http_parser_test$(PreprocessSuffix): ../node-v0.10.0/deps/http_parser/test.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/http_parser_test$(PreprocessSuffix) "../node-v0.10.0/deps/http_parser/test.c"

$(IntermediateDirectory)/src_stream_wrap$(ObjectSuffix): ../node-v0.10.0/src/stream_wrap.cc $(IntermediateDirectory)/src_stream_wrap$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anandrathi/sre/node-v0.10.0/src/stream_wrap.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_stream_wrap$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_stream_wrap$(DependSuffix): ../node-v0.10.0/src/stream_wrap.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_stream_wrap$(ObjectSuffix) -MF$(IntermediateDirectory)/src_stream_wrap$(DependSuffix) -MM "../node-v0.10.0/src/stream_wrap.cc"

$(IntermediateDirectory)/src_stream_wrap$(PreprocessSuffix): ../node-v0.10.0/src/stream_wrap.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_stream_wrap$(PreprocessSuffix) "../node-v0.10.0/src/stream_wrap.cc"

$(IntermediateDirectory)/libjspp_http_parser$(ObjectSuffix): libjspp_http_parser.cpp $(IntermediateDirectory)/libjspp_http_parser$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anandrathi/sre/jsppnodejs/libjspp_http_parser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/libjspp_http_parser$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/libjspp_http_parser$(DependSuffix): libjspp_http_parser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/libjspp_http_parser$(ObjectSuffix) -MF$(IntermediateDirectory)/libjspp_http_parser$(DependSuffix) -MM "libjspp_http_parser.cpp"

$(IntermediateDirectory)/libjspp_http_parser$(PreprocessSuffix): libjspp_http_parser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/libjspp_http_parser$(PreprocessSuffix) "libjspp_http_parser.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/src_tcp_wrap$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_tcp_wrap$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_tcp_wrap$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/http_parser_test$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/http_parser_test$(DependSuffix)
	$(RM) $(IntermediateDirectory)/http_parser_test$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_stream_wrap$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_stream_wrap$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_stream_wrap$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/libjspp_http_parser$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/libjspp_http_parser$(DependSuffix)
	$(RM) $(IntermediateDirectory)/libjspp_http_parser$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) ".build-release/jsppnodejs"


