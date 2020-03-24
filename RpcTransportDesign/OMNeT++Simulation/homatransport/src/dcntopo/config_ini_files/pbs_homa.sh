#!/bin/bash



for i in 1 
do 
	nohup ../homatransport -u Cmdenv -c WorkloadFabricatedHeavyMiddle  --r_alpha=$1 --r_mode=blind -r 6 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET homaTransportConfig_pbs.ini &


	nohup ../homatransport -u Cmdenv -c WorkloadHadoop  --r_alpha=$1 --r_mode=blind -r 6 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET homaTransportConfig_pbs_aware.ini &


	nohup ../homatransport -u Cmdenv -c WorkloadGoogleAllRpc  --r_alpha=$1 --r_mode=blind -r 6 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET homaTransportConfig_homa.ini &

	nohup ../homatransport -u Cmdenv -c WorkloadFabricatedHeavyHead  --r_alpha=$1 --r_mode=blind -r 6 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET homaTransportConfig_pbs_blind.ini &


	nohup ../homatransport -u Cmdenv -c WorkloadDCTCP  --r_alpha=$1 --r_mode=blind -r 6 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET homaTransportConfig_pbs_blind.ini &
done 
