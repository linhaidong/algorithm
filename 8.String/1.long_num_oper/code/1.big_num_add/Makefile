TARGET=long_num_char
DIRS=./
SRCS_C += $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
$(TARGET):$(SRCS_C)
	gcc -g -o $@ $^
clean:
	rm -fr $(TARGET)
