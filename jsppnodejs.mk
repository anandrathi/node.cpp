##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=jsppnodejs
ConfigurationName      :=Debug
WorkspacePath          := "/home/anandrathi/sre/jsppnodejs"
ProjectPath            := "/home/anandrathi/sre/jsppnodejs"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=anandrathi
Date                   :=04/04/2013
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
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)/home/anandrathi/sre/node-v0.10.0/deps/http_parser $(IncludeSwitch)/home/anandrathi/sre/boost_1_53_0/ $(IncludeSwitch)/home/anandrathi/sre/node-v0.10.0/deps 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)boost_thread $(LibrarySwitch)pthread $(LibrarySwitch)boost_system $(LibrarySwitch)uv $(LibrarySwitch)rt 
ArLibs                 :=  "boost_thread.so" "pthread" "boost_system" "uv.a" "rt" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/home/anandrathi/sre/boost_1_53_0/stage/lib $(LibraryPathSwitch)//home/anandrathi/sre/node-v0.10.0/deps/uv 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
LD_LIBRARY_PATH:=/home/anandrathi/sre/boost_1_53_0/stage/lib
Objects0=$(IntermediateDirectory)/libjspp_http_parser$(ObjectSuffix) $(IntermediateDirectory)/server3_main$(ObjectSuffix) $(IntermediateDirectory)/http_parser_http_parser$(ObjectSuffix) $(IntermediateDirectory)/event_loop$(ObjectSuffix) $(IntermediateDirectory)/worker$(ObjectSuffix) $(IntermediateDirectory)/client_connection$(ObjectSuffix) $(IntermediateDirectory)/SynchronisedQueue$(ObjectSuffix) $(IntermediateDirectory)/workerPool$(ObjectSuffix) 

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
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/libjspp_http_parser$(ObjectSuffix): libjspp_http_parser.cpp $(IntermediateDirectory)/libjspp_http_parser$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anandrathi/sre/jsppnodejs/libjspp_http_parser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/libjspp_http_parser$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/libjspp_http_parser$(DependSuffix): libjspp_http_parser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/libjspp_http_parser$(ObjectSuffix) -MF$(IntermediateDirectory)/libjspp_http_parser$(DependSuffix) -MM "libjspp_http_parser.cpp"

$(IntermediateDirectory)/libjspp_http_parser$(PreprocessSuffix): libjspp_http_parser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/libjspp_http_parser$(PreprocessSuffix) "libjspp_http_parser.cpp"

$(IntermediateDirectory)/server3_main$(ObjectSuffix): server3/main.cpp $(IntermediateDirectory)/server3_main$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anandrathi/sre/jsppnodejs/server3/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/server3_main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/server3_main$(DependSuffix): server3/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/server3_main$(ObjectSuffix) -MF$(IntermediateDirectory)/server3_main$(DependSuffix) -MM "server3/main.cpp"

$(IntermediateDirectory)/server3_main$(PreprocessSuffix): server3/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/server3_main$(PreprocessSuffix) "server3/main.cpp"

$(IntermediateDirectory)/http_parser_http_parser$(ObjectSuffix): ../node-v0.10.0/deps/http_parser/http_parser.c $(IntermediateDirectory)/http_parser_http_parser$(DependSuffix)
	$(CXX) $(SourceSwitch) "/home/anandrathi/sre/node-v0.10.0/deps/http_parser/http_parser.c" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/http_parser_http_parser$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/http_parser_http_parser$(DependSuffix): ../node-v0.10.0/deps/http_parser/http_parser.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/http_parser_http_parser$(ObjectSuffix) -MF$(IntermediateDirectory)/http_parser_http_parser$(DependSuffix) -MM "../node-v0.10.0/deps/http_parser/http_parser.c"

$(IntermediateDirectory)/http_parser_http_parser$(PreprocessSuffix): ../node-v0.10.0/deps/http_parser/http_parser.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/http_parser_http_parser$(PreprocessSuffix) "../node-v0.10.0/deps/http_parser/http_parser.c"

$(IntermediateDirectory)/event_loop$(ObjectSuffix): event_loop.cpp $(IntermediateDirectory)/event_loop$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anandrathi/sre/jsppnodejs/event_loop.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/event_loop$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/event_loop$(DependSuffix): event_loop.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/event_loop$(ObjectSuffix) -MF$(IntermediateDirectory)/event_loop$(DependSuffix) -MM "event_loop.cpp"

$(IntermediateDirectory)/event_loop$(PreprocessSuffix): event_loop.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/event_loop$(PreprocessSuffix) "event_loop.cpp"

$(IntermediateDirectory)/worker$(ObjectSuffix): worker.cpp $(IntermediateDirectory)/worker$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anandrathi/sre/jsppnodejs/worker.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/worker$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/worker$(DependSuffix): worker.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/worker$(ObjectSuffix) -MF$(IntermediateDirectory)/worker$(DependSuffix) -MM "worker.cpp"

$(IntermediateDirectory)/worker$(PreprocessSuffix): worker.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/worker$(PreprocessSuffix) "worker.cpp"

$(IntermediateDirectory)/client_connection$(ObjectSuffix): client_connection.cpp $(IntermediateDirectory)/client_connection$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anandrathi/sre/jsppnodejs/client_connection.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/client_connection$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/client_connection$(DependSuffix): client_connection.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/client_connection$(ObjectSuffix) -MF$(IntermediateDirectory)/client_connection$(DependSuffix) -MM "client_connection.cpp"

$(IntermediateDirectory)/client_connection$(PreprocessSuffix): client_connection.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/client_connection$(PreprocessSuffix) "client_connection.cpp"

$(IntermediateDirectory)/SynchronisedQueue$(ObjectSuffix): SynchronisedQueue.cpp $(IntermediateDirectory)/SynchronisedQueue$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anandrathi/sre/jsppnodejs/SynchronisedQueue.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SynchronisedQueue$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SynchronisedQueue$(DependSuffix): SynchronisedQueue.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SynchronisedQueue$(ObjectSuffix) -MF$(IntermediateDirectory)/SynchronisedQueue$(DependSuffix) -MM "SynchronisedQueue.cpp"

$(IntermediateDirectory)/SynchronisedQueue$(PreprocessSuffix): SynchronisedQueue.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SynchronisedQueue$(PreprocessSuffix) "SynchronisedQueue.cpp"

$(IntermediateDirectory)/workerPool$(ObjectSuffix): workerPool.cpp $(IntermediateDirectory)/workerPool$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anandrathi/sre/jsppnodejs/workerPool.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/workerPool$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/workerPool$(DependSuffix): workerPool.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/workerPool$(ObjectSuffix) -MF$(IntermediateDirectory)/workerPool$(DependSuffix) -MM "workerPool.cpp"

$(IntermediateDirectory)/workerPool$(PreprocessSuffix): workerPool.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/workerPool$(PreprocessSuffix) "workerPool.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/libjspp_http_parser$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/libjspp_http_parser$(DependSuffix)
	$(RM) $(IntermediateDirectory)/libjspp_http_parser$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/server3_main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/server3_main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/server3_main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/http_parser_http_parser$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/http_parser_http_parser$(DependSuffix)
	$(RM) $(IntermediateDirectory)/http_parser_http_parser$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/event_loop$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/event_loop$(DependSuffix)
	$(RM) $(IntermediateDirectory)/event_loop$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/worker$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/worker$(DependSuffix)
	$(RM) $(IntermediateDirectory)/worker$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/client_connection$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/client_connection$(DependSuffix)
	$(RM) $(IntermediateDirectory)/client_connection$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/SynchronisedQueue$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SynchronisedQueue$(DependSuffix)
	$(RM) $(IntermediateDirectory)/SynchronisedQueue$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/workerPool$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/workerPool$(DependSuffix)
	$(RM) $(IntermediateDirectory)/workerPool$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) ".build-debug/jsppnodejs"


