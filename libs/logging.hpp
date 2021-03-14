#pragma once
#include <map>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "constants.hpp"

int table_from_file(std::map<int, float> &q_table, int player_id);
int table_to_file(std::map<int, float> &q_table, int player_id);