#include <user_config.h>
#include <SmingCore/SmingCore.h>
#include <SmingCore/Debug.h>
// #include "Services/CommandProcessing/CommandProcessingIncludes.h"

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
 * FunctionName : user_rf_cal_sector_set
 * Description  : SDK just reversed 4 sectors, used for rf init data and paramters.
 *                We add this function to force users to set rf cal sector, since
 *                we don't know which sector is free in user's application.
 *                sector map for last several sectors : ABCCC
 *                A : rf cal
 *                B : rf init data
 *                C : sdk parameters
 * Parameters   : none
 * Returns      : rf cal sector
*******************************************************************************/
uint32 ICACHE_FLASH_ATTR
user_rf_cal_sector_set(void)
{
	enum flash_size_map size_map = system_get_flash_size_map();
	uint32 rf_cal_sec = 0;

	switch (size_map) {
		case FLASH_SIZE_4M_MAP_256_256:
			rf_cal_sec = 128 - 5;
			break;

		case FLASH_SIZE_8M_MAP_512_512:
			rf_cal_sec = 256 - 5;
			break;

		case FLASH_SIZE_16M_MAP_512_512:
		case FLASH_SIZE_16M_MAP_1024_1024:
			rf_cal_sec = 512 - 5;
			break;

		case FLASH_SIZE_32M_MAP_512_512:
		case FLASH_SIZE_32M_MAP_1024_1024:
			rf_cal_sec = 1024 - 5;
			break;

		default:
			rf_cal_sec = 0;
			break;
	}

	return rf_cal_sec;
}
#ifdef __cplusplus
}
#endif

void help(String commandLine  ,CommandOutput* commandOutput)
{
	commandOutput->printf("Hello from Telnet Example application\r\nYou entered : '");
	commandOutput->printf(commandLine.c_str());
	commandOutput->printf("'\r\n");
	commandOutput->printf("Tokenized commandLine is : \r\n");
}

void appheapCommand(String commandLine  ,CommandOutput* commandOutput)
{
	Vector<String> commandToken;
	int numToken = splitString(commandLine, ' ' , commandToken);
	if (numToken != 2)
	{
		commandOutput->printf("Usage appheap on/off/now\r\n");
	}
	else if (commandToken[1] == "on")
	{
		commandOutput->printf("Timer heap display started \r\n");
	}
	else if (commandToken[1] == "off")
	{
		commandOutput->printf("Timer heap display stopped \r\n");
	}
	else if (commandToken[1] == "now")
	{
		commandOutput->printf("Heap current free = %d\r\n", system_get_free_heap_size());
	}
	else
	{
		commandOutput->printf("Usage appheap on/off/now\r\n");
	}
}

void initializeApplication(void) {
	Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
	Serial.systemDebugOutput(false); // Enable debug output to serial
	Serial.commandProcessing(true);
	WifiStation.enable(false);
	WifiAccessPoint.enable(false);

	// Serial.setCallback(serialCallBack);
	commandHandler.registerCommand(CommandDelegate("help","Usage help\r\n","netcut", help));
}

void showResult(bool result) {

}

void init()
{
	initializeApplication();
}
