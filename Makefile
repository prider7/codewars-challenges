CC = gcc
CFLAGS = -std=c18 -Wall -Wextra -O0 -g
LDLIBS = -lm

TARGETS = \
	adding_big_numbers \
	alphabet_position \
	array_exchange \
	bonus_time \
	count_codepoints \
	decode_roman \
	evaporator \
	find_date \
	find_the_odd_int \
	format_duration \
	get_count \
	get_the_vowels \
	high_and_low \
	human_readable_time \
	irreducible_sum_of_rationals \
	is_anagram \
	is_ordered \
	is_valid_ip \
	is_valid_ISBN_10 \
	land_perimeter \
	letters_to_numbers \
	longest \
	multply_number_strings \
	number_proper_fractions \
	order_words \
	range_extraction \
	rational_arithmetic \
	roman_num_encoder \
	roman_num_helper \
	rotate \
	run_length_encoding \
	scramble \
	skyscrapers_4x4_puzzle \
	skyscrapers_6x6_puzzle \
	skyscrapers_7x7_puzzle \
	strclr \
	sum_number_strings \
	ten_minutes_walk

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
