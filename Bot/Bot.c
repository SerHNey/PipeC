#define _CRT_SECURE_NO_WARNINGS
#include <Stdio.h>
#include <Windows.h>
#include <math.h>

char* provekra(char* stroka) {
	char message[256];
	int i = 0;
	while (stroka[i]) {
		i++;
		if (stroka[i] > 96 || stroka[i] < -1) {
			return "Ошибка";
		}
	}
	double number = pow(atof(stroka),2);
	sprintf(message, "%f", number);
	return message;
}



int main()
{
	system("chcp 1251");
	HANDLE hNamePipe;
	LPSTR pipeName = L"\\\\.\\pipe\\MyPipe";
	DWORD read_buffer = 100;
	LPWSTR buffer = calloc(read_buffer, sizeof(char));
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
				printf("\n");
				printf("\nВведите сообщение для клиента");
				sprintf(message, "%s", provekra(buffer));
				buffer = &message;
				WriteFile(hNamePipe, buffer, read_buffer, &actual_read, NULL);
			}
		}
		else
		{
			printf("\nКлиент отключился от сервера");
		}
		CloseHandle(hNamePipe);
	}
}


