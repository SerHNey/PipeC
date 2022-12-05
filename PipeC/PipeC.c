#include <Stdio.h>
#include <Windows.h>
int main()
{
	system("chcp 1251");
	while (1)
	{
		HANDLE hNamePipe;
		LPSTR pipeName = L"";
		hNamePipe = CreateNamedPipe(pipeName, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 512, 512, INFINITE, NULL);

		BOOL Connected = ConnectNamedPipe(hNamePipe, NULL);
		if (Connected) {
			printf("\nКлиент подключился\n");
			DWORD read_buffer = 100;
			LPWSTR buffer = calloc(read_buffer, sizeof(char));

			DWORD actual_read;
			BOOL SuccessRead = ReadFile(hNamePipe, buffer, read_buffer, &actual_read, NULL);
			if (!SuccessRead)
				printf("\nКлиент отключился");

			printf(buffer);
			CloseHandle(hNamePipe);
		}
	}

}


