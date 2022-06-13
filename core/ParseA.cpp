#include "ParseA.h"

vector<AModel> ParseA::AVector(char *pUrl)
{
  vector<AModel> ret_ = vector<AModel>();
  std::ifstream ifs;
  ifs.open(pUrl);
  if (!ifs.is_open())
  {
    printf("err open err \n");
  }
  std::string str_buffer;
  while (getline(ifs, str_buffer))
  {
    char *data = (char *)str_buffer.data();
    if ((data[0] < '0' || data[0] > '9'))
    {
      continue;
    }
    AModel model = ParseStr2A(data);
    ret_.push_back(model);
  }
  ifs.close();
  return ret_;
}

AModel ParseA::ParseStr2A(char *line)
{
  int index = 0; //区分v1 v2
  AModel ret_ = AModel();
  int i = 0;
  std::string tmp_str = "";
  while (1)
  {
    try
    {
      char tmp_c = line[i];
      if (tmp_c == '\0')
      {
        if (!tmp_str.empty() && tmp_str.find("E") != string::npos)
        {
          if (tmp_str.find("+") != string::npos)
          {
            // E
            float tmp_float1 = std::stof(tmp_str.substr(0, tmp_str.find("E")));
            // +
            float tmp_float2 = std::stof(tmp_str.substr(tmp_str.find("+")));
            // pow
            float tmp_float3 = tmp_float1 * pow(10, tmp_float2);
            // ret
            ret_.ret_ = tmp_float3;
          }
          else if (tmp_str.find("-") != string::npos)
          {
            // E
            float tmp_float1 = std::stof(tmp_str.substr(0, tmp_str.find("E")));
            // -
            float tmp_float2 = std::stof(tmp_str.substr(tmp_str.find("-")));
            // pow
            float tmp_float3 = tmp_float1 * pow(10, tmp_float2);
            // ret
            ret_.ret_ = tmp_float3;
          }
        }
        tmp_str = "";
        break;
      }
      else if (tmp_c == 'R' || tmp_c == 'Q' || tmp_c == 'P')
      { // j= -1, j= 0, j'= 1
        tmp_str = "";
        float diff = 0.0;
        if (tmp_c == 'R')
        {
          diff = -1.0;
        }
        else if (tmp_c == 'Q')
        {
          diff = 0.0;
        }
        else if (tmp_c == 'P')
        {
          diff = 1.0;
        }
        while (1)
        {
          tmp_c = line[i];
          if (line[i] == ')')
          { // j1=j2-1, j1=j2, j1=j2+1 . j2=n , j2=n-1 , j2=n+1
            float tmp_float = std::stof(tmp_str);
            tmp_float += diff;
            ret_.j2 = tmp_float;
            tmp_float += diff;
            ret_.j1 = tmp_float;
            tmp_str = "";
            break;
          }
          else if (tmp_c >= '0' && tmp_c <= '9')
          {
            tmp_str += tmp_c;
          }
          i++;
        }
      }
      else if ((tmp_c < '0' || tmp_c > '9') && tmp_c != '.' && tmp_c != 'E' && tmp_c != '+' && tmp_c != '-')
      { // V1 v2
        if (index == 0)
        {
          float tmp_float = std::stof(tmp_str);
          ret_.v1 = tmp_float;
        }
        else if (index == 1)
        {
          float tmp_float = std::stof(tmp_str);
          ret_.v2 = tmp_float;
        }
        index++;
        tmp_str = "";
      }
      else if ((tmp_c >= '0' && tmp_c <= '9') || tmp_c == '.' || tmp_c == 'E' || tmp_c == '+' || tmp_c == '-')
      {
        tmp_str += tmp_c;
      }
      i++;
      continue;
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
  }
  // std::cout << ret_.v1 << " " << ret_.v2 << " " << ret_.j1 << " " << ret_.j2 << " = " << ret_.ret_ << " \n";
  return ret_;
}