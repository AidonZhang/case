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
 * \file     *.c
 * \brief    ������д�ļ��ĸ���
 * \author   liminxian
 * \par      GENERAL DESCRIPTION:
 *               ������ļ���������
 * \par      EXTERNALIZED FUNCTIONS:
 *               �����������õ������ģ��
 * \version 1.0
 * \date  2011/9/15
 *******************************************************************************/
#include "plist.h"
#include "plist_8k.h"
#include "plist_16k.h"


#include "rdata_ex.h"

static void sort_album(char *str_buf);
static void sort_artist(char *str_buf);
static void sort_title(char *str_buf);
static void sort_genre(char *str_buf);
extern void init_file_index(void) __FAR__;
extern void build_ex_index(uint16 *ex_buf) __FAR__;
extern void tidy_same_table(uint16 *tidy_buf, uint16 *record_buf, uint16 *index_buf) __FAR__;
extern void son_sort_index(uint16 *data_buf,uint16 *count_buf,uint16 *depend_buf,uint8 cmp_type) __FAR__;
extern void tidy_son_unit(uint16 *record_buf,uint16 *data_buf,uint16 *same_buf,uint16 *depend_buf) __FAR__;
extern bool creat_index_map(uint16 *map_buf,uint16 *index_buf,uint16 *count_buf) __FAR__;
extern uint16* tidy_son_table(uint16 *data_buf,uint16 *record_buf,uint16 count,uint16 *depend_buf) __FAR__;
extern bool write_to_file(uint8* dest, uint8* source, uint32 len) __FAR__;
extern bool read_from_file(uint8* source, uint8* dest, uint32 len) __FAR__;
extern bool list_resort(uint16* index_buf, uint16 index_num, char* str_buf, plist_type_e type, uint8 resort_len, uint8 len) __FAR__;
extern uint16 creat_plist_tree(uint16 *index_buf,uint16 *cur_buf,uint16 *son_buf,uint16 *parent_buf,uint8 type) __FAR__;
extern void debug_printf(plist_type_e type);

/******************************************************************************/
/*
 * \par  Description: ����title �б�
 *
 * \param[in]    str_buf--�������ݻ����ַ

 * \param[out]

 * \return

 * \note
 *******************************************************************************/
//music ��һ����
static void sort_title(char *str_buf)
{    
    init_file_index();
		
		
	/*sort the first str_len of string datas*/
	  //libc_print("cmp_len",sort_cmp_len,2);
    list_sort((char*) file_index_buf, sort_file_total, 2, str_buf, SORT_CMP_STRING, sort_cmp_len);
    plist_get_app_msg();

    list_resort(file_index_buf, sort_file_total, str_buf, PLIST_TITLE, (sorting_map_level_cur->title_cmp_lenth), sort_cmp_len);

#ifdef DEBUG_PRINT
    debug_printf(PLIST_TITLE);
#endif

    //������title����������buffer����Ϊ��title������������
    //libc_memset(sort_index_buf, 0, INDEX_BUFFER_SIZE); 
    build_ex_index(sort_index_buf); 

    ap_file_index_offset[0] = ap_pos_file_offset;
    save_to_file((uint8*) file_index_buf, sort_file_total * 2);

    ap_sort_index_offset[0] = ap_pos_file_offset;
    save_to_file((uint8*) sort_index_buf, sort_file_total * 2);

    //���������Ƿ�����ļ�
    if(ap_plist_sorting_level == 16000){
        write_to_file((uint8*)TITLE_SORT_INDEX_VM_ADDR_16k,(uint8*)sort_index_buf,sort_file_total*2);
    }
    return;
}

/******************************************************************************/
/*
 * \par  Description: ���� album �б�
 *
 * \param[in]    str_buf--�������ݻ����ַ

 * \param[out]

 * \return

 * \note
 *******************************************************************************/
//music �ڶ�����
//album->title
static void sort_album(char *str_buf)
{
    uint8 str_len;
    
    init_file_index();
    str_len = sort_cmp_len;
    if (str_len > (sorting_map_level_cur->album_cmp_lenth))
    {
        str_len = (sorting_map_level_cur->album_cmp_lenth);
    }
    /*read string datas from mmusic.lib for sorting*/
    read_string(file_index_buf, sort_file_total, str_buf, 0, str_len, PLIST_ALBUM);
    plist_get_app_msg();
    
    /*sort the first str_len of string datas*/
    list_sort((char*) file_index_buf, sort_file_total, 2, str_buf, SORT_CMP_STRING, str_len);
    plist_get_app_msg();

    list_resort(file_index_buf, sort_file_total, str_buf, PLIST_ALBUM, (sorting_map_level_cur->album_cmp_lenth), str_len);
    
#ifdef DEBUG_PRINT
    debug_printf(PLIST_ALBUM);
#endif
    if(ap_plist_sorting_level != 16000)
	   { 
	     tidy_same_table(tidy_buf_a, count_buf_a, file_index_buf);//8+8+8
	   }
	   else{
			  tidy_same_table(NULL, count_buf_a, file_index_buf);//8+8
			    sort_index_buf	    = (uint16*) COUNT_BUF_B_ADDR_16k; 
			  read_from_file((uint8 *)sort_index_buf, (uint8 *)TITLE_SORT_INDEX_VM_ADDR_16k, sort_file_total*2);
		    read_from_file((uint8 *)(sorting_map_level_16k.track_data_addr), (uint8 *)ALBUM_SORT_INDEX_VM_ADDR_16k, sort_file_total);

	   }
   
    son_sort_index(file_index_buf, count_buf_a, sort_index_buf, SORT_CMP_ALBUM);

    ap_son_tree_offset[1][0] = ap_pos_file_offset;
    ap_son_tree_num[1][0] = creat_plist_tree(file_index_buf, count_buf_a, NULL, NULL, PLIST_ALBUM);

    build_ex_index(sort_index_buf);
     ap_file_index_offset[1] = ap_pos_file_offset;
    save_to_file((uint8*) file_index_buf, sort_file_total * 2);

    ap_sort_index_offset[1] = ap_pos_file_offset;
    save_to_file((uint8*) sort_index_buf, sort_file_total * 2);

    index_parent_buf = (uint16*) (sorting_map_level_cur->count_buf_c_addr);//�ռ临�ã�ע��

    creat_index_map(index_parent_buf, file_index_buf, count_buf_a);

   

    ap_index_parent_offset[1] = ap_pos_file_offset;
    save_to_file((uint8*) index_parent_buf, sort_file_total * 2);
    
    /*
	    if (( ap_plist_sorting_level == 4000) && ((MUSIC_MAX == 8000) || (GENRE_LIST_MODE == 1)))
	    //���������Ƿ�����ļ�
		  {  
		      write_to_file((uint8*)(sorting_map_level_cur->album_sort_index_vm_addr), (uint8*)sort_index_buf, sort_file_total*2);
		  }
	  */

    return;
}

/******************************************************************************/
/*
 * \par  Description: ���� artist �б�
 *
 * \param[in]    str_buf--�������ݻ����ַ

 * \param[out]

 * \return

 * \note
 *******************************************************************************/
//music ��������
//artist->album->title
static void sort_artist(char *str_buf)
{
    uint8 str_len;
    
    init_file_index();
    
    str_len = sort_cmp_len;
    if (str_len > (sorting_map_level_cur->artist_cmp_lenth))
    {
        str_len = (sorting_map_level_cur->artist_cmp_lenth);
    }
    
    /*read string datas from mmusic.lib for sorting*/
    read_string(file_index_buf, sort_file_total, str_buf, 0, str_len, PLIST_ARTIST);
    plist_get_app_msg();

    /*sort the first str_len of string datas*/
    list_sort((char*) file_index_buf, sort_file_total, 2, str_buf, SORT_CMP_STRING, str_len);
    plist_get_app_msg();
    

    list_resort(file_index_buf, sort_file_total, str_buf, PLIST_ARTIST, (sorting_map_level_cur->artist_cmp_lenth), str_len);

#ifdef DEBUG_PRINT
    debug_printf(PLIST_ARTIST);
#endif

		if(ap_plist_sorting_level == 4000)
		{
		    tidy_same_table(tidy_buf_b, count_buf_a, file_index_buf);

		}else{   
		     tidy_same_table(NULL, count_buf_a, file_index_buf);//8+8+8
		}

    son_sort_index(file_index_buf, count_buf_a, sort_index_buf, SORT_CMP_WORD);
    tidy_son_unit(count_buf_b, file_index_buf, count_buf_a, tidy_buf_a);
    build_ex_index(sort_index_buf);

    ap_son_tree_offset[2][0] = ap_pos_file_offset;
    ap_son_tree_num[2][0] = creat_plist_tree(file_index_buf, count_buf_a, count_buf_b, NULL, PLIST_ARTIST);
    ap_son_tree_offset[2][1] = ap_pos_file_offset;
    ap_son_tree_num[2][1] = creat_plist_tree(file_index_buf, count_buf_b, NULL, count_buf_a, PLIST_ALBUM);

    index_parent_buf = (uint16*) (sorting_map_level_cur->count_buf_a_addr); //�ռ临�ã�ע��
    creat_index_map(index_parent_buf, file_index_buf, count_buf_b);

    ap_file_index_offset[2] = ap_pos_file_offset;
    save_to_file((uint8*) file_index_buf, sort_file_total * 2);

    ap_sort_index_offset[2] = ap_pos_file_offset;
    save_to_file((uint8*) sort_index_buf, sort_file_total * 2);

    ap_index_parent_offset[2] = ap_pos_file_offset;
    save_to_file((uint8*) index_parent_buf, sort_file_total * 2);

    return;
}

/******************************************************************************/
/*
 * \par  Description: ���� genre �б�
 *
 * \param[in]    str_buf--�������ݻ����ַ

 * \param[out]

 * \return

 * \note
 *******************************************************************************/
//music ��������
//genre->artist->album->title (mode=0)
//or genre->album->title (mode=1)
static void sort_genre(char *str_buf)
{


    uint8 str_len;
    
    init_file_index();
    
    str_len = sort_cmp_len;
    if (str_len > GENRE_CMP_LENGTH)
    {
        str_len = GENRE_CMP_LENGTH;
    }
    
    /*read string datas from mmusic.lib for sorting*/
    read_string(file_index_buf, sort_file_total, str_buf, 0, str_len, PLIST_GENRE);
    plist_get_app_msg();

    /*sort the first str_len of string datas*/
    list_sort((char*) file_index_buf, sort_file_total, 2, str_buf, SORT_CMP_STRING, str_len);
    plist_get_app_msg();
   

    list_resort(file_index_buf, sort_file_total, str_buf, PLIST_GENRE, GENRE_CMP_LENGTH, str_len);

#ifdef DEBUG_PRINT
    debug_printf(PLIST_GENRE);
#endif

    tidy_same_table(NULL, count_buf_a, file_index_buf);

#if(GENRE_LIST_MODE == 1)
    read_from_file((uint8 *)sort_index_buf, (uint8 *)ALBUM_SORT_INDEX_VM_ADDR, sort_file_total*2);
#else 

#endif

    son_sort_index(file_index_buf, count_buf_a, sort_index_buf, SORT_CMP_WORD);

#if(GENRE_LIST_MODE == 1)
    // tidy album
    tidy_son_unit(count_buf_b,file_index_buf,count_buf_a,tidy_buf_a);
#else
    //tidy artist and album
    tidy_son_unit(count_buf_b, file_index_buf, count_buf_a, tidy_buf_b);



    tidy_son_unit(count_buf_c, file_index_buf, count_buf_b, tidy_buf_a);
#endif

    ap_son_tree_offset[3][0] = ap_pos_file_offset;
    ap_son_tree_num[3][0] = creat_plist_tree(file_index_buf, count_buf_a, count_buf_b, NULL, PLIST_GENRE);

    index_parent_buf = (uint16*) COUNT_BUF_A_ADDR;//�ռ临�ã�ע��

#if(GENRE_LIST_MODE == 1)
    ap_son_tree_offset[3][1]=ap_pos_file_offset;
    ap_son_tree_num[3][1]=creat_plist_tree(file_index_buf,count_buf_b,NULL,count_buf_a,PLIST_ALBUM);
    creat_index_map(index_parent_buf,file_index_buf,count_buf_b);
#else
    ap_son_tree_offset[3][1] = ap_pos_file_offset;
    ap_son_tree_num[3][1] = creat_plist_tree(file_index_buf, count_buf_b, count_buf_c, count_buf_a, PLIST_ARTIST);
    ap_son_tree_offset[3][2] = ap_pos_file_offset;
    ap_son_tree_num[3][2] = creat_plist_tree(file_index_buf, count_buf_c, NULL, count_buf_b, PLIST_ALBUM);
    creat_index_map(index_parent_buf, file_index_buf, count_buf_c);
#endif

    build_ex_index(sort_index_buf);

    ap_file_index_offset[3] = ap_pos_file_offset;
    save_to_file((uint8*) file_index_buf, sort_file_total * 2);

    ap_sort_index_offset[3] = ap_pos_file_offset;
    save_to_file((uint8*) sort_index_buf, sort_file_total * 2);

    ap_index_parent_offset[3] = ap_pos_file_offset;
    save_to_file((uint8*) index_parent_buf, sort_file_total * 2);
    

    return;
}


/******************************************************************************/
/*
 * \par  Description: �����б�
 *
 * \param[in]

 * \param[out]

 * \return

 * \note
 *******************************************************************************/
void sort_music_list(void)
{
    
    char *str_buf = (char*)(sorting_map_level_cur->sort_data_addr);// SORT_DATA_ADDR;//title����ǰsort_cmp_len��byte�Ѿ�������ram��
    sort_file_total = ap_plist_file_total;
    track_buf = (uint8*) (sorting_map_level_cur->track_data_addr);//trackǰ1byte�Ѿ�������RAM��
  //  libc_print("macro",TRACK_DATA_ADDR,2);
  //  libc_print("p",sorting_map_level_cur->track_data_addr,2);
    
	if(ap_plist_sorting_level == 16000){
						 write_to_file((uint8*)ALBUM_SORT_INDEX_VM_ADDR_16k,(uint8*)(sorting_map_level_16k.track_data_addr),sort_file_total);
				 }
    //clear buffer
    libc_memset(file_index_buf, 0, (sorting_map_level_cur->file_info_buf_size));

#if 1
    sort_title(str_buf);
#endif

    plist_get_app_msg();
    plist_reflash_progress(-1);
    //libc_print("<album star> ", sys_get_ab_timer(), 2);    
#if 1
    sort_album(str_buf);
#endif

    plist_get_app_msg();
    plist_reflash_progress(-1);
    //libc_print("<artist star> ", sys_get_ab_timer(), 2);
if(ap_plist_sorting_level != 16000)
{
#if 0
    sort_artist(str_buf);
#endif
}
    plist_get_app_msg();
    plist_reflash_progress(-1);
#if (ID3_GENRE_SUPPORT == 1)
  if(ap_plist_sorting_level == 4000)
  {   //libc_print("<genre star> ", sys_get_ab_timer(), 2);
    #if 0
    sort_genre(str_buf);
    #endif
  }
#endif

    return;
}

