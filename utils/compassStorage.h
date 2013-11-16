TFileHandle   hFileHandle;              // will keep track of our file
TFileIOResult nIOResult;                // will store our IO results
string        sFileName = "compass.txt";   // the name of our file
int           nFileSize = 100;

void write(short val) {
	Delete(sFileName ,nIOResult);
	OpenWrite(hFileHandle, nIOResult, sFileName, nFileSize);
	WriteShort(hFileHandle, nIOResult, val);
	Close(hFileHandle, nIOResult);

}

int read() {
	OpenRead(hFileHandle, nIOResult, sFileName, nFileSize);
	short readVal = 0;
	ReadShort(hFileHandle, nIOResult, readVal);
	Close(hFileHandle, nIOResult);
	return readVal;
}
