#include "main.h"
/**
 * handle_print - Prints an argument based on its type
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @index: current index in the string.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: 1 or 2;
 */
int handle_print(const char *fmt, int *index, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, uk_len = 0, printed_chars = -1;
	fmt_t fmt_categories[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_categories[i].fmt != '\0'; i++)
		if (fmt[*index] == fmt_categories[i].fmt)
			return (fmt_categories[i].fn(list, buffer, flags, width, precision, size));

	if (fmt_categories[i].fmt == '\0')
	{
		if (fmt[*index] == '\0')
			return (-1);
		uk_len += write(1, "%%", 1);
		if (fmt[*index - 1] == ' ')
			uk_len += write(1, " ", 1);
		else if (width)
		{
			--(*index);
			while (fmt[*index] != ' ' && fmt[*index] != '%')
				--(*index);
			if (fmt[*index] == ' ')
				--(*index);
			return (1);
		}
		uk_len += write(1, &fmt[*index], 1);
		return (uk_len);
	}
	return (printed_chars);
}
