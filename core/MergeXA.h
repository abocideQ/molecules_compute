#include <vector>
#include "XYModel.h"
#include <iostream>

class MergeXA
{
public:
  vector<XModel> Merge(vector<XModel> x_vec, vector<AModel> a_vec);

private:
  AModel FindA(XModel x_model, vector<AModel> a_vec);
};
