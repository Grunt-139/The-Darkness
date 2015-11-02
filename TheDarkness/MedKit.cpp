#include "MedKit.h"


MedKit::MedKit(string name, string description, bool use):Item(name,description,use)
{
}


MedKit::~MedKit(void)
{
}

int MedKit::UseItem()
{return 0;}