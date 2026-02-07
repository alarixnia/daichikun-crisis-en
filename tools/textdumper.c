#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char *charset[256];
char *altset[256];

/*
 * Public domain.
 */

void *
read_file_full(const char *path, size_t *len)
{
	FILE *file = fopen(path, "rb");
	if (file == NULL) {
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	fseek(file, 0, SEEK_SET);

	uint8_t *buffer = malloc(length);
	if (buffer == NULL) {
		fclose(file);
		return NULL;
	}

	fread(buffer, 1, length, file);
	fclose(file);

	if (len != NULL) {
		*len = (size_t)length;
	}

	return buffer;
}

int
main(int argc, char **argv)
{
	bool altfont = false;

	charset[0x0a] = "\n";
	charset[0x0e] = "[/altfont]";
	charset[0x0f] = "[altfont]";
	charset[0x20] = " ";
	charset[0x21] = "!";
	charset[0x22] = "\"";
	charset[0xa1] = "。";
	charset[0xa2] = "「";
	charset[0xa3] = "」";
	charset[0xa4] = "、";
	charset[0xa6] = "を";
	charset[0xa8] = "ィ";
	charset[0xaa] = "ぇ";
	charset[0xac] = "ゃ";
	charset[0xad] = "ゅ";
	charset[0xae] = "ょ";
	charset[0xaf] = "っ";
	charset[0xb0] = "ー";
	charset[0xb1] = "あ";
	charset[0xb2] = "い";
	charset[0xb3] = "う";
	charset[0xb4] = "え";
	charset[0xb5] = "お";
	charset[0xb6] = "か";
	charset[0xb7] = "き";
	charset[0xb8] = "く";
	charset[0xb9] = "け";
	charset[0xba] = "こ";
	charset[0xbb] = "さ";
	charset[0xbc] = "し";
	charset[0xbd] = "す";
	charset[0xbe] = "せ";
	charset[0xbf] = "そ";
	charset[0xc0] = "た";
	charset[0xc1] = "ち";
	charset[0xc2] = "つ";
	charset[0xc3] = "て";
	charset[0xc4] = "と";
	charset[0xc5] = "な";
	charset[0xc6] = "に";
	charset[0xc7] = "ぬ";
	charset[0xc8] = "ね";
	charset[0xc9] = "の";
	charset[0xca] = "は";
	charset[0xcb] = "ひ";
	charset[0xcc] = "ふ";
	charset[0xcd] = "へ";
	charset[0xce] = "ほ";
	charset[0xcf] = "ま";
	charset[0xd0] = "み";
	charset[0xd1] = "む";
	charset[0xd2] = "め";
	charset[0xd3] = "も";
	charset[0xd4] = "や";
	charset[0xd5] = "ゆ";
	charset[0xd6] = "よ";
	charset[0xd7] = "ら";
	charset[0xd8] = "り";
	charset[0xd9] = "る";
	charset[0xda] = "れ";
	charset[0xdb] = "ろ";
	charset[0xdc] = "わ";
	charset[0xdd] = "ん";
	charset[0xde] = "゛";
	charset[0xdf] = "゜";

	memcpy(altset, charset, sizeof(charset));

	altset[0xb1] = "ア";
	altset[0xb2] = "イ";
	altset[0xb3] = "ウ";
	altset[0xb4] = "エ";
	altset[0xb5] = "オ";
	altset[0xb6] = "カ";
	altset[0xb7] = "キ";
	altset[0xb8] = "ク";
	altset[0xb9] = "ケ";
	altset[0xba] = "コ";
	altset[0xbb] = "サ";
	altset[0xbc] = "シ";
	altset[0xbd] = "ス";
	altset[0xbe] = "セ";
	altset[0xbf] = "ソ";
	altset[0xc0] = "タ";
	altset[0xc1] = "チ";
	altset[0xc2] = "ツ";
	altset[0xc3] = "テ";
	altset[0xc4] = "ト";
	altset[0xc5] = "ナ";
	altset[0xc6] = "ニ";
	altset[0xc7] = "ヌ";
	altset[0xc8] = "ネ";
	altset[0xc9] = "ノ";
	altset[0xca] = "ハ";
	altset[0xcb] = "ヒ";
	altset[0xcc] = "フ";
	altset[0xd3] = "モ";
	altset[0xd7] = "ラ";
	altset[0xd8] = "リ";	
	altset[0xd9] = "ル";
	altset[0xda] = "レ";
	altset[0xdb] = "ロ";
	altset[0xdc] = "ワ";
	altset[0xdd] = "ン";

	size_t len;
	char *buf = read_file_full(argv[1], &len);
	if (buf == NULL) {
		printf("failed to read\n");
		return 1;
	}
	for (size_t i = 0; i < len; ++i) {
		uint8_t ch = buf[i] & 0xff;
		if (ch == 0x0f) {
			altfont = true;
		} else if (ch == 0x0e) {
			altfont = false;
		} else if (ch >= '0' && ch <= '9') {
			fputc(ch, stdout);
		} else if (ch >= 'A' && ch <= 'Z') {
			fputc(ch, stdout);
		} else if (charset[ch] != NULL) {
			printf("%s", altfont ? altset[ch] : charset[ch]);
		} else {
			printf("?");
		}
	}
	printf("\n");
	return 0;
}
