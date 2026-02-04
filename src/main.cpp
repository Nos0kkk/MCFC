/* MCFC - MC Function Creator */

#include <stdlib.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>

#include <json/json.h>
#include <fmt/core.h>
#include <fmt/color.h>

void clear() {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void create_shaded_dir(const std::string& pach) {
  try {
    if (!std::filesystem::exists(pach)) {
    std::filesystem::create_directories(pach);
    if (!std::filesystem::exists(pach)) {
      throw std::runtime_error("failed to create directory.");
    }
   }
  } catch (const std::exception& ex) {
    std::cerr << "Error: " << ex.what() << std::endl;
  }
}

int main() {
  clear();
  Json::Value setting;
  try {
  std::ifstream ReadJson("config/setting.json");
  ReadJson >> setting;
  } catch (const Json::RuntimeError &e) {
    std::cerr << "Json error: " << e.what() << std::endl;
  }
  
  std::ofstream FileLog("logs/fclog.log");
  
  fmt::print(fmt::fg(fmt::color::magenta), "<~~[McFunctionCreator]~~>\n");
  fmt::print(fmt::fg(fmt::color::cyan), "[1]:  start\n");
  fmt::print(fmt::fg(fmt::color::cyan), "[2]: settings (unlocked)\n");
  fmt::print(fmt::fg(fmt::color::cyan), "[3]: exit\n");
  fmt::print(fmt::fg(fmt::color::blue), "[1/2/3]: ");
  FileLog << "pojav MCFC\n";
  
  int vibor;
  std::cin >> vibor;
  std::cout << std::endl;
  
  if (vibor != 1) {
    if (setting["inputLog"].asBool() == true) {
      FileLog << "extra exit: 1\n";
    }
    return 1;
  }
  
  clear();
  fmt::print(fmt::fg(fmt::color::cyan), "- directory /path/to/your/world: ");
  std::cin.ignore();
  std::string directory;
  getline(std::cin, directory);
  std::cout << std::endl;
  
  size_t LastWorldForLog = directory.find_last_of("/");
  
  std::string WorldForLog = directory.substr(LastWorldForLog + 1);
  
  if (setting["inputLog"].asBool() == true) {
    FileLog << "add path to world: " << "[" << WorldForLog << "] full path ...\n";
  }
  
  clear();
  std::string mcnamespace;
  fmt::print(fmt::fg(fmt::color::cyan), "- name for namespace: ");
  std::cin >> mcnamespace;
  std::cout << std::endl;
  
  if (setting["inputLog"].asBool() == true) {
    if (mcnamespace == "") {
      FileLog << "fatal error: namespace error: namespace empty: None\n";
    } else {
      FileLog << "create namespace mcfunction: " << mcnamespace << " for world " << WorldForLog << " add\n";
    }
  }
  
  clear();
  
  std::string namefun;
  fmt::print(fmt::fg(fmt::color::cyan), "- name function: ");
  std::cin >> namefun;
  std::cout << std::endl;
  
  if (setting["inputLog"].asBool() == true) {
    if (namefun == "") {
      FileLog << "fatal error: name for mcfunction empty: None\n";
    } else {
      FileLog << "add name for mcfunction for world: " << WorldForLog << " name for mcfunction: " << namefun << " add\n";
    }
  }
  
  clear();
  
  std::string des;
  fmt::print(fmt::fg(fmt::color::cyan), "- description: ");
  std::cin.ignore();
  getline(std::cin, des);
  
  if (setting["inputLog"].asBool() == true) {
    FileLog << "add description for world: " << WorldForLog << " description: " << '"' << des << '"' << " add\n";
  }
  
  clear();
  
  std::string versionforformat;
  fmt::print(fmt::fg(fmt::color::cyan), "- minecraft version 1.13, 1.16, 1.21: ");
  std::cin >> versionforformat;
  
  if (setting["inputLog"].asBool() == true) {
    FileLog << "version for format mcfunction " << versionforformat << " add\n";
  }
  
  int format;
  if (versionforformat == "1.13") {
    format = 4;
  } else if (versionforformat == "1.14") {
    format = 5;
  } else if (versionforformat == "1.15") {
    format = 6;
  } else if (versionforformat == "1.16") {
    format = 8;
  } else if (versionforformat == "1.17") {
      format = 9;
  } else if (versionforformat == "1.18") {
     format = 10;
  } else if (versionforformat == "1.19") {
     format = 11;
  } else if (versionforformat == "1.20") {
     format = 12;
  } else if (versionforformat == "1.21") {
     format = 13;
  } else {
     clear();
     fmt::print(fmt::fg(fmt::color::red), "Error: Invalid format, the format must follow the template - 1.13/1.16/1.21\n");
     if (setting["inputLog"].asBool() == true) {
       FileLog << "fatal error: invalid version for format, don't follow the template: " << versionforformat << " error\n";
     }
     return 1;
  }
  
  if (setting["inputLog"].asBool() == true) {
    FileLog << "Format for mcfunction: " << format << " add\n";
  }
   
  std::string fulldirectory = directory + "/datapacks/" + namefun + "/data/" + mcnamespace + "/functions";
  
  if (setting["inputLog"].asBool() == true) {
    FileLog << "fulldirectory for mcmeta: " << fulldirectory << " add\n";
  }
  
  std::string tagsdir = directory + "/datapacks/" + namefun + "/data/" + mcnamespace + "/minecraft/tags/functions";
  
  if (setting["inputLog"].asBool() == true) {
    FileLog << "directory for tags dir: " << tagsdir << " add\n";
  }
  
  create_shaded_dir(fulldirectory);
  create_shaded_dir(tagsdir);
  
  if (setting["inputLog"].asBool() == true) {
    FileLog << "make directory...\n";
  }
  
  std::cout << std::endl;
  
  clear();
  int numcommand;
  fmt::print(fmt::fg(fmt::color::cyan), "count command: ");
  std::cin >> numcommand;
  
  if (setting["inputLog"].asBool() == true) {
    FileLog << "count for command mcfunction: " << numcommand << " add\n";
  }
  
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cout << std::endl;
  clear();
  
  std::vector<std::string> commands(numcommand);
  
  for (int i = 0; i < numcommand; i++) {
    clear();
    std::string outcommands;
    int fulli = i + 1;
    std::string hashstr = std::to_string(fulli);
    std::string fulltext = "command " + hashstr + ": ";
    fmt::print(fmt::fg(fmt::color::cyan), fulltext);
    
    std::getline(std::cin, outcommands);
    commands.push_back(outcommands);
    std::cout << std::endl;
  }
  
  std::string fullfile = fulldirectory + "/" + namefun + ".mcfunction";
  std::ofstream outfile(fullfile);
  
  if (!outfile.is_open()) {
    fmt::print(fmt::fg(fmt::color::red), "Error: failed open file mcfunction\n");
    if (setting["inputLog"].asBool() == true) {
      FileLog << "fatal error: failed open mcfunction for world: " << WorldForLog << " exit\n";
    }
    return 1;
  }
  
  if (setting["inputLog"].asBool() == true) {
    FileLog << "all command:\n";
  }
  
  for (const auto& elem : commands) {
    outfile << elem << "\n";
    if (setting["inputLog"].asBool() == true) {
      FileLog << "commands: " << elem << "\n";
    }
  }
  
  clear();
  
  std::string mcmetadir = directory + "/datapacks/" + namefun + "/pack.mcmeta";
  std::ofstream mcmeta(mcmetadir);
  
  if (!mcmeta.is_open()) {
    fmt::print(fmt::fg(fmt::color::red), "Error: failed open file mcmeta");
    if (setting["inputLog"].asBool() == true) {
      FileLog << "fatal error: failed open mcmeta for mcfunction\n";
    }
    return 1;
  }
  
  mcmeta << "{" << "\n" << "  " << '"' << "pack" << '"' << ": {" << "\n" << "    " << '"' << "pack_format" << '"' << ": " << format << ", " << "\n" << "    " << '"' << "description" << '"' << ": " << '"' << des << '"' << "\n" << "  }" << "\n" << "}" << "\n";
  if (setting["inputLog"].asBool() == true) {
    FileLog << "mcmeta was best make\n";
  }
  
  std::string loaddir = tagsdir + "/load.json";
  std::ofstream loadfile(loaddir);
  
  if (!loadfile.is_open()) {
    fmt::print(fmt::fg(fmt::color::red), "Error: failed open file load");
    if (setting["inputLog"].asBool() == true) {
      FileLog << "fatal error: failed open load json for mcfunction\n";
    }
    return 1;
  } 
  loadfile << "{" << "\n" << "  " << '"' << "values" << '"' << ": [" << "\n" << "    " << '"' << mcnamespace << ":" << namefun << '"' << "\n" << "  ]" << "\n" << "}" << "\n";
  
  if (setting["inputLog"].asBool() == true) {
    FileLog << "load.json was best make\n";
  }
  
  size_t lastworldname = directory.find_last_of("/");
  
  std::string worldname = directory.substr(lastworldname + 1);
  std::string ResultTextWan = "mcfunction was best make, in chat " + worldname + ": ";
  std::string ResultTextTwo = "/function " + mcnamespace + ":" + namefun + "\n";
  
  fmt::print(fmt::fg(fmt::color::cyan), ResultTextWan);
  fmt::print(fmt::fg(fmt::color::magenta), ResultTextTwo);
  if (setting["inputLog"].asBool() == true) {
    FileLog << "Exit MCFC";
  }
  return 0;
}
