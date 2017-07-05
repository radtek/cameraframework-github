OBJS=*.o
ODIR=linux/obj
$(ROOT_DIR)/$(BIN_DIR)/$(BIN):$(ODIR)/$(OBJS)
	$(CC) -shared -fPIC $(CFLAGS) -o $@ $^
	