/*
 * Blocks vendor header
 *
 * Copyright (C) 2017 BayLibre, SAS - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Author(s) :
 * LE Phong <ple@baylibre.com>
 */
#ifndef __BLOCKS_VENDOR_H__
#define __BLOCKS_VENDOR_H__

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

/* Define module label (20 wchar) */
#define BLOCKS_MODULE_LABEL				u"Sample Module"
/* Define module vendor ID (20 wchar) */
#define BLOCKS_MODULE_VENDORID			u"Blocks"
/* Define module model ID (4 bytes) */
#define BLOCKS_MODULE_MODELID			{ 0x01, 0x02, 0x03, 0x04, }

/* Define module standard function list */
#define BLOCKS_STANDARD_FUNCTIONS		{ \
	FUNC_LED_ON, \
	FUNC_LED_OFF, \
	FUNC_GPS_GET_LOCATION, \
}

/* Current API version */
#define BLOCKS_API_VERSION		0

#define ARRAY_SIZE(_A) (sizeof(_A) / sizeof((_A)[0]))

typedef enum _blocks_standard_function_ids_t
{
	FUNC_NONE					= 0x00,

	FUNC_LED_ON					= 0x01,
	FUNC_LED_OFF				= 0x02,

	FUNC_EBM_GET_STATUS			= 0x03,
	FUNC_EBM_GET_LEVEL			= 0x04,
	FUNC_EBM_GET_CAPACITY		= 0x05,
	FUNC_EBM_SET_ENABLED		= 0x28,

	FUNC_PPG_GET_HEARTRATE		= 0x06,
	FUNC_PPG_GET_HEARTRATERAW	= 0x07,
	FUNC_PPG_GET_RATE			= 0x08,
	FUNC_PPG_SET_ENABLED		= 0x0A,
	FUNC_PPG_RESET				= 0x0B,

	FUNC_GPS_START				= 0x0C,
	FUNC_GPS_STOP				= 0x0D,
	FUNC_GPS_RESET				= 0x0E,
	FUNC_GPS_GET_LOCATION		= 0x0F,
	FUNC_GPS_GET_NAV_STATUS		= 0x10,
	FUNC_GPS_GET_NMEA			= 0x11,
	FUNC_GPS_GET_DTM			= 0x12,
	FUNC_GPS_GET_GBS			= 0x13,
	FUNC_GPS_GET_GGA			= 0x14,
	FUNC_GPS_GET_GLL			= 0x15,
	FUNC_GPS_GET_GNS			= 0x18,
	FUNC_GPS_GET_GRS			= 0x1A,
	FUNC_GPS_GET_GSA			= 0x1B,
	FUNC_GPS_GET_GST			= 0x1C,
	FUNC_GPS_GET_GSV			= 0x1D,
	FUNC_GPS_GET_RMC			= 0x1E,
	FUNC_GPS_GET_TXT			= 0x1F,
	FUNC_GPS_GET_VTG			= 0x20,
	FUNC_GPS_GET_ZDA			= 0x21,
	FUNC_GPS_GET_CN				= 0x27,
	FUNC_GPS_WARM_START			= 0x35,
	FUNC_GPS_HOT_START			= 0x36,

	FUNC_HTP_GETPRESSURE		= 0x22,
	FUNC_HTP_GET_HUMIDITY		= 0x23,
	FUNC_HTP_EXTERNAL_TEMP		= 0x24,
	FUNC_HTP_RESET				= 0x25,
	FUNC_HTP_TURN_OFF			= 0x26,
	FUNC_HTP_GET_REL_ALT		= 0x42,
	FUNC_HTP_GET_REF_ALT		= 0x43,

	FUNC_BTN_GET_INFO			= 0x40,
	FUNC_LED_GET_INFO			= 0x41,

	// Notifications
	FUNC_BTN_PRESSES			= 0x101,
} blocks_standard_function_ids_t;

typedef enum _blocks_errorcode_t
{
	ERROR_NONE					= 0x00,
	ERROR_TIMED_OUT,
	ERROR_INVALID_ARGUMENT,
	ERROR_OUT_OF_MEMORY,
	ERROR_BUSY,
	ERROR_NO_CHANGE,
	ERROR_INVALID_REQUEST,
	ERROR_BAD_DATA,
	ERROR_CHECKSUM,
	ERROR_INVALID_OPERATION,
	ERROR_HARDWARE,
	ERROR_DATA_UNAVAILABLE,
	ERROR_LENGTH_EXCEEDED,
	ERROR_PENDING_OPERATION,
	ERROR_CONNECTION,
	ERROR_ASYNC_REQUEST,
	ERROR_BS,
} blocks_errorcode_t;

#define VENDOR_LABEL_MAX_LEN	30
#define VENDOR_ID_MAX_LEN		30
#define VENDOR_MODEL_ID_MAX_LEN	4

#define VENDOR_NOTIFY_NOT_READY				0xFF
#define VENDOR_NOTIFY_LOW_PRIORITY			0xFE
#define VENDOR_NOTIFY_HIGH_PRIORITY			0x01

/**
 * Maximum execution time in ticks that the vendor standard function can spend.
 * If it reaches this limit, the module will reboot.
 */
#define BLOCKS_MAX_EXECUTION_TIME			20

typedef struct _vendor_module_info_t
{
	uint16_t label [VENDOR_LABEL_MAX_LEN];
	uint16_t vendorID [VENDOR_ID_MAX_LEN];
	uint8_t modelID [VENDOR_MODEL_ID_MAX_LEN];
} vendor_module_info_t;

#define BLOCKS_MODULE_INFO { \
	BLOCKS_MODULE_LABEL, \
	BLOCKS_MODULE_VENDORID, \
	BLOCKS_MODULE_MODELID, \
}

typedef uint8_t bool;
typedef struct __attribute((packed)) blocks_GpsLocation 
{
	uint32_t lattitude;
	uint32_t longitude;
	uint32_t altitude;
	uint32_t h_accuracy;
	uint32_t v_accuracy;
} blocks_GpsLocation;


/**
 * Standard function handler.\n
 * The vendor has to implement this function which will be called when the 
 * Corehub requests a read command on I2C dynamic address.
 * This function shall not block, and shall return as quickly as possible.
 * Be careful if the runtime in this callback takes too much time, a software 
 * watchdog will force an exit and the module will reboot.
 * @return error code. 
 */
typedef blocks_errorcode_t (*LedOn) (uint8_t brightness);
typedef blocks_errorcode_t (*LedOff) (void);
typedef blocks_errorcode_t (*BatteryGetStatus) (uint8_t * blocks_BatteryStatus);
typedef blocks_errorcode_t (*BatteryGetLevel) (uint8_t * level);
typedef blocks_errorcode_t (*BatteryGetCapacity) (uint16_t * capacity);
typedef blocks_errorcode_t (*BatterySetEnabled) (bool enabled);
typedef blocks_errorcode_t (*PpgGetHeartRate) (uint8_t * rate);
typedef blocks_errorcode_t (*PpgSetEnabled) (bool enabled);
typedef blocks_errorcode_t (*GetBaroPressure) (uint16_t * pressure);
typedef blocks_errorcode_t (*GetHumidity) (uint8_t * humidity);
typedef blocks_errorcode_t (*GetTemperature) (uint8_t * temperature);
typedef blocks_errorcode_t (*GpsSetEnabled) (bool enabled);
typedef blocks_errorcode_t (*GpsGetLocation) (blocks_GpsLocation * location);
typedef blocks_errorcode_t (*BlocksStdFunction) (int dummy, ...);

typedef union blocks_standard_function
{
	BlocksStdFunction			func;
	LedOn					led_on;
	LedOff					led_off;
	BatteryGetStatus			battery_get_status;
	BatteryGetLevel				battery_get_level;
	BatteryGetCapacity			battery_get_capacity;
	BatterySetEnabled			battery_set_enabled;
	PpgGetHeartRate				ppg_get_heart_rate;
	PpgSetEnabled				ppg_set_enabled;
	GetBaroPressure				get_baro_pressure;
	GetHumidity				get_humidity;
	GetTemperature				get_temperature;
	GpsSetEnabled				gps_set_enabled;
	GpsGetLocation				gps_get_location;
} blocks_standard_function;

/**
 * Vendor initialization \n
 */
void blocks_initializeModule (void);

/**
 * Vendor main process.\n
 */
void blocks_main (void);

/**
 * Vendor notify to module that it's ready to reply to Corehub's request.\n
 * This function is implemented in module platform and shall be called in 
 * blocks_main whenever the vendor has finished its process and is ready to 
 * sendback its result to Corehub.\n
 * @param [in] priority value can be from: \n
 * - 0xFF : not ready \n
 * - 0xFE : ready with lowest priority \n
 * - 0x01 : ready with highest priority \n
 * - 0x00 : forbidden \n
 */
void blocks_notify (uint8_t notification);

void blocks_vendorNotify (uint16_t notification);

void blocks_updateBackgroundTask(size_t ticks_elapsed);

// TODO for power management
void module_vendor_idle ();

/**
 * Vendor handler.\n
 */
typedef struct _vendor_handler_t
{
        uint16_t hashcode;                             /**< standard function hashcode */
        blocks_standard_function handler;              /**< standard function handler */
} vendor_handler_t;

/**
 * Array of vendor handler.\n
 */
typedef struct _vendor_array_handler_t
{
        uint16_t count;                                /**< number of standard functions */
        vendor_handler_t funcs [];                     /**< array of vendor handlers */
} vendor_array_handler_t;

extern const vendor_module_info_t blocks_module_info __attribute__((section (".vendor_info")));
extern const vendor_array_handler_t blocks_module_functions;

#ifdef  __cplusplus
}
#endif

#endif //__BLOCKS_VENDOR_H__
