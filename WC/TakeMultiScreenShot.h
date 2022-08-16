#include <atlimage.h>
#include <vector>
#include <fstream>
#include <string>

int screenCounter;

BOOL CALLBACK MonitorEnumProcCallback(_In_  HMONITOR hMonitor, _In_  HDC DevC, _In_  LPRECT lprcMonitor, _In_  LPARAM dwData) {
    screenCounter++;

    std::string fileName = "Screen" + std::to_string(screenCounter) + ".jpg";

    MONITORINFO  info{};
    info.cbSize = sizeof(MONITORINFO);

    BOOL monitorInfo = GetMonitorInfo(hMonitor, &info);

    if (monitorInfo) {

        DWORD Width = info.rcMonitor.right - info.rcMonitor.left;
        DWORD Height = info.rcMonitor.bottom - info.rcMonitor.top;

        DWORD FileSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (sizeof(RGBTRIPLE) + 1 * (Width * Height * 4));
        char* BmpFileData = (char*)GlobalAlloc(0x0040, FileSize);

        HDC CaptureDC = CreateCompatibleDC(DevC);
        HBITMAP CaptureBitmap = CreateCompatibleBitmap(DevC, Width, Height);
        SelectObject(CaptureDC, CaptureBitmap);
        BitBlt(CaptureDC, 0, 0, Width, Height, DevC, info.rcMonitor.left, info.rcMonitor.top, SRCCOPY | CAPTUREBLT);

        std::vector<BYTE> buf;
        IStream* stream = NULL;
        HRESULT hr = CreateStreamOnHGlobal(0, TRUE, &stream);
        CImage image;
        ULARGE_INTEGER liSize;

        // screenshot to jpg and save to stream
        image.Attach(CaptureBitmap);
        image.Save(stream, Gdiplus::ImageFormatJPEG);
        IStream_Size(stream, &liSize);
        DWORD len = liSize.LowPart;
        IStream_Reset(stream);
        buf.resize(len);
        IStream_Read(stream, &buf[0], len);
        stream->Release();

        // just testing if the buf contains the correct data
        std::fstream fi;
        fi.open(fileName, std::fstream::binary | std::fstream::out);
        fi.write(reinterpret_cast<const char*>(&buf[0]), buf.size() * sizeof(BYTE));
        fi.close();

        GlobalFree(BmpFileData);
    }

    return TRUE;
}

void TakeScreenshot() {
    HDC DevC = GetDC(NULL);
    BOOL b = EnumDisplayMonitors(DevC, NULL, MonitorEnumProcCallback, 0);
}