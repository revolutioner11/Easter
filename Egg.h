#pragma once
#include <iostream>
#include <string.h>

void StrCon(char*Dest, const char*Source);

class Egg
{
public:
	Egg();
	Egg(char*Name);
	Egg(const Egg &New_Egg);
	Egg& operator=(const Egg &New_Egg);
	~Egg();
public:
	void SetName(char*Name);
	size_t GetSize() const;
	char* GetName() const;
	void Print() const;
	void Free();
private:
	void SetSize(size_t size);
public:		//operators
	bool operator==(const Egg &New_Egg) const;
	bool operator[](const char* str) const;
	void operator+=(const char* str);
	void operator*=(const size_t multi);
	void operator/=(const size_t div);
public:		//bool operators
	bool operator!=(const Egg &New_Egg) const;
	bool operator<(const Egg &New_Egg) const;
	bool operator>(const Egg &New_Egg) const;
	bool operator>=(const Egg &New_Egg) const;
	bool operator<=(const Egg &New_Egg) const;
private:
	char*Name;
	size_t size;
};