#ifndef	__ECINTERFACE_H__
#define	__ECINTERFACE_H__
//****************************************************************************/
//                                                                           */
//     File   : EcInterface.h                                                */
//                                                                           */
//     Content: Interface definitions for EtherCAT Master Lib                */
//                                                                           */
//     Author : adapted by Max Fischer from Beckhoff Master Sample Code      */
//                                                                           */
//     Date   : 2. 12. 2008                                                  */
//                                                                           */
//****************************************************************************/

//**************************** INCLUDES **************************************/
#include <stdarg.h>
#include "EcPlatformDefs.h"

//MF EtherCAT Master version number 
#define ECAT_MASTER_VERSION_MAJOR (3)
#define ECAT_MASTER_VERSION_MINOR (8)

//**************************** TYPES *****************************************/

///\name EtherCAT states
///  Represents device state in the respective process image section (close to the end)
///\{
#ifndef DEVICE_STATE_INIT
# define	DEVICE_STATE_MASK					0x000F
# define	DEVICE_STATE_INIT					0x0001
# define	DEVICE_STATE_PREOP					0x0002
# define	DEVICE_STATE_BOOTSTRAP					0x0003
# define	DEVICE_STATE_SAFEOP					0x0004
# define	DEVICE_STATE_OP						0x0008
# define	DEVICE_STATE_ERROR					0x0010
#endif
///\}

///\name Process image direction
///\{
#ifndef	VG_IN
#define	VG_IN		0
#define	VG_OUT		1
#endif
///\}

///\name IO State  
///  Represents device state in the respective process image section (close to the end)
///\{
#define	ETHERNETRTMP_STATE_LINKERROR			0x0001
#define	ETHERNETRTMP_STATE_LOCKLINKERROR		0x0002
#define	ETHERNETRTMP_STATE_ALLOCFRAME			0x0010
#define	ETHERNETRTMP_STATE_WATCHDOG			0x0020
#define	ETHERNETRTMP_STATE_NOMINIPORT			0x0040
#define	ETHERNETRTMP_STATE_RESETACTIVE		0x0080
#define	ETHERNETRTMP_STATE_CYC_WCNTOUT_ERR	0x0100
#define	ETHERNETRTMP_STATE_CYC_WCNTIN_ERR	0x0200
///\}

///\name Return code of getIoState
///  
///\{
#define	IOSTATE_READY		0 //!< no process image update
#define	IOSTATE_BUSY		1 //!< process image cyclically updated
///\}

///\name Error codes
///  
///\{
#ifndef ERR_ECERRS
#define	ERR_ECERRS					0x0700  //!< Error base (added to all errors)

#define ECERR_NOERR 0x00
#define ECERR_DEVICE_ERROR					(0x00+ERR_ECERRS) //!< Error class < device error >
#define ECERR_DEVICE_SRVNOTSUPP			(0x01+ERR_ECERRS) //!< Service is not supported
#define ECERR_DEVICE_INVALIDCMD			(0x02+ERR_ECERRS) //!< invalid index
#define ECERR_DEVICE_INVALIDINDEX		(0x03+ERR_ECERRS) //!< invalid offset
#define ECERR_DEVICE_INVALIDACCESS		(0x04+ERR_ECERRS) //!< reading/writing not permitted
#define ECERR_DEVICE_INVALIDSIZE			(0x05+ERR_ECERRS) //!< parameter size not correct
#define ECERR_DEVICE_INVALIDDATA			(0x06+ERR_ECERRS) //!< invalid parameter value(s)
#define ECERR_DEVICE_NOTREADY				(0x07+ERR_ECERRS) //!< device is not in a ready state
#define ECERR_DEVICE_BUSY					(0x08+ERR_ECERRS) //!< device is busy
#define ECERR_DEVICE_INVALIDCONTEXT		(0x09+ERR_ECERRS) //!< invalid context
#define ECERR_DEVICE_NOMEMORY				(0x0A+ERR_ECERRS) //!< out of memory
#define ECERR_DEVICE_INVALIDPARM			(0x0B+ERR_ECERRS) //!< invalid parameter value(s)
#define ECERR_DEVICE_NOTFOUND				(0x0C+ERR_ECERRS) //!< not found (files, ...)
#define ECERR_DEVICE_SYNTAX				(0x0D+ERR_ECERRS) //!< syntax error in command or file
#define ECERR_DEVICE_INVALIDSTATE		(0x12+ERR_ECERRS) //!< device is in invalid state
#define ECERR_DEVICE_NOMOREHDLS			(0x16+ERR_ECERRS) //!< no more handles	
#define ECERR_DEVICE_TIMEOUT				(0x19+ERR_ECERRS) //!< device has a timeout
#define ECERR_DEVICE_OPENFAILED			(0x20+ERR_ECERRS) //!< resource could not be opened
#define ECERR_DEVICE_SENDFAILED			(0x21+ERR_ECERRS) //!< sending a packet failed
#define ECERR_DEVICE_INSERTMAILBOX		(0x22+ERR_ECERRS) //!< no more mem for mailbox command
#define ECERR_DEVICE_INVALIDOFFSET		(0x23+ERR_ECERRS) //!< invalid offset or subindex
#define ECERR_DEVICE_UNKNOWNMAILBOXCMD (0x24+ERR_ECERRS)  //!< unknown mailbox command
#define ECERR_DEVICE_ACCESSDENIED		(0x25+ERR_ECERRS) //!< ->  ECAT_FOE_ERRCODE_ACCESS
#define ECERR_DEVICE_INVALIDARRAYIDX	(0x26+ERR_ECERRS) //!< FoE packet sent twice
#define ECERR_DEVICE_EXISTS				(0x27+ERR_ECERRS) //!< -> ECAT_FOE_ERRCODE_EXISTS
#define ECERR_DEVICE_INVALIDADDR			(0x28+ERR_ECERRS) //!< invalid address
#define ECERR_DEVICE_INCOMPATIBLE		(0x29+ERR_ECERRS) //!< frame and buffer size mismatch
#define ECERR_DEVICE_ABORTED				(0x2a+ERR_ECERRS) //!< request is aborted
#define ECERR_DEVICE_PENDING				(0x2b+ERR_ECERRS) //!< request is pending
#define ECERR_DEVICE_READFAILED				(0x2c+ERR_ECERRS) //!< reading a packet failed


#define ECERR_CLIENT_ERROR					(0x100+ERR_ECERRS) //!< no device or mailbox associated
#define ECERR_CLIENT_TIMEOUT				(0x101+ERR_ECERRS) //!< response timeout
#define ECERR_CLIENT_INVALIDPARM			(0x102+ERR_ECERRS) //!< invalid parameter, e.g. null pointer
#define ECERR_CLIENT_INVALIDSIZE			(0x103+ERR_ECERRS) //!< invalid size
#endif
///\}

///\name ReportLog verbosity
///  
///\{
#define EC_LOG_MSGTYPE_HINT		0x001
#define EC_LOG_MSGTYPE_WARN		0x002
#define EC_LOG_MSGTYPE_ERROR		0x004
#define EC_LOG_MSGTYPE_LOG			0x010
///\}




// MF to stay close to Windows implementation
#define __declspec(x)
class IUnknown {
};

//MF from EthernetServices.h
#ifndef ETHERNET_ADDRESS_LEN
typedef struct TETHERNET_ADDRESS
{
	BYTE b[6];
} ETHERNET_ADDRESS, *PETHERNET_ADDRESS;
#define	ETHERNET_ADDRESS_LEN	sizeof(ETHERNET_ADDRESS)
#endif	

//MF from TcGlobal.h
#ifndef ENDOF
#define ENDOF(p)				((p)+1)
#endif

///\endcond

typedef struct TETYPE_EC_HEADER
{
	union
	{
		struct
		{
			BYTE	cmd;
			BYTE	idx;
		}SOS9(1);
		USHORT cmdIdx;
	};
	union
	{
		struct
		{
			USHORT	adp;
			USHORT	ado;
		}SOS9(2);
#ifndef __FORCE_PACKED
		ULONG laddr;
#else
		USHORT laddr;
		USHORT os9dummy;
#endif
	};
	union
	{
		struct
		{
#ifdef _LIL_END
			USHORT	len : 11;
			USHORT	res : 4;
			USHORT	next: 1;
#else
			USHORT	next: 1;
			USHORT	res : 4;
			USHORT	len : 11;
#endif
		}SOS9(3);
		USHORT length;
	};
	USHORT irq;
} __attribute__((packed)) ETYPE_EC_HEADER, *PETYPE_EC_HEADER;

typedef enum 
{
	EC_CMD_TYPE_NOP		= 0,
	EC_CMD_TYPE_APRD	= 1,
	EC_CMD_TYPE_APWR	= 2,
	EC_CMD_TYPE_APRW	= 3,
	EC_CMD_TYPE_FPRD	= 4,
	EC_CMD_TYPE_FPWR	= 5,
	EC_CMD_TYPE_FPRW	= 6,
	EC_CMD_TYPE_BRD		= 7,
	EC_CMD_TYPE_BWR		= 8,
	EC_CMD_TYPE_BRW		= 9,
	EC_CMD_TYPE_LRD		= 10,
	EC_CMD_TYPE_LWR		= 11,
	EC_CMD_TYPE_LRW		= 12,
	EC_CMD_TYPE_ARMW	= 13,
	EC_CMD_TYPE_EXT	= 255,
} EC_CMD_TYPE;

#define	ETYPE_EC_HEADER_LEN	sizeof(ETYPE_EC_HEADER)
#define	ETYPE_EC_CNT_LEN		sizeof(USHORT)
#define	ETYPE_EC_OVERHEAD		(ETYPE_EC_HEADER_LEN+ETYPE_EC_CNT_LEN)
											
#define	ETYPE_EC_CMD_LEN(p)			(ETYPE_EC_OVERHEAD+((PETYPE_EC_HEADER)p)->SOS9A(3)len)
#define	ETYPE_EC_CMD_COUNTPTR(p)	((PUSHORT)&(((PBYTE)p)[(ETYPE_EC_HEADER_LEN+((PETYPE_EC_HEADER)p)->SOS9A(3)len)]))
#define	ETYPE_EC_CMD_COUNT(p)		(*((PUSHORT)&(((PBYTE)p)[(ETYPE_EC_HEADER_LEN+((PETYPE_EC_HEADER)p)->SOS9A(3)len)])))
#define	ETYPE_EC_CMD_DATA(p)		(*((PUSHORT)&(((PBYTE)p)[ETYPE_EC_HEADER_LEN])))
#define	ETYPE_EC_CMD_DATAPTR(p)		(&(((PBYTE)p)[ETYPE_EC_HEADER_LEN]))
#define	NEXT_EcHeader(p)			((PETYPE_EC_HEADER)&((PBYTE)p)[((PETYPE_EC_HEADER)p)->SOS9A(3)len + ETYPE_EC_OVERHEAD])

#define MAILBOXCMD_CANOPEN_BEGIN				0xF300		// begin of reserved CANopen area
#define MAILBOXCMD_CANOPEN_SDO				0xF302		
#define MAILBOXCMD_CANOPEN_SDO_INFO_LIST	0xF3FC		// listType = index
#define MAILBOXCMD_CANOPEN_SDO_INFO_OBJ	0xF3FD		
#define MAILBOXCMD_CANOPEN_SDO_INFO_ENTRY	0xF3FE		
#define MAILBOXCMD_CANOPEN_END				0xF3FF		// end of reserved CANopen area

#define MAILBOXCMD_ECAT_FOE_BEGIN			0xF400		// File Access over EtherCAT
#define MAILBOXCMD_ECAT_FOE_FOPENREAD		0xF401	// 
#define MAILBOXCMD_ECAT_FOE_FOPENWRITE		0xF402	// 
#define MAILBOXCMD_ECAT_FOE_FCLOSE			0xF403	// 
#define MAILBOXCMD_ECAT_FOE_FREAD			0xF404	// 
#define MAILBOXCMD_ECAT_FOE_FWRITE			0xF405	// 
#define MAILBOXCMD_ECAT_FOE_PROGRESSINFO	0xF406	// 
#define MAILBOXCMD_ECAT_FOE_END				0xF41F		// File Access over EtherCAT

#define MAILBOXCMD_ECAT_SOE					0xF420		// Servo Drive over EtherCAT: IDN = LOWORD(iOffs), ELEMENT = LOBYTE(HIWORD(iOffs))
#define MAILBOXIOFFS_ECAT_SOE_ELEMENT_MASK		0x00FF0000	// element mask of soe idn
#define MAILBOXIOFFS_ECAT_SOE_DATASTATE			0x00010000	// element of soe idn
#define MAILBOXIOFFS_ECAT_SOE_NAME				0x00020000	// element of soe idn
#define MAILBOXIOFFS_ECAT_SOE_ATTRIBUTE			0x00040000	// element of soe idn
#define MAILBOXIOFFS_ECAT_SOE_UNIT				0x00080000	// element of soe idn
#define MAILBOXIOFFS_ECAT_SOE_MIN				0x00100000	// element of soe idn
#define MAILBOXIOFFS_ECAT_SOE_MAX				0x00200000	// element of soe idn
#define MAILBOXIOFFS_ECAT_SOE_VALUE				0x00400000	// element of soe idn
#define MAILBOXIOFFS_ECAT_SOE_DEFAULT			0x00800000	// element of soe idn
#define MAILBOXIOFFS_ECAT_SOE_DRIVENO_MASK		0x07000000	// element mask of drive no
#define MAILBOXIOFFS_ECAT_SOE_COMMAND			0x08000000	// command execution requested


#define MAILBOXCMD_ECAT_AOE					0xF100	// Send/Receive Ams command ( asynchronous communication )

///\brief Mailbox command types
typedef enum EC_MAILBOX_CMD
{	
	EC_MAILBOX_CMD_UPLOAD					 = 1, //!< upload a SDO from a slave
	EC_MAILBOX_CMD_DOWNLOAD					 = 2, //!< download a SDO from a slave
	EC_MAILBOX_CMD_READWRITE				 = 3, //!< perform mailbox read/write
}EC_MAILBOX_CMD;


typedef struct TEcMailboxAddr
{
	USHORT	id;
	USHORT	port;
} __attribute__((packed)) EcMailboxAddr, *PEcMailboxAddr;

///\brief Structure describing a mailbox command
///
typedef struct TEcMailboxCmd
{
#ifdef __FORCE_PACKED
	union {
	ULONG	os9dummy;
#endif
  	EcMailboxAddr addr;       //!< Mailbox address
#ifdef __FORCE_PACKED
	};
#endif
	ULONG		invokeId; //!< Identifier to assign a response to this command			
	ULONG		result;	  //!< Result of this command	
	ULONG		length; //!< number of bytes to read or to write
        ULONG		cmdId;	 //!< command id
	USHORT	type;   //!< SDO_DOWNLOAD or SDO_UPLOAD 		
	union
	{
#ifndef __FORCE_PACKED
		ULONG indexOffset;
#else
		USHORT indexOffset;
#endif
		struct
		{						
			BYTE		subIndex;       //!< Mailbox subindex	
			union
			{
				BYTE		valueInfo;			
				BYTE		complete;
			};
			USHORT	index;        //!< Mailbox index
		}SOS9(1);
	};
} __attribute__((packed)) EcMailboxCmd, *PEcMailboxCmd;

typedef struct TEcMailboxCmdRW : public TEcMailboxCmd
{
	ULONG writeLength; 	
} EcMailboxCmdRW, *PEcMailboxCmdRW;

//**************************** CLASSES/FUNCTIONS *****************************/
#ifndef WIN
#define interface struct
#endif

interface IEcMaster;
interface IEcMailboxClient;
interface IEcMailboxOwner;
interface IEcDeviceCallback;

#ifndef WIN
#undef interface
#endif

#ifdef WIN
// {0FAAD148-97DE-47d5-854B-F5DF08BC1391}
static const GUID IID_EcNpfDevice = 
{ 0xfaad148, 0x97de, 0x47d5, { 0x85, 0x4b, 0xf5, 0xdf, 0x8, 0xbc, 0x13, 0x91 } };

// {653EA647-B75A-45ff-A477-C9097A34E5C0}
static const GUID IID_EcFilterDevice = 
{ 0x653ea647, 0xb75a, 0x45ff, { 0xa4, 0x77, 0xc9, 0x9, 0x7a, 0x34, 0xe5, 0xc0 } };

// {A82C6E63-583C-4979-BDE0-C774F1D467F4}
static const GUID IID_EcUdpDevice = 
{ 0xa82c6e63, 0x583c, 0x4979, { 0xbd, 0xe0, 0xc7, 0x74, 0xf1, 0xd4, 0x67, 0xf4 } };

// {4FC1D9DB-E1F7-4f79-B012-24ABE98DBC05}
static const GUID IID_IEcDevice = 
{ 0x4fc1d9db, 0xe1f7, 0x4f79, { 0xb0, 0x12, 0x24, 0xab, 0xe9, 0x8d, 0xbc, 0x5 } };
#endif
///\brief Interface class to access an EtherCAT device.
///
/// This class is used by the application to access an EtherCAT device. 
/// The functionality comprises 
///
/// - Opening and closing of the device
///
/// - Retrieving the Master interface to control the EtherCAT state machine
///
/// - Retrieving the Master interface to control the EtherCAT state machine
///
/// - Getting access to the process image
///
/// - Initiating I/O read, write and async (status, mailbox) access

struct __declspec(novtable) IEcDevice : public IUnknown
{	
	///\brief Opens the selected network adapter.
	///\return result of the call.      
	virtual HRESULT Open(char* openName = NULL)=0;
	
	///\brief Closes the selected network adapter.
	///\return result of the call.         
	virtual HRESULT Close()=0;

	///\brief Timer method called cyclically by the application (State information update, timeout treatment, mailbox communication). 
	virtual HRESULT OnTimer()=0;	
	
	///\brief Gets the IO state (read part of the IO cycle). This method is called cyclically.
	///\return result of the call. Either IOSTATE_READY or ECERR_DEVICE_TIMEOUT.        		        		
	virtual long GetIoState()=0;
	
	///\brief Starts the IO communications (write part of the IO cycle). This method is called cyclically.
	///\return result of the call. Either IOSTATE_READY or IOSTATE_BUSY.        		        	
	virtual long StartIo()=0;	
		
	///\brief Retrieves the respective EtherCAT master.
	///	
	///\return Pointer to the CEcMaster.        	
	virtual IEcMaster* GetMaster()=0;	

	///\brief Returns the MAC address of the EtherCAT master.
	///	
	///\return MAC Address of the EtherCAT master.        	
	virtual ETHERNET_ADDRESS	GetMacAddress()=0;			
	
	///\brief Gets a pointer to the process data.
	virtual PBYTE ProcessDataPtr(INT inOut, INT offs, INT size)=0;	
	///\brief Gets the size of the process data.
	virtual INT ProcessDataSize(INT inOut)=0;	
	
	//MF
	///\brief Sets memory to be used for the process image.
	virtual HRESULT SetProcessDataMem( INT inOut, PBYTE mem, ULONG size )=0;

	///\brief Sends an EtherCAT Frame
	///
	///\param invokeId number to identify the sent frame with
	///\param cbLength length of the EtherCAT Frame
	///\param pFrame EtherCAT frame	
	virtual long SendEcFrame(ULONG invokeId, ULONG cbLength, PETYPE_EC_HEADER pFrame)=0;

	///\brief Sets the Callback interface
	virtual void SetCallbackInterface(IEcDeviceCallback *pCallback)=0;

	///\brief Returns if the device is opened
	///
	///\return Returns TRUE if device is opened
	virtual BOOL IsOpened()=0;

	/* $EXTENSION_START <PIVariableInfo> */
	//////////////////////////////////////////////////////////////////////
	///\brief Obtain number of process image output variables
	///
	///\return Returns the number of process image output variables
	virtual int GetNrInputVars( void )=0;

	//////////////////////////////////////////////////////////////////////
	///\brief Obtain name of the nth process image input variable
	///
	///\param idx Index of input variable
	///\return Returns the name of the nth process image input variable
	virtual const char *GetInputVar( unsigned int idx )=0;

	///\brief Obtain size and type information on a process image input variable
	///
	///\param varName name of the input variable to obtain info for
	///\param bitSize bit size of the respective variable in the process image
	///\param bitOffset bit offset of the respective variable
	///\param type type name of the respective variable
	///
	///\return Returns TRUE if variable info could be obtained (i.e. the var name exists)
	virtual BOOL GetInputVarInfo( const char *varName, ULONG &bitSize, ULONG &bitOffset, char *type )=0;

	//////////////////////////////////////////////////////////////////////
	///\brief Obtain number of process image output variables
	///
	///\return Returns the number of process image output variables
	virtual int GetNrOutputVars( void )=0;

	//////////////////////////////////////////////////////////////////////
	///\brief Obtain name of the nth process image output variable
	///
	///\param idx Index of output variable
	///\return Returns the name of the nth process image output variable
	virtual const char *GetOutputVar( unsigned int idx )=0;

	///\brief Obtain size and type information on a process image output variable
	///
	///\param varName name of the output variable to obtain info for
	///\param bitSize bit size of the respective variable in the process image
	///\param bitOffset bit offset of the respective variable
	///\param type type name of the respective variable
	///
	///\return Returns TRUE if variable info could be obtained (i.e. the var name exists)
	virtual BOOL GetOutputVarInfo( const char *varName, ULONG &bitSize, ULONG &bitOffset, char *type )=0;
	/* $EXTENSION_END <PIVariableInfo> */

	/* $EXTENSION_START <ErrorAnalysis> */
	//////////////////////////////////////////////////////////////////////
	///\brief Obtain number of process image output variables
	///
	///\return Returns the number of process image output variables
//RAS #warning aufräumen
	virtual const char* GetStateString(USHORT nState)=0;
	virtual BOOL RequestState(USHORT desiredState, ULONG cycles = 10000)=0;
	virtual BOOL CyclicCheckAllWCs(void (*preWCCheckErrFkt)(void) = 0, BOOL (*wcCheckErrFkt)(ULONG &frame, USHORT &cmd, USHORT &actualWcnt, USHORT &expectedWcnt) = 0, void (*postWCCheckErrFkt)(void) = 0) = 0;
	virtual BOOL CyclicCheckBusStateWC(USHORT* actualWcnt = 0, USHORT* expectedWcnt = 0) = 0;
	virtual BOOL CyclicCheckBusState(USHORT* actualState = 0) = 0;
	/* $EXTENSION_END <ErrorAnalysis> */
};

///\brief EcDevice Callback Interface
struct __declspec(novtable) IEcDeviceCallback
{
	///\brief Processes a returning EtherCAT frame sent with SendEcFrame
	///
	///\param nResult result
	///\param nInvokeId invokeId passed in SendEcFrame
	///\param cbLength length of the EtherCAT Frame
	///\param pFrame EtherCAT frame
	virtual void OnReturningEcFrame(ULONG nResult, ULONG nInvokeId, ULONG cbLength, PETYPE_EC_HEADER pFrame)=0;

	virtual long OnReportLog(DWORD msgCtrlMask, PCHAR szFormat, va_list pArgs )=0;
};

///\brief EtherCAT slave interface. 
/// Gets name, vendor id, product id and mailbox type (w/ or w/o mailbox) information from
/// a slave retrieved/enumerated by the master

///\brief EtherCAT slave Interface
struct __declspec(novtable) IEcSlave
{
	virtual BOOL HasMailBox()=0;
	virtual const char* GetName()=0;
	virtual void RequestState(USHORT state)=0;
	///\brief Gets the vendorId of the EtherCAT slave.
	///
	///\return The vendorId of the EtherCAT slave.
	virtual CONST ULONG GetVendorId()=0;

	///\brief Gets the productId of the EtherCAT slave.
	///
	///\return The productId of the EtherCAT slave.
	virtual CONST ULONG GetProductId()=0;

	virtual CONST ULONG GetNrInitCmds()=0;
	/* $EXTENSION_START <MailboxSize> */
	virtual USHORT GetOutputMailBoxLength() = 0;
	virtual USHORT GetInputMailBoxLength() = 0;
	virtual USHORT GetMailBoxType() = 0;
	/* $EXTENSION_END <MailboxSize> */
};

///\brief EtherCAT mailbox interface. 
/// Needed to implement communication interfaces using mailboxes

struct __declspec(novtable) IEcMailbox
{
	///\brief Allocates memory for a mailbox command (including data to be sent).
	///
	///\param size Size of the Mailbox command to be allocated.	
	///\return The allocated Mailbox command or NULL.		
	virtual  PEcMailboxCmd MailboxAlloc(long size)=0;
		
	///\brief Frees a previously allocated mailbox command.
	///
	///\param pCmd Mailbox command to be freed.	
	virtual  void	MailboxFree(PEcMailboxCmd pCmd)=0; 		
		
	///\brief Returns the mailbox address
	///
	///\return mailbox address.
	virtual	EcMailboxAddr	GetMailboxAddr()=0;	

	///\brief Returns the mailbox identification number
	///
	///\return mailbox identification number.
	virtual	USHORT	GetMailboxId()=0;		

	///\brief Returns the mailbox port number
	///
	///\return mailbox port number.
	virtual	USHORT	GetMailboxPort()=0;		

	///\brief Returns pointer to mailbox client
	///
	///\return pointer to mailbox usr interface
	virtual	IEcMailboxClient*	GetMailboxClient()=0;		

	///\brief Sets mailbox client
	///
	///\param pClient pointer to mailbox usr interface
	virtual	void	SetMailboxClient(IEcMailboxClient* pClient)=0;
	

	///\brief Returns pointer to mailbox owner interface
	///
	///\return pointer to mailbox owner interface
	virtual	IEcMailboxOwner*	GetMailboxOwner()=0;		
	
	///\brief Mailbox response to a previosly sent mailbox(see SendMailboxCmd) command.
	///
	/// Called by the EtherCAT Master, initiates a Mailbox callback.
	///
	///\param pCmd Mailbox command
	virtual  void  MailboxResponse(PEcMailboxCmd pCmd)=0;
		
	///\brief Sends a mailbox command
	///	
	///\return Result of the call.		
	virtual	HRESULT SendMailboxCmd(PEcMailboxCmd pCmd)=0;	
};

struct __declspec(novtable) IEcMailboxOwner
{
	///\brief Returns a pointer a mailbox interface
	///
	///\return pointer to mailbox interface.
	virtual	IEcMailbox*	GetMailbox()=0;		
	
	///\brief Processes a mailbox command sent by the application.Called by IEcMailbox::SendMailboxCmd.
	///
	///\param pCmd Mailbox command
	///\return Result of the call.
	virtual  long  OnMailboxReceive(PEcMailboxCmd pCmd)=0;
};

///\brief Mailbox Client Interface
struct __declspec(novtable) IEcMailboxClient
{
	///\brief Mailbox response to a previously sent mailbox cmd
	///
	///\param pCmd Mailbox command.
	///\param pMailbox Mailbox that sent the command
	virtual void OnMailboxResponse(PEcMailboxCmd pCmd, IEcMailbox *pMailbox)=0;
};

///\brief EtherCAT master Interface
/// Retrieved from an EtherCAT device. Used to control the EtherCAT state machine and to access the slave devices.

struct __declspec(novtable) IEcMaster: public IEcMailboxOwner
{	
	///\brief Request EtherCAT master to change to the specified state.
	///
	///\param state The requested EtherCAT state.
	virtual	void		RequestState(USHORT state)=0;

	///\brief Gets the requested EtherCAT master state
	///
	///\return Requested EtherCAT master state
	virtual	USHORT	GetRequestState()=0;

	///\brief Returns the current state of the EtherCAT master.
	///
	///\param slaveStatesOredIn If true, the slave states are ored in to the result, if false (default), only the Master state is returned.
	///\return Current state of the EtherCAT master.
	virtual	USHORT	GetStateMachine( BOOL slaveStatesOredIn = false )=0;
	
	///\brief Gets a pointer to the EtherCAT slave with the specified address.
	///
	///\param addr Address of the EtherCAT slave.
	///\return Pointer to the requested EtherCAT slave or NULL if no slave with this address was found.
	virtual	IEcSlave*	GetSlaveByAddr(USHORT addr)=0;

	///\brief Gets a pointer to the EtherCAT slave with the specified position.
	///
	///\param nPos Position of the EtherCAT slave.
	///\return Pointer to the requested EtherCAT slave or NULL if no slave exists at this position.	
	virtual  IEcSlave*	GetSlaveByPos(ULONG nPos)=0; 

	///\brief Gets the number of EtherCAT slaves.
	///
	///\return Number of EtherCAT slaves.
	virtual	ULONG	GetSlaveCount()=0;

	///\brief Gets the count of cyclic frames
	///
	///\return Number of cyclic frames. Usually zero if slave is configured, but not active on the bus.
	virtual	ULONG GetCyclicFrameCount()=0;

	///\brief Gets information about a specific cycic frame
	///
	///\param nFrame Index of cylcic frames
	///\param imageOffsIn Offset of the frame in the input image
	///\param imageOffsOut Offset of the frame in the output image
	///\param nCmds number EtherCAT sub commands in the frame
	virtual	BOOL	GetCyclicFrameInfo(ULONG nFrame, USHORT& imageOffsIn, USHORT& imageOffsOut, USHORT& nCmds) = 0; 

	///\brief Gets information about a specific cycic frame sub command
	///
	///\param nFrame Index of cylcic frames
	///\param nCmd Index of sub command
	///\param cmdHeader EtherCAT command header
	///\param imageOffsIn Offset of the cmd in the input image
	///\param imageOffsOut Offset of the cmd in the output image
	///\param expWcnt Expected working counter. NB: To realize a default parameter, this is a pointer and no reference!!!
	///\param actWcnt Actual working counter as received by the last command. NB: To realize a default parameter, this is a pointer and no reference!!!
	///\param execState Mask containing the master states in which this command gets executed. NB: To realize a default parameter, this is a pointer and no reference!!!
	virtual BOOL    GetCyclicCommandInfo(ULONG nFrame, USHORT nCmd, ETYPE_EC_HEADER& cmdHeader, USHORT& imageOffsIn, USHORT& imageOffsOut, USHORT* expWcnt = 0, USHORT* actWcnt = 0, USHORT* execState = 0) = 0;

/* $EXTENSION_START <ENI conformity> */
//MF introduced for ENI conformity
	///\brief Gets the required cycle time
	///
	///\return Returns the required cycle time (greatest common divisor of all cyclic frames) in microseconds as specified in the ENI, or 0, if none is specified
	virtual	ULONG GetCycleTimeInMicroSecs()=0;
/* $EXTENSION_END <ENI conformity> */

/* $EXTENSION_START <Heartbeat> */
	///\brief Set the EtherCAT cycle time that WaitForHeartbeat shall use
	///
	///\param cycleTimeUS The cycle time in microseconds
	virtual    ULONG SetCycleTimeInMicroSecs(ULONG cycleTimeUS) = 0;

	///\brief Wait for the next heartbeat
	///
	///\param useDC (default)1: synchronize heartbeat with DC, if we have a DC master; 0: use a heartbeat that is derived from the system clock
	virtual    ULONG WaitForHeartbeat(BOOL useDC = 1) = 0;
/* $EXTENSION_END <Heartbeat> */
	///\brief Opens the EtherCAT master.
	virtual	HRESULT		Open(USHORT state = DEVICE_STATE_INIT) = 0;

	///\brief Closes the EtherCAT master.
	virtual	HRESULT		Close() = 0;
};


#endif //__ECINTERFACE_H__
