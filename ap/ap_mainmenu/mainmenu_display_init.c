/*******************************************************************************
 *                              US212A
 *                            Module: MainMenu
 *                 Copyright(c) 2003-2012 Actions Semiconductor,
 *                            All Rights Reserved.
 *
 * History:
 *      <author>    <time>           <version >             <desc>
 *       zhangxs     2011-09-05 10:00     1.0             build this file
 *******************************************************************************/
/*!
 * \file     mainmenu_display_init.c
 * \brief    初始化显示信息
 * \author   zhangxs
 * \version  1.0
 * \date  2011/10/08
 *******************************************************************************/
#include  "main_menu.h"

/*!应用图片的的STYLE ID*/
/*const uint16 PIC_BOX[] =
{
    STY_MUSIC_PIC, STY_AUDIBLE_PIC, STY_VIDEO_PIC, STY_PHOTO_PIC, STY_READER_PIC, STY_BROWSER_PIC,
    STY_VOICE_PIC, STY_RECORD_PIC, STY_RADIO_PIC, STY_TOOLS_PIC, STY_SETTING_PIC, STY_USER1_PIC, 
    STY_USER2_PIC, STY_USER3_PIC
};*/

const uint16 PIC_BOX[] =
{
    STY_MUSIC_PIC, STY_BROWSER_PIC, STY_RECORD_PIC, STY_RADIO_PIC, STY_SETTING_PIC, STY_USER1_PIC, 
    STY_USER2_PIC
};

/*!应用名称的STYLE ID*/
const uint16 TEXT_BOX[][MAX_APP_NUM] =
{
    {
        STY_MUSIC_TEXT, STY_BROWSER_TEXT, STY_RECORD_TEXT, STY_RADIO_TEXT, STY_SETTING_TEXT, STY_USER1_TEXT, 
        STY_USER2_TEXT
    }
};

/*!正在播放的STYLE ID*/
const uint16 TEXT_NOWPLAY_BOX[FRAME_NUM] =
{
    STY_NOWPLAY_TEXT
};

/*!上一次播放的STYLE ID*/
const uint16 TEXT_LASTPLAY_BOX[FRAME_NUM] =
{
    STY_LASTPLAY_TEXT
};

/*!显示应用信息的STYLE ID，向后翻*/
const uint16 INFO_BOX[][MAX_APP_NUM] =
{
    {
        STY_MUSIC_INFO, STY_BROWSER_INFO, STY_RECORD_INFO, STY_RADIO_INFO, STY_SETTING_INFO, STY_USER1_INFO, 
        STY_USER2_INFO
    }
};

/*!正在播放信息的STYLE ID，向后翻*/
const uint16 TEXT_NOWPLAY_INFO[FRAME_NUM] =
{
    STY_NOWPLAY_INFO
};

/*!应用信息不滚动部分的RES ID*/
const uint16 STR_ID_BOX[] =
{ 
    TOTAL_S, 0xffff, 0xffff, TOTAL_S, DATE_S, 0xffff, 
    0xffff
};
/*!应用信息滚动部分的RES ID*/
const uint16 STR_INFO_BOX[] =
{ 
    TRACKNUM_S, 0xffff, 0xffff, PRESETNUM_S, DATE_S, 0xffff, 
    0xffff
};

/******************************************************************************/
/*!
 * \par  Description:
 *	  初始化各个用于显示的STYLE ID数据
 * \param[in]    none
 * \param[out]   none
 * \return       none
 * \ingroup      module name
 * \par          exmaple code
 * \code
 *               list example code in here
 * \endcode
 * \note
 *******************************************************************************/
void _init_ap_display_infor(void)
{
    uint16 cnt, total;
    uint16 tmp, i;

    total = g_mainmenu_var.cfg_var.total_item;
    if (total > MAX_APP_NUM)
    {
        total = MAX_APP_NUM;
    }
    for (cnt = 0; cnt < total; cnt++)
    {
        tmp = g_mainmenu_var.cfg_var.ap_id[cnt];
        if (tmp >= MAX_APP_NUM)
        {
            break;
        }
        ap_pic_box[cnt] = PIC_BOX[tmp];
        for (i = 0; i < FRAME_NUM; i++)
        {
            ap_text_box[i][cnt] = TEXT_BOX[i][tmp];
            ap_info_box[i][cnt] = INFO_BOX[i][tmp];
        }
        ap_string_box[cnt] = STR_ID_BOX[tmp];
        ap_string_info_box[cnt] = STR_INFO_BOX[tmp];
        ap_file_amount[cnt] = g_ap_file_num[tmp];
        libc_print("file_num",ap_file_amount[cnt],2);
    }
    if (get_engine_state() != ENGINE_STATE_NULL)
    {
        ap_pic_box[cnt] = STY_PLAYING_PIG;
        ap_string_box[cnt] = TRACK_S;
        if (get_engine_state() == ENGINE_STATE_PLAYING)
        {
            for (i = 0; i < FRAME_NUM; i++)
            {
                ap_text_box[i][cnt] = TEXT_NOWPLAY_BOX[i];
                ap_info_box[i][cnt] = TEXT_NOWPLAY_INFO[i];
            }
        }
        else
        {
            for (i = 0; i < FRAME_NUM; i++)
            {
                ap_text_box[i][cnt] = TEXT_LASTPLAY_BOX[i];
                ap_info_box[i][cnt] = TEXT_NOWPLAY_INFO[i];
            }
        }
    }
}
