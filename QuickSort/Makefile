CC = gcc-cilkplus-4.7
LIBS = -lcilkrts

# add the names of the object files to be generated from your source files
# (multiple files are OK).
OBJS = qsort.o 

qsort: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

%.o : %.cc
	$(CC) -c -o $@ $<
	$(CC) -MM -MP -MT $@ -MF $(basename $@).d $<

.PHONY : clean
clean :
	rm -f *.o *~ *.d qsort

## include the generated dependency files
-include $(addsuffix .d,$(basename $(OBJS)))
