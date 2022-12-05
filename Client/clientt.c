#define _CRT_SECURE_NO_WARNINGS
#include <Stdio.h>
#include <Windows.h>
int main()
{
	system("chcp 1251");
	BOOL flag_awser = TRUE;
	char message[100];
	DWORD read_buffer = 100;
	DWORD actual_read;
	DWORD actual_write;
	LPWSTR buffer = calloc(read_buffer, sizeof(char));
	HANDLE hNamePipe;
	LPSTR pipeName = L"";
	BOOL SuccessRead;
	BOOL isSuccess;
	DWORD dwMode = PIPE_READMODE_MESSAGE;
	while (1)
	{
		
		hNamePipe = CreateFile(pipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		isSuccess = SetNamedPipeHandleState(hNamePipe, &dwMode, NULL, NULL);
		if (!isSuccess) {
			printf("\nСервер не отвечает\n");
			flag_awser = TRUE;
		}
		else
		{
			if (flag_awser) {
				printf("Введите сообщение для сервера:\n");
				gets(message);
				buffer = &message;
				WriteFile(hNamePipe, buffer, read_buffer, &actual_write, NULL);
				flag_awser = FALSE;
			}
			SuccessRead = ReadFile(hNamePipe, buffer, 100, &actual_read, NULL);
			if (SuccessRead) {
				printf("\n Сервер пишет: ");
				printf(buffer);
				printf("\n");
				flag_awser = TRUE;
				if (buffer == NULL)
					printf("Пусто");
			}
		}
		Sleep(100);
		CloseHandle(hNamePipe);
	}
}



