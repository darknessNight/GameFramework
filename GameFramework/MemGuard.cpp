#define IMPLEM
#include "MemGuard.h"
#include <stdio.h>
#include <memory>
#include <exception>

class MemoryGuard{
public:
	MemoryGuard();
	~MemoryGuard();
	bool delDynVar(void* p);
	void addDynVar(void* p, size_t size, const char* file, unsigned line);
protected:
	void ToScreen();
	void ToFile();
protected:
	bool toFile = true;
	bool toScreen = true;
	char fileName[1000];
	static const unsigned int maxEls = 10000000;//maksymalna liczba zainicjowanych zmniennych

	unsigned dynVar = 0;//iloœæ aktualnie zainicjowanych i nieusuniêtych zmiennych
	unsigned long long dynVarBytes = 0;
	unsigned long long maxBytes = 0;
	unsigned long long actBytes = 0;
	unsigned* dynVars;
	char** dynVarsFile;
	unsigned* dynVarsLine;
	size_t* dynVarsBytes;

	const char commChar = ';';
}guard;
//-----------------------------------------------------------------------------------------------------------------------------------



void operator delete[](void* p) {
	if(guard.delDynVar(p))
		free(p);
}
//-----------------------------------------------------------------------------------------------------------------------------------


void operator delete(void* p) {
	if(guard.delDynVar(p))
		free(p);
}
//-----------------------------------------------------------------------------------------------------------------------------------


void* operator new(size_t size){
	void* m = malloc(size);
	guard.addDynVar(m,size,0,0);
	return m;
}
//-----------------------------------------------------------------------------------------------------------------------------------


void* operator new[](size_t size){
	void* m = malloc(size);
	guard.addDynVar(m, size, 0, 0);
	return m;
}
//-----------------------------------------------------------------------------------------------------------------------------------


void* operator new(size_t size, const char* file, int line){
	void* m = malloc(size);
	guard.addDynVar(m, size, file, line);
	return m;
}
//-----------------------------------------------------------------------------------------------------------------------------------


void* operator new[](size_t size, const char* file, int line){
	void* m = malloc(size);
	guard.addDynVar(m, size, file, line);
	return m;
}
//-----------------------------------------------------------------------------------------------------------------------------------


MemoryGuard::MemoryGuard(){
	dynVars = (unsigned*) malloc(maxEls*sizeof(unsigned));
	dynVarsFile = (char**)malloc(maxEls*sizeof(char*));
	dynVarsLine = (unsigned*)malloc(maxEls*sizeof(unsigned));
	dynVarsBytes = (size_t*)malloc(maxEls*sizeof(size_t));
	if (dynVars == nullptr) throw std::exception("Cannot initialize tabs");

	memset(dynVars, 0, maxEls*sizeof(unsigned));
	strcpy_s(fileName, "MemoryLeaksLog.log");

	char buff[10000];
	FILE* file;
	if (fopen_s(&file, "MemoryGuard.conf", "r")) {
		if (file != nullptr) {
			while (!feof(file)) {
				fscanf_s(file, "%[^\n]\n", buff);
				if (buff[0] == commChar || buff[0] == 0) continue;

				if (strstr(buff, "ToFile=")) {
					if (strstr(buff, "true")) toFile = true;
					else toFile = false;
				}

				if (strstr(buff, "ToScreen=")) {
					if (strstr(buff, "true")) toScreen = true;
					else toScreen = false;
				}

				if (strstr(buff, "Filename=") && strlen(buff + strlen("Filename=")) > 0) {
					strcpy_s(fileName, buff + strlen("Filename="));
				}
			}
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------


MemoryGuard::~MemoryGuard(){
	if (toScreen) ToScreen();
	if (toFile) ToFile();

	free(dynVars);
	free(dynVarsFile);
	free(dynVarsLine);
	free(dynVarsBytes);

	dynVars = nullptr;
}
//-----------------------------------------------------------------------------------------------------------------------------------


void MemoryGuard::ToScreen(){
	system("cls");
	printf("%s %d\n", "Pozostalo nie usunietych elementow: ", dynVar);
	printf("%s %d\n", "W sumie zaalokowano pamieci: ", dynVarBytes);
	printf("%s %d%s\n\n", "Maksymalnie w jednym momencie uzywano: ", maxBytes,"B");
	printf("%s %d%s\n\n", "MemGuard uzywal: ", maxEls*sizeof(char**)+maxEls*sizeof(unsigned)*2+maxEls*sizeof(size_t), "B");
	system("pause");
	printf("%s\n", "Niezwolnione elementy: ");
	for (long long i = 0; i < maxEls; i++){
		if (dynVars[i]==0) continue;
		printf("%X File: %s Line: %d Bytes: %d\n", dynVars[i], dynVarsFile[i], dynVarsLine[i], dynVarsBytes[i]);
	}
	system("pause");
}
//-----------------------------------------------------------------------------------------------------------------------------------


void MemoryGuard::ToFile(){
	FILE* file;
	fopen_s(&file, fileName, "w");
	if (file != nullptr){
		fprintf(file,"%s %d\n", "Pozostalo nie usunietych elementow: ", dynVar);
		fprintf(file, "%s %d\n\n", "W sumie zaalokowano pamieci: ", dynVarBytes);
		fprintf(file, "%s %d%s\n\n", "Maksymalnie w jednym momencie uzywano: ", maxBytes,"B");
		fprintf(file, "%s\n", "Niezwolnione elementy: ");
		for (long long i = 0; i < maxEls; i++){
			if (dynVars[i]==0) continue;
			fprintf(file, "%X File: %s Line: %d Bytes: %d\n", dynVars[i], dynVarsFile[i], dynVarsLine[i], dynVarsBytes[i]);
		}
		fclose(file);
	}
	else{
		printf("\n\n%s", "Nie udalo sie zapisac do pliku");
		system("pause");
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------


bool MemoryGuard::delDynVar(void* p){
	if (dynVars == nullptr) return false;
	dynVar--;
	for (int i = 0; i < maxEls; i++){
		if (dynVars[i] == (int)p){
			dynVars[i] = 0;
			actBytes -= dynVarsBytes[i];
			return true;
		}
	}
	return false;
}
//-----------------------------------------------------------------------------------------------------------------------------------


void MemoryGuard::addDynVar(void* p, size_t size, const char* file, unsigned line){
	if (dynVars == nullptr) 
		return;
	dynVar++;
	actBytes += size;
	if (actBytes > maxBytes)maxBytes = actBytes;

	if (dynVar > maxEls){
		printf("%s %d %s\n", "Ilosc zainicjowanych zmiennych przekroczyla",maxEls,"program zakonczy dzialanie natychmiastowo");
		system("pause");
		exit(0);
	}
	dynVarBytes += size;
	for (int i = 0; i < maxEls; i++){
		if (dynVars[i]==0){
			dynVars[i] = (unsigned)p;
			dynVarsBytes[i] = size;
			dynVarsFile[i] = (char*)file;
			dynVarsLine[i] = line;
			break;
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------