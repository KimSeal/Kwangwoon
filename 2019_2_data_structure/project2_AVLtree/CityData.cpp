#define _CRT_SECURE_NO_WARNINGS
#include "CityData.h"

CityData::CityData()//initialize citydata value to put data
{
	LocationId = 0;
	name = new char[50];
	country = new char[50];
}

CityData::~CityData()
{
}

int CityData::GetLocationId()//get locationId
{
	return this->LocationId;
}

char * CityData::Getname()//get city name value
{
	return this->name;
}

char * CityData::Getcountry()//get country value
{
	return this->country;
}

void CityData::SetLocationId(int LocationId)//give location value
{
	this->LocationId= LocationId;
}

void CityData::Setname(char * name)//give name value
{
	strcpy(this->name, name);
}

void CityData::Setcountry(char * country)//give country value
{
	strcpy(this->country, country);
}


