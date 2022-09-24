# Microsoft Developer Studio Generated NMAKE File, Based on skifree_decomp.dsp
!IF "$(CFG)" == ""
CFG=skifree_decomp - Win32 Debug
!MESSAGE No configuration specified. Defaulting to skifree_decomp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "skifree_decomp - Win32 Release" && "$(CFG)" != "skifree_decomp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "skifree_decomp - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\skifree_decomp.exe" "$(OUTDIR)\skifree_decomp.bsc"


CLEAN :
	-@erase "$(INTDIR)\skifree_decomp.obj"
	-@erase "$(INTDIR)\skifree_decomp.pch"
	-@erase "$(INTDIR)\skifree_decomp.res"
	-@erase "$(INTDIR)\skifree_decomp.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\skifree_decomp.bsc"
	-@erase "$(OUTDIR)\skifree_decomp.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\skifree_decomp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\skifree_decomp.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\skifree_decomp.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\skifree_decomp.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\skifree_decomp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\skifree_decomp.pdb" /machine:I386 /out:"$(OUTDIR)\skifree_decomp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\skifree_decomp.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\skifree_decomp.res" \
	".\data.obj" \
	".\rdata.obj" \
	".\semblance.obj"

"$(OUTDIR)\skifree_decomp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "skifree_decomp - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\skifree_decomp.exe" "$(OUTDIR)\skifree_decomp.bsc"


CLEAN :
	-@erase "$(INTDIR)\skifree_decomp.obj"
	-@erase "$(INTDIR)\skifree_decomp.pch"
	-@erase "$(INTDIR)\skifree_decomp.res"
	-@erase "$(INTDIR)\skifree_decomp.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\skifree_decomp.bsc"
	-@erase "$(OUTDIR)\skifree_decomp.exe"
	-@erase "$(OUTDIR)\skifree_decomp.ilk"
	-@erase "$(OUTDIR)\skifree_decomp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\skifree_decomp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\skifree_decomp.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\skifree_decomp.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\skifree_decomp.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\skifree_decomp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\skifree_decomp.pdb" /debug /machine:I386 /out:"$(OUTDIR)\skifree_decomp.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\skifree_decomp.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\skifree_decomp.res" \
	".\data.obj" \
	".\rdata.obj" \
	".\semblance.obj"

"$(OUTDIR)\skifree_decomp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("skifree_decomp.dep")
!INCLUDE "skifree_decomp.dep"
!ELSE 
!MESSAGE Warning: cannot find "skifree_decomp.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "skifree_decomp - Win32 Release" || "$(CFG)" == "skifree_decomp - Win32 Debug"
SOURCE=.\data.asm

!IF  "$(CFG)" == "skifree_decomp - Win32 Release"

InputPath=.\data.asm
InputName=data

".\data.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	ml /Zi /Zf /c /Cx /nologo /coff $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "skifree_decomp - Win32 Debug"

InputPath=.\data.asm
InputName=data

".\data.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	ml /Zi /Zf /c /Cx /nologo /coff $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\rdata.asm

!IF  "$(CFG)" == "skifree_decomp - Win32 Release"

InputPath=.\rdata.asm
InputName=rdata

".\rdata.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	ml /Zi /Zf /c /Cx /nologo /coff $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "skifree_decomp - Win32 Debug"

InputPath=.\rdata.asm
InputName=rdata

".\rdata.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	ml /Zi /Zf /c /Cx /nologo /coff $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\semblance.asm

!IF  "$(CFG)" == "skifree_decomp - Win32 Release"

InputPath=.\semblance.asm
InputName=semblance

".\semblance.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	ml /Zi /Zf /c /Cx /nologo /coff $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "skifree_decomp - Win32 Debug"

InputPath=.\semblance.asm
InputName=semblance

".\semblance.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	ml /Zi /c /nologo /coff $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\skifree_decomp.c

"$(INTDIR)\skifree_decomp.obj"	"$(INTDIR)\skifree_decomp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\skifree_decomp.pch"


SOURCE=.\skifree_decomp.rc

"$(INTDIR)\skifree_decomp.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.c

!IF  "$(CFG)" == "skifree_decomp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\skifree_decomp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\skifree_decomp.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "skifree_decomp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\skifree_decomp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\skifree_decomp.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

