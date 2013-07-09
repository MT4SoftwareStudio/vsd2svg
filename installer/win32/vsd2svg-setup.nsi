# vsd2svg - Convert VSD files into SVG
#
# Copyright (C) 2013 Steffen Macke <sdteffen@sdteffen.de>
#  
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

# NOTE: this .NSI script is designed for NSIS v2.0

Name vsd2svg

SetCompressor lzma

# Defines
!define REGKEY "SOFTWARE\$(^Name)"
!define VERSION 0.1.0
!define COMPANY "Steffen Macke"
!define URL http://dia-installer.de/vsd2svg

# MUI defines
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\orange-install.ico"
!define MUI_FINISHPAGE_NOAUTOCLOSE
!define MUI_STARTMENUPAGE_REGISTRY_ROOT HKLM
!define MUI_STARTMENUPAGE_REGISTRY_KEY ${REGKEY}
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME StartMenuGroup
!define MUI_STARTMENUPAGE_DEFAULTFOLDER vsd2svg
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\orange-uninstall.ico"
!define MUI_UNFINISHPAGE_NOAUTOCLOSE
!define MUI_FINISHPAGE_LINK	"dia-installer.de/vsd2svg"
!define MUI_FINISHPAGE_LINK_LOCATION	"http://dia-installer.de/vsd2svg"

# Included files
!include Sections.nsh
!include MUI.nsh
!include Library.nsh

# Variables
Var StartMenuGroup

# Installer pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE ..\..\COPYING
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_STARTMENU Application $StartMenuGroup
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

# Installer languages
!insertmacro MUI_LANGUAGE English

# Installer attributes
OutFile vsd2svg-setup-0.1.0-1.exe
InstallDir $PROGRAMFILES\vsd2svg
CRCCheck on
XPStyle on
ShowInstDetails show
VIProductVersion 0.1.0.0
VIAddVersionKey /LANG=${LANG_ENGLISH} ProductName vsd2svg
VIAddVersionKey /LANG=${LANG_ENGLISH} ProductVersion "${VERSION}"
VIAddVersionKey /LANG=${LANG_ENGLISH} CompanyName "${COMPANY}"
VIAddVersionKey /LANG=${LANG_ENGLISH} CompanyWebsite "${URL}"
VIAddVersionKey /LANG=${LANG_ENGLISH} FileVersion "${VERSION}"
VIAddVersionKey /LANG=${LANG_ENGLISH} FileDescription ""
VIAddVersionKey /LANG=${LANG_ENGLISH} LegalCopyright ""
InstallDirRegKey HKLM "${REGKEY}" Path
ShowUninstDetails show

# Installer sections
Section -Main SEC0000
	SetOutPath $INSTDIR
	File ..\..\COPYING
    SetOutPath $INSTDIR\bin
    SetOverwrite on
	File icudata51.dll
	File icui18n51.dll
	File icuio51.dll
	File icule51.dll
	File iculx51.dll
	File icutest51.dll
	File icutu51.dll
	File icuuc51.dll
	File libgcc_s_sjlj-1.dll
	File libstdc++-6.dll
	File libvisio-0.0.dll
	File libwpd-0.9.dll
	File libwpd-stream-0.9.dll
	File libwpg-0.2.dll
	File libxml2-2.dll
	File vsd2svg-win.exe
	File vsd2svg.exe
	File zlib1.dll
	
	ReadRegStr $1 HKCR ".vsd" ""
    
	StrCmp "$1" "" NoVSD
	StrCmp "$1" "vsd2svg.vsd" NoVSD
	
	Goto Action
	
	NoVSD:
	StrCpy $1 "vsd2svg.vsd"
    WriteRegStr HKCR ".vsd" "" "vsd2svg.vsd"
    WriteRegStr HKCR "vsd2svg.vsd" "" ""
	
	Action: 
	
	WriteRegStr HKLM "${REGKEY}" "*.vsd" "$1"
	
	WriteRegStr HKCR "$1\Shell\vsd2svg" "subcommands" ""
	WriteRegStr HKCR "$1\Shell\vsd2svg" "Icon" "$INSTDIR\bin\vsd2svg-win.exe,0"
	
	WriteRegStr HKCR "$1\Shell\vsd2svg\Shell\cmd1" "" "Convert to SVG"
	WriteRegStr HKCR "$1\Shell\vsd2svg\Shell\cmd1" "Icon" "$INSTDIR\bin\vsd2svg-win.exe,0"
	WriteRegStr HKCR "$1\Shell\vsd2svg\Shell\cmd1\command" "" '$INSTDIR\bin\vsd2svg-win.exe "%1"'
	
    WriteRegStr HKLM "${REGKEY}\Components" Main 1
SectionEnd

Section -post SEC0001
    WriteRegStr HKLM "${REGKEY}" Path $INSTDIR
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninstall-vsd2svg.exe 
	SetOutPath $SMPROGRAMS\$StartMenuGroup
	CreateShortcut "$SMPROGRAMS\$StartMenuGroup\vsd2svg-win.lnk" $INSTDIR\bin\vsd2svg-win.exe
	File "/oname=vsd2svg homepage.url" vsd2svg_homepage.url
	
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayName "$(^Name)"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayVersion "${VERSION}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" Publisher "${COMPANY}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" URLInfoAbout "${URL}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayIcon $INSTDIR\uninstall-vsd2svg.exe
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" UninstallString $INSTDIR\uninstall-vsd2svg.exe
    WriteRegDWORD HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" NoModify 1
    WriteRegDWORD HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" NoRepair 1
SectionEnd

# Macro for selecting uninstaller sections
!macro SELECT_UNSECTION SECTION_NAME UNSECTION_ID
    Push $R0
    ReadRegStr $R0 HKLM "${REGKEY}\Components" "${SECTION_NAME}"
    StrCmp $R0 1 0 next${UNSECTION_ID}
    !insertmacro SelectSection "${UNSECTION_ID}"
    GoTo done${UNSECTION_ID}
next${UNSECTION_ID}:
    !insertmacro UnselectSection "${UNSECTION_ID}"
done${UNSECTION_ID}:
    Pop $R0
!macroend

# Uninstaller sections
Section /o -un.Main UNSEC0000
	Delete /REBOOTOK $INSTDIR\bin\icudata51.dll
	Delete /REBOOTOK $INSTDIR\bin\icui18n51.dll
	Delete /REBOOTOK $INSTDIR\bin\icuio51.dll
	Delete /REBOOTOK $INSTDIR\bin\icule51.dll
	Delete /REBOOTOK $INSTDIR\bin\iculx51.dll
	Delete /REBOOTOK $INSTDIR\bin\icutest51.dll
	Delete /REBOOTOK $INSTDIR\bin\icutu51.dll
	Delete /REBOOTOK $INSTDIR\bin\icuuc51.dll
	Delete /REBOOTOK $INSTDIR\bin\libgcc_s_sjlj-1.dll
	Delete /REBOOTOK $INSTDIR\bin\libstdc++-6.dll
	Delete /REBOOTOK $INSTDIR\bin\libvisio-0.0.dll
	Delete /REBOOTOK $INSTDIR\bin\libwpd-0.9.dll
	Delete /REBOOTOK $INSTDIR\bin\libwpd-stream-0.9.dll
	Delete /REBOOTOK $INSTDIR\bin\libwpg-0.2.dll
	Delete /REBOOTOK $INSTDIR\bin\libxml2-2.dll
	Delete /REBOOTOK $INSTDIR\bin\vsd2svg-win.exe
	Delete /REBOOTOK $INSTDIR\bin\vsd2svg.exe
	Delete /REBOOTOK $INSTDIR\bin\zlib1.dll

	ReadRegStr $1 HKLM "${REGKEY}" "*.vsd"
	DeleteRegValue HKLM "${REGKEY}" "*.vsd"
	StrCmp "$1" "vsd2svg.vsd" OwnVSD ForeignVSD
	
	OwnVSD:
    DeleteRegValue HKCR ".vsd" ""
	DeleteRegValue HKCR ".vsd" "Content Type"
    DeleteRegKey /IfEmpty HKCR ".vsd"
	DeleteRegValue HKCR "$1" ""
	
    ForeignVSD:    

	DeleteRegValue HKCR "$1\Shell\vsd2svg" "subcommands"
	DeleteRegValue HKCR "$1\Shell\vsd2svg" "Icon"
	
	DeleteRegValue HKCR "$1\Shell\vsd2svg\Shell\cmd1" ""
	DeleteRegValue HKCR "$1\Shell\vsd2svg\Shell\cmd1" "Icon"
	DeleteRegValue HKCR "$1\Shell\vsd2svg\Shell\cmd1\command" ""
	
	DeleteRegKey /IfEmpty HKCR "$1\Shell\vsd2svg\Shell\cmd1\command"
	DeleteRegKey /IfEmpty HKCR "$1\Shell\vsd2svg\Shell\cmd1"
	DeleteRegKey /IfEmpty HKCR "$1\Shell\vsd2svg\Shell"
	DeleteRegKey /IfEmpty HKCR "$1\Shell\vsd2svg"
	DeleteRegKey /IfEmpty HKCR "$1\Shell"
	DeleteRegKey /IfEmpty HKCR "$1"

    DeleteRegValue HKLM "${REGKEY}\Components" Main
SectionEnd

Section -un.post UNSEC0001
    DeleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)"
	Delete "$SMPROGRAMS\$StartMenuGroup\vsd2svg-win.lnk"
	Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\vsd2svg-win.lnk"
	Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\vsd2svg homepage.url"
    Delete /REBOOTOK $INSTDIR\uninstall-vsd2svg.exe
	Delete /REBOOTOK $INSTDIR\COPYING
    DeleteRegValue HKLM "${REGKEY}" StartMenuGroup
    DeleteRegValue HKLM "${REGKEY}" Path
    DeleteRegKey /IfEmpty HKLM "${REGKEY}\Components"
    DeleteRegKey /IfEmpty HKLM "${REGKEY}"
	RmDir /REBOOTOK $SMPROGRAMS\$StartMenuGroup
    RmDir /REBOOTOK $INSTDIR\bin
    RmDir /REBOOTOK $INSTDIR
	
    Push $R0
    StrCpy $R0 $StartMenuGroup 1
    StrCmp $R0 ">" no_smgroup
no_smgroup:
    Pop $R0
SectionEnd

# Installer functions
Function .onInit
	!insertmacro MUI_LANGDLL_DISPLAY
    InitPluginsDir
FunctionEnd

# Uninstaller functions
Function un.onInit
    ReadRegStr $INSTDIR HKLM "${REGKEY}" Path
    !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuGroup
    !insertmacro SELECT_UNSECTION Main ${UNSEC0000}
FunctionEnd
