
#include <vector>
#include "FileUtils.h"
#include "XYModel.h"

class ParseX
{
public:
  vector<XModel> XVector(string g1, float t1, char *pUrl1, string g2, float t2, char *pUrl2);

  vector<VJModel> ParseStr2VJ(string g, float t, char *pUrl);
};
