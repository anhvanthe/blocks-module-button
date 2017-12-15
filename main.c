#include "vendor.h"

void blocks_initializeModule (void) {
	/* Enter your hardware initialisation code here, e.g. GPIO setup */
}

void blocks_main (void) {
	/* Enter your main run loop implementation here */
	while (1) {
		module_vendor_idle();
	}
}

const vendor_module_info_t blocks_module_info = { 
	.label    = u"Example Module", 
	.vendorID = u"Blocks Wearables Ltd.", 
	.modelID  = {0x12, 0x34, 0x56, 0x78} 
};
	
const vendor_array_handler_t blocks_module_functions = { .count = 0, {
	/* Add standard function handlers here, and update the count value */
}};
