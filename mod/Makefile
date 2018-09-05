CXX = mpiicpc
CXXFLAGS=-qopenmp -mkl
CPUFLAGS = $(CXXFLAGS) -xAVX
KNCFLAGS = $(CXXFLAGS) -mmic
OPTFLAGS = -qopt-report -qopt-report-file=$@.optrpt -fp-model fast=2

CPUOBJECTS = nbody.o
KNCOBJECTS = nbody.oKNC

NSIZE=1048576

TARGET=app-CPU app-KNC

.SUFFIXES: .o .cc .oKNC

all: $(TARGET) 

%-CPU: $(CPUOBJECTS)
	$(info )
	$(info Linking the CPU executable:)
	$(CXX) $(CXXFLAGS) $(CPUFLAGS) -o $@ $(CPUOBJECTS)

%-KNC: $(KNCOBJECTS)
	$(info )
	$(info Linking the KNC executable:)
	$(CXX) $(CXXFLAGS) $(KNCFLAGS) -o $@ $(KNCOBJECTS)


.cc.o:
	$(info )
	$(info Compiling a CPU object file:)
	$(CXX) $(CXXFLAGS) -c $(CPUFLAGS) $(OPTFLAGS) -o "$@" "$<"

.cc.oKNC:
	$(info )
	$(info Compiling a KNC object file:)
	$(CXX) $(CXXFLAGS) -c $(KNCFLAGS) $(OPTFLAGS) -o "$@" "$<"


run-cpu: app-CPU
	mpirun -host localhost -np 4 -genv KMP_AFFINITY=compact,granularity=fine ./app-CPU $(NSIZE)

run-knc: app-KNC
	scp app-KNC mic0:~/
	mpirun -host mic0 -np 4 -genv LD_LIBRARY_PATH=$(MIC_LD_LIBRARY_PATH) -genv KMP_AFFINITY=compact,granularity=fine ./app-KNC $(NSIZE)

clean: 
	rm -f $(CPUOBJECTS) $(KNCOBJECTS) $(KNLOBJECTS) $(TARGET) *.optrpt
