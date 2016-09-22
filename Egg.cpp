#include "Egg.h"

Egg::Egg()
{
	Name = nullptr;
	size = 0;
}

Egg::Egg(char * Name)
{
	SetName(Name);
}

Egg::Egg(const Egg & New_Egg)
{
	this->Egg::Egg();
	this->SetName(New_Egg.Name);
}

Egg & Egg::operator=(const Egg & New_Egg)
{
	this->SetName(New_Egg.Name);
	return *this;
}

bool Egg::operator==(const Egg & New_Egg) const
{
	if (size != New_Egg.size)
		return false;
	for (size_t i = 0; i < size; ++i)
	{
		if (Name[i] != New_Egg.Name[i])
			return false;
	}
	return true;
}

bool Egg::operator[](const char * str) const
{
	size_t size = strlen(str);
	if (size > this->size)
		return false;
	if (strstr(Name, str) == nullptr)
		return false;
	else
		return true;
}

void Egg::operator+=(const char * str)
{
	SetSize(size + strlen(str) + 1);
	char* New_Str = new char[size];
	for (size_t i = 0; i < size; ++i)
		New_Str[i] = '\0';
	
	StrCon(New_Str, Name);
	StrCon(New_Str, str);

	SetName(New_Str);
	delete[] New_Str;
}

void Egg::operator*=(const size_t multi)
{
	char*str = new char[size + 1];
	for (size_t i = 0; i <= size; ++i)
		str[i] = Name[i];
	size_t str_size = size;
	size *= multi;
	delete[] Name;
	Name = new char[size + 1];
	for (size_t i = 0; i < str_size; ++i)
		Name[i] = str[i];
	for (size_t i = str_size; i < size; ++i)
		Name[i] = ' ';
	Name[size] = '\0';
	delete[] str;
}

void Egg::operator/=(const size_t div)
{
	size /= div;
	char*str = new char[size + 1];
	for (size_t i = 0; i < size; ++i)
		str[i] = Name[i];
	str[size] = '\0';
	SetName(str);
}

bool Egg::operator!=(const Egg & New_Egg) const
{
	return !(*this == New_Egg);
}

bool Egg::operator<(const Egg & New_Egg) const
{
	size_t new_size = (size < New_Egg.size) ? size : New_Egg.size;
	for (size_t i = 0; i < new_size; ++i)
	{
		if (Name[i] < New_Egg.Name[i])
			return true;
		if (Name[i] > New_Egg.Name[i])
			return false;
	}
	return (size < New_Egg.size) ? true : false;
}

bool Egg::operator>(const Egg & New_Egg) const
{
	return (!(*this < New_Egg)) && (!(*this == New_Egg));
}

bool Egg::operator>=(const Egg & New_Egg) const
{
	return !(*this < New_Egg);
}

bool Egg::operator<=(const Egg & New_Egg) const
{
	return *this < New_Egg || *this == New_Egg;
}

Egg::~Egg()
{
	Free();
}

void Egg::SetName(char * Name)
{
	if (Name == nullptr)
	{
		this->Name = nullptr;
		this->size = 0;
		return;
	}
	if (this->Name != nullptr)
	{
		delete[]this->Name;
	}
	SetSize(strlen(Name));
	this->Name = new char[size + 1];

	for (size_t i = 0; i < size; ++i)
	{
		this->Name[i] = Name[i];
	}
	this->Name[size] = '\0';
}

void Egg::SetSize(size_t size)
{
	this->size = size;
}

size_t Egg::GetSize() const
{
	return size;
}

char * Egg::GetName() const
{
	return Name;
}

void Egg::Print() const
{
	std::cout << Name << " " << size << std::endl;
}

void Egg::Free()
{
	delete[] Name;
	Name = nullptr;
	size = 0;
}
