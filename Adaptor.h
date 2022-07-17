#pragma once

#define _FixRecFixStrAdap 1
#define _FixRecDynStrAdap 2
#define _DynRecFixStrAdap 3
#define _DynRecDynStrAdap 4

class Adaptor
{
private: 
	static int adaptorType;
	
public:
	Adaptor();
	void setAdaptorType(int adap);
	int getAdaptorType();

};

