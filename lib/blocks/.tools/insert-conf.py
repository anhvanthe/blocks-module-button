#!/usr/bin/env python

import os
import sys
import struct
import string
import argparse

BOOTLOADER_SEARCH_TAG = 0xDA7ADA7A
BOOTLOADER_CONF_TAG = 0xB10CDA7A

'''
Target conf structure :
{
	little endian unsigned long int (4) : 0xB10CDA7A
	little endian unsigned long int (4) : filesize
	little endian unsigned long int (4) : reserved
	little endian unsigned long int (4) : version
}
'''
def pack_data(version, filesize):
	return "%s" % (struct.pack("<IIII", BOOTLOADER_CONF_TAG, filesize, 0, version))

def firmware_insert_conf(firmware, data, output):
	# Convert as little endian
	tag = struct.pack("<I", BOOTLOADER_SEARCH_TAG);

	plaintext = firmware.read()

	start = plaintext.rfind(tag)

	if start == -1:
		print >> sys.stderr, "Start marker not found"
        	sys.exit(1)

	output.write(plaintext)
	output.seek(start)
	output.write(data)

if __name__ == '__main__':
	parser = argparse.ArgumentParser(description='Module Firmware Configuration')
	parser.add_argument('-v', '--version', dest='version', default=None, type=int, 
			    help="Module configuration file")
	parser.add_argument('-f', '--firmware', dest='firmware', default=None, 
			    help="Firmware binary file source")
	parser.add_argument('-o', '--output', dest='output', default=None, 
			    help="Firmware binary OTA file to output")
	args = parser.parse_args()

	filesize = os.path.getsize(args.firmware)

	data = pack_data(args.version, filesize)

	with open(args.firmware, "r") as firmware:
		with open(args.output, "w") as output:
			firmware_insert_conf(firmware, data, output)

	sys.exit(0)
