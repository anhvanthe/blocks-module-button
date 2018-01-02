/* main.c - (c) 2017 Blocks Wearables Ltd. */
#include <vendor.h>
#include "btn.h"

static bool res = true;

void blocks_initializeModule(void)
{
	res = Button_init();

	// TODO: Enable once vendor-notify confirmed working
	//if (!Button_init()) {
		//blocks_vendorNotify(0xFF); // ModuleError
	//}
}

void Button_handle_press(void)
{
	blocks_vendorNotify(0x101); // ButtonPressed
}

void blocks_main(void)
{
	while (1) {
		module_vendor_idle();
		blocks_vendorNotify(res ? 0xBEEF : 0xFA11);
	}
}

const vendor_module_info_t blocks_module_info = {
	.label    = u"Button Module",
	.vendorID = u"Blocks Wearables Ltd.",
	.modelID  = {0x12, 0x34, 0x56, 0x78}
};

/* Register "get info" dummy function to indicate button-press capability */
const vendor_array_handler_t blocks_module_functions = { .count = 0, {
	{FUNC_BTN_GET_INFO, NULL} /* Will never be invoked */
}};
