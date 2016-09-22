#include "Basket.h"
#include <fstream>
#include <iomanip>

size_t StrSize(const char* str)
{
	if (str == nullptr)
		return 0;
	return strlen(str);
}

void StrCon(char*Dest, const char*Source)
{
	size_t DestSize = StrSize(Dest);
	size_t size = DestSize + StrSize(Source) + 1;
	
	for (size_t i = DestSize; i < size; ++i)
	{
		Dest[i] = Source[i - DestSize];
	}
}

void Report(const Basket & New_Basket)
{
	size_t size = strlen("report_.txt") + New_Basket.GetNameSize() + 1;
	char* str = new char[size];
	for (size_t i = 0; i < size; ++i)
		str[i] = '\0';

	StrCon(str, "report_");
	StrCon(str, New_Basket.GetName());
	StrCon(str, ".txt");

	std::ofstream Report(str);

	for (size_t i = 0; i < New_Basket.GetTaken(); ++i)
	{
		Report << New_Basket.GetEggName(i) << " - size: " << New_Basket.GetEggSize(i) << "\n";
	}
	delete[] str;
	Report.close();
}

void Serialize(const Basket & New_Basket, char*str)
{
	std::ofstream binfile(str, std::ios::binary);
	size_t EggSize = 0;
	char*EggName;
	size_t NumberEggs = New_Basket.GetTaken();
	binfile.write((const char*)&NumberEggs, sizeof(NumberEggs));
	for (size_t i = 0; i < New_Basket.GetTaken(); ++i)
	{
		EggSize = New_Basket.GetEggSize(i) + 1;
		EggName = new char[EggSize];
		strcpy_s(EggName, EggSize, New_Basket.GetEggName(i));
		EggName[EggSize - 1] = '\0';
		binfile.write((const char*)&EggSize, sizeof(EggSize));
		binfile.write((const char*)EggName, EggSize);
		delete[] EggName;
	}
	binfile.close();
}

void Deserialize(Basket& New_Basket, char*FileName)
{
	New_Basket.SetName("De Basket");
	std::ifstream binfile(FileName, std::ios::binary);
	binfile.seekg(0, std::ios::beg);
	size_t NextStrSize = 0;
	size_t NumberEggs = 0;
	binfile.read((char*)&NumberEggs, sizeof(NumberEggs));
	char* str;
	size_t j = 0;
	while (binfile&&j<NumberEggs)
	{
		binfile.read((char*)&NextStrSize, sizeof(NextStrSize));
		str = new char[NextStrSize + 1];
		binfile.read((char*)str, NextStrSize);
		str[NextStrSize] = '\0';
		New_Basket.AddEgg(str);
		delete[] str;
		++j;
	}
	binfile.close();
}

void main()
{	
	Basket Stavri;
	Stavri.SetName("Stavri");

	Stavri.AddEgg("Red Egg");
	Stavri.AddEgg("Blue Egg");
	Stavri.AddEgg("Cool Egg");
	Stavri.AddEgg("The Egg");
	Stavri.AddEgg("Just An Egg");
	Stavri.AddEgg("Gosho's Egg");

	Stavri.Print();

	Basket Josh("Joshua");
	Josh.AddEgg("Drako");
	Josh.AddEgg("Dragon");
	Josh.AddEgg("Just An Egg");
	Josh.AddEgg("Divergent");
	Josh.Print();
	//			Basket:		< <= > >= != ==
	Basket A("A");
	A.AddEgg("aab");
	A.AddEgg("bca");
	A.AddEgg("bbb");
	Basket B("B");
	B.AddEgg("aab");
	B.AddEgg("bca");
	Basket C("C");
	C.AddEgg("aab");
	C.AddEgg("bba");
	C.AddEgg("bab");
	A.Print();
	B.Print();
	C.Print();

	if (A < B) std::cout << "A<B\n";
	if (A <= B) std::cout << "A<=B\n";
	if (A > B) std::cout << "A>B\n";
	if (A >= B) std::cout << "A>=B\n";
	if (A != B) std::cout << "A!=B\n";
	if (A == B) std::cout << "A==B\n";

	if (A < C) std::cout << "A<C\n";
	if (A <= C) std::cout << "A<=C\n";
	if (A > C) std::cout << "A>C\n";
	if (A >= C) std::cout << "A>=C\n";
	if (A != C) std::cout << "A!=C\n";
	if (A == C) std::cout << "A==C\n";

	if (B < C) std::cout << "B<C\n";
	if (B <= C) std::cout << "B<=C\n";
	if (B > C) std::cout << "B>C\n";
	if (B >= C) std::cout << "B>=C\n";
	if (B != C) std::cout << "B!=C\n";
	if (B == C) std::cout << "B==C\n\n";
	// % and %= Basket
	Basket Tom("Not Jerry");
	Tom.AddEgg("Red Egg");
	Tom.AddEgg("The Egg");
	Tom.AddEgg("Nee");
	Tom.AddEgg("Gosho's Egg");
	Tom.AddEgg("pak ne");
	Tom.Print();
	Basket X("XXX");
	X = Tom % Stavri;
	std::cout << "Tom % Stavri:\n";
	X.Print();
	//		/ and /= Basket
	std::cout << "Tom /= 2:\n";
	Tom /= 2;
	Tom.Print();
	std::cout << "Josh / 3:\n";
	Basket Todor("Todor");
	Todor = Josh / 3;
	Todor.Print();
	//		*= and * Basket
	std::cout << "Stavri * 5:\n";
	Basket Rex("Rexxy");
	Rex = Stavri * 5;
	Rex.Print();
	//		Bakset + string
	std::cout << "Stavri + \"of Stavri\":\n";
	Basket Nencho("Nayden");
	Nencho = Stavri + " of Stavri";
	Nencho.Print();
	//		Basket += String
	std::cout << "Josh + Stavri:\n";
	Basket Tim("Timmy");
	Tim = Josh + Stavri;
	Tim.Print();
	//		Report
	Report(Stavri);
	Report(Josh);
	char*str = "BinaryFile.dat";
	//			[int]  [string]
	char str1[_MAX_PATH];
	std::cout << "Search egg in Stavri(string): ";
	std::cin.clear();
	std::cin.sync();
	std::cin.getline(str1, _MAX_PATH);

	try
	{
		std::cout << "Egg in Stavri containing \"" << str1 << "\": " << Stavri[str1].GetName() << std::endl << std::endl;
		std::cout << "\n3rd egg in Stavri:\t" << Stavri[3].GetName() << std::endl << std::endl;
	}
	catch (char*Error)
	{
		std::cout << Error << std::endl << std::endl;
	}

	//			(De)serialize	
	Serialize(Stavri, str);
	Basket T;
	Deserialize(T, str);

	T.Print();
	Report(T);

	char c;
	std::cin >> c;
}