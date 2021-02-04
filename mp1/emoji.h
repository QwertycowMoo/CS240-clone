#pragma once

const char *emoji_favorite();
int emoji_count(char *utf8str);
void emoji_invertChar(char *utf8str);
void emoji_invertAll(char *utf8str);
char *emoji_random_alloc();