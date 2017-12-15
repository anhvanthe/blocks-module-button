INCLUDES = $(INCLUDE_PATHS:%=-I%)
OBJS     = $(CFILES:%.c=$(BUILD_DIR)%.o) $(SFILES:%.s=$(BUILD_DIR)%.o)

all: $(BUILD_DIR)fw.bin
	@echo Inserting Config
	$(shell $(BLOCKS_DIR).tools/insert-conf.py -v $(VERSION) -f $(BUILD_DIR)fw.bin -o $(BUILD_DIR)fw.flash)
	
$(BUILD_DIR)%.o: %.c
	@echo CC $@
	mkdir -p `dirname $@`
	$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)fw.o: $(OBJS)
	@echo LD $@
	$(CC) $(C_FLAGS) $(INCLUDES) $(LD_FLAGS) $(BLOCKS_DIR)/platform_$(TARGET).o lib/stm/stm_$(TARGET).o $< -o build/fw.o
	
$(BUILD_DIR)fw.bin: $(BUILD_DIR)fw.o
	@echo objcopy
	$(PREFIX)objcopy -O binary $< $@
