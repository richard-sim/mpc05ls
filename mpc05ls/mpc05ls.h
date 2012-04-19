// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MPC05LS_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MPC05LS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MPC05LS_EXPORTS
#define MPC05LS_API __declspec(dllexport)
#else
#define MPC05LS_API __declspec(dllimport)
#endif

#define MPC05LS_CC	WINAPI

#ifdef __cplusplus
extern "C"
#endif
{
	MPC05LS_API		int		MPC05LS_CC		M05_init_board();
	MPC05LS_API		int		MPC05LS_CC		M05_on_comm(int ch);
	MPC05LS_API		int		MPC05LS_CC		M05_open_link(int ch, int rate);
	MPC05LS_API		int		MPC05LS_CC		M05_close_file();
	MPC05LS_API		int		MPC05LS_CC		M05_close_link(int ch);
	MPC05LS_API		int		MPC05LS_CC		M05_compile_work_file(char* filename);
	MPC05LS_API		int		MPC05LS_CC		M05_create_file(PBYTE filename, DWORD filelenbytes);
	MPC05LS_API		int		MPC05LS_CC		M05_del_file(int FileID);
	MPC05LS_API		int		MPC05LS_CC		M05_del_all_file();
	MPC05LS_API		int		MPC05LS_CC		M05_download_work_file(char* filename);
	MPC05LS_API		int		MPC05LS_CC		M05_get_file_num(int* CurFileID, int* FileNum);
	MPC05LS_API		int		MPC05LS_CC		M05_open_file(BYTE fileID, PDWORD filelen, PBYTE filename);
	MPC05LS_API		int		MPC05LS_CC		M05_set_work_file(char* file);
	MPC05LS_API		int		MPC05LS_CC		M05_send_cmd(DWORD dwDataLenDword, PDWORD pdwData);
	MPC05LS_API		int		MPC05LS_CC		M05_control_func(int FuncID);
	MPC05LS_API		int		MPC05LS_CC		M05_get_board_info(int* info);
	MPC05LS_API		DWORD	MPC05LS_CC		M05_get_board_ver();
	MPC05LS_API		DWORD	MPC05LS_CC		M05_get_hdw_ver();
	MPC05LS_API		DWORD	MPC05LS_CC		M05_get_lib_ver();
	MPC05LS_API		int		MPC05LS_CC		M05_GetCardNumber(int foofoo);
	MPC05LS_API		int		MPC05LS_CC		M05_WriteDogNumber(int foofoo);
	MPC05LS_API		int		MPC05LS_CC		M05_ReadDogNumber(int foofoo);
	MPC05LS_API		int		MPC05LS_CC		M05_GetCanUseTime();
	MPC05LS_API		int		MPC05LS_CC		M05_SetCanUseTime(int foofoo);
	MPC05LS_API		int		MPC05LS_CC		M05_GetHasUseTime();
	MPC05LS_API		int		MPC05LS_CC		M05_SetHasUseTime(int foofoo);
	MPC05LS_API		int		MPC05LS_CC		M05_get_pre_worktime(int foo);
	MPC05LS_API		int		MPC05LS_CC		M05_write_data_to_flash(int foo, int bar, int doo);
	MPC05LS_API		int		MPC05LS_CC		M05_read_data_from_flash(int foo, int bar, int doo);
	MPC05LS_API		int		MPC05LS_CC		M05_erase_flash(int foo, int bar);
#ifdef __cplusplus
}
#endif
