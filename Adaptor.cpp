#include "stdafx.h"
#include "Adaptor.h"


Adaptor::Adaptor()
{

}

void Adaptor::setAdaptorType(int adap)
{
	this->adaptorType = adap; 
}
int Adaptor::getAdaptorType() {
	return this->adaptorType; 
}