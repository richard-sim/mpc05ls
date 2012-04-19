// mpc05ls.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "mpc05ls.h"
#include <stdio.h>


typedef	int		(MPC05LS_CC		*tM05_init_board)();
typedef	int		(MPC05LS_CC		*tM05_on_comm)(int ch);
typedef	int		(MPC05LS_CC		*tM05_open_link)(int ch, int rate);
typedef	int		(MPC05LS_CC		*tM05_close_file)();
typedef	int		(MPC05LS_CC		*tM05_close_link)(int ch);
typedef	int		(MPC05LS_CC		*tM05_compile_work_file)(char* filename);
typedef	int		(MPC05LS_CC		*tM05_create_file)(PBYTE filename, DWORD filelenbytes);
typedef	int		(MPC05LS_CC		*tM05_del_file)(int FileID);
typedef	int		(MPC05LS_CC		*tM05_del_all_file)();
typedef	int		(MPC05LS_CC		*tM05_download_work_file)(char* filename);
typedef	int		(MPC05LS_CC		*tM05_get_file_num)(int* CurFileID, int* FileNum);
typedef	int		(MPC05LS_CC		*tM05_open_file)(BYTE fileID, PDWORD filelen, PBYTE filename);
typedef	int		(MPC05LS_CC		*tM05_set_work_file)(char* file);
typedef	int		(MPC05LS_CC		*tM05_send_cmd)(DWORD dwDataLenDword, PDWORD pdwData);
typedef	int		(MPC05LS_CC		*tM05_control_func)(int FuncID);
typedef	int		(MPC05LS_CC		*tM05_get_board_info)(int* info);
typedef	DWORD	(MPC05LS_CC		*tM05_get_board_ver)();
typedef	DWORD	(MPC05LS_CC		*tM05_get_hdw_ver)();
typedef	DWORD	(MPC05LS_CC		*tM05_get_lib_ver)();
typedef	int		(MPC05LS_CC		*tM05_GetCardNumber)(int foofoo);
typedef	int		(MPC05LS_CC		*tM05_WriteDogNumber)(int foofoo);
typedef	int		(MPC05LS_CC		*tM05_ReadDogNumber)(int foofoo);
typedef	int		(MPC05LS_CC		*tM05_GetCanUseTime)();
typedef	int		(MPC05LS_CC		*tM05_SetCanUseTime)(int foofoo);
typedef	int		(MPC05LS_CC		*tM05_GetHasUseTime)();
typedef	int		(MPC05LS_CC		*tM05_SetHasUseTime)(int foofoo);
typedef	int		(MPC05LS_CC		*tM05_get_pre_worktime)(int foo);
typedef	int		(MPC05LS_CC		*tM05_write_data_to_flash)(int foo, int bar, int doo);
typedef	int		(MPC05LS_CC		*tM05_read_data_from_flash)(int foo, int bar, int doo);
typedef	int		(MPC05LS_CC		*tM05_erase_flash)(int foo, int bar);


struct tMPC05LS
{
	HMODULE						hDLL;
	FILE*						hLog;

	tM05_init_board				M05_init_board;
	tM05_on_comm				M05_on_comm;
	tM05_open_link				M05_open_link;
	tM05_close_file				M05_close_file;
	tM05_close_link				M05_close_link;
	tM05_compile_work_file		M05_compile_work_file;
	tM05_create_file			M05_create_file;
	tM05_del_file				M05_del_file;
	tM05_del_all_file			M05_del_all_file;
	tM05_download_work_file		M05_download_work_file;
	tM05_get_file_num			M05_get_file_num;
	tM05_open_file				M05_open_file;
	tM05_set_work_file			M05_set_work_file;
	tM05_send_cmd				M05_send_cmd;
	tM05_control_func			M05_control_func;
	tM05_get_board_info			M05_get_board_info;
	tM05_get_board_ver			M05_get_board_ver;
	tM05_get_hdw_ver			M05_get_hdw_ver;
	tM05_get_lib_ver			M05_get_lib_ver;
	tM05_GetCardNumber			M05_GetCardNumber;
	tM05_WriteDogNumber			M05_WriteDogNumber;
	tM05_ReadDogNumber			M05_ReadDogNumber;
	tM05_GetCanUseTime			M05_GetCanUseTime;
	tM05_SetCanUseTime			M05_SetCanUseTime;
	tM05_GetHasUseTime			M05_GetHasUseTime;
	tM05_SetHasUseTime			M05_SetHasUseTime;
	tM05_get_pre_worktime		M05_get_pre_worktime;
	tM05_write_data_to_flash	M05_write_data_to_flash;
	tM05_read_data_from_flash	M05_read_data_from_flash;
	tM05_erase_flash			M05_erase_flash;
};


tMPC05LS g_DLL = {NULL};


void Log(const char* fmt, ...)
{
	if (!g_DLL.hLog)
		return;

	const int bufferSize = 1024;
	char logEntry[bufferSize];

	va_list args;
	va_start(args, fmt);

	vsnprintf_s(logEntry, bufferSize, bufferSize-1, fmt, args);

	fprintf(g_DLL.hLog, "%s\n", logEntry);
	fflush(g_DLL.hLog);
}


void InitDLL()
{
	if (g_DLL.hDLL)
		return;

	if (fopen_s(&g_DLL.hLog, "C:\\Temp\\mpc05ls.log", "wt") != 0)
	{
		MessageBoxA(NULL, "Could not open activity log for writing!", "Error", MB_ICONERROR);
	}

	Log("Loading module to shadow...");
	g_DLL.hDLL = LoadLibraryA("mpc05lsX.dll");
	if (!g_DLL.hDLL)
	{
		Log("Could not load module!");
		MessageBoxA(NULL, "Could not load original DLL!", "Error", MB_ICONERROR);
		return;
	}

	Log("Looking up function addresses...");

	g_DLL.M05_init_board			= (tM05_init_board			)GetProcAddress(g_DLL.hDLL, "M05_init_board");
	g_DLL.M05_on_comm				= (tM05_on_comm				)GetProcAddress(g_DLL.hDLL, "M05_on_comm");
	g_DLL.M05_open_link				= (tM05_open_link			)GetProcAddress(g_DLL.hDLL, "M05_open_link");
	g_DLL.M05_close_file			= (tM05_close_file			)GetProcAddress(g_DLL.hDLL, "M05_close_file");
	g_DLL.M05_close_link			= (tM05_close_link			)GetProcAddress(g_DLL.hDLL, "M05_close_link");
	g_DLL.M05_compile_work_file		= (tM05_compile_work_file	)GetProcAddress(g_DLL.hDLL, "M05_compile_work_file");
	g_DLL.M05_create_file			= (tM05_create_file			)GetProcAddress(g_DLL.hDLL, "M05_create_file");
	g_DLL.M05_del_file				= (tM05_del_file			)GetProcAddress(g_DLL.hDLL, "M05_del_file");
	g_DLL.M05_del_all_file			= (tM05_del_all_file		)GetProcAddress(g_DLL.hDLL, "M05_del_all_file");
	g_DLL.M05_download_work_file	= (tM05_download_work_file	)GetProcAddress(g_DLL.hDLL, "M05_download_work_file");
	g_DLL.M05_get_file_num			= (tM05_get_file_num		)GetProcAddress(g_DLL.hDLL, "M05_get_file_num");
	g_DLL.M05_open_file				= (tM05_open_file			)GetProcAddress(g_DLL.hDLL, "M05_open_file");
	g_DLL.M05_set_work_file			= (tM05_set_work_file		)GetProcAddress(g_DLL.hDLL, "M05_set_work_file");
	g_DLL.M05_send_cmd				= (tM05_send_cmd			)GetProcAddress(g_DLL.hDLL, "M05_send_cmd");
	g_DLL.M05_control_func			= (tM05_control_func		)GetProcAddress(g_DLL.hDLL, "M05_control_func");
	g_DLL.M05_get_board_info		= (tM05_get_board_info		)GetProcAddress(g_DLL.hDLL, "M05_get_board_info");
	g_DLL.M05_get_board_ver			= (tM05_get_board_ver		)GetProcAddress(g_DLL.hDLL, "M05_get_board_ver");
	g_DLL.M05_get_hdw_ver			= (tM05_get_hdw_ver			)GetProcAddress(g_DLL.hDLL, "M05_get_hdw_ver");
	g_DLL.M05_get_lib_ver			= (tM05_get_lib_ver			)GetProcAddress(g_DLL.hDLL, "M05_get_lib_ver");
	g_DLL.M05_GetCardNumber			= (tM05_GetCardNumber		)GetProcAddress(g_DLL.hDLL, "M05_GetCardNumber");
	g_DLL.M05_WriteDogNumber		= (tM05_WriteDogNumber		)GetProcAddress(g_DLL.hDLL, "M05_WriteDogNumber");
	g_DLL.M05_ReadDogNumber			= (tM05_ReadDogNumber		)GetProcAddress(g_DLL.hDLL, "M05_ReadDogNumber");
	g_DLL.M05_GetCanUseTime			= (tM05_GetCanUseTime		)GetProcAddress(g_DLL.hDLL, "M05_GetCanUseTime");
	g_DLL.M05_SetCanUseTime			= (tM05_SetCanUseTime		)GetProcAddress(g_DLL.hDLL, "M05_SetCanUseTime");
	g_DLL.M05_GetHasUseTime			= (tM05_GetHasUseTime		)GetProcAddress(g_DLL.hDLL, "M05_GetHasUseTime");
	g_DLL.M05_SetHasUseTime			= (tM05_SetHasUseTime		)GetProcAddress(g_DLL.hDLL, "M05_SetHasUseTime");
	g_DLL.M05_get_pre_worktime		= (tM05_get_pre_worktime	)GetProcAddress(g_DLL.hDLL, "M05_get_pre_worktime");
	g_DLL.M05_write_data_to_flash	= (tM05_write_data_to_flash	)GetProcAddress(g_DLL.hDLL, "M05_write_data_to_flash");
	g_DLL.M05_read_data_from_flash	= (tM05_read_data_from_flash)GetProcAddress(g_DLL.hDLL, "M05_read_data_from_flash");
	g_DLL.M05_erase_flash			= (tM05_erase_flash			)GetProcAddress(g_DLL.hDLL, "M05_erase_flash");

	Log("Function address lookup complete.");
}


extern "C"
{
	int MPC05LS_CC M05_init_board()
	{
		InitDLL();

		Log(__FUNCTION__);
		if (g_DLL.M05_init_board)
			return (*g_DLL.M05_init_board)();
		return -1;
	}

	int MPC05LS_CC M05_on_comm(int ch)
	{
		InitDLL();

		Log("%s(%d)", __FUNCTION__, ch);
		if (g_DLL.M05_on_comm)
		{
			int res = (*g_DLL.M05_on_comm)(ch);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_open_link(int ch, int rate)
	{
		InitDLL();

		Log("%s(%d, %d)", __FUNCTION__, ch, rate);
		if (g_DLL.M05_open_link)
		{
			int res = (*g_DLL.M05_open_link)(ch, rate);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_close_file()
	{
		InitDLL();

		Log(__FUNCTION__);
		if (g_DLL.M05_close_file)
		{
			int res = (*g_DLL.M05_close_file)();
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_close_link(int ch)
	{
		InitDLL();

		Log("%s(%d)", __FUNCTION__, ch);
		if (g_DLL.M05_close_link)
		{
			int res = (*g_DLL.M05_close_link)(ch);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_compile_work_file(char* filename)
	{
		InitDLL();

		Log("%s(%s)", __FUNCTION__, filename);
		if (g_DLL.M05_compile_work_file)
		{
			int res = (*g_DLL.M05_compile_work_file)(filename);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_create_file(PBYTE filename, DWORD filelenbytes)
	{
		InitDLL();

		Log("%s(%s, %u)", __FUNCTION__, filename, filelenbytes);
		if (g_DLL.M05_create_file)
		{
			int res = (*g_DLL.M05_create_file)(filename, filelenbytes);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_del_file(int FileID)
	{
		InitDLL();

		Log("%s(%d)", __FUNCTION__, FileID);
		if (g_DLL.M05_del_file)
		{
			int res = (*g_DLL.M05_del_file)(FileID);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_del_all_file()
	{
		InitDLL();

		Log(__FUNCTION__);
		if (g_DLL.M05_del_all_file)
		{
			int res = (*g_DLL.M05_del_all_file)();
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_download_work_file(char* filename)
	{
		InitDLL();

		Log("%s(%s)", __FUNCTION__, filename);
		if (g_DLL.M05_download_work_file)
		{
			int res = (*g_DLL.M05_download_work_file)(filename);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_get_file_num(int* CurFileID, int* FileNum)
	{
		InitDLL();

		Log(__FUNCTION__);
		if (g_DLL.M05_get_file_num)
		{
			int res = (*g_DLL.M05_get_file_num)(CurFileID, FileNum);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_open_file(BYTE fileID, PDWORD filelen, PBYTE filename)
	{
		InitDLL();

		Log("%s(%d, %s)", __FUNCTION__, fileID, filename);
		if (g_DLL.M05_open_file)
		{
			int res = (*g_DLL.M05_open_file)(fileID, filelen, filename);
			Log("\tResult: %d (%u, %s)", res, *filelen, filename);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_set_work_file(char* file)
	{
		InitDLL();

		Log("%s(%s)", __FUNCTION__, file);
		if (g_DLL.M05_set_work_file)
		{
			int res = (*g_DLL.M05_set_work_file)(file);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_send_cmd(DWORD dwDataLenDword, PDWORD pdwData)
	{
		InitDLL();

		Log(__FUNCTION__);
		if (g_DLL.M05_send_cmd)
		{
			int res = (*g_DLL.M05_send_cmd)(dwDataLenDword, pdwData);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_control_func(int FuncID)
	{
		InitDLL();

		Log("%s(%d)", __FUNCTION__, FuncID);
		if (g_DLL.M05_control_func)
		{
			int res = (*g_DLL.M05_control_func)(FuncID);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_get_board_info(int* info)
	{
		InitDLL();

		Log(__FUNCTION__);
		if (g_DLL.M05_get_board_info)
		{
			int res = (*g_DLL.M05_get_board_info)(info);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	DWORD MPC05LS_CC M05_get_board_ver()
	{
		InitDLL();

		Log(__FUNCTION__);
		if (g_DLL.M05_get_board_ver)
		{
			DWORD res = (*g_DLL.M05_get_board_ver)();
			Log("\tResult: %u", res);
			return res;
		}
		return ~0u;
	}

	DWORD MPC05LS_CC M05_get_hdw_ver()
	{
		InitDLL();

		Log(__FUNCTION__);
		if (g_DLL.M05_get_hdw_ver)
		{
			DWORD res = (*g_DLL.M05_get_hdw_ver)();
			Log("\tResult: %u", res);
			return res;
		}
		return ~0u;
	}

	DWORD MPC05LS_CC M05_get_lib_ver()
	{
		InitDLL();

		Log(__FUNCTION__);
		if (g_DLL.M05_get_lib_ver)
		{
			DWORD res = (*g_DLL.M05_get_lib_ver)();
			Log("\tResult: %u", res);
			return res;
		}
		return ~0u;
	}

	int MPC05LS_CC M05_GetCardNumber(int foofoo)
	{
		InitDLL();

		Log(__FUNCTION__);
		if (g_DLL.M05_GetCardNumber)
		{
			int res = (*g_DLL.M05_GetCardNumber)(foofoo);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_WriteDogNumber(int foofoo)
	{
		InitDLL();

		Log(__FUNCTION__);
		if (g_DLL.M05_WriteDogNumber)
		{
			int res = (*g_DLL.M05_WriteDogNumber)(foofoo);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_ReadDogNumber(int foofoo)
	{
		InitDLL();

		Log(__FUNCTION__);
		if (g_DLL.M05_ReadDogNumber)
		{
			int res = (*g_DLL.M05_ReadDogNumber)(foofoo);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_GetCanUseTime()
	{
		InitDLL();

		Log(__FUNCTION__);
		if (g_DLL.M05_GetCanUseTime)
		{
			int res = (*g_DLL.M05_GetCanUseTime)();
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_SetCanUseTime(int foofoo)
	{
		InitDLL();

		Log(__FUNCTION__);
		if (g_DLL.M05_SetCanUseTime)
		{
			int res = (*g_DLL.M05_SetCanUseTime)(foofoo);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_GetHasUseTime()
	{
		InitDLL();

		Log(__FUNCTION__);
		if (g_DLL.M05_GetHasUseTime)
		{
			int res = (*g_DLL.M05_GetHasUseTime)();
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_SetHasUseTime(int foofoo)
	{
		InitDLL();

		Log(__FUNCTION__);
		if (g_DLL.M05_SetHasUseTime)
		{
			int res = (*g_DLL.M05_SetHasUseTime)(foofoo);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_get_pre_worktime(int foo)
	{
		InitDLL();

		Log(__FUNCTION__);
		if (g_DLL.M05_get_pre_worktime)
		{
			int res = (*g_DLL.M05_get_pre_worktime)(foo);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_write_data_to_flash(int foo, int bar, int doo)
	{
		InitDLL();

		Log(__FUNCTION__);
		if (g_DLL.M05_write_data_to_flash)
		{
			int res = (*g_DLL.M05_write_data_to_flash)(foo, bar, doo);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_read_data_from_flash(int foo, int bar, int doo)
	{
		InitDLL();

		Log(__FUNCTION__);
		if (g_DLL.M05_read_data_from_flash)
		{
			int res = (*g_DLL.M05_read_data_from_flash)(foo, bar, doo);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}

	int MPC05LS_CC M05_erase_flash(int foo, int bar)
	{
		InitDLL();

		Log(__FUNCTION__);
		if (g_DLL.M05_erase_flash)
		{
			int res = (*g_DLL.M05_erase_flash)(foo, bar);
			Log("\tResult: %d", res);
			return res;
		}
		return -1;
	}
}
