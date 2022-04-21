#include "main.h"

/**
 * handle_length - matches length modifiers with their corresponding value.
 * @modifier: A pointer to a potential length modifier.
 * @index: An index counter for the original format string.
 *
 * Return: If a length modifier is matched its corresponding value
 * Otherwise 0.
 */
unsigned char handle_length(const char *modifier, char *index)
{
	int SHORT, LONG;

	if (*modifier == 'h')
	{
		(*index)++;
		return (SHORT);
	}

	else if (*modifier == 'l')
	{
		(*index)++;
		return (LONG);
	}

	return (0);
}

/**
 * handle_width - matches a width modifier with its corresponding value.
 * @args: a va_list of arguments.
 * @modifier: A pointer to a potential modifier.
 * @index: An index counter for the original format string.
 *
 * Return: if a width modifier is matched - its value
 * otherwise - 0.
 */
int handle_width(va_list args, const char *modifier, char *index)
{
	int value = 0;

	while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * handle_precision - matches a precision modifier with its corresponding
 * value
 * @args: a va_list of arguments.
 * @modifier: a pointer to a potential precision modifier.
 * @index: An index counter for the original format string.
 *
 * Return: if a precision modifier is matched - its value.
 * if the precision modifier is empty, zero, or negative - 0.
 * other wise - -1.
 */
int handle_precision(va_list args, const char *modifier, char *index)
{
	int value = 0;

	if (*modifier != '.')
		return (-1);

	modifier++;
	(*index)++;

	if ((*modifier <= '0' || *modifier > '9') &&
			*modifier != '*')
	{
		if (*modifier == '0')
			(*index)++;
		return (0);
	}

	while ((*modifier >= '0' && *modifier <= '9') ||
			(*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}
