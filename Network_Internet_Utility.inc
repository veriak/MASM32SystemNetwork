;----------------------------------------------------------------------------------------
; MASM32 Netwrok and Internet Library
;
; Copyright 2010 Veria Kalantary
; veria.kalantary@gmail.com
; https://github.com/veriak
;
;----------------------------------------------------------------------------------------

include \masm32\include\ws2_32.inc
include \masm32\include\iphlpapi.inc
include \masm32\include\wininet.inc
include \masm32\include\mpr.inc

includelib \masm32\lib\ws2_32.lib
includelib \masm32\lib\iphlpapi.lib
includelib \masm32\lib\wininet.lib
includelib \masm32\lib\mpr.lib	

include WinSock2.inc

ICMP struct 
    i_type 									db	? 
    i_code 									db	? 
    i_cksum 								dw	? 
    i_id 									dw	? 
    i_seq 									dw	? 
    timestamp 								dd	? 
ICMP ends 

tcp_hdr struct
    tcp_sourc_port 							dw	?
    tcp_dest_port 							dw	?
    tcp_seq 								dd	?
    tcp_ack 								dd	?
    tcp_len 								db	?
    tcp_flag 								db	?
    tcp_win 								dw	?
    tcp_cksum 								dw	?
    tcp_urgent 								dw	?
tcp_hdr ends
	
PMIB_TCPROW									typedef ptr	MIB_TCPROW
PMIB_UDPROW									typedef ptr	MIB_UDPROW
PMIB_TCPROW_EX								typedef ptr	MIB_TCPROW_EX
PMIB_UDPROW_EX								typedef ptr	MIB_UDPROW_EX			

MIB_TCPROW_TABLE_EX struct
	dwNumEntries							dd	?
	Table									MIB_TCPROW_EX	<>
MIB_TCPROW_TABLE_EX ends
PMIB_TCPROW_TABLE_EX						typedef ptr MIB_TCPROW_TABLE_EX

MIB_UDPROW_TABLE_EX struct
	dwNumEntries							dd	?
	Table									MIB_UDPROW_EX	<>
MIB_UDPROW_TABLE_EX ends
PMIB_UDPROW_TABLE_EX						typedef ptr MIB_UDPROW_TABLE_EX
   
TCPIPConnection struct
    Protocol								LPCSTR	?
    LocalAddr								LPCSTR	?
    LocalPort								dd	?
    RemoteAddr								LPCSTR	?
    RemotePort								dd	?
    State									LPCSTR	?
TCPIPConnection ends
PTCPIPConnection							typedef ptr TCPIPConnection

PTCPIPConnections							typedef DWORD

TCPIPConnectionsList struct
	dwCount									dd	?
	pTCPIPConnections						PTCPIPConnections	?
TCPIPConnectionsList ends
PTCPIPConnectionsList						typedef ptr	TCPIPConnectionsList

TCPIPConnectionEx struct
    Protocol								LPCSTR	?
    LocalAddr								LPCSTR	?
    LocalPort								dd	?
    RemoteAddr								LPCSTR	?
    RemotePort								dd	?
    State									LPCSTR	?
    ProcessID								dd	?
    ProcessName								LPCSTR	?
TCPIPConnectionEx ends
PTCPIPConnectionEx							typedef ptr TCPIPConnectionEx

PTCPIPConnectionsEx							typedef DWORD

TCPIPConnectionsExList struct
	dwCount									dd	?
	pTCPIPConnectionsEx						PTCPIPConnectionsEx	?
TCPIPConnectionsExList ends
PTCPIPConnectionsExList						typedef ptr	TCPIPConnectionsExList

PingInfo struct
	wID										dw	?
	bTTL									db	?
	dwSizeRet								dd	?
    dwRetTime								dd	?     
    pAddress								dd	?		
PingInfo ends
PPingInfo									typedef ptr PingInfo

ScanPortInfo struct
	DestAddr								DWORD	?
	dwStartPort								DWORD	?
	dwStopPort								DWORD	?
	hWnd									HANDLE	?
	wmInform								UINT	?
ScanPortInfo ends
PScanPortInfo								typedef ptr ScanPortInfo

SendBuff									PROTO	:SOCKET, :LPCSTR
SendExact									PROTO	:SOCKET, :LPVOID, :DWORD
RecvExact									PROTO	:SOCKET, :LPVOID, :DWORD
GetLocalIPAddress							PROTO
GetIPAddr									PROTO	:LPCSTR
CloseAllConnections 						PROTO	:PTCPIPConnection
CloseConnection 							PROTO	:PTCPIPConnection
GetNetStat									PROTO	:PTCPIPConnectionsList
GetTCPConnections							PROTO	:PTCPIPConnectionsList
GetUDPConnections							PROTO	:PTCPIPConnectionsList
GetNetStatEx								PROTO	:PTCPIPConnectionsExList
GetTCPConnectionsEx							PROTO	:FARPROC, :PTCPIPConnectionsExList, :HANDLE
GetUDPConnectionsEx							PROTO	:FARPROC, :PTCPIPConnectionsExList, :HANDLE
NetShell									PROTO	:SOCKET, :LPSTR
UploadFile 									PROTO	:SOCKET, :LPCSTR
DownloadURL  								PROTO	:LPCSTR, :DWORD, :DWORD
FindRealIP 									PROTO 	:LPCSTR
LookupAddress 								PROTO	:LPCSTR
LookupName	 								PROTO	:LPCSTR
CheckSum									PROTO	:DWORD, :DWORD
FillICMPPacket 								PROTO 	:DWORD, :DWORD
Ping										PROTO	:LPCSTR, :PPingInfo, :DWORD
DecodePingResponse							PROTO	:DWORD, :DWORD, :DWORD
ScanPort									PROTO	:PScanPortInfo
WakeOnLan									PROTO	:LPCSTR
AddRemoveNetworkResource					PROTO	:LPCSTR, :LPCSTR, :LPCSTR, :LPCSTR, :BOOL
ShowNetErrorMessage 						PROTO	:HANDLE
LogNetErrorMessage							PROTO	:LPCSTR, :LPCSTR

.const
	ICMP_ECHO_REQUEST       				equ 8

.data	
	szSocketError							db	"Socket error.", 0	
	szszTCP									db	"TCP", 0
	szszUDP									db	"UDP", 0
	szCommandLine       					db	"cmd.exe", 0	
	szAnyAddr								db	"*.*.*.*", 0
	szAnyPort								db	"*", 0
	szWakeOnLanPrefix						db	"FFFFFFFFFFFF", 0
	lpszAgent 								db	"Mozilla", 0
	URLCheckIP             					db	"http://checkip.dyndns.org/", 0
	szStateClosed	    					db	"CLOSED", 0
	szStateListen	    					db	"LISTEN", 0
    szStateSynSent	    					db	"SYN_SENT", 0
    szStateSynRcvd	    					db	"SYN_RCVD", 0
    szStateEstab	    					db	"ESTAB", 0
    szStateFinWait1	    					db	"FIN_WAIT1", 0
    szStateFinWait2	    					db	"FIN_WAIT2", 0
    szStateCloseWait	    				db	"CLOSE_WAIT", 0
    szStateClosing	    					db	"CLOSING", 0
    szStateLastAck	   						db	"LAST_ACK", 0
    szStateTimeWait	    					db	"TIME_WAIT", 0
    szStateDeleteTCB	    				db  "DELETE_TCB", 0
    szStateUnkown	    					db	"UNKNOWN", 0   
            	  
.data	    
    stateTable	            				dd offset szStateClosed
			                				dd offset szStateListen		
					        				dd offset szStateSynSent	
					        				dd offset szStateSynRcvd	
					        				dd offset szStateEstab		
					        				dd offset szStateFinWait1	
					        				dd offset szStateFinWait2	
					        				dd offset szStateCloseWait
					        				dd offset szStateClosing	
					        				dd offset szStateLastAck	
					        				dd offset szStateTimeWait	
					        				dd offset szStateDeleteTCB
						    				dd offset szStateUnkown       						     
						    
.code

SendBuff proc uses ebx ecx edx ClientSocket:SOCKET, lpBuff:LPCSTR
	.if ClientSocket	 
		invoke lstrlen, lpBuff
		mov ebx, eax
	@@:	
		invoke send, ClientSocket, lpBuff, ebx, 0
		cmp eax, SOCKET_ERROR
		je @B
	.endif											
	ret
SendBuff endp

SendExact proc uses ecx edx _socket:SOCKET, lpBuff:LPVOID, sendlen:DWORD
	.if _socket	 
		invoke send, _socket, lpBuff, sendlen, 0
	.endif
	
	.if eax == sendlen
		mov eax, TRUE		
	.else	
		mov eax, FALSE
	.endif											
	ret
SendExact endp

RecvExact proc uses ecx edx _socket:SOCKET, lpBuff:LPVOID, recvlen:DWORD
	LOCAL pBuff: PBYTE
	LOCAL dwCount: DWORD
	LOCAL dwSum: DWORD
			 
	m2m pBuff, lpBuff
	m2m dwCount, recvlen
	mov dwSum, 0
	.if _socket    
		.while TRUE  
			invoke recv, _socket, pBuff, dwCount, 0
			.if eax == 0
				jmp @@RetFalse
				
			.elseif eax == SOCKET_ERROR												
				jmp @@RetFalse										
			.endif			
								
			add pBuff, eax
			sub dwCount, eax
			add dwSum, eax
			mov eax, recvlen
			.if dwSum >= eax
				.break
			.endif
		.endw	    
		mov eax, TRUE
		ret
	.endif	
@@RetFalse:
	mov eax, FALSE
	ret	
RecvExact endp

SetTimeOut proc uses ecx edx _socket:SOCKET, secs:DWORD
	LOCAL timeout: DWORD
	m2m timeout, secs
	invoke setsockopt, _socket, SOL_SOCKET, SO_RCVTIMEO, addr timeout, sizeof timeout
	invoke setsockopt, _socket, SOL_SOCKET, SO_SNDTIMEO, addr timeout, sizeof timeout
	ret
SetTimeOut endp	
	
GetLocalIPAddress proc uses ecx edx
	LOCAL hostname [128]: BYTE		
	invoke gethostname, addr hostname, sizeof hostname
    invoke gethostbyname, addr hostname            
    mov eax, (hostent ptr [eax]).h_list
    mov eax, [eax]                   
    mov eax, [eax]
	invoke inet_ntoa, eax	  
	ret
GetLocalIPAddress endp

GetIPAddr proc uses ecx edx lpszHost:LPCSTR
	invoke gethostbyname, lpszHost
    .if eax 
        mov eax, (hostent ptr [eax]).h_list 
        mov eax, [eax] 
        mov eax, [eax] 
    .else 
        invoke inet_addr, lpszHost 
        .if eax == INADDR_NONE
        	xor eax, eax
        .endif
    .endif     	
	ret
GetIPAddr endp

CloseAllConnections proc uses esi edi ebx ecx edx lpExceptConnection:PTCPIPConnection
	LOCAL bResult: BOOLEAN
	LOCAL dwLenBuffer: DWORD
	LOCAL fakeBuffer: DWORD
	LOCAL ExceptRow: MIB_TCPROW
	LOCAL ExceptRow2: MIB_TCPROW 
	LOCAL dwCount: DWORD	
	mov bResult, TRUE
	.if lpExceptConnection
		assume ebx: ptr MIB_TCPROW
		assume edi: ptr TCPIPConnection
		lea ebx, ExceptRow
		mov edi, lpExceptConnection
		mov [ebx].dwState, MIB_TCP_STATE_ESTAB 
		invoke inet_addr, [edi].LocalAddr
		mov [ebx].dwLocalAddr, eax
		mov edx, [edi].LocalPort	
		invoke htons, edx	
		mov [ebx].dwLocalPort, eax 
		invoke inet_addr, [edi].RemoteAddr
		mov [ebx].dwRemoteAddr, eax		
		mov edx, [edi].RemotePort
		invoke htons, edx		
		mov [ebx].dwRemotePort, eax  
		assume edi: nothing
		assume edi: ptr MIB_TCPROW
		lea edi, ExceptRow2
		mov [edi].dwState, MIB_TCP_STATE_ESTAB 
		m2m [edi].dwLocalAddr, [ebx].dwRemoteAddr
		m2m [edi].dwLocalPort, [ebx].dwRemotePort
		m2m [edi].dwRemoteAddr, [ebx].dwLocalAddr
		m2m [edi].dwRemotePort, [ebx].dwLocalPort
		assume ebx: nothing 
		assume edi: nothing
	.endif		     			        				       			        			
	mov dwLenBuffer, 1
	invoke GetTcpTable, addr fakeBuffer, addr dwLenBuffer, 1      	
  	invoke GlobalAlloc, GPTR, dwLenBuffer
  	mov edi, eax	
  	lea ecx, dwLenBuffer
	invoke GetTcpTable, eax, ecx, 1
	m2m dwCount, [edi]	
   	push edi
  	add edi, 4
	xor esi, esi	
	.while esi < dwCount
		mov eax, (MIB_TCPROW ptr [edi]).dwState
		.if eax == MIB_TCP_STATE_ESTAB			
			invoke CompareStructVar, addr ExceptRow, edi, sizeof MIB_TCPROW
			mov ebx, eax
			invoke CompareStructVar, addr ExceptRow2, edi, sizeof MIB_TCPROW			
			.if (eax != 0) && (ebx != 0)			
				m2m (MIB_TCPROW ptr [edi]).dwState, MIB_TCP_STATE_DELETE_TCB	
				invoke SetTcpEntry, edi 
				.if eax != NO_ERROR
					mov bResult, FALSE
				.endif
			.endif	
		.endif	              		         
		add edi, sizeof MIB_TCPROW
		inc	esi
  	.endw
	pop edi	
	invoke GlobalFree, edi	
	xor eax, eax
	mov al, bResult
	ret
CloseAllConnections endp

CloseConnection proc uses esi ebx ecx edx lpConnection:PTCPIPConnection
	LOCAL TCPRow: MIB_TCPROW		 	
	assume ebx: PMIB_TCPROW
	assume esi: PTCPIPConnection
	lea ebx, TCPRow
	mov esi, lpConnection
	mov [ebx].dwState, MIB_TCP_STATE_DELETE_TCB		
	invoke inet_addr, [esi].LocalAddr
	mov [ebx].dwLocalAddr, eax
	mov edx, [esi].LocalPort
	invoke htons, edx
	mov [ebx].dwLocalPort, eax	
	invoke inet_addr, [esi].RemoteAddr
	mov [ebx].dwRemoteAddr, eax
	mov edx, [esi].RemotePort
	invoke htons, edx      	
    mov [ebx].dwRemotePort, eax 
	assume ebx: nothing 
	assume esi: nothing   		    			        				       			        				
	invoke SetTcpEntry, addr TCPRow
	.if eax != NO_ERROR
		mov eax, FALSE
	.else
		mov eax, TRUE
	.endif			
	ret
CloseConnection endp

GetNetStat PROC lpConnections:PTCPIPConnectionsList	  	
    invoke GetTCPConnections, lpConnections    
    invoke GetUDPConnections, lpConnections     
	ret
GetNetStat endp

GetTCPConnections proc uses esi edi ebx ecx edx lpConnections:PTCPIPConnectionsList
	LOCAL lnBuffer: DWORD
    LOCAL fakeBuffer: DWORD
    LOCAL pBuff: DWORD
    LOCAL dwCount: DWORD 
    LOCAL dwOffset: DWORD            
	mov lnBuffer, 1
	invoke GetTcpTable, addr fakeBuffer, addr lnBuffer, 1      	
    invoke GlobalAlloc, GPTR, lnBuffer
  	mov edi, eax	  	
  	invoke GetTcpTable, edi, addr lnBuffer, 1
  	m2m dwCount, dword ptr [edi]	
  	push edi
  	add edi, 4  	  	  	   	
  	assume ebx:ptr TCPIPConnection
  	assume edx:ptr TCPIPConnectionsList  	
  	mov edx, lpConnections
  	push edx   	  	
  	mov ecx, [edx].dwCount			  		
  	mov eax, sizeof TCPIPConnection  		  		 
  	mul ecx 
  	mov dwOffset, eax  	 	    		  					   	  	 
  	pop edx    
  	mov ecx, dwCount
  	add [edx].dwCount, ecx		  			  		
  	lea eax, [edx].pTCPIPConnections   	 	
  	invoke SetLength, eax, sizeof TCPIPConnection, [edx].dwCount
  	mov edx, lpConnections
  	mov ebx, [edx].pTCPIPConnections
  	assume edx:nothing
  		
  	add ebx, dwOffset
  	mov pBuff, ebx	 	    
  	xor esi, esi  
  	.while esi < dwCount 
  		mov ebx, pBuff 		 		  	  		  			  		  		  			
  		mov [ebx].Protocol, offset szszTCP  		  	  					  			     	 
      	invoke inet_ntoa, (MIB_TCPROW ptr [edi]).dwLocalAddr      	
      	mov fakeBuffer, eax      	
      	invoke lstrlen, fakeBuffer
      	inc eax
      	invoke GlobalAlloc, GPTR, eax      	      	      	
      	mov [ebx].LocalAddr, eax      	      	
      	invoke lstrcpy, [ebx].LocalAddr, fakeBuffer
      	mov eax, (MIB_TCPROW ptr [edi]).dwLocalPort 
      	and eax, 0000FFFFh   
      	invoke ntohs, eax  	    	      				      	    	     	 
        mov [ebx].LocalPort, eax                       
        mov eax, (MIB_TCPROW ptr [edi]).dwRemoteAddr
        push eax        
		invoke inet_ntoa, eax
        mov fakeBuffer, eax
      	invoke lstrlen, fakeBuffer
      	inc eax
      	invoke GlobalAlloc, GPTR, eax
      	mov [ebx].RemoteAddr, eax      	
      	invoke lstrcpy, [ebx].RemoteAddr, fakeBuffer
      	pop eax      	     	       	                
        .if eax      	      				
        	mov eax, (MIB_TCPROW ptr [edi]).dwRemotePort
        	and eax, 0000FFFFh
      		invoke ntohs, eax      		
      	.endif	       		 
      	mov [ebx].RemotePort, eax                         		
        mov eax, (MIB_TCPROW ptr [edi]).dwState
        .if eax > 12
	    	mov eax, 13
	    .endif
   		dec eax   		
        m2m [ebx].State, stateTable[eax * 4]		      	
		add edi, sizeof MIB_TCPROW			  		
  		add pBuff, sizeof TCPIPConnection  		  		 
		inc	esi			
  	.endw
  	pop edi
  	invoke GlobalFree, edi     	  	
  	assume ebx:nothing  	
  	ret
GetTCPConnections endp

GetUDPConnections proc uses esi edi ebx ecx edx lpConnections:PTCPIPConnectionsList
	LOCAL lnBuffer: DWORD
    LOCAL fakeBuffer: DWORD
    LOCAL pBuff: DWORD
    LOCAL dwCount: DWORD     
    LOCAL dwOffset: DWORD                  
	mov lnBuffer, 1
	invoke GetUdpTable, addr fakeBuffer, addr lnBuffer, 1      	
    invoke GlobalAlloc, GPTR, lnBuffer
  	mov edi, eax	  	
  	invoke GetUdpTable, edi, addr lnBuffer, 1
  	m2m dwCount, dword ptr [edi]	
  	push edi
  	add edi, 4  	  	  	   	
  	assume ebx:ptr TCPIPConnection
  	assume edx:ptr TCPIPConnectionsList
  	mov edx, lpConnections
  	push edx   	  	
  	mov ecx, [edx].dwCount			  		
  	mov eax, sizeof TCPIPConnection  		  		 
  	mul ecx 
  	mov dwOffset, eax  	 	    		  					   	  	 
  	pop edx    
  	mov ecx, dwCount
  	add [edx].dwCount, ecx		  			  		
  	lea eax, [edx].pTCPIPConnections   	 	
  	invoke SetLength, eax, sizeof TCPIPConnection, [edx].dwCount
  	mov edx, lpConnections
  	mov ebx, [edx].pTCPIPConnections
  	assume edx:nothing
  		
  	add ebx, dwOffset
  	mov pBuff, ebx	 	    
  	xor esi, esi  
  	.while esi < dwCount 
  		mov ebx, pBuff 		 		  	  		  			  		  		  		  			
  		mov [ebx].Protocol, offset szszUDP    	  					  			     	 
      	invoke inet_ntoa, (MIB_UDPROW ptr [edi]).dwLocalAddr      	
      	mov fakeBuffer, eax
      	invoke lstrlen, fakeBuffer
      	inc eax
      	invoke GlobalAlloc, GPTR, eax      	      	      	
      	mov [ebx].LocalAddr, eax      	      	      	
      	invoke lstrcpy, [ebx].LocalAddr, fakeBuffer       	      		
      	mov eax, (MIB_UDPROW ptr [edi]).dwLocalPort
      	and eax, 0000FFFFh    	      				      	      	      				
      	invoke ntohs, eax      		   	     	 
        mov [ebx].LocalPort, eax                               	      	
		add edi, sizeof MIB_UDPROW
		add pBuff, sizeof TCPIPConnection
		inc	esi			
  	.endw
  	pop edi
  	invoke GlobalFree, edi     	  	
  	assume ebx:nothing		
	ret
GetUDPConnections endp

GetNetStatEx proc uses ecx edx lpConnectionsEx:PTCPIPConnectionsExList
	LOCAL hDll: HINSTANCE	
	LOCAL hSnapShot: HANDLE		
	invoke LoadLibrary, StrM("iphlpapi.dll")
    mov hDll, eax 
    invoke CreateToolhelp32Snapshot, TH32CS_SNAPPROCESS, 0
	mov hSnapShot, eax
    invoke GetProcAddress, hDll, StrM("AllocateAndGetTcpExTableFromStack")
    invoke GetTCPConnectionsEx, eax, lpConnectionsEx, hSnapShot    
    invoke GetProcAddress, hDll, StrM("AllocateAndGetUdpExTableFromStack")         		        
    invoke GetUDPConnectionsEx, eax, lpConnectionsEx, hSnapShot
    invoke CloseHandle, hSnapShot 
    invoke FreeLibrary, hDll    
	ret
GetNetStatEx endp

GetTCPConnectionsEx proc uses esi edi ebx ecx edx lpAllocateAndGetTcpExTableFromStack:FARPROC,\
			lpConnectionsEx:PTCPIPConnectionsExList, hSnapShot:HANDLE
	LOCAL pTcpTableEx: PMIB_TCPROW_TABLE_EX
	LOCAL tempbuff[32]: BYTE				
    LOCAL pTempBuff: DWORD
    LOCAL pBuff: DWORD
    LOCAL dwCount: DWORD 
    LOCAL dwOffset: DWORD            
	
	push AF_INET
	push 2		
	invoke GetProcessHeap
	push eax
	push TRUE
	lea eax, pTcpTableEx
	push eax
	call lpAllocateAndGetTcpExTableFromStack
  	mov edi, pTcpTableEx	  	  	
  	m2m dwCount, dword ptr [edi]	
  	add edi, 4  	  	  	   	
  	assume ebx:ptr TCPIPConnectionEx
  	assume edx:ptr TCPIPConnectionsExList  	
  	mov edx, lpConnectionsEx
  	push edx   	  	
  	mov ecx, [edx].dwCount			  		
  	mov eax, sizeof TCPIPConnectionEx  		  		 
  	mul ecx 
  	mov dwOffset, eax  	 	    		  					   	  	 
  	pop edx    
  	mov ecx, dwCount
  	add [edx].dwCount, ecx		  			  		
  	lea eax, [edx].pTCPIPConnectionsEx   	 	
  	invoke SetLength, eax, sizeof TCPIPConnectionEx, [edx].dwCount
  	mov edx, lpConnectionsEx
  	mov ebx, [edx].pTCPIPConnectionsEx
  	assume edx:nothing
  		
  	add ebx, dwOffset
  	mov pBuff, ebx	 	    
  	xor esi, esi  
  	.while esi < dwCount 
  		mov ebx, pBuff 		 		  	  		  			  		  		  		  			
  		mov [ebx].Protocol, offset szszTCP  		  	  					  			     	 
      	invoke inet_ntoa, (MIB_TCPROW_EX ptr [edi]).dwLocalAddr      	
      	mov pTempBuff, eax      	
      	invoke lstrlen, pTempBuff
      	inc eax
      	invoke GlobalAlloc, GPTR, eax      	      	      	
      	mov [ebx].LocalAddr, eax      	      	
      	invoke lstrcpy, [ebx].LocalAddr, pTempBuff
      	mov eax, (MIB_TCPROW_EX ptr [edi]).dwLocalPort 
      	and eax, 0000FFFFh   
      	invoke ntohs, eax  	    	      				      	    	     	 
        mov [ebx].LocalPort, eax                       
        mov eax, (MIB_TCPROW_EX ptr [edi]).dwRemoteAddr
        push eax        
		invoke inet_ntoa, eax
        mov pTempBuff, eax
      	invoke lstrlen, pTempBuff
      	inc eax
      	invoke GlobalAlloc, GPTR, eax
      	mov [ebx].RemoteAddr, eax      	
      	invoke lstrcpy, [ebx].RemoteAddr, pTempBuff
      	pop eax      	     	       	                
        .if eax      	      				
        	mov eax, (MIB_TCPROW_EX ptr [edi]).dwRemotePort
        	and eax, 0000FFFFh
      		invoke ntohs, eax      		
      	.endif	       		 
      	mov [ebx].RemotePort, eax                         		
        mov eax, (MIB_TCPROW_EX ptr [edi]).dwState
        .if eax > 12
	    	mov eax, 13
	    .endif
   		dec eax   		
        m2m [ebx].State, stateTable[eax * 4]	
        m2m [ebx].ProcessID, (MIB_TCPROW_EX ptr [edi]).dwProcessId 
        invoke GetProcessName, hSnapShot, [ebx].ProcessID         
        mov [ebx].ProcessName, eax	      	
		add edi, sizeof MIB_TCPROW_EX
		add pBuff, sizeof TCPIPConnectionEx
		inc	esi			
  	.endw  	     	  	
  	assume ebx:nothing  	
  	ret
GetTCPConnectionsEx endp

GetUDPConnectionsEx proc uses esi edi ebx ecx edx lpAllocateAndGetUdpExTableFromStack:FARPROC,\
			lpConnectionsEx:PTCPIPConnectionsExList, hSnapShot:HANDLE
	LOCAL pUdpTableEx: PMIB_UDPROW_TABLE_EX	
	LOCAL pTempBuff: DWORD	
    LOCAL pBuff: DWORD
    LOCAL dwCount: DWORD     
    LOCAL dwOffset: DWORD                  

	push AF_INET
	push 2		
	invoke GetProcessHeap
	push eax
	push TRUE
	lea eax, pUdpTableEx
	push eax
	call lpAllocateAndGetUdpExTableFromStack
  	mov edi, pUdpTableEx	  	  
  	m2m dwCount, dword ptr [edi]	  	
  	add edi, 4  	  	  	   	
  	assume ebx:ptr TCPIPConnectionEx
  	assume edx:ptr TCPIPConnectionsExList
  	mov edx, lpConnectionsEx
  	push edx   	  	
  	mov ecx, [edx].dwCount			  		
  	mov eax, sizeof TCPIPConnectionEx  		  		 
  	mul ecx 
  	mov dwOffset, eax  	 	    		  					   	  	 
  	pop edx    
  	mov ecx, dwCount
  	add [edx].dwCount, ecx		  			  		
  	lea eax, [edx].pTCPIPConnectionsEx   	 	
  	invoke SetLength, eax, sizeof TCPIPConnectionEx, [edx].dwCount
  	mov edx, lpConnectionsEx
  	mov ebx, [edx].pTCPIPConnectionsEx
  	assume edx:nothing
  		
  	add ebx, dwOffset
  	mov pBuff, ebx	 	    
  	xor esi, esi  
  	.while esi < dwCount 
  		mov ebx, pBuff 		 		  	  		  			  		  		  		  			
  		mov [ebx].Protocol, offset szszUDP    	  					  			     	 
      	invoke inet_ntoa, (MIB_UDPROW_EX ptr [edi]).dwLocalAddr      	
      	mov pTempBuff, eax
      	invoke lstrlen, pTempBuff
      	inc eax
      	invoke GlobalAlloc, GPTR, eax      	      	      	
      	mov [ebx].LocalAddr, eax      	      	      	
      	invoke lstrcpy, [ebx].LocalAddr, pTempBuff       	      		
      	mov eax, (MIB_UDPROW_EX ptr [edi]).dwLocalPort
      	and eax, 0000FFFFh    	      				      	      	      				
      	invoke ntohs, eax      		   	     	 
        mov [ebx].LocalPort, eax  
        m2m [ebx].ProcessID, (MIB_UDPROW_EX ptr [edi]).dwProcessId 
        invoke GetProcessName, hSnapShot, [ebx].ProcessID                  
        mov [ebx].ProcessName, eax                            	      	
		add edi, sizeof MIB_UDPROW_EX
		add pBuff, sizeof TCPIPConnectionEx
		inc	esi			
  	.endw
  	assume ebx:nothing		
	ret
GetUDPConnectionsEx endp

NetShell proc uses ebx ecx edx _socket:SOCKET, lpPassword:LPSTR
	LOCAL pShellBuff: HANDLE
	LOCAL dwBuffSize: DWORD
    LOCAL sat: SECURITY_ATTRIBUTES 
    LOCAL hiRead: DWORD
    LOCAL hoRead: DWORD
    LOCAL hiWrite: DWORD
    LOCAL hoWrite: DWORD
    LOCAL startupinfo: STARTUPINFO 
    LOCAL processinfo: PROCESS_INFORMATION 
    LOCAL exitcode: DWORD    
    LOCAL bytes: DWORD 
    LOCAL available: DWORD
    LOCAL data: DWORD    
	
	invoke SetTimeOut, _socket, 1
	 
    mov sat.nLength, sizeof SECURITY_ATTRIBUTES 
    mov sat.lpSecurityDescriptor, 0 
    mov sat.bInheritHandle, TRUE 
    invoke CreatePipe, addr hiRead, addr hiWrite, addr sat, 0 
    invoke CreatePipe, addr hoRead, addr hoWrite, addr sat, 0 
    invoke GetStartupInfo, addr startupinfo
    mov startupinfo.cb, sizeof STARTUPINFO 
    mov eax, hoWrite
    mov startupinfo.hStdOutput, eax
    mov startupinfo.hStdError, eax
    mov eax, hiRead
    mov startupinfo.hStdInput, eax
    mov startupinfo.dwFlags, STARTF_USESHOWWINDOW + STARTF_USESTDHANDLES 
    mov startupinfo.wShowWindow, SW_HIDE     
    invoke CreateProcess, 0, addr szCommandLine, 0, 0, TRUE, CREATE_NEW_CONSOLE, 0, 0,\
    					addr startupinfo, addr processinfo    
    invoke CloseHandle, hoWrite
    invoke CloseHandle, hiRead
    
    mov bytes, 1 
    mov dwBuffSize, 65535
    invoke GlobalAlloc, GPTR, dwBuffSize 
    mov pShellBuff, eax
          
    .while TRUE
     	invoke Sleep, 1
     	invoke GetExitCodeProcess, processinfo.hProcess, addr exitcode
     	.if exitcode != STILL_ACTIVE
       		.break
     	.endif
     	     	
      	invoke PeekNamedPipe, hoRead, pShellBuff, dwBuffSize, addr bytes, addr available, 0
      	.if bytes
        	.if available > 65535
          		.while bytes >= 65535
            		invoke Sleep, 1
            		invoke ReadFile, hoRead, pShellBuff, dwBuffSize, addr bytes, 0
            		.if bytes
            			invoke HashCrypt, lpPassword, pShellBuff, bytes, 1																										
						invoke SendExact, _socket, pShellBuff, bytes
					.endif
          		.endw 
          		 
       		.else
       			invoke Sleep, 1
        		invoke ReadFile, hoRead, pShellBuff, dwBuffSize, addr bytes, 0
          		.if bytes
          			invoke HashCrypt, lpPassword, pShellBuff, bytes, 1										
					invoke SendExact, _socket, pShellBuff, bytes								
          		.endif
        	.endif    
      	.endif
      	  
      	invoke memset, pShellBuff, 0, dwBuffSize
      	invoke recv, _socket, pShellBuff, dwBuffSize, 0
		.if eax == SOCKET_ERROR || eax == 0
			invoke WSAGetLastError
			.if eax != WSAETIMEDOUT
				invoke TerminateProcess, processinfo.hProcess, 0
          		.break
          	.else	
		    	.continue
		    .endif
		    	  
      	.else            
      		mov ebx, eax
      		invoke HashCrypt, lpPassword, pShellBuff, ebx, 2        
        	invoke WriteFile, hiWrite, pShellBuff, ebx, addr bytes, 0
      	.endif
    .endw
    
    invoke CloseHandle, hiWrite 
    invoke CloseHandle, hoRead
    invoke GlobalFree, pShellBuff
    invoke SetTimeOut, _socket, 0
    ret 
NetShell endp 

UploadFile proc uses ecx edx _socket:SOCKET, lpszFilePath:LPCSTR
	LOCAL hFile: HANDLE
	LOCAL pSendBuff: LPVOID
    LOCAL dwByteCount: DWORD
	LOCAL dwFileSize: DWORD	
    LOCAL BytesCount: DWORD
     
    invoke GlobalAlloc, GPTR, 65535
	mov pSendBuff, eax
				
	invoke CreateFile, lpszFilePath, GENERIC_READ, 0, 0, OPEN_EXISTING,\
					 FILE_ATTRIBUTE_NORMAL, 0                     
	.if eax == INVALID_HANDLE_VALUE
		invoke CloseHandle, eax		        
	.else                 					
		mov hFile, eax	
		invoke GetFileSize, hFile, 0
		mov dwFileSize, eax         
		      			        			                						     						
@@SendNextBlock:												
		.if dwFileSize > 65535					  								         		                            						   		                		                		 
			invoke ReadFile, hFile, pSendBuff, 65535, addr dwByteCount, 0
		.else								
			invoke ReadFile, hFile, pSendBuff, dwFileSize, addr dwByteCount, 0
		.endif																        				
		
		invoke SendExact, _socket, pSendBuff, dwByteCount
		.if eax 							        											
			.if dwFileSize > 65535
				mov eax, dwByteCount								
				sub dwFileSize, eax
				jmp @@SendNextBlock
			.endif
		.endif
		
		invoke GlobalFree, pSendBuff  		               	                			                		                		
		invoke CloseHandle, hFile			
	.endif  	  	
	ret
UploadFile endp

DownloadURL proc uses ecx edx lpszURL:DWORD, lpBuff:DWORD, dwNumberOfBytesToRead:DWORD 
    LOCAL hInternet: DWORD 
    LOCAL hURL: DWORD 
    LOCAL hUrlFile: DWORD 
    LOCAL BufferLen: DWORD 
    LOCAL BytesWrite: DWORD
    invoke InternetOpen, addr lpszAgent, INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, 0 
    mov hInternet, eax 
    invoke InternetOpenUrl, hInternet, lpszURL, 0, 0, 0, 0 
    mov hURL, eax 
    invoke InternetReadFile, hURL, lpBuff, dwNumberOfBytesToRead, addr BufferLen 
    invoke CloseHandle, hUrlFile 
    invoke InternetCloseHandle, hURL 
    cmp eax, 0 
    jz @@Failed 
    invoke InternetCloseHandle, hInternet 
    mov eax, 1
    ret    
@@Failed: 
    xor eax, eax 
    ret    
DownloadURL endp 

FindRealIP proc uses esi edi lpIPAddr:LPCSTR
	LOCAL htmlBuffer[256]: BYTE
	invoke DownloadURL, addr URLCheckIP, addr htmlBuffer, sizeof htmlBuffer     
	lea esi, htmlBuffer   
@@: 
	cmp byte ptr [esi], 0 
	je @@Error            
	cmp byte ptr [esi], ':' 
	je @f 
	inc esi      
	jmp @b            
@@: 
	inc esi 
	inc esi   
	mov edi, lpIPAddr 
@@: 
	lodsb 
	cmp al, 0 
	je @@NoMore 
	cmp al, '<' 
	je @@NoMore 
	stosb     
	jmp @b 
@@Error: 
	mov eax, -1 
	ret 
@@NoMore: 
	inc edi 
	mov byte ptr [edi], 0
	mov eax, 0 
	ret 
FindRealIP endp 

LookupAddress proc uses ecx edx lpszBuff:DWORD
    invoke gethostbyname, lpszBuff
    .if eax
        mov eax, (hostent ptr [eax]).h_list
        mov eax, [eax]           
        mov eax, [eax]
        invoke inet_ntoa, eax            
    .endif        
    ret
LookupAddress endp

LookupName proc uses ecx edx lpszBuff:DWORD
    LOCAL IP: DWORD        
    invoke inet_addr, lpszBuff
    .if eax != INADDR_NONE
        mov IP, eax
        invoke gethostbyaddr, addr IP, 4, AF_INET 
        .if eax               
        	mov eax, [eax]
        .endif	
    .else
    	xor eax, eax        
    .endif
    ret
LookupName endp 

CheckSum PROC uses ecx edx lpBuffer:DWORD, dwSize:DWORD 
    LOCAL dwCheksum: DWORD     
    mov dwCheksum, 0 
@@: 
    cmp dwSize, 1 
    jle @F 
    mov eax, lpBuffer 
    xor ecx, ecx 
    mov cx, [eax] 
    mov edx, dwCheksum 
    add edx, ecx 
    mov dwCheksum, edx 
    mov eax, lpBuffer 
    add eax, 2 
    mov lpBuffer, eax 
    mov ecx, dwSize 
    sub ecx, 2 
    mov dwSize, ecx 
    jmp @B 
@@: 
    cmp dwSize, 0 
    jz @F 
    mov edx, lpBuffer 
    xor eax, eax 
    mov al, [edx] 
    mov ecx, dwCheksum 
    add ecx, eax 
    mov dwCheksum, ecx 
@@: 
    mov edx, dwCheksum 
    shr edx, 10h 
    mov eax, dwCheksum 
    and eax, 0FFFFh 
    add edx, eax 
    mov dwCheksum, edx 
    mov ecx, dwCheksum 
    shr ecx, 10h 
    mov edx, dwCheksum 
    add edx, ecx 
    mov dwCheksum, edx 
    mov eax, dwCheksum 
    not eax 
    ret 
CheckSum ENDP 

FillICMPData proc uses esi edi ebx ecx edx lpICMPData:dword, dwDataSize:dword
	assume ebx:ptr ICMP 
    mov ebx, lpICMPData 
    mov [ebx].i_type, ICMP_ECHO_REQUEST 
    mov [ebx].i_code, 0 
    mov [ebx].i_cksum, 0 
    invoke GetCurrentProcessId 
    push eax
    mov [ebx].i_id, ax 
    mov [ebx].i_seq, 1 
    invoke GetTickCount 
    mov [ebx].timestamp, eax 
    add ebx, sizeof ICMP 
    mov eax, dwDataSize 
    sub eax, sizeof ICMP 
    invoke memset, ebx, 'E', eax 
    invoke CheckSum, lpICMPData, dwDataSize 
    sub ebx, sizeof ICMP 
    mov [ebx].i_cksum, ax
    assume ebx:nothing 
    pop eax
    ret     
FillICMPData endp 

Ping proc uses ebx ecx edx lpszBuff:LPCSTR, lpPingInfo:PPingInfo, dwTimeOut:DWORD
	LOCAL _socket: SOCKET
	LOCAL saddr: sockaddr_in
	LOCAL pPacket: DWORD
			                           
    invoke GetIPAddr, lpszBuff  
    .if eax 
    	mov saddr.sin_addr, eax
    	mov saddr.sin_family, AF_INET 
        mov ebx, 32
        add ebx, sizeof ICMP 
        invoke GlobalAlloc, GPTR, ebx 
        mov pPacket, eax             
        invoke FillICMPData, pPacket, ebx
        mov edx, lpPingInfo
        mov (PingInfo ptr [edx]).wID, ax    
    	invoke socket, AF_INET, SOCK_RAW, IPPROTO_ICMP
    	.if eax != -1 
        	mov _socket, eax         	 
    	.else
    		jmp @@Error
    	.endif
    	invoke SetTimeOut, _socket, dwTimeOut                          
        invoke sendto, _socket, pPacket, ebx, 0, addr saddr, sizeof saddr 
        push eax 
        invoke GlobalFree, pPacket 
        pop eax 
        .if eax == SOCKET_ERROR             
            invoke closesocket, _socket 
            jmp @@Error
        .endif 
    .else          		
		jmp @@Error
    .endif
    mov eax, _socket
    ret
@@Error:
	xor eax, eax     
	ret
Ping endp

DecodePingResponse proc uses esi edi ebx ecx edx lpRecvData:DWORD, lpRecvAddr:DWORD, lpPingInfo:DWORD
	assume ebx:ptr PingInfo  	
	mov ebx, lpPingInfo       
    mov edi, lpRecvAddr 
    mov esi, lpRecvData 
    invoke inet_ntoa, dword ptr (sockaddr_in ptr [edi]).sin_addr 
    mov [ebx].pAddress, eax 
    mov al, (ip_hdr ptr [esi]).ip_ttl
    mov [ebx].bTTL, al
    mov ax, (ip_hdr ptr [esi]).ip_len
    xor eax, eax 
    invoke htons, eax 
    movzx eax, ax 
    mov [ebx].dwSizeRet, eax 
    mov al, (ip_hdr ptr [esi]).ip_hlv 
    and al, 0Fh 
    movzx eax, al 
    lea ecx, [eax * 4] 
    add esi, ecx  
    assume esi:ptr ICMP   
    .if byte ptr [esi].i_type == ICMP_ECHOREPLY 
        mov ax, [ebx].wID 
        .if word ptr [esi].i_id == ax 
            invoke GetTickCount 
            xor ecx, ecx
            mov ecx, [esi].timestamp
            sub eax, ecx 
            mov [ebx].dwRetTime, eax                             
        .endif         
    .endif 
    assume esi:nothing
    assume ebx:nothing  	
    ret 
DecodePingResponse endp

ScanPort proc uses esi ebx ecx edx lpScanPortInfo:PScanPortInfo
	LOCAL DestAddr: DWORD
	LOCAL dwStopPort: DWORD
	LOCAL hWnd: HANDLE  
	LOCAL wmInform: UINT
    LOCAL TCPSock: SOCKET 
	LOCAL CreateSock: DWORD  
    LOCAL saddr: sockaddr_in    
    assume ebx:ptr ScanPortInfo   
    mov ebx, lpScanPortInfo    
    .if [ebx].DestAddr	
    	m2m DestAddr, [ebx].DestAddr
    	mov esi, [ebx].dwStartPort
    	m2m dwStopPort, [ebx].dwStopPort
    	m2m hWnd, [ebx].hWnd    
    	m2m wmInform, [ebx].wmInform	    	    			    		   
	    mov CreateSock, 1   				    	                    
		.while esi <= dwStopPort        	           
	    	.if CreateSock == 1
	        	invoke socket, PF_INET, SOCK_STREAM, 0
	            mov TCPSock, eax
	            .if TCPSock < 0	            	
	                ret    
	            .endif
	            mov CreateSock, 0
	        .endif                            
	        invoke htons, esi                                                                            
	        mov saddr.sin_port, ax   
	        mov saddr.sin_family, AF_INET
	        mov eax, DestAddr 
	        mov saddr.sin_addr, eax	
	        invoke connect, TCPSock, addr saddr, sizeof saddr
	        .if eax == 0
	        	invoke SendMessage, hWnd, wmInform, esi, TRUE	        	
	            invoke closesocket, TCPSock
	            mov CreateSock, 1
	        .else
	        	invoke SendMessage, hWnd, wmInform, esi, FALSE    
	        .endif
	        inc esi	                    
	    .endw 
	    invoke SendMessage, hWnd, wmInform, 65536, 0 
	.endif 
	assume ebx:nothing     
	ret
ScanPort endp

WakeOnLan proc uses ebx ecx edx lpMacAddress:LPCSTR
	LOCAL optval: BYTE 
	LOCAL saddr: sockaddr_in
	LOCAL _socket: SOCKET
	LOCAL sendbuff[102]: BYTE	
	LOCAL pBuff: LPVOID
	LOCAL pMac: LPVOID
	
	mov optval, 1
	invoke socket, AF_INET, SOCK_DGRAM, IPPROTO_UDP
	mov _socket, eax	
	invoke setsockopt, _socket, SOL_SOCKET, SO_BROADCAST, addr optval, sizeof optval

	mov saddr.sin_family, AF_INET	      	        	  	
	invoke htons, 0	
	mov saddr.sin_port, ax	
	mov saddr.sin_addr.S_un.S_addr, INADDR_BROADCAST
	
	invoke ReversHexStr, addr szWakeOnLanPrefix, 12
	mov ebx, eax     		
    invoke memcpy, ebx, addr sendbuff, 6
    invoke GlobalFree, ebx
    invoke ReversHexStr, lpMacAddress, 12
    mov pMac, eax
    lea eax, sendbuff
    mov pBuff, eax
 	mov ebx, 16
 	.while ebx != 0
 		add pBuff, 6
 		invoke memcpy, pMac, pBuff, 6	     		
 		dec ebx
 	.endw
 	invoke GlobalFree, pMac	     	     
    invoke sendto, _socket, addr sendbuff, 102, 0, addr saddr, sizeof saddr
    invoke closesocket, _socket	      	
	ret
WakeOnLan endp

AddRemoveNetworkResource proc uses ecx edx lpszRemoteMachine:LPCSTR, lpszResource:LPCSTR, lpszUserName:LPCSTR,
		lpszPassword:LPCSTR, bEstablish:BOOL
	LOCAL szRemoteResource[MAX_PATH]: BYTE
	LOCAL nr: NETRESOURCE
	LOCAL dwResult: DWORD
	
	invoke wsprintf, addr szRemoteResource, StrM("\\%s\%s"), lpszRemoteMachine, lpszResource
	.if bEstablish 
		mov nr.dwType, RESOURCETYPE_ANY
		mov nr.lpLocalName, NULL
		lea eax, szRemoteResource
		mov nr.lpRemoteName, eax
		mov nr.lpProvider, NULL
		
		invoke WNetAddConnection2, addr nr, lpszPassword, lpszUserName, CONNECT_UPDATE_PROFILE
   		mov dwResult, eax
      	.if (eax != NO_ERROR)
      		invoke ShowErrorMessage, NULL	
		.endif    
  
	.else
		invoke WNetCancelConnection2, addr szRemoteResource, 0, NULL
		mov dwResult, eax
	.endif	
   
	.if dwResult == NO_ERROR
   		mov eax, TRUE
   	.else
   		mov eax, FALSE
   	.endif	  
	ret
AddRemoveNetworkResource endp

ShowNetErrorMessage proc uses ebx ecx edx hDlg:HANDLE
	LOCAL pErrorMessage: DWORD
    invoke WSAGetLastError	
	push eax	
	pop ebx
	invoke FormatMessage, FORMAT_MESSAGE_ALLOCATE_BUFFER or FORMAT_MESSAGE_FROM_SYSTEM, NULL, ebx,\
					0, addr pErrorMessage, 0, 0
	invoke MessageBox, hDlg, pErrorMessage, NULL, MB_OK
	invoke LocalFree, pErrorMessage 
    ret
ShowNetErrorMessage endp

LogNetErrorMessage proc uses ebx ecx edx lpszAppName:LPCSTR, lpszMessage:LPCSTR
	LOCAL tempbuff[512]: BYTE 
	LOCAL pErrorMessage: DWORD
	LOCAL Strings[2]: DWORD
	LOCAL hEventSrc: HANDLE
	pushad
	invoke WSAGetLastError
	mov ebx, eax	
	invoke wsprintf, addr tempbuff, StrM("%s error: %d"), lpszAppName, ebx		
	invoke FormatMessage, FORMAT_MESSAGE_ALLOCATE_BUFFER or FORMAT_MESSAGE_FROM_SYSTEM, NULL, ebx,\
					0, addr pErrorMessage, 0, 0
	invoke lstrcat, addr tempbuff, pErrorMessage
	invoke LocalFree, pErrorMessage	
	invoke RegisterEventSource, NULL, lpszAppName 
	.if eax	
		mov hEventSrc, eax
		lea ebx, Strings  
		lea eax, tempbuff
		mov (dword ptr [ebx]), eax
		add ebx, sizeof DWORD
		m2m (dword ptr [ebx]), lpszMessage
		invoke ReportEvent, hEventSrc, EVENTLOG_ERROR_TYPE, 0, 0, NULL, 2, 0, addr Strings, NULL
		invoke DeregisterEventSource, hEventSrc 
	.endif
	popad	  	
	ret
LogNetErrorMessage endp
