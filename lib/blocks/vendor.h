/* vendor.h - (c) 2017 Blocks Wearables Ltd. */
#pragma once

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* Current API version */
#define BLOCKS_API_VERSION 0

#define VENDOR_LABEL_MAX_LEN 30
#define VENDOR_ID_MAX_LEN 30
#define VENDOR_MODEL_ID_MAX_LEN 4

/**
 * Maximum execution time in ticks that the vendor standard function can spend.
 * If it reaches this limit, the module will reboot.
 */
#define BLOCKS_MAX_EXECUTION_TIME 20


typedef enum _blocks_standard_function_id
{
    STDFUNC_NONE                 = 0x00,

    STDFUNC_LED_ON               = 0x01,
    STDFUNC_LED_OFF              = 0x02,

    STDFUNC_EBM_GET_STATUS       = 0x03,
    STDFUNC_EBM_GET_LEVEL        = 0x04,
    STDFUNC_EBM_GET_CAPACITY     = 0x05,
    STDFUNC_EBM_SET_ENABLED      = 0x28,

    STDFUNC_PPG_GET_HEARTRATE    = 0x06,
    STDFUNC_PPG_GET_HEARTRATERAW = 0x07,
    STDFUNC_PPG_GET_RATE         = 0x08,
    STDFUNC_PPG_SET_ENABLED      = 0x0A,
    STDFUNC_PPG_RESET            = 0x0B,

    STDFUNC_GPS_START            = 0x0C,
    STDFUNC_GPS_STOP             = 0x0D,
    STDFUNC_GPS_RESET            = 0x0E,
    STDFUNC_GPS_GET_LOCATION     = 0x0F,
    STDFUNC_GPS_GET_NAV_STATUS   = 0x10,
    STDFUNC_GPS_GET_NMEA         = 0x11,
    STDFUNC_GPS_GET_DTM          = 0x12,
    STDFUNC_GPS_GET_GBS          = 0x13,
    STDFUNC_GPS_GET_GGA          = 0x14,
    STDFUNC_GPS_GET_GLL          = 0x15,
    STDFUNC_GPS_GET_GNS          = 0x18,
    STDFUNC_GPS_GET_GRS          = 0x1A,
    STDFUNC_GPS_GET_GSA          = 0x1B,
    STDFUNC_GPS_GET_GST          = 0x1C,
    STDFUNC_GPS_GET_GSV          = 0x1D,
    STDFUNC_GPS_GET_RMC          = 0x1E,
    STDFUNC_GPS_GET_TXT          = 0x1F,
    STDFUNC_GPS_GET_VTG          = 0x20,
    STDFUNC_GPS_GET_ZDA          = 0x21,
    STDFUNC_GPS_GET_CN           = 0x27,
    STDFUNC_GPS_WARM_START       = 0x35,
    STDFUNC_GPS_HOT_START        = 0x36,

    STDFUNC_HTP_GETPRESSURE      = 0x22,
    STDFUNC_HTP_GET_HUMIDITY     = 0x23,
    STDFUNC_HTP_EXTERNAL_TEMP    = 0x24,
    STDFUNC_HTP_RESET            = 0x25,
    STDFUNC_HTP_TURN_OFF         = 0x26,
    STDFUNC_HTP_GET_REL_ALT      = 0x42,
    STDFUNC_HTP_GET_REF_ALT      = 0x43,

    STDFUNC_BTN_GET_INFO         = 0x40,
    STDFUNC_LED_GET_INFO         = 0x41,

    // Notifications
    STDFUNC_BTN_PRESSES          = 0x101,
} blocks_standard_function_id_t;


typedef enum _blocks_notification
{
	NOTIFY_MODULE_ERROR   = 0xFF,
	NOTIFY_BUTTON_PRESSED = 0x101
} blocks_notification_t;


typedef enum _blocks_errorcode_t
{
    BLOCKS_ERROR_NONE = 0x00,
    BLOCKS_ERROR_TIMED_OUT,
    BLOCKS_ERROR_INVALID_ARGUMENT,
    BLOCKS_ERROR_OUT_OF_MEMORY,
    BLOCKS_ERROR_BUSY,
    BLOCKS_ERROR_NO_CHANGE,
    BLOCKS_ERROR_INVALID_REQUEST,
    BLOCKS_ERROR_BAD_DATA,
    BLOCKS_ERROR_CHECKSUM,
    BLOCKS_ERROR_INVALID_OPERATION,
    BLOCKS_ERROR_HARDWARE,
    BLOCKS_ERROR_DATA_UNAVAILABLE,
    BLOCKS_ERROR_LENGTH_EXCEEDED,
    BLOCKS_ERROR_PENDING_OPERATION,
    BLOCKS_ERROR_CONNECTION,
    BLOCKS_ERROR_ASYNC_REQUEST
} blocks_errorcode_t;


typedef struct _vendor_module_info_t
{
    uint16_t label [VENDOR_LABEL_MAX_LEN];
    uint16_t vendorID [VENDOR_ID_MAX_LEN];
    uint8_t modelID [VENDOR_MODEL_ID_MAX_LEN];
} vendor_module_info_t;


typedef struct __attribute((packed)) _blocks_gps_location_t
{
    uint32_t latitude;
    uint32_t longitude;
    uint32_t altitude;
    uint32_t h_accuracy;
    uint32_t v_accuracy;
} blocks_gps_location_t;


typedef enum _blocks_battery_status_t
{
	BLOCKS_BATTERY_CHARGING    = 0x1,
	BLOCKS_BATTERY_IDLE        = 0x2,
	BLOCKS_BATTERY_DISCHARGING = 0x3,
	BLOCKS_BATTERY_UNAVAILABLE = 0x4,
} blocks_battery_status_t;


typedef struct __attribute((packed))
{
	uint16_t length;
	char data[];
} blocks_string;


typedef struct __attribute((packed))
{
	uint16_t length;
	char data[];
} blocks_buffer;


/**
 * Standard function handler.
 * The vendor has to implement this function which will be called when the
 * Corehub requests a read command on I2C dynamic address.
 * This function shall not block, and shall return as quickly as possible.
 * Be careful if the runtime in this callback takes too much time, a software
 * watchdog will force an exit and the module will reboot.
 * @return error code.
 */
typedef blocks_errorcode_t (*Blocks_LedOn) (uint8_t brightness);
typedef blocks_errorcode_t (*Blocks_LedOff) (void);
typedef blocks_errorcode_t (*Blocks_BatteryGetStatus) (blocks_battery_status_t* status);
typedef blocks_errorcode_t (*Blocks_BatteryGetLevel) (uint8_t* level);
typedef blocks_errorcode_t (*Blocks_BatteryGetCapacity) (uint16_t* capacity);
typedef blocks_errorcode_t (*Blocks_BatterySetEnabled) (bool enabled);
typedef blocks_errorcode_t (*Blocks_PpgGetHeartRate) (uint8_t* heartrate);
typedef blocks_errorcode_t (*Blocks_PpgGetHeartRateRaw) (blocks_buffer* data);
typedef blocks_errorcode_t (*Blocks_PpgGetRate) (uint8_t* rate);
typedef blocks_errorcode_t (*Blocks_PpgSetEnabled) (bool enabled);
typedef blocks_errorcode_t (*Blocks_PpgReset) (void);
typedef blocks_errorcode_t (*Blocks_GetBaroPressure) (uint16_t* pressure);
typedef blocks_errorcode_t (*Blocks_GetHumidity) (uint8_t* humidity);
typedef blocks_errorcode_t (*Blocks_GetTemperature) (uint8_t* temperature);
typedef blocks_errorcode_t (*Blocks_GpsSetEnabled) (bool enabled);
typedef blocks_errorcode_t (*Blocks_GpsGetLocation) (blocks_gps_location_t* location);
typedef blocks_errorcode_t (*Blocks_BlocksStdFunction) (int dummy, ...);


typedef union _blocks_standard_function
{
    Blocks_BlocksStdFunction  func;
    Blocks_LedOn              led_on;
    Blocks_LedOff             led_off;
    Blocks_BatteryGetStatus   battery_get_status;
    Blocks_BatteryGetLevel    battery_get_level;
    Blocks_BatteryGetCapacity battery_get_capacity;
    Blocks_BatterySetEnabled  battery_set_enabled;
    Blocks_PpgGetHeartRate    ppg_get_heart_rate;
    Blocks_PpgGetHeartRateRaw ppg_get_heart_rate_raw;
    Blocks_PpgGetRate         ppg_get_rate;
    Blocks_PpgSetEnabled      ppg_set_enabled;
    Blocks_PpgReset           ppg_reset;
    Blocks_GetBaroPressure    get_baro_pressure;
    Blocks_GetHumidity        get_humidity;
    Blocks_GetTemperature     get_temperature;
    Blocks_GpsSetEnabled      gps_set_enabled;
    Blocks_GpsGetLocation     gps_get_location;
} blocks_standard_function;

/**
 * Vendor-defined initialization function. Called before main module operation.
 */
void blocks_initializeModule(void);

/**
 * Vendor main process. Returning from this function will cause the module to reboot.
 */
void blocks_main(void);

/**
 * Notifies the Core of the given event. Certain notification
 * types may have additional behavior.
 */
void blocks_notify(blocks_notification_t notification);

/**
 * Allows the vendor to define a routine to run in the background
 * without requiring a standard function to be called.
 *
 * @param ticks_elapsed The number of ticks since the previous invocation.
 */
void blocks_updateBackgroundTask(size_t ticks_elapsed);

/**
 * Call from within `blocks_main` to enable power saving.
 */
void module_vendor_idle();

/**
 * Vendor handler.
 */
typedef struct _vendor_handler_t
{
    uint16_t hashcode;                /**< standard function hashcode */
    blocks_standard_function handler; /**< standard function handler */
} vendor_handler_t;

/**
 * Array of vendor handlers.
 */
typedef struct _vendor_array_handler_t
{
    uint16_t count;           /**< number of standard functions */
    vendor_handler_t funcs[]; /**< array of vendor handlers */
} vendor_array_handler_t;

extern const vendor_module_info_t blocks_module_info __attribute__((section (".vendor_info")));
extern const vendor_array_handler_t blocks_module_functions;

#ifdef  __cplusplus
}
#endif
