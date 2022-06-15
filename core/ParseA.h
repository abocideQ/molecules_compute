
#include <fstream>
#include <vector>
#include "FileUtils.h"
#include "XYModel.h"
#include <math.h>

class ParseA
{
public:
  vector<AModel> AVector(string pUrl);

private:
  AModel ParseStr2A(char *line);
};
