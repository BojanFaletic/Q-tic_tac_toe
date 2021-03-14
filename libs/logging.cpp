#include "logging.hpp"

const char *q_table_fname = "model/q_table.dat";
const char *q_table_fname_p1 = "model/q_table_p1.dat";
const char *q_table_fname_p2 = "model/q_table_p2.dat";

int split_name_and_path(std::string full_fname, std::string &folder, std::string &name)
{
  int split_idx = full_fname.rfind('/');
  if (split_idx != std::string::npos)
  {
    folder = full_fname.substr(0, split_idx);
    name = full_fname.substr(split_idx + 1);
    return EXIT_SUCCESS;
  }
  folder = "error";
  name = "error.error";
  return EXIT_FAILURE;
}

void create_folder(const std::string f_name)
{
  std::filesystem::path dir(f_name);
  if (!std::filesystem::is_directory(f_name))
  {
    std::filesystem::create_directory(f_name);
  }
}

int table_to_file(std::map<int, float> &q_table, int player_id)
{

  std::string folder, name;
  if (split_name_and_path(q_table_fname, folder, name))
  {
    return EXIT_FAILURE;
  }
  create_folder(folder);

  std::ofstream outfile;
  if (player_id == board::PLAYER1)
  {
    outfile.open(q_table_fname_p1);
  }
  else if (player_id == board::PLAYER2)
  {
    outfile.open(q_table_fname_p2);
  }
  else
  {
    return EXIT_FAILURE;
  }

  int size_of_map = q_table.size();
  int idx = 0;
  if (outfile.is_open())
  {
    for (auto it = q_table.begin(); it != q_table.end(); it++)
    {
      if (it->second == 0)
      {
        continue;
      }
      outfile << it->first << ":" << it->second;
      idx++;
      if (idx != size_of_map)
      {
        outfile << "\n";
      }
    }
    outfile.close();
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int table_from_file(std::map<int, float> &q_table, int player_id)
{
  std::string folder, name;
  if (split_name_and_path(q_table_fname, folder, name))
  {
    return EXIT_FAILURE;
  }

  std::ifstream instream;
  if (player_id == board::PLAYER1)
  {
    instream.open(q_table_fname_p1);
  }
  else if (player_id == board::PLAYER2)
  {
    instream.open(q_table_fname_p2);
  }
  else
  {
    return EXIT_FAILURE;
  }

  if (!instream.is_open())
  {
    std::cout << "No model file found!\n";
  }
  else
  {
    std::string line;
    q_table.clear();
    while (std::getline(instream, line))
    {
      std::string key, value;
      int it = line.rfind(':');
      if (it != std::string::npos)
      {
        key = line.substr(0, it);
        value = line.substr(it + 1);
        try
        {
          q_table[std::stoi(key)] = std::stof(value);
        }
        catch (std::invalid_argument)
        {
          std::cout << "Model corrupted\n";
          instream.close();
          return EXIT_FAILURE;
        }
      }
      else
      {
        instream.close();
        return EXIT_FAILURE;
      }
    }

    instream.close();
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}