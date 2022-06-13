
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#ifndef _BASESFILEUTILS_H_
#define _BASESFILEUTILS_H_
class FileUtils
{
public:
  std::vector<std::vector<float>> Load(char *pFileUrl)
  {
    std::vector<std::vector<float>> ret_;
    std::ifstream ifs;
    ifs.open(pFileUrl);
    if (!ifs.is_open())
    {
      printf("err open err \n");
    }
    std::string str_buffer;
    while (getline(ifs, str_buffer))
    {
      std::vector<float> tmp_vec_float = FloatObtain((char *)str_buffer.data());
      ret_.push_back(tmp_vec_float);
    }
    ifs.close();
    return ret_;
  }

  std::vector<std::vector<std::string>> Load(char *pFileUrl, char *pSplit)
  {
    std::vector<std::vector<std::string>> ret_;
    std::string str_split = pSplit;
    std::ifstream ifs;
    ifs.open(pFileUrl);
    if (!ifs.is_open())
    {
      printf("err open err \n");
    }
    std::string str_buffer;
    while (getline(ifs, str_buffer))
    {
      std::vector<std::string> tmp_vec_str = StrSplit(str_buffer, str_split);
      ret_.push_back(tmp_vec_str);
    }
    ifs.close();
    return ret_;
  }

private:
  std::vector<float> FloatObtain(char *content)
  {
    std::vector<float> ret_;
    std::string tmp_str = "";
    int i = 0;
    while (1)
    {
      try
      {
        char tmp_c = content[i];
        if (tmp_c == '\0')
        {
          if (!tmp_str.empty())
          {
            // std::cout << tmp_str << " ";
            float tmp_float = std::stof(tmp_str);
            ret_.push_back(tmp_float);
            tmp_str = "";
          }
          goto __Exit;
        }
        else if ((tmp_c >= '0' && tmp_c <= '9') || tmp_c == '.' || tmp_c == '-' || tmp_c == '+')
        {
          tmp_str += tmp_c;
        }
        else if (!tmp_str.empty())
        {
          // std::cout << tmp_str << " ";
          float tmp_float = std::stof(tmp_str);
          ret_.push_back(tmp_float);
          tmp_str = "";
        }
        i++;
        continue;
      }
      catch (const std::exception &e)
      {
        std::cerr << e.what() << '\n';
      }
    }
  __Exit:
    // std::cout << tmp_str << std::endl;
    return ret_;
  }

  std::vector<std::string> StrSplit(std::string content, std::string split)
  {
    std::vector<std::string> ret_;
    int size_split = split.length();
    size_t pos_first = content.find(split);
    size_t pos = 0;
    if (pos_first == 0)
    { //-?-?-?
      pos = size_split;
    }
    size_t len = content.find(split, pos) - pos;
    while (1)
    {
      try
      {
        std::string str_tmp = content.substr(pos, len);
        ret_.push_back(str_tmp);
        pos = content.find(split, pos + 1) + size_split;
        len = content.find(split, pos + 1) - pos;
        if ((pos - size_split) == content.npos)
        {
          goto __Exit;
        }
      }
      catch (const std::exception &e)
      {
        std::cerr << e.what() << '\n';
      }
    }
  __Exit:
    return ret_;
  }
};
#endif
