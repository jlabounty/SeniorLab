#include "headers/UnpackFiles.C"

int convertDataFiles()
{

	std::string data_path = "data/";

	UnpackFiles(data_path+"mV_vs_T111416_Run2.txt", data_path+"T_vs_t_111416_Run2.txt");

	return 0;
}
