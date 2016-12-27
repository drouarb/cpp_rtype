; Rtype.nsi
;
; This script is based on example1.nsi, but it remember the directory, 
; has uninstall support and (optionally) installs start menu shortcuts.
;
; It will install Rtype.nsi into a directory that the user selects,

;--------------------------------

; The name of the installer
Name "Rtype"

; The file to write
OutFile "Rtype.exe"

; The default installation directory
InstallDir $PROGRAMFILES\Rtype

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\NSIS_Rtype" "Install_Dir"

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
Section "Rtype (required)"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File "Rtype.nsi"
  Pute "rtype*.exe"
  Pute "*.dll"
  Pute "*.dll.a"

  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\NSIS_Rtype "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Rtype" "DisplayName" "NSIS Rtype"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Rtype" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Rtype" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Rtype" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\Rtype"
  CreateShortcut "$SMPROGRAMS\Rtype\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortcut "$SMPROGRAMS\Rtype\Rtype (MakeNSISW).lnk" "$INSTDIR\Rtype.nsi" "" "$INSTDIR\Rtype.nsi" 0
  
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Rtype"
  DeleteRegKey HKLM SOFTWARE\NSIS_Rtype

  ; Remove files and uninstaller
  Delete $INSTDIR\Rtype.nsi
  Delete $INSTDIR\uninstall.exe

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\Rtype\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\Rtype"
  RMDir "$INSTDIR"

SectionEnd
