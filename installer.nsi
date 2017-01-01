; rtype.nsi
;
; This script is based on example1.nsi, but it remember the directory, 
; has uninstall support and (optionally) installs start menu shortcuts.
;
; It will install rtype.nsi into a directory that the user selects,

;--------------------------------

; The name of the installer
Name "rtype"

; The file to write
OutFile "rtype_setup.exe"

; The default installation directory
InstallDir $PROGRAMFILES\rtype

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\NSIS_rtype" "Install_Dir"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages

Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "rtype (required)"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  ; File "rtype.nsi"
  
  File "build\server\Release\rtype_server.exe"
  File "build\client\Release\rtype_client.exe"
  File "C:\SFML-2.4.1\bin\*.dll"

  SetOutPath $INSTDIR\levels
  File /nonfatal /a /r "levels\"
  
  SetOutPath $INSTDIR\build\entity
  File "build\entity\Release\*.dll"
  
  SetOutPath $INSTDIR\media
  File /nonfatal /a /r "media\"
  
  SetOutPath $INSTDIR\config
  File /nonfatal /a /r "config\"
  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\NSIS_rtype "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\rtype" "DisplayName" "NSIS rtype"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\rtype" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\rtype" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\rtype" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\rtype"
  CreateShortcut "$SMPROGRAMS\rtype\rtype client.lnk" "$INSTDIR\rtype_client.exe" "" "$INSTDIR\rtype_client.exe" 0
  CreateShortcut "$SMPROGRAMS\rtype\rtype server.lnk" "$INSTDIR\rtype_server.exe" "" "$INSTDIR\rtype_server.exe" 0
  CreateShortcut "$SMPROGRAMS\rtype\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\rtype"
  DeleteRegKey HKLM SOFTWARE\NSIS_rtype

  ; Remove files and uninstaller
  ; Delete $INSTDIR\*

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\rtype\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\rtype"
  RMDir /r /REBOOTOK "$INSTDIR"

SectionEnd
