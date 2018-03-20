/********************************************************************************
 *        Copyright(c) 2014-2015 Actions (Zhuhai) Technology Co., Limited,
 *                            All Rights Reserved.
 *
 * ������CASE ������Ķ���ѡ��ͷ�ļ���ÿ������İ��Ӹ����Լ��Ĺ��ܹ����ϸ���ú�
 *       ��Щ�꿪�أ���ͷ�ļ������� CASE ������������Ӧ�ð�����
 * ���ߣ�cailizhen
 ********************************************************************************/

#ifndef _case_independent_H
#define _case_independent_H

#include "psp_includes.h"

#define CASE_BOARD_EVB       0
#define CASE_BOARD_DEMO    1
#define CASE_BOARD_DVB       2

#define CASE_BOARD_TYPE    CASE_BOARD_DVB

#define CASE_LINEIN_CHANNEL_SEL 1  //LINEIN AA/ADDAͨ��ѡ��0��ʾAA��1��ʾADDA
#define CASE_FM_CHANNEL_SEL     1  //FM AA/ADDAͨ��ѡ��0��ʾAA��1��ʾADDA

#if (CASE_BOARD_TYPE == CASE_BOARD_DEMO)
#define SPEAKER_HEADPHONE_FIX   0
#else
#define SPEAKER_HEADPHONE_FIX   1  //EVB�̶��Ӷ����������Ҫ����DAE
#endif

#define ENABLE_LEVEL_LOW        0  //�͵�ƽʹ��
#define ENABLE_LEVEL_HIGH       1  //�ߵ�ƽʹ��
#define ENABLE_FIX_ACTIVE       2  //ֱ�����߻�����ʼ��ʹ��

#define DETECT_NO_SUPPORT       0 //�����Ȱβ���
#define DETECT_BY_ADCKEY        1 //ADCKEY���
#define DETECT_BY_GPIO          2 //GPIO���
#define DETECT_BY_GPIOB0        3 //GPIOB0���
#define DETECT_BY_CMD           4 //SD��������
#define DETECT_BY_SIO           5 //SIO���

//�����м���Ԫ��
#define ARR_COUNT(arr)  (sizeof(arr) / sizeof((arr)[0]))

#define SUPPORT_MUSIC_FOLDER    0 //�Ƿ�֧������Ŀ¼����
#define SUPPORT_RECORD          0 //�Ƿ�֧��¼������
#define SUPPORT_RECORD_PLAY     0 //�Ƿ�֧��¼���طŹ���
#define SUPPORT_RING_FOLDER     1 //�Ƿ�֧������Ŀ¼����
#define SUPPORT_PLIST_FILE      1 //�Ƿ�֧���ļ����б�
#define SUPPORT_PLIST_TITLE     0 //�Ƿ�֧�ֱ����б�
#define SUPPORT_PLIST_ARTIST    0 //�Ƿ�֧���ݳ����б�
#define SUPPORT_PLIST_ALBUM     0 //�Ƿ�֧��ר���б�
#define SUPPORT_PLIST_GENRE     0 //�Ƿ�֧�ַ���б�
#define SUPPORT_DETECT_ENERGY   0 //�Ƿ�֧���������
#define SUPPORT_RCP_FUNC        1 //�Ƿ�֧��RCPЭ��

#if (CASE_BOARD_TYPE == CASE_BOARD_DEMO)
#define SUPPORT_AUX_DETECT      DETECT_BY_GPIOB0 //�Ƿ�֧��AUX�β���
#else
#define SUPPORT_AUX_DETECT      DETECT_BY_GPIO //�Ƿ�֧��AUX�β���
#endif

#if (SPEAKER_HEADPHONE_FIX == 1)
#define SUPPORT_HP_DETECT       DETECT_NO_SUPPORT //�Ƿ�֧�ֶ����β��� headphone
#else
#define SUPPORT_HP_DETECT       DETECT_NO_SUPPORT //�Ƿ�֧�ֶ����β��� headphone
#endif

#define SUPPORT_CARD_DETECT     DETECT_BY_CMD //�Ƿ�֧��SD���β���
//#define SUPPORT_CARD_DETECT     DETECT_BY_GPIO//�Ƿ�֧��SD���β���

#define SUPPORT_RCP             1 //�Ƿ�֧��RCP����
#define SUPPORT_SLAVE_CONTROL   0 //�Ƿ�֧��I2C/SPI/UART����
#define SUPPORT_LED_DRIVER      1 //�Ƿ�֧��LED����
#define SUPPORT_IR_DRIVER       0//�Ƿ�֧�ֺ���ң����
#define SUPPORT_HPY_DRIVER      0 //�Ƿ�֧��IO����(����)

#if (CASE_BOARD_TYPE == CASE_BOARD_DEMO)
#define SUPPORT_ADC_KEY         0 //�Ƿ�֧���߿ذ���
#else
#define SUPPORT_ADC_KEY         1 //�Ƿ�֧���߿ذ���
#endif

#define TK_DRIVER_OUTER         1 //֧���ⲿ��������
#define TK_DRIVER_INNER         2 //֧���ڲ���������
#if (CASE_BOARD_TYPE == CASE_BOARD_DEMO)
#define SUPPORT_TK_DRIVER       TK_DRIVER_OUTER //�Ƿ�֧�ִ���������1��ʾ֧���ⲿ����������2��ʾ֧���ڲ���������
#else
#define SUPPORT_TK_DRIVER       0 //�Ƿ�֧�ִ���������1��ʾ֧���ⲿ����������2��ʾ֧���ڲ���������
#endif

#if (CASE_BOARD_TYPE == CASE_BOARD_DEMO)
#define SUPPORT_PHONE_KEY       1 //�Ƿ�֧��ר�õĵ绰��
#else
#define SUPPORT_PHONE_KEY       0 //�Ƿ�֧��ר�õĵ绰��
#endif

#define SUPPORT_BTT_TEST          //�Ƿ�֧��Ƶƫ���Թ���
#define SUPPORT_ASET_TEST         //�Ƿ�֧��ASET���Թ���

//�򿪺�󣬽ű�fwimage.cfg�����Ӵ��test_chl.drv�ļ�
//���븴��ǰ̨ENHANCED1������ֻ��������������Ӧ����ʹ��
//#define SUPPORT_SPPBLE_TEST       //�Ƿ�֧��SPPBLEͨ������



//�Ƿ�ʹ����ҳ���·
#if (CASE_BOARD_TYPE == CASE_BOARD_DEMO)
#define SUPPORT_OUTER_CHARGE    1
#else
#define SUPPORT_OUTER_CHARGE    0
#endif

#define BAT_CHARGE_MODE_INNER          (0) //�ڲ����
#define BAT_CHARGE_MODE_OUTER          (1) //�ⲿ���

#define EXTERN_CHARGE_DETECT_GPIOIN    GPIOAINEN
#define EXTERN_CHARGE_DETECT_GPIODAT   GPIOADAT
#define EXTERN_CHARGE_DETECT_PIN       (1 << 11)
#define EXTERN_CHARGE_FULL_GPIOIN      GPIOAINEN
#define EXTERN_CHARGE_FULL_GPIODAT     GPIOADAT
#define EXTERN_CHARGE_FULL_PIN         (1 << 9)

#define EXTERN_BATTERY_DETECT_GPIOIN   GPIOAINEN
#define EXTERN_BATTERY_DETECT_GPIODAT  GPIOADAT
#define EXTERN_BATTER_DETECT_PIN       (1 << 10)

#define EXTERN_CHARGE_VAL_MSK          (~(3 << 0))

#define EXTERN_CHARGE_VAL_SEL          (1 << 0)

#define IS_EXTERN_CAHREGE_IN()         ((act_readl(EXTERN_CHARGE_DETECT_GPIODAT) & EXTERN_CHARGE_DETECT_PIN) != 0)

#define IS_EXTERN_BATTERY_IN()  	   ((act_readl(EXTERN_BATTERY_DETECT_GPIODAT) & EXTERN_BATTER_DETECT_PIN) == 0)

//for tk plane power control
#define EXTERN_TK_PLANE_GPIOOUT       GPIOBOUTEN
#define EXTERN_TK_PLANE_GPIODAT       GPIOBDAT
#define EXTERN_TK_PLANE_PIN           (1 << 7)

//�Ƿ�ʹ�ò��뿪�ؼ���Ƿ���Ҫ�ػ�(���ػ�)
//#define SWITCH_KEY_POWER_OFF

//BT BURN LED
#define BT_BURN_IO_EN_REG               GPIOAOUTEN
#define BT_BURN_IO_DATA_REG             GPIOADAT
#define BT_BURN_SET_BIT                 (1 << 11)
#define BT_BURN_CLEAR_BIT               (~(1 << 11))

//AUX����������
//ADCKEY��ⷽʽ
#define AUX_ADC_VALUE       (0x6d) //����ƫ��3
//GPIO��ⷽʽ
#define AUX_GPIO_IN         GPIOBINEN
#define AUX_GPIO_DATA       GPIOBDAT
#define AUX_GPIO_PIN        (1 << 9)
//#define AUX_GPIO_IN         GPIOAINEN
//#define AUX_GPIO_DATA       GPIOADAT
//#define AUX_GPIO_PIN        (1 << 0)
#define AUX_GPIO_EN_LEVEL   ENABLE_LEVEL_LOW
//SIO��ⷽʽ
#define AUX_SIO_PIN         (1 << 7)
#define AUX_SIO_EN_LEVEL    ENABLE_LEVEL_LOW

//HP GPIO����������
#define HP_GPIO_IN          GPIOAINEN
#define HP_GPIO_DATA        GPIOADAT
#define HP_GPIO_PIN         (1 << 8)
#define HP_GPIO_EN_LEVEL    ENABLE_LEVEL_LOW

//SD��GPIO����������
#define CARD_GPIO_IN        GPIOBINEN
#define CARD_GPIO_DATA      GPIOBDAT
#define CARD_GPIO_PIN       (1 << 7)
#define CARD_GPIO_EN_LEVEL  ENABLE_LEVEL_LOW

//���뿪�صļ��GPIO,����ʹ��A30,ע���uhost��power enable pin�г�ͻ
#ifdef SWITCH_KEY_POWER_OFF
#define SHUTOFF_DETECT_IO_IN_EN_REG     GPIOAINEN
#define SHUTOFF_DETECT_IO_OUT_EN_REG    GPIOAOUTEN
#define SHUTOFF_DETECT_IO_DATA_REG      GPIOADAT
#define SHUTOFF_DETECT_SET_BIT          ((uint32)0x40000000)
#define SHUTOFF_DETECT_CLR_BIT          ((uint32)0xBFFFFFFF)
#define SHUTOFF_DETECT_IO_PU_EN_REG     GPIOAPUEN
#endif

#define ENABLE_USB_DETECT()       	(GLOBAL_KERNEL_BACKDOOR_FLAG &= (~(BACKDOOR_DISUSB_DETECT)))
#define DISABLE_USB_DETECT()  		(GLOBAL_KERNEL_BACKDOOR_FLAG |= (BACKDOOR_DISUSB_DETECT))

#define ENABLE_UHOST_DETECT()       	(GLOBAL_KERNEL_BACKDOOR_FLAG &= (~(BACKDOOR_DISUHOST_DETECT)))
#define DISABLE_UHOST_DETECT()  		(GLOBAL_KERNEL_BACKDOOR_FLAG |= (BACKDOOR_DISUHOST_DETECT))

#define DAC_INNER   0//�ڲ�DAC
#define DAC_EXTERNAL 1//�ⲿDAC

/*!
 * \brief
 *  usb_port_state_e ����״̬ö������
 */
typedef enum
{
    /*! USB Device */
    USB_PORT_DEVICE = 0,
    /*! USB Host */
    USB_PORT_HOST = 1,
} usb_port_state_e;

//��ȡ��ǰusb�˿��豸״̬
static inline uint8 get_usb_port_state(void)
{
    if ((act_readb(DPDMCTRL) & 0x0f) != 0)
    {
        return USB_PORT_DEVICE;
    }
    else
    {
        return USB_PORT_HOST;
    }
}

//pc���ߵ�����
typedef enum
{
    STUB_PC_TOOL_ASQT_MODE = 1,
    STUB_PC_TOOL_ASET_MODE = 2,
    STUB_PC_TOOL_ASET_EQ_MODE = 3,
    STUB_PC_TOOL_ATT_MODE = 4,
    STUB_PC_TOOL_TK_PMODE = 5,
    STUB_PC_TOOL_BTT_MODE = 0x42,
} PC_stub_mode_e;

//��Ҫע�ᵽ������������I2C TK�����е���
typedef void (*scan_isr_cbk)(void);

#endif