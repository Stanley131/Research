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



