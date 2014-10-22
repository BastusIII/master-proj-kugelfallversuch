//****************************************************************************/
//                                                                           */
//     File   : main.cc                                                      */
//                                                                           */
//     Content: QNX EtherCAT ProcessImage demo                               */
//                                                                           */
//     Author : Max Fischer                                                  */
//                                                                           */
//     Date   : 13. 7. 2012                                                  */
//                                                                           */
//****************************************************************************/
//**************************** INCLUDES **************************************/
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "EcDeviceFactory.h"
#include "EcInterface.h"
#ifdef QNX
# include <sys/neutrino.h>
#endif

//**************************** MACROS ****************************************/

//**************************** TYPES *****************************************/

//**************************** VARIABLES *************************************/

//**************************** FUNCTIONS *************************************/
// convert ECAT state to a string
const char* GetStateString(USHORT nState)
{
   switch (nState) {
      case DEVICE_STATE_INIT:
         return "Init";
      case DEVICE_STATE_PREOP:
         return "Pre-Operational";
      case DEVICE_STATE_SAFEOP:
         return "Safe-Operational";
      case DEVICE_STATE_OP:
         return "Operational";
      default:
         return "Invalid State";
   }
}

using namespace std;

#ifdef QNX
int changeSystemTick ( int cycle_usec ){
	   struct timespec reso;
	   struct _clockperiod period;

		/* query system clock resolution */
	   if (clock_getres(CLOCK_REALTIME, &reso) == -1) {
	      perror("clock get resolution");
	      return -1;
	   }
	   printf("Resolution is %ld nano seconds.\n",
	      reso.tv_nsec);

	   /* set new system clock resolution */
	   if (cycle_usec < 50)
	      cycle_usec = 50;
	   period.nsec = cycle_usec*1000;
	   period.fract = 0;
	   int ret = ClockPeriod(CLOCK_REALTIME, &period, NULL, 0);
	   if (ret != 0) {
	      perror ("ClockPeriod");
	      return -1;
	   }

	   /* query system clock resolution */
	   if (clock_getres(CLOCK_REALTIME, &reso) == -1) {
	      perror("clock get resolution");
	      return -1;
	   }
	   printf("New resolution is %ld nano seconds.\n", reso.tv_nsec);
	   return 0;
}
#endif

void preWCCheckErrFkt (void) {
	cout << "<OWN_WCNT_ERR ";
}

BOOL wcCheckErrFkt(ULONG &frame, USHORT &cmd, USHORT &actualWcnt, USHORT &expectedWcnt){
	cout << "[frame " << frame << ",cmd " << cmd << ": " << actualWcnt << "!=" << expectedWcnt << "]";
	return TRUE;
}
void postWCCheckErrFkt (void){
	cout << ">" << endl;
}

void usage(char *argv) {
	cout << "usage: " << argv << " [-c loops] [-t cycletime_in_microsecs] [-p] [-w] <xmlfile>" << endl;
	cout << "\t\t-c :\tnumber of process image update loops (default 100000)\n\t\t-t : \tcycletime in microsecs\n\t\t-p :\tprint process image\t\t-w :\tprint working counters\n" << endl;
	exit(1);
}

int main(int argc, char *argv[]) {
	int i;
	int cycle = 1000;
	int ecPrintPI = 0;
	int doCheckWcnt = 0;
	char *filename = NULL;
	int loops = 100000;
	IEcDevice *pEcDevice;
	IEcMaster *pMaster;

	// dispatch command line options
	if (argc < 2)
		usage(argv[0]);
	for (i = 1; i < argc; i++) {
		if (strncmp(argv[i], "-t", 2) == 0) {
			if (i >= argc - 1)
				usage(argv[0]);
			else
				cycle = atoi(argv[++i]);
		} else if (strncmp(argv[i], "-c", 2) == 0) {
			if (i >= argc - 1)
				usage(argv[0]);
			else
				loops = atoi(argv[++i]);
		} else if (strncmp(argv[i], "-p", 2) == 0) {
			ecPrintPI = 1;
		} else if (strncmp(argv[i], "-w", 2) == 0) {
			doCheckWcnt = 1;
		} else if (i != argc - 1) {
			usage(argv[0]);
		} else {
			filename = argv[i];
		}
	}

#ifdef QNX
	/* change system ticks
	 * !!!WATCH OUT!!! THIS MAY AFFECT OVERALL SYSTEM BEHAVIOUR!!!
	 * Necessary especially if working with DC synchronisation
	 */
	if (changeSystemTick(100) != 0)
	{
		printf("Changing system ticks failed\n");
		return 0;
	}
#endif

	// =========================================================================
	// DEMO: Creating and setting up an EtherCAT device
	// =========================================================================

	// create an EtherCAT device corresponding to a given config file
	CEcDeviceFactory factory;

	assert(filename);
	int res = factory.CreateDevice(filename, &pEcDevice);
	if (res != 0) {
		cout << "factory.CreateDevice failed" << endl;
		return (-1);
	}

	// Open EtherCAT device
	res = pEcDevice->Open();
	if (res != 0) {
		cout << "Failed to open EtherCAT device (error = " << hex << res << dec << ")" << endl;
		return (-1);
	}

	// get the master from the device
	pMaster = pEcDevice->GetMaster();
	assert(pMaster);

	// =========================================================================
	// DEMO: Use of info interface to EtherCAT slaves,
	//       EtherCAT process variables and EtherCAT process image
	// =========================================================================

	// enumerate the slaves by position (physical address would be possible, too),
	// print their names and mailbox type
	for (ULONG i = 0; i < pMaster->GetSlaveCount(); i++) {
		IEcSlave *pSlave = pMaster->GetSlaveByPos(i);
		if (pSlave && pSlave->HasMailBox()) {
			cout << "Slave " << i << " with mailbox: <" << pSlave->GetName() << ">" << endl;
		} else {
			cout << "Slave " << i << " w/o  mailbox: <" << pSlave->GetName() << ">" << endl;
		}
	}

	// print the names, size, bit offset and type of all input and output variables in the ENI file
	// additionally, we look for the smallest bit offsets in the input and output PI to use these as
	// general offsets in the main loop
	ULONG inputBitOffs = (ULONG) (-1);
	for (int i = 0; i < pEcDevice->GetNrInputVars(); i++) {
		const char *varName = pEcDevice->GetInputVar(i);
		ULONG bitSize, bitOffs;
		char varType[100];
		pEcDevice->GetInputVarInfo(varName, bitSize, bitOffs, varType);
		cout << "InVar  <" << varName << ">, bitSize: " << bitSize << ", bitOffs: " << bitOffs << ", varType: " << varType << endl;
		if (bitOffs < inputBitOffs)
			inputBitOffs = bitOffs;
	}

	ULONG outputBitOffs = (ULONG) (-1);
	for (int i = 0; i < pEcDevice->GetNrOutputVars(); i++) {
		const char *varName = pEcDevice->GetOutputVar(i);
		ULONG bitSize, bitOffs;
		char varType[100];
		pEcDevice->GetOutputVarInfo(varName, bitSize, bitOffs, varType);
		cout << "OutVar <" << varName << ">, bitSize: " << bitSize << ", bitOffs: " << bitOffs << ", varType: " << varType << endl;
		if (bitOffs < outputBitOffs)
			outputBitOffs = bitOffs;
	}

	// get length of the process data areas (in and out)
	ULONG nDataIn = pEcDevice->ProcessDataSize(VG_IN);
	ULONG nDataOut = pEcDevice->ProcessDataSize(VG_OUT);

	// Get pointer to the process data areas (in and out)
	// In this example we just use the bit offsets to the first variable found above.
	// To assure the interface that one doesn't want to access data beyond the end of the PI, one needs
	// to reduce the desired size by the offset
	ULONG inputByteOffs = inputBitOffs / 8; //convert bit offset to byte offset
	PBYTE pDataIn = pEcDevice->ProcessDataPtr(VG_IN, inputByteOffs, nDataIn - inputByteOffs);
	assert(pDataIn);

	ULONG outputByteOffs = outputBitOffs / 8; //convert bit offset to byte offset
	PBYTE pDataOut = pEcDevice->ProcessDataPtr(VG_OUT, outputByteOffs, nDataOut - outputByteOffs);
	assert(pDataOut);


	// =========================================================================
	// DEMO: Setting up EtherCAT cycle time
	// =========================================================================

	// set the bus cycle time
	// if cycle time is not explicitly given, check for a cycle time given in the XML file
	// if there is none given in the XML file, use the default value 4ms
	if (cycle == 0) {
		cout << "No cycle time given, trying to figure it out from the XML file... " << endl;
		cycle = pMaster->GetCycleTimeInMicroSecs();
		if (cycle == 0) {
			cout << "No cycle time given in the XML file, setting cycle to 4000 us... " << endl;
			cycle = 4000;
		} else {
			cout << "Cycle time given in the XML file, setting cycle to " << cycle << " us... " << endl;
		}
	}
	pMaster->SetCycleTimeInMicroSecs(cycle);

	//wait for heartbeat, just to be in sync
	pMaster->WaitForHeartbeat();


	// =========================================================================
	// DEMO: Bringing the EtherCAT slaves to Operational and back to init
	//       for a few times
	// =========================================================================

	int maxOpInitCycles = 100;
	for (int opInitCycles = 0; opInitCycles < maxOpInitCycles; opInitCycles++) {
		// try to reach OP state
		// WATCH OUT!!! For some slaves it may take several seconds to change from Init to Operational
		cout << endl << "Requesting State: Operational" << endl;
		if (!pEcDevice->RequestState(DEVICE_STATE_OP, 10000)) {
			cout << "giving up..." << endl;
			sleep(1);
			pMaster->Close();
			pMaster->Open();
			continue;
		}

		// initial write part of the EtherCAT process image cycle
		if (pEcDevice->StartIo() != IOSTATE_BUSY) {
			cout << "StartIo error, probably no process image" << endl;
		}

		// =========================================================================
		// DEMO: Main loop
		// =========================================================================

		// perform a few IO steps
		for (i = 0; i < loops; i++) {

			// wait for the heartbeat
			pMaster->WaitForHeartbeat();

			// start read part of the EtherCAT process image cycle
			if (pEcDevice->GetIoState() == ECERR_DEVICE_TIMEOUT) {
				cout << "GetIoState timeout" << endl;
			}

			// =========================================================================
			// DEMO: This is the place where
			//       - the input data are available and
			//       - the user application generates output from the input
			// =========================================================================
			// print parts of the input and output images
			if (ecPrintPI) {
				// realize a few 16 bit counters in the outbound process image
				for (ULONG j = 0; j * sizeof(USHORT) < nDataOut && j < 4; j++) {
					((USHORT*) pDataOut)[j]++;
				}
				for (ULONG j = 0; j < nDataIn && j < 24; j++) {
					cout << hex << setw(2) << setfill('0') << (USHORT) (pDataIn[j]) << " ";
				}
				cout << "    ";
				for (ULONG j = 0; j < nDataOut && j < 24; j++) {
					cout << hex << setw(2) << setfill('0') << (USHORT) (pDataOut[j]) << " ";
				}
				cout << endl;
				cout.flush();
			}

			// =========================================================================
			// DEMO: Analysis of bus and slave state to detect error states
			// =========================================================================
			// report working counter errors and - if desired - result of working counter analysis every 2 s (for demonstration)

			BOOL res;
			res = pEcDevice->CyclicCheckAllWCs(preWCCheckErrFkt, wcCheckErrFkt, postWCCheckErrFkt);
			if ( res != TRUE ){
				cout << "WCNT error!!!" << endl;
				if ( i > 10000 )
					break;
			}

			USHORT actualWcnt, expectedWcnt;
			res = pEcDevice->CyclicCheckBusStateWC(&actualWcnt, &expectedWcnt);
			if ( res != TRUE ){
				cout << "BusState WCNT error!!! (" << actualWcnt << " != " << expectedWcnt << ")" << endl;
				break;
			}

			USHORT actualState;
			res = pEcDevice->CyclicCheckBusState(&actualState);
			if ( res != TRUE ){
				cout << "Wrong bus device state " << pEcDevice->GetStateString(actualState) << endl;
				break;
			}

			// start write part of the EtherCAT process image cycle
			if (pEcDevice->StartIo() != IOSTATE_BUSY) {
				cout << "StartIo error, probably no process image" << endl;
			}

			// asynchronous calls (state update, mailboxes, ...), mandatory
			if (pEcDevice->OnTimer() == ECERR_DEVICE_TIMEOUT)
				cout << "OnTimer timeout" << endl;
		}

		if (pEcDevice->GetIoState() == ECERR_DEVICE_TIMEOUT) {
			cout << "GetIoState timeout" << endl;
		}

#ifdef XXXX
		// =========================================================================
		// DEMO: Bringing down the EtherCAT device
		// =========================================================================
		// try to reach INIT state
		// WATCH OUT!!! For some slaves it may take some seconds to go from Operational to Init!!!
		cout << endl << "Requesting State: Init" << endl;
		if (!pEcDevice->RequestState(DEVICE_STATE_INIT, 10000)) {
			cout << "giving up..." << endl;
		}

		// except for the last close/open cycle: close the device, wait a few seconds and open the device again
		// after the last cycle, close and cleanup is done in the 'Final cleanup' section below
		if ( opInitCycles < maxOpInitCycles-1 ){
			pEcDevice->Close();
			usleep(4000000);
			pEcDevice->Open();
		}
#endif
		pMaster->Close();
		pMaster->Open();
		sleep(1);
	}

	if (pEcDevice->GetIoState() == ECERR_DEVICE_TIMEOUT) {
		cout << "GetIoState timeout" << endl;
	}

	// =========================================================================
	// DEMO: Final cleanup
	// =========================================================================
	// close the device
	res = pEcDevice->Close();
	if (res != 0)
		cout << "pEcDevice->Close() failed:" << res << endl;

	// free all resources
	factory.DisposeDevice(pEcDevice);
	if (res != 0)
		cout << "pEcDevice->DisposeDevice() failed:" << res << endl;

	return res;
}

