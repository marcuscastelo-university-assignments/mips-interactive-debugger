#include "print.h"
#include <stdio.h>

void printByteInt (char *arr) {
    printf("%d", (int) arr[0]);
}

void printShortInt (char *arr) {
    short value;
    sscanf(arr, "%hd", &value);
    printf("%hd", value);
}

void printInt (char *arr) {
    int value;
    sscanf(arr, "%d", &value);
    printf("%d", value);
}

void printLLInt (char *arr) {
    long long value;
    sscanf(arr, "%lld", &value);
    printf("%lld", value);
}

void printShortUns (char *arr) {
    short unsigned value;
    sscanf(arr, "%hu", &value);
    printf("%hu", value);
}

void printUns (char *arr) {
    unsigned value;
    sscanf(arr, "%u", &value);
    printf("%u", value);
}

void printLLUns (char *arr) {
    long long value;
    sscanf(arr, "%llu", &value);
    printf("%llu", value);
}

void printByteHex (char *arr) {
    printf("0x%x", (int) arr[0]);
}

void printShortHex (char *arr) {
    short value;
    sscanf(arr, "%hd", &value);
    printf("0x%hx", value);
}

void printHex (char *arr) {
    int value;
    sscanf(arr, "%d", &value);
    printf("0x%x", value);
}

void printLLHex (char *arr) {
    long long value;
    sscanf(arr, "%lld", &value);
    printf("0x%llx", value);
}

void printStr (char *arr) {
    printf("\"%s\"", arr);
}

void printChar (char *arr) {
    printf("%d: %c", (int) arr[0], arr[0]);
}

void printFloat (char *arr) {
    float value;
    sscanf(arr, "%f", &value);
    printf("%f", value);
}

void printDouble (char *arr) {
    double value;
    sscanf(arr, "%lf", &value);
    printf("%lf", value);
}