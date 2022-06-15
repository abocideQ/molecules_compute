
#include <vector>
#include "FileUtils.h"
#include "XYModel.h"

class ParseX
{
public:
  vector<XModel> XVector(string g1, float t1, string pUrl1, string g2, float t2, string pUrl2);

  vector<VJModel> ParseStr2VJ(string g, float t, string pUrl);
};
