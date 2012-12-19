#include <windows.h>
#include <malloc.h>
#include <stdio.h>

#define TOTALBYTES    8192
#define BYTEINCREMENT 4096

void main()
{
    DWORD BufferSize = TOTALBYTES;
    DWORD cbData;
    DWORD dwRet;

    PPERF_DATA_BLOCK PerfData = (PPERF_DATA_BLOCK) malloc( BufferSize );
    cbData = BufferSize;

    printf("\nRetrieving the data...");

    dwRet = RegQueryValueEx( HKEY_PERFORMANCE_DATA,
                             TEXT("Global"),
                             NULL,
                             NULL,
                             (LPBYTE) PerfData,
                             &cbData );
    while( dwRet == ERROR_MORE_DATA )
    {
        // Get a buffer that is big enough.

        BufferSize += BYTEINCREMENT;
        PerfData = (PPERF_DATA_BLOCK) realloc( PerfData, BufferSize );
        cbData = BufferSize;

        printf(".");
        dwRet = RegQueryValueEx( HKEY_PERFORMANCE_DATA,
                         TEXT("Global"),
                         NULL,
                         NULL,
                         (LPBYTE) PerfData,
                         &cbData );
    }
    if( dwRet == ERROR_SUCCESS )
        printf("\n\nFinal buffer size is %d\n", BufferSize);
    else printf("\nRegQueryValueEx failed (%d)\n", dwRet);
}
