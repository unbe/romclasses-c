#include"stdafx.h"
#include<j9port.h>
#include<malloc.h>
#include<stdio.h>

struct J9ROMClass;
struct J9ROMMethod;
extern "C" {
	IDATA j9bcutil_dumpRomClass(J9ROMClass *romClass, J9PortLibrary *portLib, void *translationBuffers, U_32 flags);
	void j9bcv_verifyDumpROMMethodPreverifyInfo() {}; 
	void j9bcv_verifyDumpPreverifyClassTable() {};
	void j9bcv_verifyGetROMClassPreverifyInfo() {};
}

typedef I_32 J9SRP;

#define NNSRP_GET(field, type) ((type) (((U_8 *) &(field)) + (J9SRP)(field)))

typedef struct J9ROMImageHeader {
	U_32 idTag;
	U_32 flagsAndVersion;
	U_32 romSize;
	U_32 classCount;
	J9SRP jxePointer;
	J9SRP tableOfContents;
	J9SRP firstClass;
	J9SRP aotPointer;
	U_8 symbolFileID[16];
} J9ROMImageHeader;

#define J9ROMIMAGEHEADER_TABLEOFCONTENTS(base) NNSRP_GET((base)->tableOfContents, struct J9ROMClassTOCEntry*)

typedef struct J9ROMClassTOCEntry {
	J9SRP className;
	J9SRP romClass;
} J9ROMClassTOCEntry;

#define J9ROMCLASSTOCENTRY_CLASSNAME(base) NNSRP_GET((base)->className, const char*)
#define J9ROMCLASSTOCENTRY_ROMCLASS(base) NNSRP_GET((base)->romClass, struct J9ROMClass*)


int main(int argc, char* argv[])
{
	printf("Caller at your service.\n");
	J9PortLibraryVersion portver;
	portver.majorVersionNumber = 6;
	portver.minorVersionNumber = 1;
	portver.capabilities = 15;
	int size = j9port_getSize(&portver);
	printf("Portlib struct size: %d\n", size);
	
	J9PortLibrary* portlib;
	portlib = (J9PortLibrary*)malloc(size);
	int r = j9port_create_library(portlib, &portver, size);
	printf("j9port_create_library: %d\n", r);
	r = j9port_startup_library(portlib);
	printf("j9port_startup_library: %d\n", r);

	FILE* f = fopen(argv[1], "rb");
	fseek(f, 0, SEEK_END);
	size_t sz = ftell(f);
	fseek(f, 0, SEEK_SET);
	printf("rom.classes: %d bytes\n", sz);
	char* rom = (char *)malloc(sz);
	r = fread(rom, sz, 1, f);
	printf("read: %d\n", r);
	perror("read");
	fclose(f);

	J9ROMImageHeader* image = (J9ROMImageHeader*)rom;
	J9ROMClassTOCEntry* toc_entry = J9ROMIMAGEHEADER_TABLEOFCONTENTS(image);
	printf("Dumping %d classes\n", image->classCount);
	for (int i = 0; i < image->classCount; i++) {
		printf("Class #%d:\n", i);
		r = j9bcutil_dumpRomClass(J9ROMCLASSTOCENTRY_ROMCLASS(toc_entry + i), portlib, 0, 0);
		printf("Dump #%d: %d\n", i, r);
	}
	return 0;
}

