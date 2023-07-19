/**
  * @date  2011-04-17
  * @brief application.
  **/
#include "app.h"
#include "ff.h"
#include "main.h"
	extern u8 init_lseek(void);
	extern u8 Initbbfile(void);
	extern char* itoa(int, char*, int);
	extern u32 aton(char *, u8);
	extern void bcdtoa(u8 ,char* , char );
	extern void LogData(void);
	extern void ConcateArr(u8 *,u8 *, u8 *);
	extern _ARMABI size_t strlen(const char * /*s*/) __attribute__((__nonnull__(1)));

FATFS fs; /* Work area (file system object) for logical drives */
BYTE w_buffer[8192];   /* file copy buffer */
FRESULT res;  /* FatFs function common result code */
UINT bw,br; /* File read/write count */
static u32 De_L_Seek=0;									//<<============================= Added ***

static u32 L_Seek = 0;
u8 FileOk = 0;
u8 save_lseek(void);
u8 DeSaveOnSDCard(u8 *);


/*******************************************************************************
* Function Name  : De_save_lseek
* Description    : Configure the TIM4 Ouput Channels.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
u8 De_save_lseek(void)
	{
	u8 ret=1;
	char slk[11];
	u32 datalength=0;
	FIL fil;
	char *buffer;
	//-----------------------------------------
	Delay(5);	
	f_mount(0, &fs); 
	res = f_open(&fil, "De_lseek.txt", FA_CREATE_ALWAYS | FA_WRITE);
	if(res != FR_OK)
		{
		printf(" failed to open file\r\n");
		return ret;
		} 
	itoa(De_L_Seek, slk, 10);
	for(ret=11;ret>0;ret--)
		slk[ret] = slk[ret-1];
	ret = 1;
	slk[0] = '0';
	buffer = slk; 
	printf(" DE_LSEEK : ");
	printf(slk);
	printf("\r\n");
	datalength = strlen(buffer);
	res = f_lseek(&fil,0);//L_Seek);
	res = f_write(&fil, buffer, datalength, &bw);
	//	L_Seek += datalength;
	res = f_close(&fil);
	if(res != FR_OK)
		{
		printf(" f_close error\r\n");
		return ret;
		}
	f_mount(0, NULL);
	ret = 0;
	return ret;
	}

/*******************************************************************************
* Function Name  : App_Prog
* Description    : 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void App_Prog(void)
	{
	u16 i;
	FIL fil;
	//-----------------------------------------
	//	printf(" f_mount\r\n");
	f_mount(0, &fs);
	//	printf(" opening file\r\n");
	res = f_open(&fil, "dd.txt", FA_CREATE_ALWAYS | FA_WRITE);
	if(res != FR_OK)
		{
		printf(" failed to open file\r\n");
		return;
		}
	printf(" writing...\r\n");
	w_buffer[0] = 'T';
	w_buffer[1] = 'T';
	for(i=2; i<8192; i++)	
		w_buffer[i] = 't';
	GPIO_ResetBits(GPIOC, GPIO_Pin_7);
	//	for(i=12500; i>0; i--)	//100M
	//	{
	res = f_write(&fil, "Testing.", 8, &bw);
	//		if(bw < 8192)
	//			break;
	//	}
	//	GPIO_SetBits(GPIOC, GPIO_Pin_7);
	res = f_close(&fil);
	if(res != FR_OK)
		{
		printf(" f_close error\r\n");
		return;
		}
		f_mount(0, NULL);
	}

/*******************************************************************************
* Function Name  : Create File
* Description    : 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
u8 CreateFile(void)
	{ 
	FIL fil;
	//	BYTE *buffer; 
	Delay(5);	
	f_mount(0, &fs); 
	res = f_open(&fil, "cws_bb.txt", FA_CREATE_ALWAYS | FA_WRITE);
	if(res != FR_OK)
		{
		printf(" failed to open file\r\n");
		return 1;
		}
	res = f_close(&fil);
	if(res != FR_OK)
		{
		printf(" f_close error\r\n");
		return 1;
		}
	f_mount(0, NULL); 
	return 0;
	}

/*******************************************************************************
* Function Name  : Init BB File
* Description    : Configure the TIM4 Ouput Channels.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
u8 Initbbfile(void)
	{
	u8 ret=1;
	u32 datalength=0;
	FIL fil;
	char *buffer;

	Delay(5);	
	f_mount(0, &fs); 
	res = f_open(&fil, "cws_bb.txt", FA_CREATE_ALWAYS | FA_WRITE);
	if(res != FR_OK)
		{
		printf(" failed to open file\r\n");
		return ret;
		}
	//buffer = "Date\tTime\tSpeed\tAlarm\tBrake status\tXcord\tYcord\tRelative velocity\tTTC\tAccident\tBypass\tStatus\n"; 
	//	buffer = "Speed\tAPS1\tAPS2\t\n";
	
//	datalength = strlen(buffer);
	res = f_lseek(&fil,0);//L_Seek);
	res = f_write(&fil, buffer, datalength, &bw);
	L_Seek += datalength;
	res = f_close(&fil);
	if(res != FR_OK)
		{
		printf(" f_close error\r\n");
		return ret;
		}
	f_mount(0, NULL);
	ret = 0;
	return ret;
	}
	
	

#include ".\BB Read Write SD Card.c"	
	
#include ".\DE Read Write SD Card.c"
	

