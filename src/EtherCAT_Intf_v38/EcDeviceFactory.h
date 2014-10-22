#if !defined(AFX_ECDEVICEFACTORY__0B7F9B68_E1B5_4A4D_9732_B1467D64183A__INCLUDED_)
#define AFX_ECDEVICEFACTORY__0B7F9B68_E1B5_4A4D_9732_B1467D64183A__INCLUDED_
//****************************************************************************/
//                                                                           */
//     File   : EcDeviceFactory.h                                            */
//                                                                           */
//     Content: Interface for the CEcDeviceFactory class                     */
//                                                                           */
//     Author : adapted by Max Fischer from Beckhoff Master Sample Code      */
//                                                                           */
//     Date   : 2. 12. 2008                                                  */
//                                                                           */
//****************************************************************************/

//**************************** INCLUDES **************************************/
#include "EcInterface.h"

using namespace std;

//**************************** TYPES *****************************************/
struct expat_stack;
struct XML_ParserStruct;
class CEcDevice;
class IEcMailboxClient;

//**************************** CLASSES/FUNCTIONS *****************************/

///\brief Class factory for creating an EtherCAT device.

/// This class is used by the application to create an EtherCAT device. An EtherCAT
/// Configuration file(XML) is passed to the CreateDevice method. Here the file is parsed
/// and one master and one or more slave objects are created according to the information
/// found in the XML file.
///
/// For applications without file input facility, one might use the 'CreateDeviceStart', 
/// 'CreateDeviceParseLine', 'CreateDeviceEnd' interface: Call 'CreateDeviceStart', 
/// then for each XML line (e.g. from string, from EEPROM) 'CreateDeviceParseLine' once, 
/// and finish parsing with 'CreateDeviceEnd'

class CEcDeviceFactory
{
public:	
	///\brief constructor of CEcDeviceFactory
	CEcDeviceFactory();
	
	///\brief destructor of CEcDeviceFactory
	~CEcDeviceFactory();
	
	///\brief Creates an EtherCAT device.
	///
	///\param strXMLConfig Name of the xml Configuration File.
	///\param ppEcDevice Address of IEcDevice* pointer variable that receives the interface pointer to the new EhterCAT device object. 
	///\param pMbCallback Pointer to a callback interface for mailbox communication.
	///\return Result of the call.
	HRESULT CreateDevice(char *strXMLConfig, IEcDevice **ppEcDevice, IEcMailboxClient *pMbCallback = NULL);

  HRESULT DisposeDevice (IEcDevice *ppEcDevice);

	///\brief Creates an EtherCAT device, starts parsing (part of the interface for applications w/o file access).
	///
	///\param pMbCallback Pointer to a callback interface for mailbox communication, may be NULL if no mailbox is used.
	///\param pDev usually not needed.
	///\return Result of the call.
    HRESULT CreateDeviceStart ( IEcMailboxClient *pMbCallback, CEcDevice* pDev = 0 );
	///\brief Creates an EtherCAT device, push one line to the parser (part of the interface for applications w/o file access).
	///
	///\param buf Line (string) to be sent to the parser.
	///\param len String length.
	///\return Result of the call.
    HRESULT CreateDeviceParseLine ( char *buf, int len );
	///\brief Creates an EtherCAT device, finishes parsing (part of the interface for applications w/o file access).
	///
	///\param ppEcDevice Address of IEcDevice* pointer variable that receives the interface pointer to the new EhterCAT device object. 
	///\return Result of the call.
    HRESULT CreateDeviceEnd ( IEcDevice **ppEcDevice );

	static BOOL GetInfoDCPresent(void);


protected:	
    struct expat_stack *m_userData;
    XML_ParserStruct *m_parser;
    FILE* m_fpXML;
    IEcMailboxClient* m_callback;
	CEcDevice* m_pDevice;
};



#endif //AFX_ECDEVICEFACTORY__0B7F9B68_E1B5_4A4D_9732_B1467D64183A__INCLUDED_
