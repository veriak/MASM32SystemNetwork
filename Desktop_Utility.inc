;----------------------------------------------------------------------------------------
; MASM32 Desktop Library
;
; Copyright 2010 Veria Kalantary
; veria.kalantary@gmail.com
; https://github.com/veriak
;
;----------------------------------------------------------------------------------------

SelectDesktopByHandle 					PROTO	:HDESK
SelectDesktopByName 					PROTO	:LPCSTR
IsInputDesktopSelected					PROTO
SimulateCtrlaltDeleteThreadFunction		PROTO	:DWORD
SimulateCtrlAltDelete					PROTO
KillScreenSaverFunc						PROTO	:HWND, :LPARAM
KillScreenSaver 						PROTO	:DWORD

.data
	szScreenSaverClassName			db	"WindowsScreenSaverClass", 0
			
.code

SelectDesktopByHandle proc uses ecx edx hDesktop:HDESK
	LOCAL hOldDesktop: HDESK
	LOCAL tempBuff[256]: BYTE	 
	LOCAL dwNeededSize: DWORD		
	invoke GetUserObjectInformation, hDesktop, UOI_NAME, addr tempBuff, sizeof tempBuff,\
					addr dwNeededSize
	.if eax == 0
		mov eax, FALSE
		ret
	.endif
	invoke GetCurrentThreadId
	invoke GetThreadDesktop, eax
	mov hOldDesktop, eax
	invoke SetThreadDesktop, hDesktop
	.if eax == 0
		mov eax, FALSE
		ret
	.endif			
	invoke CloseDesktop, hOldDesktop
	mov eax, TRUE
	ret	
SelectDesktopByHandle endp

SelectDesktopByName proc uses ecx edx lpszDesktopName:LPCSTR
	LOCAL hDesktop: HDESK
	.if lpszDesktopName
		invoke OpenDesktop, lpszDesktopName, 0, FALSE, DESKTOP_CREATEMENU or\
						DESKTOP_CREATEWINDOW or	DESKTOP_ENUMERATE or DESKTOP_HOOKCONTROL or\
						DESKTOP_WRITEOBJECTS or	DESKTOP_READOBJECTS or DESKTOP_SWITCHDESKTOP or\
						GENERIC_WRITE
	.else
		invoke OpenInputDesktop, 0, FALSE, DESKTOP_CREATEMENU or\
						DESKTOP_CREATEWINDOW or	DESKTOP_ENUMERATE or DESKTOP_HOOKCONTROL or\
						DESKTOP_WRITEOBJECTS or	DESKTOP_READOBJECTS or DESKTOP_SWITCHDESKTOP or\
						GENERIC_WRITE
	.endif					
	mov hDesktop, eax				
	.if eax == NULL
		mov eax, FALSE
		ret
	.endif
	invoke SelectDesktopByHandle, hDesktop
	.if eax == FALSE			
		invoke CloseDesktop, hDesktop
		.if eax == 0
			mov eax, FALSE
		.endif	
	.endif	
	mov eax, TRUE
	ret
SelectDesktopByName endp

IsInputDesktopSelected proc uses ecx edx
	LOCAL hThreadDesktop: HDESK
	LOCAL hInputDesktop: HDESK
	LOCAL szThreadDesktop[256]: BYTE
	LOCAL szInputDesktop[256]: BYTE	 
	LOCAL dwNeededSize: DWORD
			
	invoke GetCurrentThreadId
	invoke GetThreadDesktop, eax
	mov hThreadDesktop, eax
	
	invoke OpenInputDesktop, 0, FALSE,	DESKTOP_CREATEMENU or DESKTOP_CREATEWINDOW or\
					DESKTOP_ENUMERATE or DESKTOP_HOOKCONTROL or	DESKTOP_WRITEOBJECTS or\
					DESKTOP_READOBJECTS or DESKTOP_SWITCHDESKTOP or GENERIC_WRITE
	mov hInputDesktop, eax
	.if eax == NULL		
		jmp @@RetFalse
	.endif		
		
	invoke GetUserObjectInformation, hThreadDesktop, UOI_NAME, addr szThreadDesktop,\
					sizeof szThreadDesktop, addr dwNeededSize
	.if eax == 0
		invoke CloseDesktop, hInputDesktop				
		jmp @@RetFalse
	.endif
	
	invoke GetUserObjectInformation, hInputDesktop, UOI_NAME, addr szInputDesktop,\
					sizeof szInputDesktop, addr dwNeededSize
	.if eax == 0
		invoke CloseDesktop, hInputDesktop				
		jmp @@RetFalse
	.endif
	
	invoke CloseDesktop, hInputDesktop
		
	invoke lstrcmp, addr szThreadDesktop, addr szInputDesktop
	.if eax
		jmp @@RetFalse
	.endif	
	
	mov eax, TRUE
	ret
@@RetFalse:	
	mov eax, FALSE
	ret	
IsInputDesktopSelected endp

SimulateCtrlAltDeleteThreadFunction proc uses ecx edx dwParam:DWORD	
	LOCAL hOldThreadDesktop: HDESK		
	LOCAL hCtrlAltDeleteWnd: HANDLE
	invoke GetCurrentThreadId
	invoke GetThreadDesktop, eax
	push eax
	invoke SelectDesktopByName, StrM("Winlogon")
	.if eax
		invoke FindWindow, StrM("SAS window class"), StrM("SAS window")
		.if eax
			mov hCtrlAltDeleteWnd, eax
		.else
			mov hCtrlAltDeleteWnd, HWND_BROADCAST	
		.endif
		invoke PostMessage, hCtrlAltDeleteWnd, WM_HOTKEY, 0,\
						MAKELONG(MOD_ALT or MOD_CONTROL, VK_DELETE)
	.endif	
	pop eax
	invoke SelectDesktopByHandle, eax
	ret
SimulateCtrlAltDeleteThreadFunction endp

SimulateCtrlAltDelete proc
	push eax
    invoke CreateThread, NULL, NULL, offset SimulateCtrlAltDeleteThreadFunction, eax,\
    				NORMAL_PRIORITY_CLASS, esp
    invoke CloseHandle, eax    								 	
    pop eax   					
	ret
SimulateCtrlAltDelete endp

KillScreenSaverFunc proc uses ecx edx hWnd:HWND, lParam:LPARAM
	LOCAL tempBuff[256]: BYTE
	invoke GetClassName, hWnd, addr tempBuff, sizeof tempBuff  
	.if eax
		invoke lstrcmp, addr tempBuff, addr szScreenSaverClassName
		.if eax == 0
			invoke PostMessage, hWnd, WM_CLOSE, 0, 0
		.endif
	.endif		
	mov eax, TRUE
	ret
KillScreenSaverFunc endp

KillScreenSaver proc uses ecx edx dwPlatformId:DWORD
	LOCAL hDesktop: HDESK
	mov eax, dwPlatformId
	.if eax == VER_PLATFORM_WIN32_WINDOWS
		invoke FindWindow, addr szScreenSaverClassName, NULL
		.if eax
			invoke PostMessage, eax, WM_CLOSE, 0, 0 			
		.endif
		 
	.elseif eax == VER_PLATFORM_WIN32_NT
		invoke OpenDesktop, StrM("Screen-saver"), 0, FALSE,\
						DESKTOP_READOBJECTS or DESKTOP_WRITEOBJECTS		
		.if eax		
			mov hDesktop, eax
			invoke EnumDesktopWindows, hDesktop, offset KillScreenSaverFunc, 0
			invoke CloseDesktop, hDesktop
			invoke Sleep, 2000
			invoke SystemParametersInfo, SPI_SETSCREENSAVEACTIVE, TRUE, 0, SPIF_SENDWININICHANGE 			
		.endif
	.endif
	ret
KillScreenSaver endp
