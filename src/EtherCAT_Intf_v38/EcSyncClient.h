#if !defined(AFX_ECSYNCCLIENT_H__A399F9C6_69CD_4F5F_BA12_3583CE54FB35__INCLUDED_)
#define AFX_ECSYNCCLIENT_H__A399F9C6_69CD_4F5F_BA12_3583CE54FB35__INCLUDED_
//****************************************************************************/
//                                                                           */
//     File   : EcSyncClient.h                                               */
//                                                                           */
//     Content: Interface for the CEcSyncClient class                        */
//                                                                           */
//     Author : adapted by Max Fischer from Beckhoff Master Sample Code      */
//                                                                           */
//     Date   : 2. 12. 2008                                                  */
//                                                                           */
//****************************************************************************/

//**************************** INCLUDES **************************************/
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EcInterface.h"


//**************************** TYPES *****************************************/
class MutexSingleton;
class COsCriticalSection;

struct TEcSyncDevReq;
struct TEcSyncMbReq;

//**************************** CLASSES/FUNCTIONS *****************************/

///\brief Helper class for sending mailbox commands to an EtherCAT device and receiving the answer to the sent command. 
class CEcSyncClient  : public IEcMailboxClient, public IEcDeviceCallback
{
public:
	CEcSyncClient(IEcDevice *pDevice, IEcMailbox *pMailbox = 0, bool bWindowsTimer = false);
	virtual ~CEcSyncClient();
	
	//IEcDeviceCallback

	///\brief Processes a returning EtherCAT frame sent with SendEcFrame
	///
	///\param nResult result
	///\param nInvokeId invokeId passed in SendEcFrame
	///\param cbLength length of the EtherCAT Frame
	///\param pFrame EtherCAT frame
	virtual void OnReturningEcFrame(ULONG nResult, ULONG nInvokeId, ULONG cbLength, PETYPE_EC_HEADER pFrame);

	//IMailboxClient

	///\brief Mailbox response to a previously sent mailbox cmd
	///
	///\param pCmd Mailbox command.
	///\param pMailbox Mailbox that sent the command	
	virtual void OnMailboxResponse(PEcMailboxCmd pCmd, IEcMailbox *pMailbox);


	///\brief Sends an EtherCAT Frame
	///
	///\param invokeId number to identify the sent frame with
	///\param cbLength length of the EtherCAT Frame
	///\param pSndFrame EtherCAT frame to be sent	
	///\param pRcvFrame EtherCAT frame to be received	
	///
	///\return result of call.
	virtual long SendSyncEcFrame(ULONG invokeId, ULONG cbLength, PETYPE_EC_HEADER pSndFrame, PETYPE_EC_HEADER pRcvFrame);
			
	//CEcSyncClient

	///\brief Set communication timeout in ms
	///
	///\param nTimeout Communication timeout in ms
	virtual void SetTimeout(long nTimeout);

	///\brief Gets communication timeout in ms
	///
	///\return Communication timeout in ms
	virtual long GetTimeout();

	///\brief Sends a Upload request to an EtherCAT slave device.
	///
	///\param nInvokeId number to identify the sent frame with
	///\param nSlave id of slave the command is sent to
	///\param nCmdId CANOpen command id
	///\param nIndexOffset index offset
	///\param cbRdLength length of the read buffer
	///\param pRdData read buffer for uploaded data
	///\param cbRead number of bytes read
	///
	///\return result of call
	virtual long SyncUploadReq(ULONG nInvokeId, USHORT nSlave, ULONG nCmdId, ULONG nIndexOffset, ULONG cbRdLength, BYTE *pRdData, ULONG &cbRead);

	
	///\brief Sends a Download request to an EtherCAT slave device.
	///
	///\param nInvokeId number to identify the sent frame with
	///\param nSlave id of slave the command is sent to
	///\param nCmdId CANOpen command id
	///\param nIndexOffset index offset
	///\param cbWrLength length of the data to be downloaded
	///\param pWrData pointer to the data to be downloaded
	///
	///\return result of call	
	virtual long SyncDownloadReq(ULONG nInvokeId, USHORT nSlave, ULONG nCmdId, ULONG nIndexOffset, ULONG cbWrLength, BYTE *pWrData);			

	
	///\brief Sends a Upload request to an EtherCAT slave device.
	///
	///\param nInvokeId number to identify the sent frame with
	///\param nSlave id of slave the command is sent to
	///\param nCmdId CANOpen command id
	///\param nIndex CANOpen index
	///\param nSubIndex CANOpen sub index
	///\param cbRdLength length of the read buffer
	///\param pRdData read buffer for uploaded data
	///\param cbRead number of bytes read
	///
	///\return result of call
	virtual long SyncUploadReq(ULONG nInvokeId, USHORT nSlave, ULONG nCmdId, USHORT nIndex, BYTE nSubIndex, ULONG cbRdLength, BYTE *pRdData, ULONG &cbRead);

	
	///\brief Sends a Download request to an EtherCAT slave device.
	///
	///\param nInvokeId number to identify the sent frame with
	///\param nSlave id of slave the command is sent to
	///\param nCmdId CANOpen command id
	///\param nIndex CANOpen index
	///\param nSubIndex CANOpen sub index
	///\param cbWrLength length of the data to be downloaded
	///\param pWrData pointer to the data to be downloaded
	///
	///\return result of call	
	virtual long SyncDownloadReq(ULONG nInvokeId, USHORT nSlave, ULONG nCmdId, USHORT nIndex, BYTE nSubIndex, ULONG cbWrLength, BYTE *pWrData);		

	///\brief Sends a ReadWrite request to an EtherCAT slave device.
	///
	///\param nInvokeId number to identify the sent frame with
	///\param nSlave id of slave the command is sent to
	///\param nCmdId command id
	///\param nIndexOffset index offset
	///\param cbWrLength length of the data to be downloaded
	///\param pWrData pointer to the data to be downloaded
	///\param cbRdLength size of the read data buffer
	///\param pRdData pointer to the read data buffer
	///\param cbRead number of bytes read
	///
	///\return result of call	
	virtual long SyncReadWriteReq(ULONG nInvokeId,  USHORT nSlave, ULONG nCmdId, ULONG nIndexOffset, ULONG cbRdLength, BYTE *pRdData, 
		ULONG cbWrLength, BYTE *pWrData, ULONG &cbRead);

	///\brief Report callback, may be overridden by user 
	///
	///\param msgCtrlMask message verbosity level, one of EC_LOG_MSGTYPE_HINT, EC_LOG_MSGTYPE_WARN, EC_LOG_MSGTYPE_ERROR, EC_LOG_MSGTYPE_LOG
	///\param szFormat printf format string
	///\param pArgs printf args
	///
	///\return result of call	

	virtual long OnReportLog(DWORD msgCtrlMask, PCHAR szFormat,va_list pArgs);
	
	///\brief Get pointer to the device associated with this SyncClient
	///
	///\return Pointer to associated device
	virtual IEcDevice* GetDevicePtr( void ){ return m_pDevice; }

protected:
	///\brief Sends a mailbox command
	///	
	///\return Result of the call.
	virtual long SyncSendMailboxCmd(PEcMailboxCmd pCmd, ULONG cbRdLength, BYTE *pRdData, ULONG &cbRead);	

	///\brief Lock mutex, which is a singleton for all SyncClients and derived classes 
	///
	virtual void MutexLock ( void );

	///\brief Unlock mutex, which is a singleton for all SyncClients and derived classes 
	///
	virtual void MutexUnlock ( void );

protected:
	IEcMailbox*			m_pMailbox;
	IEcDevice*			m_pDevice;
	ULONG				m_nTimeout;
	TEcSyncDevReq*		m_syncDevReq;
	TEcSyncMbReq*		m_syncMbReq;
	bool				m_bWindowsTimer;

	ULONG				m_nInvokeId;

	COsCriticalSection	*m_pCritSection;

};

#endif // !defined(AFX_ECSYNCCLIENT_H__A399F9C6_69CD_4F5F_BA12_3583CE54FB35__INCLUDED_)
