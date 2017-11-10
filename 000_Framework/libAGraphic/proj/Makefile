OBJS=*.o
ODIR=linux/obj
$(ROOT_DIR)/$(BIN_DIR)/$(BIN):$(ODIR)/$(OBJS)
	$(CXX) -shared -fPIC $(CFLAGS) -o $@ $^
