#define _CRT_SECURE_NO_WARNINGS
#include <Stdio.h>
#include <Windows.h>
#include <math.h>

double provekra(char* stroka) {
	char message[256];
	int i = 0;
	while (stroka[i]) {
		i++;
		if (stroka[i] > 96 || stroka[i] < -1) {
			return 1;
		}
	}
	double number = pow(atof(stroka),2);
	return number;
}



int main()
{
	system("chcp 1251");
	HANDLE hNamePipe;
	LPSTR pipeName = L"\\\\.\\pipe\\MyPipe";
	DWORD read_buffer = 100;
	LPWSTR buffer =(CHAR*) calloc(read_buffer, sizeof(char));
	char message[100];
	DWORD actual_read;
	BOOL Connected;
	BOOL SuccessRead;
	while (1)
	{
		hNamePipe = CreateNamedPipe(
			pipeName,
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			512,
			512,
			INFINITE,
			NULL);
		Connected = ConnectNamedPipe(hNamePipe, NULL);
		if (Connected) {
			printf("\nКлиент подключился\n");
			SuccessRead = ReadFile(hNamePipe, buffer, read_buffer, &actual_read, NULL);
			if (SuccessRead) {
				printf("\nКлиент пишет");
				printf(buffer);
				double result = provekra(buffer);
				if (result == 1) {
					sprintf(message, "%s", "Ошибка");
				}
				else {
					sprintf(message, "%f", result);
				}
				printf("\n");
				printf("\nВведите сообщение для клиента");
				//sprintf(message, "%s", provekra(buffer));
				WriteFile(hNamePipe, message, read_buffer, &actual_read, NULL);
			}
		}
		else
		{
			printf("\nКлиент отключился от сервера");
		}
		CloseHandle(hNamePipe);
	}
}


