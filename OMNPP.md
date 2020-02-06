Source: https://doc.omnetpp.org/omnetpp4/manual/usman.html#toc_1


2.1.5 Parameters
Modules can have parameters. Parameters can be assigned in either the NED files or the configuration file omnetpp.ini.

Parameters can be used to customize simple module behavior, and to parameterize the model topology.

Parameters can take string, numeric or boolean values, or can contain XML data trees. Numeric values include expressions using other parameters and calling C functions, random variables from different distributions, and values input interactively by the user.

Numeric-valued parameters can be used to construct topologies in a flexible way. Within a compound module, parameters can define the number of submodules, number of gates, and the way the internal connections are made.



Assigning a Value

Parameters may get their values in several ways: from NED code, from the configuration (omnetpp.ini), or even, interactively from the user. NED lets you assign parameters at several places: in subclasses via inheritance; in submodule and connection definitions where the NED type is instantiated; and in networks and compound modules that directly or indirectly contain the corresponding submodule or connection.


initialize -- this includes building the model and
              inserting initial events to FES
              

4.4.3 How to Avoid Global Variables
If possible, avoid using global variables, including static class members. They are prone to cause several problems. First, they are not reset to their initial values (to zero) when you rebuild the simulation in Tkenv, or start another run in Cmdenv. This may produce surprising results. Second, they prevent you from running your simulation in parallel. When using parallel simulation, each partition of your model (may) run in a separate process, having its own copy of the global variables. This is usually not what you want.

The solution is to encapsulate the variables into simple modules as private or protected data members, and expose them via public methods. Other modules can then call these public methods to get or set the values. Calling methods of other modules will be discussed in section [4.12]. Examples of such modules are the Blackboard in the Mobility Framework, and InterfaceTable and RoutingTable in the INET Framework.



The NED properties of a parameter can be accessed with the getProperties() method that returns a pointer to the cProperties object that stores the properties of this parameter. Specifically, getUnit() returns the unit of measurement associated with the parameter (@unit property in NED).

Further cPar methods and related classes like cExpression and cDynamicExpression are used by the NED infrastructure to set up and assign parameters. They are documented in the API Reference, but they are normally of little interest to users.


simtime_t startTime, endTime;
if (pkt->isReceptionStart())
{
    // gate was reprogrammed with setDeliverOnReceptionStart(true)
    startTime = pkt->getArrivalTime(); // or: simTime();
    endTime = startTime + pkt->getDuration();
}
else
{
    // default case
    endTime = pkt->getArrivalTime(); // or: simTime();
    startTime = endTime - pkt->getDuration();
}
ev << "interval: " << startTime << ".." << endTime << "\n";

simtime_t timeout = 3.0;
cMessage *msg = receive(timeout);
if (msg==NULL)
{
    ...   // handle timeout
}
else
{
    ...  // process message
}
endSimulation();


cModule *calleeModule = getParentModule()->getSubmodule("callee");
Callee *callee = check_and_cast<Callee *>(calleeModule);
callee->doSomething();


cMessage Class: 
  long getId() const;
  long getTreeId() const;
  simtime_t getSendingTime() const;
  simtime_t getArrivalTime() const;


8.2.1 The opp_makemake Tool
The opp_makemake tool can automatically generate a Makefile for your simulation program, based on the source files in the current directory or directory tree. opp_makemake has several options; opp_makemake -h displays help.

The most important options are:

-f, --force : Force overwriting existing Makefile
-o filename : Name of simulation executable or library to be built.
-O directory, --out directory : Specifies the name of the output directory tree for out-of-directory build
--deep : Generates a "deep" Makefile. A deep Makefile will cover the whole source tree under the make directory, not just files in that directory.
-r, --recurse : Causes make to recursively descend into all subdirectories; subdirectories are expected to contain makefiles themselves.
-X directory, -Xdirectory, --except directory : With -r and --deep option: ignore the given directory.
-dsubdir, -d subdir, --subdir subdir : Causes make to recursively descend into the given directory.
-n, --nolink : Produce object files but do not create executable or library.
-s, --make-so : Build shared library (.so, .dll or .dylib).
-a, --make-lib : Create static library (.a or .lib).
-Idir : Additional NED and C++ include directory.
-Ldir : Add a directory to the library path.
-llibrary : Additional library to link against.



User interfaces may support the -r runnumber option to select runs, either one or more, depending on the type of the user interface.

There are several command line options to get information about the iteration variables and the number of runs in the configurations:

-a -- Prints all configuration names and the number of runs in them.
-x <configname> -- Prints the number of runs available in the given configuration.
-g -- Prints the unrolled configuration (together with the -x option) and expands the iteration variables.
-G -- Prints even more details than -g.
  
  
There are several useful configuration options that control how a simulation is run.

cmdenv-express-mode -- Provides only minimal status updates on the console.
cmdenv-interactive -- Allows the simulation to ask missing parameter values interactively
cmdenv-status-frequency -- Controls how often the status is written to the console.
cpu-time-limit -- Limits how long the simulation should run (in wall clock time)
sim-time-limit -- Limits how long the simulation should run (in simulation time)
record-eventlog -- Turns on the recording of the simulator events into an event log file. The resulting .elog file can be analyzed later in the IDE with the sequence chart tool.
fingerprint -- The simulation kernel computes a checksum while running the simulation. It is calculated from the module id and from the current simulation time of each event. If you specify the fingerprint option in the config file, the simulation runtime will compare the computed checksum with the provided one. If there is a difference it will generate an error. This feature is very useful if you make some cosmetic changes to your source and want to be reasonable sure that your changes did not alter the behaviour of the model.
WARNING
The value of the calculated fingerprint is heavily dependent on the accuracy of the floating point arithmetic. There are differences between the floating point handling of AMD and Intel CPUs. Running under a processor emulator software like valgrind may also produce a different fingerprint. This is normal. Hint: see gcc options -mfpmath=sse -msse2.
debug-on-errors -- If the runtime detects any error, it will generate a breakpoint so you will be able to check the location and the context of the problem in your debugger.
debugger-attach-on-error -- Controls just-in-time debugging. When this option is enabled and an error occurs during simulation, the simulation program will launch an external debugger, and have it attached to the simulation process. Related configuration options are debugger-attach-on-startup, debugger-attach-command and debugger-attach-wait-time.
NOTE


10.2.2 Command-Line Options
The command line environment allows you to specify more than one run by using the -r 2,4,6..8 format. See [10.4] for more information about running simulation batches.

Cmdenv can be executed in two modes, selected by the cmdenv-express-mode ini file option:

Normal (non-express) mode is for debugging; detailed information will be written to the standard output (event banners, module output, etc).
Express mode can be used for long simulation runs; only periodical status updates are displayed about the progress of the simulation.


