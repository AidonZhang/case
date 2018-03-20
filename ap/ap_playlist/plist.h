/*******************************************************************************
 *                              US212A
 *                            Module: PLAYLSIT
 *                 Copyright(c) 2003-2011 Actions Semiconductor,
 *                            All Rights Reserved.
 *
 * History:
 *      <author>    <time>           <version >             <desc>
 *       liminxian  2011-9-15 15:37    1.0             build this file
 *******************************************************************************/
/*!
 * \file     en_lrc.h
 * \brief    ���ݽṹ�ͳ�������
 * \author   liminxian
 * \version 1.0
 * \date  2011/09/15
 *******************************************************************************/

#ifndef _plist_h

#define _plist_h

#include <typeext.h>
#include <enhanced.h>

#include "psp_includes.h"
#include "case_include.h"
#include "playlist_sty.h"
#include "playlist_res.h"

//ϵͳĬ�ϴ����ļ�ʹ�ó���
//#define USE_83NAME_CREAT  //�����ļ�ʹ�ö�������

//#define DEBUG_PRINT   //��ӡ����

//ϵͳĬ�������б��ļ�LIB,debugʱ�ȹر�
#define  HIDE_FILE_OPT

//APP����
#define APP_TIMER_COUNT		1
#define APP_TIMER_TOTAL     (COMMON_TIMER_COUNT + APP_TIMER_COUNT)

/*!����playlistӦ�õ�����ջ�����߳����ȼ�*/
#define AP_PLAYLIST_STK_POS  AP_FRONT_LOW_STK_POS
#define AP_PLAYLIST_PRIO     AP_FRONT_LOW_PRIO
#define TRACK_SUPPORT 1
#ifdef PC
#define PLIST_SYS_DEF_SPACE
#endif //#ifdef PC

#ifdef  PLIST_SYS_DEF_SPACE
extern uint8 sys_sdram_space[0x20000];//128k
#define SYS_SRAM_ADDRESS            sys_sdram_space
#else //#ifdef PLIST_SYS_DEF_SPACE

/*����ʹ�õĿռ����0x20a00-0x40000*/
#define SYS_SRAM_BOTTOM_ADDRESS     0x9fc20A00
#define SYS_SRAM_TOP_ADDRESS        0x9fc40000
#endif//#ifdef PLIST_SYS_DEF_SPACE
                               
//0---GERN->ARTIST->ALBUM->TITLE
//1---GERN->ALBUM->TITLE
#define GENRE_LIST_MODE             0

//find file mode
//#define ENHANCED_FIND_MODE

//�б�������
//������С����
#define SECTOR_SIZE                 512

//0-->֧��4000������
//1-->֧��6000������
#define SORT_MUSIC_MAX  			0//Ĭ��6000������
#if (SORT_MUSIC_MAX == 1)
#define MUSIC_MAX 					4000
#else
#define MUSIC_MAX 					16000//6000
#endif
#define MAX_NUM_8K                 (8000)
#define MAX_NUM_6K                 (6000)
#define MAX_NUM_4K                 (4000)
//�б�֧������ɨ�����
#define PLIST_MUSIC_MAX             MUSIC_MAX
#define PLIST_AUDIBLE_MAX           1000

/*
 *! ÿ��ID3 TAG������򳤶� ��Ӧplist_f_info_t�ṹ
 */
#define TITLE_CMP_LENGTH        24//    ID3_TITLE_SIZE//����ܴ���title string����
#define ALBUM_CMP_LENGTH            24//ID3_ALBUM_SIZE//����ܴ���album string����
#define ARTIST_CMP_LENGTH          24// ID3_ARTIST_SIZE//����ܴ���artist string����
#define GENRE_CMP_LENGTH        24//    ID3_GENRE_SIZE//����ܴ���genre string����
#define TRACK_CMP_LENGTH            1 //��ǰ֧��track һ��byte�Ƚ�

/*
 *! ÿ��TAG��plist_f_info_t�е�ƫ��λ��
 */
 #define ID3_TITLE_OFFSET           (0)
 #define ID3_ARTIST_OFFSET          (ID3_TITLE_SIZE)
 #define ID3_ALBUM_OFFSET           (ID3_TITLE_SIZE + ID3_ARTIST_SIZE)
 #define ID3_GENRE_OFFSET           (ID3_TITLE_SIZE + ID3_ARTIST_SIZE + ID3_ALBUM_SIZE)
 
/*
 *! ram��buffer�ռ����
 */
//#if (MUSIC_MAX == 4000)
#define SORT_BUFFER_SIZE            0x10000//64k
#define INDEX_BUFFER_SIZE           0x2000//8K
#define FILE_INFO_BUF_SIZE          0x2000//8k
#define TRACK_BUFFER_SIZE           0X1000//4k track����ռ�
/*#endif
#if(MUSIC_MAX == 6000)//(MUSIC_MAX == 6000)
#define SORT_BUFFER_SIZE            0xD400//0xD400 //53k=54274>9*6000
#define INDEX_BUFFER_SIZE           0x3000//0x3000//12K
#define FILE_INFO_BUF_SIZE          0x2000//8k
#define TRACK_BUFFER_SIZE           0x1800//0X1800//6k track����ռ�
#endif
#if (MUSIC_MAX == 8000)
#define SORT_BUFFER_SIZE            0x7400//0xD400 //53k=54274>9*6000
#define INDEX_BUFFER_SIZE           0x4000//0x3000//12K
#define FILE_INFO_BUF_SIZE          0x2000//8k
#define TRACK_BUFFER_SIZE           0x2000//0X1800//6k track����ռ�
#endif
*/
/*
*! creat�ļ���С
*/
#define MUSIC_LIB_SIZE  	        ((PLIST_MUSIC_MAX + PLIST_MUSIC_MAX/4)* SECTOR_SIZE + SORT_BUFFER_SIZE)
#define AUDIBLE_LIB_SIZE            ((PLIST_AUDIBLE_MAX/2 + PLIST_AUDIBLE_MAX/4) * SECTOR_SIZE)
#define M3U_LIB_SIZE                (M3U_LIST_SIZE + M3U_DAT_SIZE + SORT_BUFFER_SIZE)
#define USERPL_PL_SIZE              (SECTOR_SIZE + USERPL_FILE_MAX * USERPL_FILE_SIZE)
#define ALBUM_PIC_SIZE              (250*SECTOR_SIZE)

/*
 *!  LIB�ļ��п���ʹ�õĿռ�[64K]
 */
#define STORE_MUSIC_ADDR            ((PLIST_MUSIC_MAX + PLIST_MUSIC_MAX/4) * SECTOR_SIZE)//0x271000
#define TITLE_SORT_INDEX_VM_ADDR    (STORE_MUSIC_ADDR + 0*INDEX_BUFFER_SIZE) 
#define ALBUM_SORT_INDEX_VM_ADDR    (STORE_MUSIC_ADDR + 1*INDEX_BUFFER_SIZE) 
#define ARTIST_SORT_INDEX_VM_ADDR   (STORE_MUSIC_ADDR + 2*INDEX_BUFFER_SIZE) 
#define TIDY_BUF_A_VM_ADDR          (STORE_MUSIC_ADDR + 3*INDEX_BUFFER_SIZE) 
#define TIDY_BUF_B_VM_ADDR          (STORE_MUSIC_ADDR + 4*INDEX_BUFFER_SIZE) 

//OTHERS
#define STORE_OTHERS_ADDR           (M3U_LIST_SIZE + M3U_DAT_SIZE)
#define OTHERS_TITLE_ADDR           (STORE_OTHERS_ADDR + 0x0000)//64K

/*
 *! ɨ���ļ�ʱ��SRAM �Ĵ洢��ַ�ռ�ֲ�  SRAM�ռ�[0x20a00-0x3ffff]125k
 *! TRACK_DATA_ADDR����COUNT_BUF_B_ADDRǰ4K�ռ�,COUNT_BUF_B_ADDR������
 *! artistʱ��ʹ�ã�����������album��ʹ��
 */
#define PLIST_DATA_BASE_ADDR        SYS_SRAM_BOTTOM_ADDRESS
#define PLIST_DATA_TOP_ADDR         SYS_SRAM_TOP_ADDRESS

#define FILE_INFO_ADDR              (PLIST_DATA_BASE_ADDR + 0x0000)//8K
#define SORT_DATA_ADDR              (SYS_SRAM_TOP_ADDRESS - SORT_BUFFER_SIZE)

#define FILE_INDEX_BUF_ADDR        (PLIST_DATA_BASE_ADDR + 0*INDEX_BUFFER_SIZE)
#define SORT_INDEX_BUF_ADDR        (PLIST_DATA_BASE_ADDR + 1*INDEX_BUFFER_SIZE)
#define TIDY_BUF_A_ADDR            (PLIST_DATA_BASE_ADDR + 2*INDEX_BUFFER_SIZE)
#define COUNT_BUF_A_ADDR           (PLIST_DATA_BASE_ADDR + 3*INDEX_BUFFER_SIZE)
#define TIDY_BUF_B_ADDR            (PLIST_DATA_BASE_ADDR + 4*INDEX_BUFFER_SIZE)
#define COUNT_BUF_B_ADDR           (PLIST_DATA_BASE_ADDR + 5*INDEX_BUFFER_SIZE)
//#if (MUSIC_MAX == 4000)
#define COUNT_BUF_C_ADDR           (PLIST_DATA_BASE_ADDR + 6*INDEX_BUFFER_SIZE)
//#endif
#define TRACK_DATA_ADDR            (COUNT_BUF_B_ADDR + TRACK_BUFFER_SIZE)

typedef struct {

	
	uint32 sort_buf_size;
	uint16 index_buf_size;
	uint16 file_info_buf_size;
	uint16 track_buf_size;

	uint8  title_cmp_lenth;
	uint8  album_cmp_lenth;
	uint8  artist_cmp_lenth;
	uint8  genre_cmp_lenth;
	uint8  track_cmp_lenth;

	uint32   music_lib_size;
	uint32   audible_lib_size;
	uint32   m3u_lib_size;
	uint32   userpl_pl_size;
	uint16   album_pic_size;

	uint32  store_music_addr;
	uint32  title_sort_index_vm_addr;
	uint32  album_sort_index_vm_addr;
	uint32  artist_sort_index_vm_addr;
	uint32  tidy_buf_a_vm_addr;
	uint32  tidy_buf_b_vm_addr;

  uint32 store_others_addr;
  uint32 others_title_addr;

	uint32 plist_data_base_addr;
	uint32 plist_data_top_addr;


	uint32 file_info_addr;
	uint32 sort_data_addr;

	
	uint32  file_index_buf_addr;
  uint32  sort_index_buf_addr;
  uint32  tidy_buf_a_addr;
  uint32  count_buf_a_addr;
  uint32  tidy_buf_b_addr;
  uint32  count_buf_b_addr;
  uint8*   track_data_addr; 
  uint16*  count_buf_c_addr;
    
}sorting_map_level;

/*��������< = 4000��ʱ���õ��ڴ����*/
extern sorting_map_level sorting_mem_4k;
/*��������< = 8000��ʱ���õ��ڴ����*/
extern sorting_map_level sorting_mem_8k;
/*��ǰ�õ��ڴ����*/
extern sorting_map_level sorting_mem_cur;

#define MP1_VAL   				   ('M' + 'P'*0x100 + '1'*0x10000)
#define MP3_VAL   				   ('M' + 'P'*0x100 + '3'*0x10000)
#define MP2_VAL   				   ('M' + 'P'*0x100 + '2'*0x10000)
#define WMA_VAL   				   ('W' + 'M'*0x100 + 'A'*0x10000)
#define ASF_VAL   				   ('A' + 'S'*0x100 + 'F'*0x10000)
#define WMV_VAL   				   ('W' + 'M'*0x100 + 'V'*0x10000)
#define AAX_VAL   				   ('A' + 'A'*0x100 + 'X'*0x10000)
#define M4A_VAL   				   ('M' + '4'*0x100 + 'A'*0x10000)
#define AA_VAL    				   ('A' + 'A'*0x100 + ' '*0x10000)//aa + �ո�
#define OGG_VAL   				   ('O' + 'G'*0x100 + 'G'*0x10000)
#define AAC_VAL   				   ('A' + 'A'*0x100 + 'C'*0x10000)
#define FLAC_VAL  				   ('F' + 'L'*0x100 + 'A'*0x10000)
#define APE_VAL   				   ('A' + 'P'*0x100 + 'E'*0x10000)

#define  TRACK_NULL      		   0xffff
#define  UNICODE_FLAG    		   0xfeff

#define  UTF8_FLAG_0    		   0xef
#define  UTF8_FLAG_1   			   0xbb
#define  UTF8_FLAG_2   			   0xbf

//compare
#define CMPSTR_MAX_BUF		  	   100//�����ʵ���С��ע�����

//ð���������
#define CUTOFF  				   8

//��������
#define PL_BUILD_MUSIC             0x01
#define PL_BUILD_AUDIBLE           0x02
#define PL_BUILD_M3U               0x04
#define PL_BUILD_ALL               0x07

//compare functions
typedef enum
{
    SORT_CMP_WORD = 0, 
    SORT_CMP_ALBUM, 
    SORT_CMP_STRING
} sort_cmp_type_e;

//ͬ��main_menu.h����

typedef struct
{
    uint16 active_item;//�AP�˵�����
    uint16 total_item; //AP�˵�����
    uint16 ap_id[MAX_APP_NUM]; //֧��Ӧ�ñ�ŵ�����
} cfg_mainmenu_var_t;

typedef struct
{
    uint16 magic; //VM ����ħ��
    cfg_mainmenu_var_t cfg_var;
    uint16 file_num[MAX_APP_NUM];//ÿ��Ӧ�õ��ļ�����
} g_mainmenu_var_t;

typedef signed char(*cmp_obj_f)(uint16 *data1, uint16 *data2, uint8 len);

//�ļ�λ�ýṹ
typedef struct
{    
    uint32 cluster_no;                    //�ļ�Ŀ¼�����ڴغ�
    uint32 dir_entry;                     //�ļ���Ŀ¼���ڵ�ǰ���ڵ�ƫ��    
} file_pos_t; // 

#ifdef SUPPORT_PLT_DEBUG
#define plt_print(str, data, mode)   libc_print(str,data,mode) 
#else
#define plt_print(str, data, mode)
#endif

extern bool plist_fsel_get_nextfile (char *strfile) __FAR__;
extern void copy_deal_string(char* dest, char* source, uint8 land_id, uint8 size);
extern void list_sort(char* base, uint16 num, uint16 width, void* depond_buf, uint8 cmp_type, uint8 cmp_len) __FAR__;
extern bool save_to_file(uint8 *data_buf,uint32 len) __FAR__;
extern app_result_e plist_get_app_msg(void) __FAR__;
extern void plist_reflash_progress(uint8 prog_value) __FAR__;
extern signed char compare_string(uint16 *data1,uint16 *data2,uint8 len) __FAR__;
extern signed char compare_word(uint16 *data1,uint16 *data2,uint8 len) __FAR__;
extern signed char compare_album_track(uint16 *data1,uint16 *data2,uint8 len) __FAR__;
extern bool read_string(uint16* index_buf, uint16 index_num, char* buf, uint8 offset, uint8 len, plist_type_e type);
extern void init_sys_data(uint8 type)__FAR__;
extern  void init_mem_by_songs_num(void)__FAR__;
extern void init_mem_by_songs_16k(void)__FAR__;

extern void _init_sorting_map_level_8k(void)__FAR__ ;
extern void _init_sorting_map_level_4k(void)__FAR__ ;
extern void _init_sorting_map_level_16k(void)__FAR__;
extern  void set_sorting_level(void)__FAR__;

extern sorting_map_level      sorting_map_level_4k;
extern sorting_map_level      sorting_map_level_8k;
extern sorting_map_level      sorting_map_level_16k;
extern sorting_map_level*     sorting_map_level_cur;
#endif
