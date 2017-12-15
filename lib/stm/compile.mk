STM_CFILES = $(STM_SRC_FILES)
STM_SFILES = $(STM_GCC_FILES)

STM_OBJS = $(STM_CFILES:%.c=$(BUILD_DIR)/%.o) $(STM_SFILES:%.s=$(BUILD_DIR)/%.o)

STM_LIB = $(BUILD_DIR)/stm_$(TARGET).o

$(STM_LIB): $(STM_OBJS) 
	@echo Partial Linking STM Objects
	$(LD) -r $(STM_OBJS) -o $(BUILD_DIR)/stm_$(TARGET).o
	
$(BUILD_DIR)/%.o: %.c
	@echo CC $@
	@-mkdir -p `dirname $@`
	$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.o: %.s
	@echo CC $@
	@-mkdir -p `dirname $@`
	@$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@
