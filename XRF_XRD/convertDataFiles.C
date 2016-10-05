#include "headers/UnpackSPE.C"

int convertDataFiles()
{

	std::string data_path = "data/";

	UnpackSPE(data_path+"Rh_045_100516_125309.Spe");
	UnpackSPE(data_path+"Co_057_100516_130227.Spe");
	UnpackSPE(data_path+"Am_241_100516_132724.Spe");
	UnpackSPE(data_path+"Fe_055_100516_135010.Spe");
	UnpackSPE(data_path+"Am_241_100516_140641.Spe");
	UnpackSPE(data_path+"Fe_055_100516_140912.Spe");
	UnpackSPE(data_path+"Co_057_100516_141254.Spe");

	return 0;
}
