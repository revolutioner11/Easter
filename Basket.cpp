#include "Basket.h"

Basket::Basket()
{
	EasterEggs = nullptr;
	Name = nullptr;
	Name_Size = 0;
	Allocated = 0;
	Taken = 0;
}

Basket::Basket(char * Name)
{
	SetName(Name);
	EasterEggs = nullptr;
	Allocated = 0;
	Taken = 0;
}

Basket::Basket(const Basket & New_Basket)
{
	EasterEggs = nullptr;
	Name = nullptr;
	Name_Size = 0;
	Allocated = 0;
	Taken = 0;
	Copy(New_Basket);
}

Basket& Basket::operator=(const Basket & New_Basket)
{
	if (Name != nullptr || EasterEggs != nullptr)
	{
		Free();
	}
	Copy(New_Basket);
	return *this;
}

Basket::~Basket()
{
	Free();
}

void Basket::SetName(char * Name)
{
	if (this->Name != nullptr)
	{
		delete[]this->Name;
	}
	SetNameSize(strlen(Name));
	this->Name = new char[Name_Size + 1];

	for (size_t i = 0; i < Name_Size; ++i)
	{
		this->Name[i] = Name[i];
	}
	this->Name[Name_Size] = '\0';
}

char * Basket::GetName() const
{
	return Name;
}

size_t Basket::GetTaken() const
{
	return Taken;
}

size_t Basket::GetAllocated() const
{
	return Allocated;
}

size_t Basket::GetNameSize() const
{
	return Name_Size;
}

char* Basket::GetEggName(size_t Index) const
{
	return EasterEggs[Index].GetName();
}

size_t Basket::GetEggSize(size_t Index) const
{
	return EasterEggs[Index].GetSize();
}

void Basket::Print() const
{
	std::cout << Name << "\t" << Taken << "/" << Allocated << std::endl;
	for (size_t i = 0; i < Taken; ++i)
	{
		std::cout << "[" << i << "] ";
		EasterEggs[i].Print();
	}
	std::cout << std::endl;
}

void Basket::AddEgg(char * Egg_Name)
{
	if (Allocated == 0)
	{
		++Allocated;
		EasterEggs = new Egg[Allocated];
	}
	else if (Taken == Allocated)
	{
		Egg*buffer = new Egg[Taken];
		for (size_t i = 0; i < Taken; ++i)
		{
			buffer[i] = EasterEggs[i];
		}
		delete[] EasterEggs;
		Allocated *= 2;
		EasterEggs = new Egg[Allocated];
		for (size_t i = 0; i < Taken; ++i)
		{
			EasterEggs[i] = buffer[i];
		}
	}
	Egg New_Egg(Egg_Name);
	EasterEggs[Taken] = New_Egg;
	++Taken;
}

void Basket::RemoveEgg(char * Egg_Name)
{
	Egg New_Egg(Egg_Name);
	size_t j = 0;
	while(j < Taken)
	{
		if (New_Egg == EasterEggs[j])
		{
			--Taken;
			while (j < Taken)
			{
				EasterEggs[j] = EasterEggs[1 + j];
				++j;
			}
			++j;			//ако j>Taken => сме влезнали в този if()
			EasterEggs[Taken].Free();
			break;
		}
		++j;
	}
	if (Taken == j)			//иначе Taken < j заради --Taken
	{
		std::cout << "No egg with this name!\n";
		return;
	}
	if (Taken == 0)
	{
		delete[] EasterEggs;
		EasterEggs = nullptr;
		Allocated = 0;
	}
	if ((Taken + 1) * 2 == Allocated)
	{
		Egg*buffer = new Egg[Taken];
		for (size_t i = 0; i < Taken; ++i)
		{
			buffer[i] = EasterEggs[i];
		}
		delete[] EasterEggs;
		Allocated /= 2;
		EasterEggs = new Egg[Allocated];
		for (size_t i = 0; i < Taken; ++i)
		{
			EasterEggs[i] = buffer[i];
		}
	}
}

void Basket::SetNameSize(size_t size)
{
	Name_Size = size;
}

void Basket::Free()
{
	delete[] EasterEggs;
	EasterEggs = nullptr;
	delete[] Name;
	Name = nullptr;
	Name_Size = 0;
	Allocated = 0;
	Taken = 0;
}

void Basket::Copy(const Basket & New_Basket)
{
	SetName(New_Basket.Name);
	Allocated = New_Basket.Allocated;
	Taken = New_Basket.Taken;
	EasterEggs = new Egg[Allocated];
	for (size_t i = 0; i < Taken; ++i)
	{
		EasterEggs[i] = New_Basket.EasterEggs[i];
	}
}

Egg & Basket::operator[](const size_t Index) const
{
	if (Index < 0 || Index >= Taken)
		throw "Bad index!";
	return EasterEggs[Index];
}

Egg & Basket::operator[](const char * str) const
{
	for (size_t i = 0; i < Taken; ++i)
	{
		if (EasterEggs[i][str])
			return EasterEggs[i];
	}
	throw "No such egg!";
}

Basket & Basket::operator+=(const Basket & New_Basket)
{
	SetNameSize(Name_Size + New_Basket.Name_Size + 2);
	char* New_Name = new char[Name_Size];
	for (size_t i = 0; i < Name_Size; ++i)
		New_Name[i] = '\0';
	StrCon(New_Name, GetName());
	StrCon(New_Name, " ");
	StrCon(New_Name, New_Basket.GetName());
	SetName(New_Name);

	for (size_t i = 0; i < New_Basket.Taken; ++i)
	{			//така не нарушаваме стойността на Allocated = 2^n
		this->AddEgg(New_Basket.EasterEggs[i].GetName());
	}
	delete[] New_Name;
	return *this;
}

Basket Basket::operator+(const Basket & New_Basket) const
{
	Basket Result = *this;
	Result += New_Basket;
	return Result;
}

void Basket::operator+=(const char * str)
{
	for (size_t i = 0; i < Taken; ++i)
	{
		EasterEggs[i] += str;
	}
}

Basket Basket::operator+(const char * str) const
{
	Basket New_Basket = *this;
	New_Basket += str;
	return New_Basket;
}

void Basket::operator*=(const size_t multi)
{
	for (size_t i = 0; i < Taken; ++i)
		EasterEggs[i] *= multi;
}

Basket Basket::operator*(const size_t multi) const
{
	Basket New_Basket = *this;
	New_Basket *= multi;
	return New_Basket;
}

void Basket::operator/=(const size_t div)
{
	for (size_t i = 0; i < Taken; ++i)
		EasterEggs[i] /= div;
}

Basket Basket::operator/(const size_t div) const
{
	Basket New_Basket = *this;
	New_Basket /= div;
	return New_Basket;
}

void Basket::operator%=(const Basket & New_Basket)
{
	bool isEgg = false;
	for (size_t i = 0; i < Taken; ++i)
	{
		for (size_t j = 0; j < New_Basket.Taken; ++j)
		{
			if (EasterEggs[i] == New_Basket.EasterEggs[j])
			{
				isEgg = true;
				break;
			}
		}
		if (!isEgg)
		{
			RemoveEgg(EasterEggs[i].GetName());
			--i;
		}
		else
			isEgg = false;
	}
}

Basket Basket::operator%(const Basket & New_Basket) const
{
	Basket Result = *this;
	Result %= New_Basket;
	return Result;
}

bool Basket::operator<(const Basket & New_Basket) const
{
	size_t size = (Taken < New_Basket.Taken) ? Taken : New_Basket.Taken;
	for (size_t i = 0; i < size; ++i)
	{
		if (EasterEggs[i] < New_Basket.EasterEggs[i])
			return true;
		if (EasterEggs[i] > New_Basket.EasterEggs[i])
			return false;
	}
	return (Taken < New_Basket.Taken) ? true : false;
}

bool Basket::operator<=(const Basket & New_Basket) const
{
	return *this<New_Basket || *this == New_Basket;
}

bool Basket::operator>(const Basket & New_Basket) const
{
	return (!(*this < New_Basket)) && (!(*this == New_Basket));
}

bool Basket::operator>=(const Basket & New_Basket) const
{
	return !(*this < New_Basket);
}

bool Basket::operator==(const Basket & New_Basket) const
{
	if (Taken != New_Basket.Taken)
		return false;
	for (size_t i = 0; i < Taken; ++i)
	{
		if (EasterEggs[i] != New_Basket.EasterEggs[i])
			return false;
	}
	return true;
}

bool Basket::operator!=(const Basket & New_Basket) const
{
	return !(*this == New_Basket);
}
