#pragma once

#include <stdio.h>
#include <unistd.h>

#include <env.h>
#include <ext.h>

static int file_ex(const char* file_path);

const char* read_f(const char* file_path);
void process_to(const char* file_path);
map_array extract_from_f(const char* file_path);
map_array extract_from_s(char* file_cstring);
