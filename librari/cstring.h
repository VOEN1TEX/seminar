#ifndef CSTRING_H
#define CSTRING_H
#include <iostream>

class 

std::size_t Strlen(const char* str);

int Strcmp(const char* first, const char* second);

int Strncmp(const char* first, const char* second, std::size_t count);

char* Strcpy(char* dest, const char* src);

char* Strncpy(char* dest, const char* src, std::size_t count);

char* Strcat(char* dest, const char* src);

char* Strncat(char* dest, const char* src, std::size_t count);

const char* Strchr(const char* str, char symbol);

const char* Strrchr(const char* str, char symbol);

std::size_t Strspn(const char* dest, const char* src);

std::size_t Strcspn(const char* dest, const char* src);

const char* Strpbrk(const char* dest, const char* breakset);

const char* Strstr(const char* str, const char* pattern);
#endif
