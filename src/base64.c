#include "base64.h"

static const char charset[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
								'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
								'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
								'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/' };

int index_of(const char* str, const char c)
{
	const size_t length = strlen(str);
	int i;
	for (i = 0; i < length; ++i)
		if (str[i] == c)
			return i;
	return -1;
}

char* base64_encode(const void* item, size_t size)
{
	const char* bytes = item;
	
	char* string = malloc((((4 * size / 3) + 3) & ~3) + 1);

	if (!string)
		return NULL;

	int length = 0;

	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (size--) 
	{
		char_array_3[i++] = *(bytes++);

		if (i == 3) 
		{
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++)
			{
				string[length++] = charset[char_array_4[i]];
			}

			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
		{
			char_array_3[j] = '\0';
		}

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
		{
			string[length++] = charset[char_array_4[j]];
		}

		while ((i++ < 3))
			string[length++] = '=';
	}

	string[length++] = '\0';
	return string;
}

void* base64_decode(const char* string, B64_BOOL tostring)
{
	size_t length = strlen(string);
	int i = 0;
	int j = 0;
	int s = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	int padding = 0;
	while (string[length - 1 - padding] == '=') ++padding;

	char* bytes;
	if (tostring == B64_TRUE)
	{
		int newLength = 3 * ((int)length / 4) - padding + 1;
		bytes = malloc(newLength);
		bytes[newLength - 1] = '\0';
	}
	else
	{
		bytes = malloc(3 * (length / 4) - padding);
	}


	if (!bytes)
		return NULL;
	size_t size = 0;

	while (length-- && (string[s] != '='))
	{
		char_array_4[i++] = string[s++];
		if (i == 4) 
		{
			for (i = 0; i < 4; ++i)
			{
				char_array_4[i] = index_of(charset, char_array_4[i]);
			}

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				bytes[size++] = char_array_3[i];

			i = 0;
		}
	}

	if (i) 
	{
		for (j = i; j < 4; j++)
			char_array_4[j] = 0;

		for (j = 0; j < 4; j++)
			char_array_4[j] = index_of(charset, char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++)
			bytes[size++] = char_array_3[j];
	}

	return bytes;
}
