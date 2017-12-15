# BLOCKS Module Platform - Template
This repo contains everything you need to start developing for a BLOCKS smartwatch module using the Module Platform and API. [Learn more about BLOCKS here](https:/wwww.chooseblocks.com).

## Prerequisites
In order to compile firmware for a module, you will need to have the GNU ARM Embedded toolchain `arm-none-eabi-*` installed on your system. 

## Getting Started
To get started, open the `main.c` file included in this template. It contains the required definitions to use the Blocks module platform. These are:

- Setup Function: `void blocks_initializeModule (void)`
  - This is where you should write the hardware initialisation code for your module. This function should return in a timely manner and should not perform any long running operations, as this will impact the registration time of the module.

- Main Loop: `void blocks_main (void)`
  - This function should contain the main run loop for your module. Here you can perform long running tasks. Context switching is performed automatically by the module platform in order to process and respond to module messages, and so you can process within this loop indefinitely without affecting module responsiveness.
  - **NOTE**: When the module is idle, the vendor should call `module_vendor_idle ()` to put the module into sleep mode. The module will wake up the next time it recieves a message from the core. 
  
- Module Info Struct: `const vendor_module_info_t blocks_module_info`
  - This struct defines the module information which will be reported to the core device:
    - Label: The name of the module
    - Vendor ID: The name of the vendor
    - Model ID: The hardware model number
    
- Supported Functions Struct: `const vendor_array_handler_t blocks_module_functions`
  - This struct defines which standard functions the module supports, and their associated handlers. 
 
For example, to register handlers for the LED_ON and LED_OFF messages:
```
static blocks_errorcode_t led_on (uint8_t brightness) { ... }
static blocks_errorcode_t led_off (void) { ... }

const vendor_array_handler_t blocks_module_functions = { .count = 2, {
	{FUNC_LED_ON,  (blocks_standard_function)led_on},
	{FUNC_LED_OFF, (blocks_standard_function)led_off}
}};
```

The functions `led_on` and `led_off` will then be called as a handler whenever the module platform loop recieves those messages. 

### Standard Function Handlers
The Blocks module platform defines a set of *Standard Function* signatures that allow module developers to support generic module actions. This allows app developers to make use of arbitrary module hardware as long as it implements the standard functions they need. 

Standard function handlers *must not execute for more than 20ms* since they are executed in the main event thread. Therefore, in the event that a standard function call needs to initiate a long running operation, it should simply set a flag to notify the main event loop to begin the processing, and then return immediately. 

### Response notifications
The main run loop is able to call for the attention of the CoreHub using the `blocks_vendorNotify` function. (TODO)

## Building
The module platform can currently be built for STM32L052 (default) and STM32L476 targets. To build, run `make (TARGET=[STM32L0X2|STM32L4X6])`, or just `make` to use the default target.

To add `.c` files to your project, edit the `Makefile` and add your files to the `CFILES` variable.
To add `.h` files to your project, edit the `Makefile` and add the include directory to the `INCLUDE_PATHS` variable.
