#pragma comment( lib, "winmm.lib" )

#include <Windows.h>
#include <mmsystem.h>

//untested might work might not 
void OpenCloseDiskTray(bool openClose){
	
    MCI_OPEN_PARMS mPar = { 0 };
    mPar.lpstrDeviceType = reinterpret_cast<LPCWSTR>(MCI_DEVTYPE_CD_AUDIO);

    // Open device
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID, (DWORD)&mPar);

    if (openClose) {
        // Open tray
        mciSendCommand(mPar.wDeviceID, MCI_SET, MCI_SET_DOOR_OPEN, 0);
    }else{
        // Close tray
        mciSendCommand(mPar.wDeviceID, MCI_SET, MCI_SET_DOOR_CLOSED, 0);
    }

    // Close device
    mciSendCommand(mPar.wDeviceID, MCI_CLOSE, MCI_WAIT, 0);

}
