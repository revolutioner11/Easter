#pragma once
#include "Egg.h"

class Basket
{
public:
	Basket();
	Basket(char*Name);
	Basket(const Basket & New_Basket);
	Basket& operator=(const Basket & New_Basket);
	~Basket();
public:
	char* GetName() const;
	size_t GetTaken() const;
	size_t GetAllocated() const;
	size_t GetNameSize() const;
	char* GetEggName(size_t Index) const;
	size_t GetEggSize(size_t Index) const;
	void Print() const;
public:
	void SetName(char*Name);
	void AddEgg(char* Egg_Name);
	void RemoveEgg(char* Egg_Name);
	void Free();
private:
	void SetNameSize(size_t size);
	void Copy(const Basket & New_Basket);

public:			//operators
	Egg & operator[](const size_t Index) const;
	Egg & operator[](const char* str) const;
	Basket & operator+=(const Basket & New_Basket);
	Basket operator+(const Basket & New_Basket) const;
	void operator+=(const char* str);
	Basket operator+(const char* str) const;
	void operator*=(const size_t multi);
	Basket operator*(const size_t multi) const;
	void operator/=(const size_t div);
	Basket operator/(const size_t div) const;
	void operator%=(const Basket & New_Basket);
	Basket operator%(const Basket & New_Basket) const;
public:			//bool operators
	bool operator<(const Basket & New_Basket) const;
	bool operator<=(const Basket & New_Basket) const;
	bool operator>(const Basket & New_Basket) const;
	bool operator>=(const Basket & New_Basket) const;
	bool operator==(const Basket & New_Basket) const;
	bool operator!=(const Basket & New_Basket) const;
private:
	Egg* EasterEggs;
	char* Name;
	size_t Name_Size;
	size_t Allocated;
	size_t Taken;
};