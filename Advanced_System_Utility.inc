;----------------------------------------------------------------------------------------
; MASM32 Andvanced System Library
;
; Copyright 2007 Veria Kalantary
; veria.kalantary@gmail.com
; https://github.com/veriak
;
;----------------------------------------------------------------------------------------

include \masm32\include\shlwapi.inc
includelib \masm32\lib\shlwapi.lib

enum SID_NAME_USE, 1, SidTypeUser, SidTypeGroup, SidTypeDomain, SidTypeAlias, SidTypeWellKnownGroup,\
				SidTypeDeletedAccount, SidTypeInvalid, SidTypeUnknown
    
PTOKEN_GROUPS						typedef ptr TOKEN_GROUPS
PACCESS_ALLOWED_ACE					typedef ptr ACCESS_ALLOWED_ACE
PSECURITY_DESCRIPTOR				typedef ptr SECURITY_DESCRIPTOR
SECURITY_INFORMATION  				typedef DWORD
PSECURITY_INFORMATION 				typedef ptr SECURITY_INFORMATION
PACL								typedef	ptr	ACL
PSID								typedef	ptr	SID
PSID_NAME_USE						typedef	ptr	SID_NAME_USE
PTOKEN_PRIVILEGES					typedef ptr TOKEN_PRIVILEGES

PHICON								typedef ptr HICON	 

_VersionInfo struct
    dwOSVersionInfoSize 			dd	?
    dwMajorVersion 					dd	?   
    dwMinorVersion 					dd	?
    dwBuildNumber 					dd	?
    dwPlatformId 					dd	?
    szCSDVersion 					db 128 dup(?)  
_VersionInfo ends

GETVERSIONOUTPARAMS struct
   bVersion							db	?
   bRevision						db	?
   bReserved						db	?
   bIDEDeviceMap					db	?
   dwCapabilities					dd	?
   dwReserved						dd	4 dup (?)
GETVERSIONOUTPARAMS ends
   
TIDERegs struct 
  bFeaturesReg     					db	? 
  bSectorCountReg 					db	?
  bSectorNumberReg 					db	?
  bCylLowReg       					db	?
  bCylHighReg      					db	?
  bDriveHeadReg    					db	?
  bCommandReg     					db	?
  bReserved       					db	?
TIDERegs ends 
  
TSendCmdInParams struct     
  dwBufferSize  					dd	?  
  IRDriveRegs  						TIDERegs <?> 
  bDriveNumber 						db		? 
  bReserved    						db 	4 	dup (?) 
  dwReserved   						dd 	4 	dup (?) 
  bBuffer      						db 	1 	dup (?) 
TSendCmdInParams ends
  
TIdSector struct 
  wGenConfig						dw	?	  	            
  wNumCyls        					dw 	?	
  wReserved       					dw 	?	
  wNumHeads       					dw 	?
  wBytesPerTrack  					dw 	?
  wBytesPerSector            		dw	?
  wSectorsPerTrack           		dw 	?
  wVendorUnique              		dw 	3 dup (?) 
  sSerialNumber              		db 	20 dup (?) 
  wBufferType                		dw	? 
  wBufferSize                		dw 	?
  wECCSize                   		dw 	?
  sFirmwareRev               		db 	8 dup (?) 
  sModelNumber               		db 	40 dup (?) 
  wMoreVendorUnique          		dw 	?
  wDoubleWordIO              		dw 	?
  wCapabilities              		dw 	?
  wReserved1                 		dw 	?
  wPIOTiming                 		dw 	?
  wDMATiming                 		dw 	?
  wBS                        		dw 	?
  wNumCurrentCyls            		dw 	?
  wNumCurrentHeads           		dw 	?
  wNumCurrentSectorsPerTrack 		dw 	?
  ulCurrentSectorCapacity    		dd 	?
  wMultSectorStuff           		dw 	?
  ulTotalAddressableSectors  		dd 	?
  wSingleWordDMA             		dw 	?
  wMultiWordDMA              		dw 	?
  bReserved                  		db 	128 dup (?) 
TIdSector ends
     
TDriverStatus struct 
  bDriverError 						db	? 
  bIDEStatus   						db	? 
  bReserved    						db 	2	dup	(?) 
  dwReserved   						dd	2	dup	(?) 
TDriverStatus ends
   
TSendCmdOutParams struct 
  dwBufferSize  					dd	? 
  DriverStatus 						TDriverStatus	<> 
  bBuffer      						db	1	dup	(?) 
TSendCmdOutParams ends 

ServiceInfo struct
	pServiceName					LPSTR	?
	pDisplayName					LPSTR	?	
	bRunningState					BOOL	?						
ServiceInfo ends
PServiceInfo						typedef ptr ServiceInfo
PServicesInfo						typedef DWORD

ServicesInfoList struct
	dwServiceCount					dd	?
	pServicesInfo					PServicesInfo	?			
ServicesInfoList ends
PServicesInfoList					typedef ptr ServicesInfoList

enum SECURITY_IMPERSONATION_LEVEL, 1, SecurityAnonymous, SecurityIdentification,\
				SecurityImpersonation, SecurityDelegation

SetPrivilege 						PROTO	:LPCSTR, :BOOLEAN 
ShutDown 							PROTO
Reboot 								PROTO
Force 								PROTO
PowerOff 							PROTO
IsServiceInstalled					PROTO	:LPCSTR, :LPCSTR
_StartService						PROTO	:LPCSTR, :LPCSTR
StopService							PROTO	:LPCSTR, :LPCSTR
InstallProcessAsAService			PROTO	:LPCSTR, :LPCSTR, :LPCSTR, :DWORD
UnInstallProcessAsAService			PROTO	:LPCSTR, :LPCSTR, :DWORD
RunProcessAsAService				PROTO	:DWORD, :LPCSTR, :DWORD, :DWORD
GetHardDriveSerialNumber 			PROTO 	:LPCSTR
GetAssociatedIcon					PROTO	:DWORD, :PHICON, :PHICON
;GetLogonSID 						PROTO	:HANDLE, :DWORD
;FreeLogonSID						PROTO	:DWORD
;AddAceToWindowStation				PROTO	:HWINSTA, :DWORD
;AddAceToDesktop						PROTO	:HDESK, :DWORD
ImpersonateCurrentUser				PROTO
SwitchToLocalSystemAccount			PROTO
GetCurrentUserName 					PROTO	:LPSTR, :DWORD
GetUserSID							PROTO	:LPCSTR
GetCurrentUserSID					PROTO
LoadUserRegistryHive				PROTO	:LPCSTR	
UnloadUserRegistryHive				PROTO	:LPCSTR

.const
	RSP_SIMPLE_SERVICE				equ	1
	DFP_GET_VERSION        			equ 00074080h
	DFP_SEND_DRIVE_COMMAND 			equ 0007C084h
	DFP_RECEIVE_DRIVE_DATA 			equ 0007C088h	
	CAP_IDE_ID_FUNCTION    			equ 1  
	CAP_IDE_ATAPI_ID       			equ 2 
	CAP_IDE_EXECUTE_SMART_FUNCTION  equ	4  	
	IDENTIFY_BUFFER_SIZE 			equ	512
	
	DESKTOP_ALL 					equ DESKTOP_READOBJECTS or DESKTOP_CREATEWINDOW or DESKTOP_CREATEMENU or\
										DESKTOP_HOOKCONTROL or	DESKTOP_JOURNALRECORD or DESKTOP_JOURNALPLAYBACK or\
										DESKTOP_ENUMERATE or DESKTOP_WRITEOBJECTS or DESKTOP_SWITCHDESKTOP or\
										STANDARD_RIGHTS_REQUIRED
	WINSTA_ALL 						equ	WINSTA_ENUMDESKTOPS or WINSTA_READATTRIBUTES or	WINSTA_ACCESSCLIPBOARD or\
										WINSTA_CREATEDESKTOP or WINSTA_WRITEATTRIBUTES or WINSTA_ACCESSGLOBALATOMS or\
										WINSTA_EXITWINDOWS or WINSTA_ENUMERATE or WINSTA_READSCREEN or\
										STANDARD_RIGHTS_REQUIRED
	GENERIC_ACCESS 					equ	GENERIC_READ or GENERIC_WRITE or GENERIC_EXECUTE or GENERIC_ALL
	
	NOTIFY_FOR_ALL_SESSIONS			equ	1
	NOTIFY_FOR_THIS_SESSION			equ	0
	WM_WTSSESSION_CHANGE			equ	02B1h
	WTS_CONSOLE_CONNECT				equ	1h
	WTS_CONSOLE_DISCONNECT			equ	2h
	WTS_REMOTE_CONNECT				equ	3h
	WTS_REMOTE_DISCONNECT			equ	4h
	WTS_SESSION_LOGON				equ	5h
	WTS_SESSION_LOGOFF				equ	6h
	WTS_SESSION_LOCK				equ	7h
	WTS_SESSION_UNLOCK				equ	8h
	WTS_SESSION_REMOTE_CONTROL		equ	9h
	
	SERVICE_CONTROL_DEVICEEVENT		equ	11
	SERVICE_CONTROL_HARDWAREPROFILECHANGE	equ	12
	SERVICE_CONTROL_POWEREVENT		equ	13
	SERVICE_CONTROL_SESSIONCHANGE	equ	14
	
	SERVICE_ACCEPT_HARDWAREPROFILECHANGE	equ	32
	SERVICE_ACCEPT_POWEREVENT		equ	64
	SERVICE_ACCEPT_SESSIONCHANGE	equ	128


.data
	szKernel32dll					db 	"kernel32.dll", 0
	szCOM							db	".COM", 0
	szSystem		 				db 	"\system\", 0
	szSystem32 						db 	"\system32\", 0
	szRegisterServiceProcess		db  "RegisterServiceProcess", 0
	
	sz_SE_ASSIGNPRIMARYTOKEN_NAME 	db	"SeAssignPrimaryTokenPrivilege", 0
	sz_SE_LOCK_MEMORY_NAME 			db	"SeLockMemoryPrivilege", 0
	sz_SE_INCREASE_QUOTA_NAME		db	"SeIncreaseQuotaPrivilege", 0
	sz_SE_UNSOLICITED_INPUT_NAME	db	"SeUnsolicitedInputPrivilege", 0
	sz_SE_MACHINE_ACCOUNT_NAME		db	"SeMachineAccountPrivilege", 0
	sz_SE_TCB_NAME					db	"SeTcbPrivilege", 0
	sz_SE_SECURITY_NAME				db	"SeSecurityPrivilege", 0
	sz_SE_TAKE_OWNERSHIP_NAME		db	"SeTakeOwnershipPrivilege", 0
	sz_SE_LOAD_DRIVER_NAME			db	"SeLoadDriverPrivilege", 0
	sz_SE_SYSTEM_PROFILE_NAME		db	"SeSystemProfilePrivilege", 0
	sz_SE_SYSTEMTIME_NAME			db	"SeSystemtimePrivilege", 0
	sz_SE_PROF_SINGLE_PROCESS_NAME	db	"SeProfileSingleProcessPrivilege", 0
	sz_SE_INC_BASE_PRIORITY_NAME	db	"SeIncreaseBasePriorityPrivilege", 0
	sz_SE_CREATE_PAGEFILE_NAME		db	"SeCreatePagefilePrivilege", 0
	sz_SE_CREATE_PERMANENT_NAME		db	"SeCreatePermanentPrivilege", 0
	sz_SE_BACKUP_NAME				db	"SeBackupPrivilege", 0
	sz_SE_RESTORE_NAME				db	"SeRestorePrivilege", 0
	sz_SE_SHUTDOWN_NAME				db	"SeShutdownPrivilege", 0
	sz_SE_DEBUG_NAME				db	"SeDebugPrivilege", 0
	sz_SE_AUDIT_NAME				db	"SeAuditPrivilege", 0
	sz_SE_SYSTEM_ENVIRONMENT_NAME	db	"SeSystemEnvironmentPrivilege", 0
	sz_SE_CHANGE_NOTIFY_NAME		db	"SeChangeNotifyPrivilege", 0
	sz_SE_REMOTE_SHUTDOWN_NAME 		db	"SeRemoteShutdownPrivilege", 0
	
.code

SetPrivilege proc uses ecx edx lpszPrivilegeName:LPCSTR, bEnabled:BOOLEAN		
	LOCAL hProcess: HANDLE
	LOCAL hToken: HANDLE
	LOCAL tp: TOKEN_PRIVILEGES
	LOCAL dwResult: DWORD
	mov dwResult, 0
	invoke GetCurrentProcess
	mov hProcess, eax
	invoke OpenProcessToken, hProcess, TOKEN_ADJUST_PRIVILEGES or TOKEN_QUERY, addr hToken
	.if eax
		invoke LookupPrivilegeValue, NULL, lpszPrivilegeName, addr tp.Privileges[0].Luid
		.if eax
			mov tp.PrivilegeCount, 1			
			.if bEnabled
				mov tp.Privileges[0].Attributes, SE_PRIVILEGE_ENABLED
			.else
				mov tp.Privileges[0].Attributes, 0
			.endif		
			invoke AdjustTokenPrivileges, hToken, FALSE, addr tp, 0, NULL, NULL
			.if eax
				mov dwResult, 1
			.endif 
		.endif
		invoke CloseHandle, hToken
	.endif	 
	invoke CloseHandle, hProcess
	mov eax, dwResult
	ret
SetPrivilege endp

LogOff proc	uses ecx edx
	invoke ExitWindowsEx, EWX_LOGOFF, 0
	ret
LogOff endp

Force proc uses ecx edx 
	invoke SetPrivilege, addr sz_SE_SHUTDOWN_NAME, TRUE                  
    invoke ExitWindowsEx, EWX_FORCE, 0    
    ret
Force endp

PowerOff proc uses ecx edx  
	invoke SetPrivilege, addr sz_SE_SHUTDOWN_NAME, TRUE                  
    invoke ExitWindowsEx, EWX_POWEROFF, 0    
    ret    
PowerOff endp    

Reboot proc uses ecx edx
	invoke SetPrivilege, addr sz_SE_SHUTDOWN_NAME, TRUE                  
    invoke ExitWindowsEx, EWX_REBOOT, 0    
    ret
Reboot endp          
          
ShutDown proc uses ecx edx
	invoke SetPrivilege, addr sz_SE_SHUTDOWN_NAME, TRUE                  
    invoke ExitWindowsEx, EWX_SHUTDOWN, 0                      
    ret
ShutDown endp

GetServiceList proc uses esi edi ebx ecx edx lpServicesInfoList:PServicesInfoList
	LOCAL hSCManager: HANDLE
	LOCAL hService: HANDLE
	LOCAL pServices: LPVOID
    LOCAL dwServicesReturned: DWORD
    LOCAL BytesNeeded: DWORD
    LOCAL ResumeHandle: DWORD
    LOCAL dwBytes: DWORD         
	LOCAL RetCode: BOOL		
    LOCAL pBuff: DWORD
    LOCAL pTemp: DWORD
    
    mov RetCode, FALSE	
	invoke OpenSCManager, NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE				
	mov hSCManager, eax
	.if eax		
		mov ResumeHandle, 0
		invoke EnumServicesStatus, hSCManager, SERVICE_WIN32, SERVICE_STATE_ALL, NULL, 0,\
					addr BytesNeeded, addr dwServicesReturned, addr ResumeHandle		
       	m2m dwBytes, BytesNeeded  
		invoke GlobalAlloc, GPTR, dwBytes
		mov pServices, eax			
		invoke EnumServicesStatus, hSCManager, SERVICE_WIN32, SERVICE_STATE_ALL,\
				pServices, dwBytes,	addr BytesNeeded, addr dwServicesReturned, addr ResumeHandle		
				
		assume ebx:ptr ServiceInfo
		assume edx:ptr ServicesInfoList
		mov edx, lpServicesInfoList  	
		m2m [edx].dwServiceCount, dwServicesReturned		  			  		
		lea eax, [edx].pServicesInfo
		invoke SetLength, eax, sizeof ServiceInfo, [edx].dwServiceCount
		mov ebx, [edx].pServicesInfo	  	
		mov pBuff, ebx
		assume edx:nothing		
		mov edi, pServices   	 	
		
		xor esi, esi
		.while esi < dwServicesReturned                                
			mov ebx, pBuff
			m2m pTemp, (ENUM_SERVICE_STATUS ptr [edi]).lpServiceName 
			invoke lstrlen, pTemp
			inc eax
      		invoke GlobalAlloc, GPTR, eax      	      	      	
      		mov [ebx].pServiceName, eax      	      	      	
      		invoke lstrcpy, [ebx].pServiceName, pTemp
			m2m pTemp, (ENUM_SERVICE_STATUS ptr [edi]).lpDisplayName
			invoke lstrlen, pTemp
			inc eax
      		invoke GlobalAlloc, GPTR, eax      	      	      	
      		mov [ebx].pDisplayName, eax      	      	      	
      		invoke lstrcpy, [ebx].pDisplayName, pTemp
      		mov eax, (ENUM_SERVICE_STATUS ptr [edi]).ServiceStatus.dwCurrentState 		 		  	  		  			  		  		  		  			
 		 	.if eax == SERVICE_RUNNING
 		 		mov [ebx].bRunningState, TRUE
 		 	.else
 		 		mov [ebx].bRunningState, FALSE
 		 	.endif
 		 			  	  		  			  		  		  		  			
			add edi, sizeof ENUM_SERVICE_STATUS
			add pBuff, sizeof ServiceInfo
			inc	esi			
		.endw  	    	  			
  		assume ebx:nothing
  		
  		invoke GlobalFree, pServices
  		invoke CloseServiceHandle, hSCManager
  	.endif  									
	mov eax, RetCode			
  	ret
GetServiceList endp				

IsServiceInstalled proc uses ecx edx lpszMachineName:LPCSTR, lpszServiceName:LPCSTR
	LOCAL hSCManager: HANDLE
	LOCAL RetCode: BOOL
	
	mov RetCode, FALSE	
	invoke OpenSCManager, lpszMachineName, NULL, SC_MANAGER_CONNECT				
	mov hSCManager, eax
	.if eax			
		invoke OpenService, hSCManager, lpszServiceName, SERVICE_QUERY_STATUS
		.if eax			
			invoke CloseServiceHandle, eax
			mov RetCode, TRUE
		.endif				 												 
		invoke CloseServiceHandle, hSCManager				
	.endif				
	mov eax, RetCode
	ret
IsServiceInstalled endp

_StartService proc uses ecx edx lpszMachineName:LPCSTR, lpszServiceDisplayName:LPCSTR
	LOCAL hSCManager: HANDLE
	LOCAL szServiceName[MAX_PATH]: BYTE
	LOCAL temp: DWORD
	LOCAL hService: HANDLE
	LOCAL _ss: SERVICE_STATUS
	LOCAL dwCheckPoint: DWORD
	LOCAL dwStartTickCount: DWORD
		
	invoke OpenSCManager, lpszMachineName, NULL, SC_MANAGER_CONNECT				
	mov hSCManager, eax	
	.if eax
		mov temp, sizeof szServiceName
		invoke GetServiceKeyName, hSCManager, lpszServiceDisplayName, addr szServiceName, addr temp
		.if eax 			
			invoke OpenService, hSCManager, addr szServiceName, SERVICE_START or SERVICE_QUERY_STATUS
			mov hService, eax
			.if eax				
				invoke QueryServiceStatus, hService, addr _ss
        		.if eax        			
					.if _ss.dwCurrentState != SERVICE_RUNNING        		
						invoke StartService, hService, 0, NULL
						.if eax	 
				    		invoke QueryServiceStatus, hService, addr _ss
				    		.if eax
				    			m2m dwCheckPoint, _ss.dwCheckPoint
	        					invoke GetTickCount
	        					mov dwStartTickCount, eax
	        					
				    			.while _ss.dwCurrentState == SERVICE_START_PENDING
				    				xor edx, edx 				      								      				
				      				mov eax, _ss.dwWaitHint
				      				mov ecx, 10
				      				div ecx
				      				
				      				.if eax < 1000
				      					mov eax, 1000
				      					
				      				.elseif eax > 10000
				      					mov eax, 10000	
				      				.endif
				      								      				
									invoke Sleep, eax
									
									invoke QueryServiceStatus, hService, addr _ss
									.if !eax
						            	.break
				        			.endif
									
									mov eax, dwCheckPoint 
									.if _ss.dwCheckPoint > eax
										m2m dwCheckPoint, _ss.dwCheckPoint
			        					invoke GetTickCount
			        					mov dwStartTickCount, eax
			        					
									.else
										invoke GetTickCount
										sub eax, dwStartTickCount
										.if eax > _ss.dwWaitHint  
						            		.break
						            	.endif	
			            			.endif
				      			.endw
				    		.endif
						.endif										
					.endif
				.endif
						
				invoke CloseServiceHandle, hService
			.endif	
		.endif
				 												 
		invoke CloseServiceHandle, hSCManager				
	.endif				
	
	.if _ss.dwCurrentState == SERVICE_RUNNING
		mov eax, TRUE
	.else
		mov eax, FALSE	
	.endif
	ret
_StartService endp

StopService proc uses ecx edx lpszMachineName:LPCSTR, lpszServiceDisplayName:LPCSTR		
	LOCAL hSCManager: HANDLE
	LOCAL szServiceName[MAX_PATH]: BYTE
	LOCAL temp: DWORD
	LOCAL hService: HANDLE
	LOCAL _ss: SERVICE_STATUS
	LOCAL dwCheckPoint: DWORD
	LOCAL dwStartTickCount: DWORD
	 	
	invoke OpenSCManager, lpszMachineName, NULL, SC_MANAGER_CONNECT				
	mov hSCManager, eax
	.if eax
		mov temp, sizeof szServiceName
		invoke GetServiceKeyName, hSCManager, lpszServiceDisplayName, addr szServiceName, addr temp
		.if eax 						
			invoke OpenService, hSCManager, addr szServiceName, SERVICE_STOP or SERVICE_QUERY_STATUS
			mov hService, eax
			.if eax
				invoke ControlService, hService, SERVICE_CONTROL_STOP, addr _ss           
				.if eax	 
	        		invoke QueryServiceStatus, hService, addr _ss
	        		.if eax
	        			m2m dwCheckPoint, _ss.dwCheckPoint
	        			invoke GetTickCount
	        			mov dwStartTickCount, eax

	        			.while _ss.dwCurrentState == SERVICE_STOP_PENDING
	        				xor edx, edx 	          											
							mov eax, _ss.dwWaitHint
				      		mov ecx, 10
				      		div ecx
				      		
				      		.if eax < 1000
				      			mov eax, 1000
				      			
				      		.elseif eax > 10000
				      			mov eax, 10000	
				      		.endif
				      						      				
							invoke Sleep, eax
									
							invoke QueryServiceStatus, hService, addr _ss
							.if !eax
				            	.break
	            			.endif
							
							mov eax, dwCheckPoint 
							.if _ss.dwCheckPoint > eax
								m2m dwCheckPoint, _ss.dwCheckPoint
	        					invoke GetTickCount
	        					mov dwStartTickCount, eax
	        					
							.else
								invoke GetTickCount
								sub eax, dwStartTickCount
								.if eax > _ss.dwWaitHint  
				            		.break
				            	.endif	
	            			.endif
	          			.endw
	        		.endif
				.endif
				
				invoke CloseServiceHandle, hService
			.endif
		.endif	
				 												 
		invoke CloseServiceHandle, hSCManager				
	.endif				
	
	.if _ss.dwCurrentState == SERVICE_STOPPED
		mov eax, TRUE
	.else
		mov eax, FALSE	
	.endif
	ret
StopService endp

InstallProcessAsAService proc uses ecx edx lpszMachineName:LPCSTR, lpszServiceName:LPCSTR, lpszProcessPath:LPCSTR,
		dwPlatformId:DWORD
	LOCAL _si: STARTUPINFO
	LOCAL pi: PROCESS_INFORMATION	
	LOCAL hSCManager: HANDLE	
	LOCAL dwRetCode: DWORD 
	mov dwRetCode, FALSE
	mov eax, dwPlatformId
	.if eax == VER_PLATFORM_WIN32_WINDOWS
		mov _si.cb, sizeof _si
		mov _si.cbReserved2, 0
		mov _si.lpReserved, NULL
		mov _si.lpReserved2, NULL
		mov _si.dwFlags, 0
		mov _si.lpTitle, NULL		
		invoke CreateProcess, NULL, lpszProcessPath, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL,\
					NULL, addr _si, addr pi	
								  
	.elseif eax == VER_PLATFORM_WIN32_NT				  
		invoke OpenSCManager, lpszMachineName, NULL, SC_MANAGER_ALL_ACCESS				
		mov hSCManager, eax
		.if eax
			invoke CreateService, hSCManager, lpszServiceName, lpszServiceName,\
							SERVICE_ALL_ACCESS,\
							SERVICE_WIN32_OWN_PROCESS or SERVICE_INTERACTIVE_PROCESS,\
							SERVICE_AUTO_START,	SERVICE_ERROR_NORMAL, lpszProcessPath,\
							NULL, NULL,	NULL, NULL, NULL							
			.if eax	
				invoke CloseServiceHandle, eax
				mov dwRetCode, TRUE
			.endif			   	 												 
			invoke CloseServiceHandle, hSCManager				
		.endif		
	.endif	
	mov eax, dwRetCode
	ret
InstallProcessAsAService endp

UnInstallProcessAsAService proc uses ecx edx lpszMachineName:LPCSTR, lpszServiceName:LPCSTR, dwPlatformId:DWORD		
	LOCAL hSCManager: HANDLE
	LOCAL hService: HANDLE
	LOCAL ServiceStatus: SERVICE_STATUS
	LOCAL dwRetCode: DWORD 
	mov dwRetCode, FALSE
	mov eax, dwPlatformId
	.if eax == VER_PLATFORM_WIN32_NT
		invoke OpenSCManager, lpszMachineName, NULL, SC_MANAGER_ALL_ACCESS				
		mov hSCManager, eax
		.if eax			
			invoke OpenService, hSCManager, lpszServiceName, SERVICE_ALL_ACCESS
			mov hService, eax
			invoke ControlService, hService, SERVICE_CONTROL_STOP, addr ServiceStatus 
			invoke DeleteService, hService
			.if hService	
				invoke CloseServiceHandle, hService
				mov dwRetCode, TRUE
			.endif	 												 
			invoke CloseServiceHandle, hSCManager				
		.endif		
	.endif	
	mov eax, dwRetCode
	ret
UnInstallProcessAsAService endp

RunProcessAsAService proc uses ecx edx lpProcessMainProc:DWORD, lpszServiceName:LPCSTR, lpServiceMain:DWORD,\
			dwPlatformId:DWORD
	LOCAL ProcAddr: FARPROC
	LOCAL ServicesTable[4]: DWORD 	    
    mov eax, dwPlatformId
	.if eax == VER_PLATFORM_WIN32_WINDOWS		
	    invoke LoadLibrary, addr szKernel32dll
	    push eax    
	    invoke GetProcAddress, eax, addr szRegisterServiceProcess 
	    mov ProcAddr, eax
	    .if eax == NULL
	        mov eax, -1
	        ret
	    .else
	        push RSP_SIMPLE_SERVICE
	        push NULL
	        call ProcAddr	        
	        call lpProcessMainProc
	        push 0
	        push NULL
	        call ProcAddr         
	    .endif
	    call FreeLibrary 
	    
	.elseif eax == VER_PLATFORM_WIN32_NT	
		lea eax, ServicesTable
		m2m (SERVICE_TABLE_ENTRY ptr [eax]).lpServiceName, lpszServiceName
	    m2m (SERVICE_TABLE_ENTRY ptr [eax]).lpServiceProc, lpServiceMain
	    add eax, sizeof SERVICE_TABLE_ENTRY	    
	    mov (SERVICE_TABLE_ENTRY ptr [eax]).lpServiceName, NULL
	    mov (SERVICE_TABLE_ENTRY ptr [eax]).lpServiceProc, NULL	    
		invoke StartServiceCtrlDispatcher, addr ServicesTable				
	.endif       
    xor eax, eax
    ret    
RunProcessAsAService endp 

GetHardDriveSerialNumber proc uses ebx ecx edx lpBuff:LPCSTR
	LOCAL dwBytesReturned: DWORD 	
	LOCAL hDevice: DWORD     
    LOCAL pch: DWORD 
    LOCAL SCIP:	TSendCmdInParams 
    LOCAL IdOutCmd[(sizeOf(TSendCmdOutParams) + IDENTIFY_BUFFER_SIZE - 1)]: BYTE     		
	LOCAL VerInfo: _VersionInfo	 
    mov VerInfo.dwOSVersionInfoSize, sizeof _VersionInfo 
    invoke GetVersionEx, addr VerInfo
    .if VerInfo.dwPlatformId != VER_PLATFORM_WIN32_WINDOWS	
		invoke CreateFile, StrM("\\.\PhysicalDrive0"), GENERIC_READ or GENERIC_WRITE, 
        			FILE_SHARE_READ or FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0
        mov hDevice, eax			 
        
    .else 
    	invoke CreateFile, StrM("\\.\SMARTVSD"), 0, 0, 0, CREATE_NEW, 0, 0
    	mov hDevice, eax 
    .endif
    	    
 	.if hDevice == INVALID_HANDLE_VALUE 
 		mov eax, 0
 		ret
 	.endif	
 	
	invoke memset, addr SCIP, 0, sizeof TSendCmdInParams  
    invoke memset, addr IdOutCmd, 0, sizeof TSendCmdOutParams  + IDENTIFY_BUFFER_SIZE - 1     
    mov SCIP.dwBufferSize, IDENTIFY_BUFFER_SIZE 
	mov SCIP.bDriveNumber, 0 
    mov SCIP.IRDriveRegs.bSectorCountReg, 1 
    mov SCIP.IRDriveRegs.bSectorNumberReg, 1
    
    .if VerInfo.dwPlatformId != VER_PLATFORM_WIN32_WINDOWS
    	xor ebx, ebx     	
    	mov bl, SCIP.bDriveNumber 
    	and bl, 1
    	shl bl, 4
    	or bl, 0A0h
	    mov SCIP.IRDriveRegs.bDriveHeadReg, bl
	    
	.else
		mov SCIP.IRDriveRegs.bDriveHeadReg, 0A0h
	.endif
		          
     mov SCIP.IRDriveRegs.bCommandReg, 0ECh           
    invoke DeviceIoControl, hDevice, DFP_RECEIVE_DRIVE_DATA, addr SCIP, sizeof TSendCmdInParams - 1, 
      						addr IdOutCmd, sizeof TSendCmdOutParams + IDENTIFY_BUFFER_SIZE - 1,
      						addr dwBytesReturned, 0
    .if eax == 0
    	ret
    .endif    
  	lea ebx, IdOutCmd
  	lea ebx, (TSendCmdOutParams ptr [ebx]).bBuffer   	 
  	lea ebx, (TIdSector ptr [ebx]).sSerialNumber  	
  	invoke memcpy, ebx, lpBuff, 20 
  	invoke Swap, lpBuff, 20
  	mov ebx, lpBuff  
  	mov byte ptr [ebx + 19], 0	
  	mov edx, 19  	
@@:   
  	dec edx
  	cmp byte ptr [ebx + edx], 20h
  	jne @F
  	mov byte ptr [ebx + edx], 0 	  	
  	.if edx > 1
  		jmp @B  	
  	.endif  	
@@:
  	mov eax, 1	 	  	                   
	ret
GetHardDriveSerialNumber endp 

GetAssociatedIcon proc uses ecx edx lpszFileName:DWORD, pLargeIcon:PHICON, pSmallIcon:PHICON
	LOCAL hReg: HANDLE
	LOCAL dwType: DWORD	
    LOCAL IconIndex: DWORD
    LOCAL pFileExt: DWORD
    LOCAL tempbuff[512]: BYTE
    LOCAL dwDataSize: DWORD 
    LOCAL p: DWORD

    mov IconIndex, 0
    invoke lstrlen, lpszFileName
    invoke stol, lpszFileName, eax, '.'
    mov pFileExt, eax
    invoke lstrcmpi, pFileExt, StrM(".exe")
    .if eax == 0
    	lea eax, szCOM
    	mov pFileExt, eax
    .endif	
@@:	
	invoke RegOpenKeyEx, HKEY_CLASSES_ROOT, pFileExt, 0, KEY_READ, addr hReg
	mov byte ptr tempbuff, 0 
	mov dwType, REG_SZ
	mov dwDataSize, sizeof tempbuff
	invoke RegQueryValueEx, hReg, NULL, NULL, addr dwType, addr tempbuff, addr dwDataSize
	invoke RegCloseKey, hReg     
	.if byte ptr tempbuff != 0
		invoke lstrcat, addr tempbuff, StrM("\DefaultIcon")
		invoke RegOpenKeyEx, HKEY_CLASSES_ROOT, addr tempbuff, 0, KEY_READ, addr hReg
		mov byte ptr tempbuff, 0 
		mov dwType, REG_SZ
		mov dwDataSize, sizeof tempbuff		
		invoke RegQueryValueEx, hReg, NULL, NULL, addr dwType, addr tempbuff, addr dwDataSize
		invoke RegCloseKey, hReg		
    .endif
    
    .if byte ptr tempbuff == 0
		jmp @@noassoc	 
	.endif
	lea eax, tempbuff
	mov p, eax	  	   
	invoke PosStr, addr tempbuff, StrM(",")
	.if eax	
		add p, eax
		invoke StrToInt, p		
		mov IconIndex, eax
		dec p
		mov eax, p
		mov byte ptr [eax], 0
	.endif
			
	invoke ExtractIconEx, addr tempbuff, IconIndex, pLargeIcon, pSmallIcon, 1
    .if eax != 1
@@noassoc:		
    	invoke GetWindowsDirectory, addr tempbuff, sizeof tempbuff
    	mov eax, g_dwPlatformId
    	.if eax == VER_PLATFORM_WIN32_WINDOWS
        	invoke lstrcat, addr tempbuff, addr szSystem 
        	
    	.elseif eax == VER_PLATFORM_WIN32_NT
        	invoke lstrcat, addr tempbuff, addr szSystem32
    	.endif     	    
		invoke lstrcat, addr tempbuff, StrM("shell32.dll") 	
		invoke ExtractIconEx, addr tempbuff, IconIndex, pLargeIcon, pSmallIcon, 1 
		.if eax != 1
			.if pLargeIcon        	
				mov dword ptr pLargeIcon, 0
			.endif	
			.if pSmallIcon
				mov dword ptr pSmallIcon, 0
			.endif	
		.endif
	.endif		
	ret
GetAssociatedIcon endp

;GetLogonSID proc uses esi ebx ecx edx hToken:HANDLE, lppSid:DWORD
;	LOCAL ptg: PTOKEN_GROUPS 
;	LOCAL dwLength: DWORD
;	LOCAL dwCount: DWORD
;	LOCAL pGroupsBuff: DWORD
;	LOCAL pSid: DWORD
;	LOCAL dwRetCode: DWORD
;	mov dwRetCode, FALSE
;	cmp hToken, NULL
;	je @@CleanUp
;	invoke GetTokenInformation, hToken, TokenGroups, ptg, 0, addr dwLength
;	invoke GetLastError
;	cmp eax, ERROR_INSUFFICIENT_BUFFER
;	jne @@CleanUp	
;	invoke GetProcessHeap
;	invoke HeapAlloc, eax, HEAP_ZERO_MEMORY, dwLength
;	mov ptg, eax
;	cmp eax, NULL
;	je @@CleanUp
;	invoke GetTokenInformation, hToken, TokenGroups, ptg, dwLength, addr dwLength
;	cmp eax, NULL
;	je @@CleanUp	
;	assume ebx:ptr SID_AND_ATTRIBUTES
;	assume edx:ptr TOKEN_GROUPS
;	mov edx, ptg	 
;	m2m dwCount, [edx].GroupCount
;	lea eax, [edx].Groups
;	mov pGroupsBuff, eax
;	xor esi, esi
;	.while esi < dwCount
;		mov ebx, pGroupsBuff 		 		  	  		
;  		mov ecx, esi			  		
;  		mov eax, sizeof SID_AND_ATTRIBUTES  		  		 
;  		mul ecx     		
;  		add ebx, eax
;  		mov eax, [ebx].Attributes
;  		and eax, SE_GROUP_LOGON_ID
;  		.if eax == SE_GROUP_LOGON_ID
;  			invoke GetLengthSid, [ebx].Sid
;  			mov dwLength, eax
;  			invoke GetProcessHeap
;  			invoke HeapAlloc, eax, HEAP_ZERO_MEMORY, dwLength
;  			mov ecx, lppSid
;  			mov (dword ptr [ecx]), eax
;  			mov pSid, eax
;  			cmp eax, NULL
;  			je @@CleanUp
;  			invoke CopySid, dwLength, pSid, [ebx].Sid
;  			.if eax == FALSE
;  				invoke GetProcessHeap
;  				invoke HeapFree, eax, 0, pSid
;  				jmp @@CleanUp
;  			.endif  			
;  			.break  					
;  		.else
;  			inc esi	
;  		.endif		
;	.endw	
;  	mov dwRetCode, TRUE  	
;@@CleanUp:
;	assume edx:nothing
;  	assume ebx:nothing		
;	.if ptg
;		invoke GetProcessHeap
;		invoke HeapFree, eax, 0, ptg		
;	.endif
;	mov eax, dwRetCode
;	ret
;GetLogonSID endp
;
;FreeLogonSID proc lppSid:DWORD
;	LOCAL pSid: DWORD
;	mov eax, lppSid
;	m2m pSid, (dword ptr [eax]) 
;	invoke GetProcessHeap
;	invoke HeapFree, eax, 0, pSid	
;	ret
;FreeLogonSID endp
;
;AddAceToWindowStation proc uses esi ebx hWinStation:HWINSTA, pSid:DWORD
;	LOCAL pAce: PACCESS_ALLOWED_ACE
;	LOCAL aclSizeInfo: ACL_SIZE_INFORMATION
;	LOCAL pSD: PSECURITY_DESCRIPTOR
;	LOCAL pSDNew: PSECURITY_DESCRIPTOR
;	LOCAL _si: SECURITY_INFORMATION
;	LOCAL dwSidSize: DWORD
;	LOCAL dwSidLength: DWORD
;	LOCAL dwSDSizeNeeded: DWORD	
;	LOCAL bDaclPresent: BOOL
;	LOCAL pAcl: PACL
;	LOCAL pNewAcl: PACL
;	LOCAL bDaclDefaulted: BOOL
;	LOCAL dwNewAclSize: DWORD 
;	LOCAL pTempAce: PVOID
;	LOCAL bRetCode: BOOL
;	mov bRetCode, FALSE
;	mov dwSidSize, 0
;	mov pSD, NULL	
;	invoke GetLengthSid, pSid
;	mov dwSidLength, eax
;	mov _si, DACL_SECURITY_INFORMATION
;	invoke GetUserObjectSecurity, hWinStation, addr _si, pSD, dwSidSize, addr dwSDSizeNeeded	 
;	invoke GetLastError
;	.if eax == ERROR_INSUFFICIENT_BUFFER
;		invoke GetProcessHeap
;		invoke HeapAlloc, eax, HEAP_ZERO_MEMORY, dwSDSizeNeeded		
;		mov pSD, eax		
;		cmp eax, NULL
;		je @@CleanUp
;		invoke GetProcessHeap
;		invoke HeapAlloc, eax, HEAP_ZERO_MEMORY, dwSDSizeNeeded		
;		mov pSDNew, eax
;		cmp eax, NULL
;		je @@CleanUp
;		m2m dwSidSize, dwSDSizeNeeded		
;		invoke GetUserObjectSecurity, hWinStation, addr _si, pSD, dwSidSize, addr dwSDSizeNeeded		
;		cmp eax, FALSE
;		je @@CleanUp		
;	.else
;		je @@CleanUp	  
;	.endif		
;	invoke InitializeSecurityDescriptor, pSDNew, SECURITY_DESCRIPTOR_REVISION
;	cmp eax, NULL
;	je @@CleanUp	 							
;	invoke GetSecurityDescriptorDacl, pSD, addr bDaclPresent, addr pAcl, addr bDaclDefaulted			
;	cmp eax, NULL
;	je @@CleanUp	
;	mov aclSizeInfo.AceCount, 0
;	mov aclSizeInfo.AclBytesInUse, sizeof ACL
;	mov aclSizeInfo.AclBytesFree, 0	
;	.if pAcl
;		invoke GetAclInformation, pAcl, addr aclSizeInfo, sizeof ACL_SIZE_INFORMATION,\
;						AclSizeInformation
;		cmp eax, FALSE
;		je @@CleanUp
;	.endif  
;	m2m dwNewAclSize, aclSizeInfo.AclBytesInUse
;	mov eax, sizeof ACCESS_ALLOWED_ACE
;	shl eax, 1
;	add dwNewAclSize, eax
;	mov eax, dwSidLength
;	shl eax, 1
;	add dwNewAclSize, eax
;	mov eax, sizeof DWORD
;	shl eax, 1
;	sub dwNewAclSize, eax
;	invoke GetProcessHeap
;	invoke HeapAlloc, eax, HEAP_ZERO_MEMORY, dwNewAclSize
;	mov pNewAcl, eax
;	cmp eax, NULL
;	je @@CleanUp	
;	invoke InitializeAcl, pNewAcl, dwNewAclSize, ACL_REVISION
;	cmp eax, FALSE
;	je @@CleanUp
;	.if bDaclPresent
;		.if aclSizeInfo.AceCount						
;			xor esi, esi
;			.while esi < aclSizeInfo.AceCount
;				invoke GetAce, pAcl, esi, addr pTempAce
;				cmp eax, FALSE
;				je @@CleanUp
;				mov ebx, pTempAce
;				invoke AddAce, pNewAcl, ACL_REVISION, MAXDWORD, pTempAce,\
;								(ACE_HEADER ptr [ebx]).AceSize
;				je @@CleanUp
;				mov eax, pTempAce
;	  			inc esi			
;			.endw				
;		.endif
;	.endif
;	mov esi, sizeof ACCESS_ALLOWED_ACE	
;	add esi, dwSidLength
;	sub esi, sizeof DWORD
;	invoke GetProcessHeap
;	invoke HeapAlloc, eax, HEAP_ZERO_MEMORY, esi
;	mov pAce, eax
;	cmp eax, NULL
;	je @@CleanUp
;	assume ebx:ptr ACCESS_ALLOWED_ACE	
;	mov ebx, pAce 
;	mov [ebx].Header.AceType, ACCESS_ALLOWED_ACE_TYPE
;	mov [ebx].Header.AceFlags, CONTAINER_INHERIT_ACE or INHERIT_ONLY_ACE or OBJECT_INHERIT_ACE	
;	mov [ebx].Header.AceSize, si
;	mov [ebx].imask, GENERIC_ACCESS		
;	invoke CopySid, dwSidLength, addr [ebx].SidStart, pSid
;	cmp eax, FALSE
;	je @@CleanUp
;	invoke AddAce, pNewAcl, ACL_REVISION, MAXDWORD, pAce, [ebx].Header.AceSize
;	cmp eax, FALSE
;	je @@CleanUp 
;	mov [ebx].Header.AceFlags, NO_PROPAGATE_INHERIT_ACE
;	mov [ebx].imask, WINSTA_ALL
;	invoke AddAce, pNewAcl, ACL_REVISION, MAXDWORD, pAce, [ebx].Header.AceSize
;	cmp eax, FALSE
;	je @@CleanUp		
;	invoke SetSecurityDescriptorDacl, pSDNew, TRUE, pNewAcl, FALSE
;	cmp eax, FALSE
;	je @@CleanUp
;	invoke SetUserObjectSecurity, hWinStation, addr _si, pSDNew
;	cmp eax, FALSE
;	je @@CleanUp
;	mov bRetCode, TRUE		
;@@CleanUp:	    
;	assume ebx:nothing
;	.if pAce
;		invoke GetProcessHeap
;    	invoke HeapFree, eax, 0, pAce
;	.endif
;    .if pNewAcl
;        invoke GetProcessHeap
;    	invoke HeapFree, eax, 0, pNewAcl
;	.endif
;    .if pSD
;    	invoke GetProcessHeap
;    	invoke HeapFree, eax, 0, pSD
;	.endif
;    .if pSDNew
;        invoke GetProcessHeap
;    	invoke HeapFree, eax, 0, pSDNew
;	.endif
;	mov eax, bRetCode
;	ret
;AddAceToWindowStation endp
;
;AddAceToDesktop proc hDesktop:HDESK, pSid:DWORD
;	LOCAL aclSizeInfo: ACL_SIZE_INFORMATION
;	LOCAL pSD: PSECURITY_DESCRIPTOR
;	LOCAL pSDNew: PSECURITY_DESCRIPTOR
;	LOCAL _si: SECURITY_INFORMATION
;	LOCAL dwSidSize: DWORD
;	LOCAL dwSidLength: DWORD
;	LOCAL dwSDSizeNeeded: DWORD	
;	LOCAL bDaclPresent: BOOL
;	LOCAL pAcl: PACL
;	LOCAL pNewAcl: PACL
;	LOCAL bDaclDefaulted: BOOL
;	LOCAL dwNewAclSize: DWORD 
;	LOCAL pTempAce: PVOID
;	LOCAL bRetCode: BOOL
;	mov bRetCode, FALSE
;	mov dwSidSize, 0
;	mov pSD, NULL	
;	invoke GetLengthSid, pSid
;	mov dwSidLength, eax
;	mov _si, DACL_SECURITY_INFORMATION
;	invoke GetUserObjectSecurity, hDesktop, addr _si, pSD, dwSidSize, addr dwSDSizeNeeded 
;	invoke GetLastError
;	.if eax == ERROR_INSUFFICIENT_BUFFER
;		invoke GetProcessHeap
;		invoke HeapAlloc, eax, HEAP_ZERO_MEMORY, dwSDSizeNeeded		
;		mov pSD, eax
;		cmp eax, NULL
;		je @@CleanUp
;		invoke GetProcessHeap
;		invoke HeapAlloc, eax, HEAP_ZERO_MEMORY, dwSDSizeNeeded		
;		mov pSDNew, eax
;		cmp eax, NULL
;		je @@CleanUp
;		m2m dwSidSize, dwSDSizeNeeded
;		invoke GetUserObjectSecurity, hDesktop, addr _si, pSD, dwSidSize, addr dwSDSizeNeeded
;		cmp eax, FALSE
;		je @@CleanUp
;	.else
;		je @@CleanUp	  
;	.endif
;	invoke InitializeSecurityDescriptor, pSDNew, SECURITY_DESCRIPTOR_REVISION 
;	cmp eax, NULL
;	je @@CleanUp
;	invoke GetSecurityDescriptorDacl, pSD, addr bDaclPresent, addr pAcl, addr bDaclDefaulted
;	cmp eax, NULL
;	je @@CleanUp
;	mov aclSizeInfo.AceCount, 0
;	mov aclSizeInfo.AclBytesInUse, sizeof ACL
;	mov aclSizeInfo.AclBytesFree, 0
;	.if pAcl
;		invoke GetAclInformation, pAcl, addr aclSizeInfo, sizeof ACL_SIZE_INFORMATION,\
;						AclSizeInformation
;		cmp eax, FALSE
;		je @@CleanUp
;	.endif  
;	m2m dwNewAclSize, aclSizeInfo.AclBytesInUse
;	add dwNewAclSize, sizeof ACCESS_ALLOWED_ACE
;	mov eax, dwSidLength
;	add dwNewAclSize, eax
;	sub dwNewAclSize, sizeof DWORD
;	invoke GetProcessHeap
;	invoke HeapAlloc, eax, HEAP_ZERO_MEMORY, dwNewAclSize
;	mov pNewAcl, eax
;	cmp eax, NULL
;	je @@CleanUp
;	invoke InitializeAcl, pNewAcl, dwNewAclSize, ACL_REVISION
;	cmp eax, FALSE
;	je @@CleanUp
;	.if bDaclPresent
;		.if aclSizeInfo.AceCount						
;			xor esi, esi
;			.while esi < aclSizeInfo.AceCount
;				invoke GetAce, pAcl, esi, addr pTempAce
;				cmp eax, FALSE
;				je @@CleanUp
;				mov ebx, pTempAce
;				invoke AddAce, pNewAcl, ACL_REVISION, MAXDWORD, pTempAce,\
;								(ACE_HEADER ptr [ebx]).AceSize
;				je @@CleanUp
;				mov eax, pTempAce
;	  			inc esi			
;			.endw				
;		.endif
;	.endif
;	invoke AddAccessAllowedAce, pNewAcl, ACL_REVISION, DESKTOP_ALL, pSid
;	cmp eax, FALSE
;	je @@CleanUp	
;	invoke SetSecurityDescriptorDacl, pSDNew, TRUE, pNewAcl, FALSE
;	cmp eax, FALSE
;	je @@CleanUp
;	invoke SetUserObjectSecurity, hDesktop, addr _si, pSDNew
;	cmp eax, FALSE
;	je @@CleanUp
;	mov bRetCode, TRUE		
;@@CleanUp:	    	
;    .if pNewAcl
;        invoke GetProcessHeap
;    	invoke HeapFree, eax, 0, pNewAcl
;	.endif
;    .if pSD
;    	invoke GetProcessHeap
;    	invoke HeapFree, eax, 0, pSD
;	.endif
;    .if pSDNew
;        invoke GetProcessHeap
;    	invoke HeapFree, eax, 0, pSDNew
;	.endif
;	mov eax, bRetCode
;	ret
;AddAceToDesktop endp

ImpersonateCurrentUser proc
	LOCAL hToken: HANDLE
	LOCAL hDll: HINSTANCE
	LOCAL lpWTSGetActiveConsoleSessionId: FARPROC
	LOCAL lpWTSQueryUserToken: FARPROC	
	LOCAL hDupToken: HANDLE
	LOCAL dwSessionID: DWORD
	invoke RegCloseKey, HKEY_CURRENT_USER
	invoke RevertToSelf		
	invoke LoadLibrary, StrM("kernel32.dll")
	mov hDll, eax     			
	invoke GetProcAddress, hDll, StrM("WTSGetActiveConsoleSessionId")
	mov lpWTSGetActiveConsoleSessionId, eax
	call lpWTSGetActiveConsoleSessionId
	mov dwSessionID, eax
	invoke FreeLibrary, hDll
	invoke LoadLibrary, StrM("wtsapi32.dll")
	mov hDll, eax
	invoke GetProcAddress, hDll, StrM("WTSQueryUserToken")
	mov lpWTSQueryUserToken, eax
	mov hToken, NULL
	lea eax, hToken
	push eax
	push dwSessionID
	call lpWTSQueryUserToken
	invoke FreeLibrary, hDll
	mov hDupToken, NULL	
	invoke DuplicateToken, hToken, SecurityImpersonation, addr hDupToken
	.if hDupToken == NULL
		invoke CloseHandle, hToken
	.endif
	invoke ImpersonateLoggedOnUser, hDupToken
	invoke CloseHandle, hDupToken
	invoke CloseHandle, hToken				
	ret
ImpersonateCurrentUser endp

SwitchToLocalSystemAccount proc	
	LOCAL hProcess: HANDLE	 
	LOCAL hToken: HANDLE
	invoke GetProcessID, StrM("winlogon.exe")
	.if eax != -1				
		push eax
		invoke RegCloseKey, HKEY_CURRENT_USER
		invoke RevertToSelf
		pop eax 
		invoke OpenProcess, PROCESS_QUERY_INFORMATION, FALSE, eax
		mov hProcess, eax			
		invoke OpenProcessToken, hProcess, TOKEN_QUERY or TOKEN_DUPLICATE or TOKEN_IMPERSONATE,\
						addr hToken						 
		invoke CloseHandle, hProcess	
		invoke ImpersonateLoggedOnUser, hToken			
		invoke CloseHandle, hToken 	
	.endif	
	ret
SwitchToLocalSystemAccount endp

GetCurrentUserName proc lpszCurrentUserName:LPSTR, dwBuffSize:DWORD
	LOCAL dwSize: DWORD	
	invoke ImpersonateCurrentUser
	m2m dwSize, dwBuffSize
	invoke GetUserName, lpszCurrentUserName, addr dwSize	
	invoke RegCloseKey, HKEY_CURRENT_USER
	invoke RevertToSelf		 	 
	ret
GetCurrentUserName endp

GetUserSID proc lpszUserName:LPCSTR
	LOCAL szDomainName[MAX_PATH]: BYTE
	LOCAL dwDomainNameSize: DWORD	
	LOCAL pSid: PSID
	LOCAL dwSidSize: DWORD
	LOCAL SidNU: SID_NAME_USE
	LOCAL lpszUserSID: DWORD
	invoke GlobalAlloc, GPTR, MAX_PATH
	mov pSid, eax 
	mov dwSidSize, MAX_PATH	
	mov dwDomainNameSize, MAX_PATH		
	invoke LookupAccountName, NULL, lpszUserName, pSid, addr dwSidSize, addr szDomainName,\
					addr dwDomainNameSize, addr SidNU				
	invoke ConvertSidToStringSid, pSid, addr lpszUserSID 
	invoke GlobalFree, pSid	
	mov eax, lpszUserSID				
	ret
GetUserSID endp

GetCurrentUserSID proc	
	LOCAL szCurrentUserName[MAX_PATH]: BYTE
	LOCAL dwBuffSize: DWORD	
	invoke ImpersonateCurrentUser
	mov dwBuffSize, sizeof szCurrentUserName
	invoke GetUserName, addr szCurrentUserName, addr dwBuffSize	
	invoke RegCloseKey, HKEY_CURRENT_USER
	invoke RevertToSelf		 	
	invoke GetUserSID, addr szCurrentUserName 
	ret
GetCurrentUserSID endp

LoadUserRegistryHive proc lpszUserName:LPCSTR
	LOCAL szSettingFile[MAX_PATH]: BYTE
	invoke SetPrivilege, addr sz_SE_BACKUP_NAME, TRUE
	invoke SetPrivilege, addr sz_SE_RESTORE_NAME, TRUE
	invoke GetWindowsDirectory, addr szSettingFile, MAX_PATH
	invoke PosStr, addr szSettingFile, StrM("\")	
	lea ebx, szSettingFile
	add ebx, eax
	mov byte ptr [ebx], 0       
	invoke lstrcat, addr szSettingFile, StrM("documents and settings\")
	invoke lstrcat, addr szSettingFile, lpszUserName 
	invoke lstrcat, addr szSettingFile, StrM("\ntuser.dat") 
	invoke RegLoadKey, HKEY_USERS, lpszUserName, addr szSettingFile 
	ret
LoadUserRegistryHive endp

UnloadUserRegistryHive proc lpszUserName:LPCSTR
	invoke RegUnLoadKey, HKEY_USERS, lpszUserName  	 
	ret
UnloadUserRegistryHive endp