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

void init_file_index(void);
void build_ex_index(uint16 *ex_buf);
void tidy_same_table(uint16 *tidy_buf, uint16 *record_buf, uint16 *index_buf);
void son_sort_index(uint16 *data_buf, uint16 *count_buf, uint16 *depend_buf, uint8 cmp_type);
void tidy_son_unit(uint16 *record_buf, uint16 *data_buf, uint16 *same_buf, uint16 *depend_buf);
bool creat_index_map(uint16 *map_buf, uint16 *index_buf, uint16 *count_buf);
uint16* tidy_son_table(uint16 *data_buf, uint16 *record_buf, uint16 count, uint16 *depend_buf);

void set_sorting_level(void)
 {
	 if (ap_plist_file_total > 0)
		 {
			
			 if(ap_plist_file_total <= 4000)
			 {
#if 0
			   libc_print("4k_mode",ap_plist_file_total,2);
				 ap_plist_sorting_level= 4000;
				 init_sys_data(0);
         sorting_map_level_cur = &sorting_map_level_4k;
 #else
         libc_print("16k_mode",ap_plist_file_total,2);
				 ap_plist_sorting_level = 16000;
			 	 init_mem_by_songs_16k();
				 sorting_map_level_cur = & sorting_map_level_16k;

 
 #endif
			 }
			 else if(ap_plist_file_total <= 8000)
			 {
#if 0 
			   libc_print("8k_mode",ap_plist_file_total,2);
				 ap_plist_sorting_level = 8000;
				 init_mem_by_songs_num();
				 sorting_map_level_cur = &sorting_map_level_8k;
				  #else
         libc_print("16k_mode",ap_plist_file_total,2);
				 ap_plist_sorting_level = 16000;
			 	 init_mem_by_songs_16k();
				 sorting_map_level_cur = & sorting_map_level_16k;

 
 #endif
			 }
			 else
			 {
			   libc_print("16k_mode",ap_plist_file_total,2);
				 ap_plist_sorting_level = 16000;
			 	 init_mem_by_songs_16k();
				 sorting_map_level_cur = & sorting_map_level_16k;
			 }
			}
			else{
          ;
			}
			   
		return ;
 }

 void _init_sorting_map_level_4k(void)
{
	  sorting_map_level_4k.sort_buf_size         = (uint32)SORT_BUFFER_SIZE ;
		sorting_map_level_4k.index_buf_size 			 = (uint16)INDEX_BUFFER_SIZE;
		sorting_map_level_4k.file_info_buf_size    = (uint16)FILE_INFO_BUF_SIZE;
		sorting_map_level_4k.track_buf_size				 = (uint16)TRACK_BUFFER_SIZE ;
	
		sorting_map_level_4k.title_cmp_lenth 			 = (uint8)TITLE_CMP_LENGTH;
		sorting_map_level_4k.album_cmp_lenth       = (uint8) ALBUM_CMP_LENGTH;
		sorting_map_level_4k.artist_cmp_lenth      = (uint8)ARTIST_CMP_LENGTH;
		sorting_map_level_4k.genre_cmp_lenth       = (uint8)GENRE_CMP_LENGTH;
		sorting_map_level_4k.track_cmp_lenth       = (uint8)TRACK_CMP_LENGTH;
	
		sorting_map_level_4k.music_lib_size        = (uint32)MUSIC_LIB_SIZE    ;
		sorting_map_level_4k.audible_lib_size			 = (uint32)AUDIBLE_LIB_SIZE;
		sorting_map_level_4k.m3u_lib_size 				 = (uint32)M3U_LIB_SIZE;
		sorting_map_level_4k.userpl_pl_size 			 = (uint32)USERPL_PL_SIZE;
		sorting_map_level_4k.album_pic_size 			 = (uint32)ALBUM_PIC_SIZE;
	
		sorting_map_level_4k.store_music_addr             =    (uint32)STORE_MUSIC_ADDR;
		sorting_map_level_4k.title_sort_index_vm_addr     = (uint32)TITLE_SORT_INDEX_VM_ADDR ;
		sorting_map_level_4k.album_sort_index_vm_addr     = (uint32)ALBUM_SORT_INDEX_VM_ADDR;
		sorting_map_level_4k.artist_sort_index_vm_addr    = (uint32)ARTIST_SORT_INDEX_VM_ADDR;
		sorting_map_level_4k.tidy_buf_a_vm_addr           = (uint32)TIDY_BUF_A_VM_ADDR;
		sorting_map_level_4k.tidy_buf_b_vm_addr           = (uint32)TIDY_BUF_B_VM_ADDR;
	
		sorting_map_level_4k.store_others_addr            = (uint32)STORE_OTHERS_ADDR;
		sorting_map_level_4k.others_title_addr            = (uint32)OTHERS_TITLE_ADDR;
	
		//sorting_map_level_4k.plist_data_base_addr         = (uint32)PLIST_DATA_BASE_ADDR;
		//sorting_map_level_4k.plist_data_top_addr          = (uint32)PLIST_DATA_TOP_ADDR ;
	
	
		sorting_map_level_4k.file_info_addr               = (uint32)FILE_INFO_ADDR;
		sorting_map_level_4k.sort_data_addr               = (uint32)SORT_DATA_ADDR;
	
		
		sorting_map_level_4k.file_index_buf_addr          = (uint32)FILE_INDEX_BUF_ADDR;
		sorting_map_level_4k.sort_index_buf_addr          = (uint32)SORT_INDEX_BUF_ADDR;
		sorting_map_level_4k.tidy_buf_a_addr              = (uint32)TIDY_BUF_A_ADDR;
		sorting_map_level_4k.count_buf_a_addr             = (uint32)COUNT_BUF_A_ADDR;
		sorting_map_level_4k.tidy_buf_b_addr              = (uint32)TIDY_BUF_B_ADDR;
		sorting_map_level_4k.count_buf_b_addr             = (uint32)COUNT_BUF_B_ADDR;
		sorting_map_level_4k.track_data_addr              = (uint32)TRACK_DATA_ADDR; 
		sorting_map_level_4k.count_buf_c_addr             = (uint32)COUNT_BUF_C_ADDR;

}


/******************************************************************************/
/*
 * \par  Description: ��ʼ����������
 *
 * \param[in]

 * \param[out]

 * \return

 * \note
 *******************************************************************************/
void init_file_index(void)
{
    uint16 i = 0;

    while (i < sort_file_total)
    {
        file_index_buf[i] = i;
        i++;
    }
}

/******************************************************************************/
/*
 * \par  Description:������ͬ�ģ������ɸ�����
 *

 * \param[out]   tidy_buf   --object ������
 * \param[out]   record_buf --save the same object 's number
 * \param[in]    index_buf  --file_index,save file's serial
 * \param[in]    depend_buf --compare data
 * \param[in]    cmp_len  --compare data's length (unit:8bit)

 * \return

 * \note
 *******************************************************************************/
void tidy_same_table(uint16 *tidy_buf, uint16 *record_buf, uint16 *index_buf)
{
    uint16 i;
    uint16 j, n;

    uint16 *same_p;
    uint16 *index_p;

    index_p = index_buf;
    same_p = record_buf;

    libc_memset(same_p, 0x00, sort_file_total * 2 + 2);

    j = 0;
    n = 1;
    *same_p = n;
    if (tidy_buf != NULL)
    {
        tidy_buf[index_p[0]] = j;
    }

    for (i = 1; i < sort_file_total; i++)
    {
        if (0 == resort_data[i])
        {
            //�����
            j++;
            n = 1;
            same_p++;
        }
        else
        {
            n++;
        }

        if (tidy_buf != NULL)
        {
            tidy_buf[index_p[i]] = j;
        }

        *same_p = n;
    }
}
/******************************************************************************/
/*
 * \par  Description:����ָ�����ȵ�index,ͳ����ͬ�ĸ���,���ش�Ÿ���ָ��λ��
 *
 * \param[in]    data_buf ---������file_index
 * \param[out]   record_buf ---ͳ�Ƹ�����ű�
 * \param[in]    count         ---�Ӹ���
 * \param[in]    depend_buf ---ͳ��������������Դ

 * \return       ��ǰд��ĵ�ַ

 * \note
 *******************************************************************************/
uint16* tidy_son_table(uint16 *data_buf, uint16 *record_buf, uint16 count, uint16 *depend_buf)
{
    uint16 i;
    uint16 n;

    uint16 *same_p;

    sort_depend_buf = (void*) depend_buf;
    same_p = record_buf;

    n = 1;
    *same_p = n;

    for (i = 1; i < count; i++)
    {
        if (0 != compare_word(data_buf + i, data_buf + i - 1, 2))
        {
            //�����
            n = 1;
            same_p++;
        }
        else
        {
            n++;
        }
        *same_p = n;
    }

    same_p++;

    return same_p;

}

/******************************************************************************/
/*
 * \par  Description: ����file_index�ķ���ӳ���
 *
 * \param[in]

 * \param[out]        ex_buf---����Ӱ���

 * \return

 * \note
 *******************************************************************************/
//���ɴ�sort_index
void build_ex_index(uint16 *ex_buf)
{
    uint16 i;
    for (i = 0; i < sort_file_total; i++)
    {
        ex_buf[file_index_buf[i]] = i;
    }
}
/******************************************************************************/
/*
 * \par  Description: �����б����Ӽ�
 *
 * \param[in][out]   data_buf ---file_index,������
 * \param[in]        count_buf ---ͳ���Ӽ�����ͬ����
 * \param[in]        depend_buf ---�����ıȽ�����
 * \param[in]        cmp_type  ---�Ƚϵ�����

 * \return

 * \note
 *******************************************************************************/
//�����Ӽ�
void son_sort_index(uint16 *data_buf, uint16 *count_buf, uint16 *depend_buf, uint8 cmp_type)
{
    uint16 *same_p, *data_p;
    uint16 i, count;
    same_p = count_buf;
    data_p = data_buf;

    for (i = 0; *same_p > 0;)
    {
        if (*same_p > 1)
        {
            count = *same_p;
            list_sort((void*) (data_buf + i), count, 2, depend_buf, cmp_type, 2);
            i = i + count;
        }
        else
        {
            data_p++;
            i++;
        }
        same_p++;
    }

}
/******************************************************************************/
/*
 * \par  Description:�ɸ����ĸ������ֶ�ͳ���Ӽ���ͬ�ĸ���
 *
 * \param[out]   record_buf   ---��¼ͳ�Ƶ��Ӽ���ͬ������
 * \param[in]    data_buf   ---����õ�file_index
 * \param[in]    same_buf   ---������ͬ������
 * \param[in]    depend_buf ---ͳ��������������Դ

 * \return

 * \note
 *******************************************************************************/
void tidy_son_unit(uint16 *record_buf, uint16 *data_buf, uint16 *same_buf, uint16 *depend_buf)
{
    uint16 *same_p, *record_p, *data_p;
    uint16 i, count;
    same_p = same_buf;
    data_p = data_buf;
    record_p = record_buf;

    libc_memset(record_p, 0x00, sort_file_total * 2 + 2);

    for (i = 0; *same_p > 0;)
    {
        if (*same_p > 1)
        {
            count = *same_p;
            record_p = tidy_son_table(data_p, record_p, count, depend_buf);
            data_p = data_p + count;
            i = i + count;
        }
        else
        {
            //            *record_p++=1;
            *record_p = 1;
            record_p++;
            i++;
            data_p++;
        }
        same_p++;
    }

}

/******************************************************************************/
/*
 * \par  Description: ����file_index ��parentλ��ӳ���,
 *
 * \param[out]     map_buf  ---������treeλ��ƫ��
 * \param[in]      index_buf---file_index
 * \param[in]      count_buf ---����treeͳ����ͬ������

 * \return         TRUE or FALSE

 * \note
 *******************************************************************************/
bool creat_index_map(uint16 *map_buf, uint16 *index_buf, uint16 *count_buf)
{
    uint16 i, count;
    uint16 son_offset;

    son_offset = 0;
    while (*count_buf > 0)
    {
        i = 0;
        count = *count_buf;
        while (i < count)
        {
            map_buf[*index_buf] = son_offset;
            i++;
            index_buf++;
        }
        son_offset++;
        count_buf++;
    }

    return TRUE;
}

/******************************************************************************/
/*
 * \par  Description: �������ṹ,����TREE�ĸ���
 *
 * \param[in]     index_buf  ---file_index
 * \param[in]     cur_buf  ---��ǰ��ͳ���Ӽ�����ͬ������
 * \param[in]     son_buf ---�Ӽ�ͳ�Ƶ��Ӽ�����ͬ������
 * \param[in]     parent_buf ---����ͳ�Ƶ��Ӽ�����ͬ������
 * \param[in]    type---����tree������

 * \return        TREE�ĸ���

 * \note
 *******************************************************************************/
uint16 creat_plist_tree(uint16 *index_buf, uint16 *cur_buf, uint16 *son_buf, uint16 *parent_buf, uint8 type)
{
    plist_tree_t *tree_p;
    uint16 *cur_p, *son_p, *pare_p;
    uint16 i, j, count, n;
    uint16 s_offset, p_offset;//��tree�͸�treeƫ��
    uint16 list_offset, son_num;
    uint16 tree_count;

    tree_p = (plist_tree_t *) temp_plist_buf;
    cur_p = cur_buf;
    son_p = son_buf;
    pare_p = parent_buf;

    if (*cur_p == 0)
    {
        //buffer error
        return 0;
    }

    j = 0;
    s_offset = 0;
    p_offset = 0;
    list_offset = 0;
    tree_count = 0;

    libc_memset(temp_plist_buf, 0, sizeof(temp_plist_buf));

    while (*cur_p > 0)
    {
        if ((0 != tree_count) && (0 == (tree_count % (SECTOR_SIZE / sizeof(plist_tree_t)))))
        {
            //buffer is full,write to file
            save_to_file(temp_plist_buf, SECTOR_SIZE);
            libc_memset(temp_plist_buf, 0x00, SECTOR_SIZE);
            tree_p = (plist_tree_t *) temp_plist_buf;
            libc_memset(temp_plist_buf, 0, sizeof(temp_plist_buf));
        }

        son_num = 0;//ÿ��tree����tree����
        count = *cur_p;
        cur_p++;
        tree_p->flag = 1;
        tree_p->type = type;
        tree_p->file_index = *index_buf;
        tree_p->file_total = count;
        tree_p->prev_offset = list_offset - 1;
        tree_p->next_offset = list_offset + 1;
        list_offset++;

        if (parent_buf == NULL)
        {
            //û�и�����
            tree_p->parent_offset = 0xffff;
        }
        else
        { //�и���
            tree_p->parent_offset = p_offset;
            j = j + count;
            if (j >= *pare_p)
            {
                j = 0;
                pare_p++;
                p_offset++;
            }
        }

        if (son_buf == NULL)
        { //û��������
            tree_p->son_offset = 0xffff;
        }
        else
        { //��������
            tree_p->son_offset = s_offset;
            i = 0;
            n = 0;
            while (i < count)
            {
                i = *son_buf + i;
                son_buf++;
                son_num++;
                s_offset++;
            }
        }

        tree_p->son_num = son_num;

        index_buf = count + index_buf;
        tree_p++;
        tree_count++;

    }

    //modify last tree's next point
    tree_p--;
    tree_p->next_offset = 0xffff;

    //save last sector
    save_to_file(temp_plist_buf, SECTOR_SIZE);

    return tree_count;

}
