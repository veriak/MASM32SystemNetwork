;----------------------------------------------------------------------------------------
; MASM32 WinSock2 Library
;
; Copyright 2010 Veria Kalantary
; veria.kalantary@gmail.com
; https://github.com/veriak
;
;----------------------------------------------------------------------------------------

WSAEVENT				typedef	DWORD
WSAOVERLAPPED struct
    Internal			DWORD	?
    InternalHigh		DWORD	?
    _Offset				DWORD	?
    OffsetHigh			DWORD	?
    hEvent				WSAEVENT	?
WSAOVERLAPPED ends
LPWSAOVERLAPPED			typedef ptr WSAOVERLAPPED

PSOCKET_ADDRESS 		typedef ptr SOCKET_ADDRESS

SOCKET_ADDRESS_LIST struct
	iAddressCount 		DWORD	?
	Address       		DWORD	?
SOCKET_ADDRESS_LIST ends
LPSOCKET_ADDRESS_LIST 	typedef ptr SOCKET_ADDRESS_LIST

AFProtocols struct
	iAddressFamily		DWORD	?
	iProtocol			DWORD	?
AFProtocols ends
PAFProtocols			typedef ptr AFProtocols

WSABUF struct
	len					DWORD	?
    buf					DWORD	?
WSABUF ends

.const    
;	WSA_IO_PENDING          			EQU	ERROR_IO_PENDING
;	WSA_IO_INCOMPLETE       			EQU	ERROR_IO_INCOMPLETE
;	WSA_INVALID_HANDLE      			EQU	ERROR_INVALID_HANDLE
;	WSA_INVALID_PARAMETER   			EQU	ERROR_INVALID_PARAMETER
;	WSA_NOT_ENOUGH_MEMORY   			EQU	ERROR_NOT_ENOUGH_MEMORY
;	WSA_OPERATION_ABORTED   			EQU	ERROR_OPERATION_ABORTED
	WSA_INVALID_EVENT       			EQU	0
	WSA_MAXIMUM_WAIT_EVENTS				EQU	MAXIMUM_WAIT_OBJECTS
	WSA_WAIT_FAILED						EQU	-1
	WSA_WAIT_EVENT_0        			EQU	WAIT_OBJECT_0
	WSA_WAIT_IO_COMPLETION				EQU	WAIT_IO_COMPLETION
	WSA_WAIT_TIMEOUT					EQU	WAIT_TIMEOUT
	WSA_INFINITE            			EQU	INFINITE
    SIO_RCVALL              			EQU	98000001h
    WSA_FLAG_OVERLAPPED     			EQU	01h  
    WSA_FLAG_MULTIPOINT_C_ROOT			EQU	02h
	WSA_FLAG_MULTIPOINT_C_LEAF			EQU	04h
	WSA_FLAG_MULTIPOINT_D_ROOT			EQU	08h
	WSA_FLAG_MULTIPOINT_D_LEAF			EQU	10h
    IOC_WS2       						EQU	08000000h
	IOC_PROTOCOL						EQU	10000000h
  	IOC_VENDOR    						EQU	18000000h
  	SIO_ASSOCIATE_HANDLE    			EQU	1 or IOC_WS2 or IOC_IN
  	SIO_ENABLE_CIRCULAR_QUEUEING    	EQU	2 or IOC_WS2
  	SIO_FIND_ROUTE                  	EQU	3 or IOC_WS2 or IOC_OUT
  	SIO_FLUSH                       	EQU	4 or IOC_WS2
  	SIO_GET_BROADCAST_ADDRESS       	EQU	5 or IOC_WS2 or IOC_OUT
  	SIO_GET_EXTENSION_FUNCTION_POINTER  EQU	6 or IOC_WS2 or IOC_INOUT
  	SIO_GET_QOS                         EQU	7 or IOC_WS2 or IOC_INOUT
  	SIO_GET_GROUP_QOS                   EQU	8 or IOC_WS2 or IOC_INOUT
  	SIO_MULTIPOINT_LOOPBACK             EQU	9 or IOC_WS2 or IOC_IN
  	SIO_MULTICAST_SCOPE                 EQU	10 or IOC_WS2 or IOC_IN
  	SIO_SET_QOS                         EQU	11 or IOC_WS2 or IOC_IN
  	SIO_SET_GROUP_QOS                   EQU	12 or IOC_WS2 or IOC_IN
  	SIO_TRANSLATE_HANDLE                EQU	13 or IOC_WS2 or IOC_INOUT
  	SIO_ROUTING_INTERFACE_QUERY         EQU	20 or IOC_WS2 or IOC_INOUT
  	SIO_ROUTING_INTERFACE_CHANGE        EQU	21 or IOC_WS2 or IOC_IN
  	SIO_ADDRESS_LIST_QUERY              EQU	22 or IOC_WS2 or IOC_OUT
  	SIO_ADDRESS_LIST_CHANGE             EQU	23 or IOC_WS2
  	SIO_QUERY_TARGET_PNP_HANDLE         EQU	24 or IOC_WS2 or IOC_OUT
