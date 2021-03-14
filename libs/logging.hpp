#pragma once
#include <map>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>

int table_from_file(std::map<int, float> &q_table);
int table_to_file(std::map<int, float> &q_table);