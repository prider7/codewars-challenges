CC = gcc
CFLAGS = -std=c18 -Wall -Wextra -O0 -g
LDLIBS = -lm

TARGETS = high_and_low \
	get_count \
	bonus_time \
	is_ordered \
	get_the_vowels \
	is_anagram \
	count_codepoints \
	strclr \
	is_valid_ip \
	longest \
	order_words \
	decode_roman \
	find_date \
	run_length_encoding \
	letters_to_numbers

.PHONY: all clean reformat run vrun

all: $(TARGETS)

%: %.c %_main.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

clean:
	rm -f $(TARGETS)

reformat:
	clang-format --style=Chromium -i *.c

run:
	./`zenity --title="Execute Program" --height 600 --list --text="Choose Executable" --column=Executable $(TARGETS)`

vrun:
	valgrind --leak-check=full --show-error-list=yes ./`zenity --title="Valgrind Program" --height 600 --list --text="Choose Executable" --column=Executable $(TARGETS)`
