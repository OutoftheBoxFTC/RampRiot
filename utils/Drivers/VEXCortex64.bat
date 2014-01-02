@echo off
echo Installing VEX Cortex USB Drivers...
echo Note: You may be prompted by Windows to accept a new device driver.
echo       Please click "Install" if this window appears.
VEXCortex64.msi /passive
echo --------------------------------------------------
echo Installing VEX USB to Serial Drivers...
VEXUSBSerialDriver.exe /s
echo Finished!