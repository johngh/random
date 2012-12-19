#include <windows.h>
#include <winbase.h>
#include <windef.h>
#include <stdio.h>
#include <string.h>

void main()
{

PPERF_DATA_BLOCK readStringFromRegistry( void* keyname, void* valuename  ) {
  HKEY hkeyPtr;
  DWORD keystatus;
  DWORD buffersize = 1;
  DWORD cbData = buffersize;
  PPERF_DATA_BLOCK PerfData = (PPERF_DATA_BLOCK) malloc( buffersize );

  keystatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE,TEXT(keyname), 0,KEY_READ, &hkeyPtr);
  if (ERROR_SUCCESS == keystatus)
  {
    keystatus = RegQueryValueEx( hkeyPtr, TEXT(valuename),NULL,NULL,(LPBYTE) PerfData,&cbData );

    while( keystatus == ERROR_MORE_DATA )
    {
      buffersize += 1;
      PerfData = (PPERF_DATA_BLOCK) realloc( PerfData, buffersize );
      cbData = buffersize;
      keystatus = RegQueryValueEx( hkeyPtr,TEXT(keyname),NULL,NULL,(LPBYTE) PerfData,&cbData );
    }

  }
  RegCloseKey(hkeyPtr);
  return PerfData;
}

}
