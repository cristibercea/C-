#include "service.h"
#include <algorithm>
vector<Stock> Service::getAll() const
{
    return rep.getAll();
}

void Service::sterge(string id)
{
    vector<Stock> all=getAll();
   // auto it=std::find_if(all.begin(), all.end());
}
