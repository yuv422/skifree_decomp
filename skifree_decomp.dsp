# Microsoft Developer Studio Project File - Name="skifree_decomp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=skifree_decomp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "skifree_decomp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "skifree_decomp.mak" CFG="skifree_decomp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "skifree_decomp - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "skifree_decomp - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "skifree_decomp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "skifree_decomp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "skifree_decomp - Win32 Release"
# Name "skifree_decomp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "asm"

# PROP Default_Filter "asm"
# Begin Source File

SOURCE=.\data.asm

!IF  "$(CFG)" == "skifree_decomp - Win32 Release"

# Begin Custom Build
InputPath=.\data.asm
InputName=data

"$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /Zi /Zf /c /Cx /nologo /coff $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "skifree_decomp - Win32 Debug"

# Begin Custom Build
InputPath=.\data.asm
InputName=data

"$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /Zi /Zf /c /Cx /nologo /coff $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rdata.asm

!IF  "$(CFG)" == "skifree_decomp - Win32 Release"

# Begin Custom Build
InputPath=.\rdata.asm
InputName=rdata

"$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /Zi /Zf /c /Cx /nologo /coff $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "skifree_decomp - Win32 Debug"

# Begin Custom Build
InputPath=.\rdata.asm
InputName=rdata

"$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /Zi /Zf /c /Cx /nologo /coff $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\semblance.asm

!IF  "$(CFG)" == "skifree_decomp - Win32 Release"

# Begin Custom Build
InputPath=.\semblance.asm
InputName=semblance

"$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /Zi /Zf /c /Cx /nologo /coff $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "skifree_decomp - Win32 Debug"

# Begin Custom Build
InputPath=.\semblance.asm
InputName=semblance

"$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /Zi /c /nologo /coff $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\skifree_decomp.c
# End Source File
# Begin Source File

SOURCE=.\skifree_decomp.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.c
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\skifree_decomp.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\resources\iconski.ico
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_1.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_2.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_22.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_23.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_24.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_25.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_26.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_27.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_28.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_29.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_30.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_34.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_35.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_36.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_37.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_38.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_39.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_4.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_41.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_42.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_43.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_44.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_45.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_53.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_54.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_55.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_59.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_60.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_63.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_64.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_65.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_80.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_81.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_82.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_83.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_84.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_85.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_86.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_87.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_88.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\ski32_89.bmp
# End Source File
# End Group
# End Target
# End Project
