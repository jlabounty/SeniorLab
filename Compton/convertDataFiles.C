#include "headers/UnpackSPE.C"

int convertDataFiles()
{

	std::string data_path = "/home/josh/github/SeniorLab/Compton/data/";
	UnpackSPE(data_path+"Co_57_Weak_090716_140819.Spe");
	UnpackSPE(data_path+"Co_57_Weak_090716_140819.Spe");
	UnpackSPE(data_path+"Co_60_Weak_090716_134748.Spe");
	UnpackSPE(data_path+"Co_60_Weak_090716_135450.Spe");
	UnpackSPE(data_path+"Co_60_Weak_090716_140110.Spe");
	UnpackSPE(data_path+"Co_60_Weak_090716_140358.Spe");
	UnpackSPE(data_path+"Cs_137_Weak_090716_124540.Spe");
	UnpackSPE(data_path+"Cs_137_Weak_090716_125726.Spe");
	UnpackSPE(data_path+"Cs_137_Weak_090716_130600.Spe");
	UnpackSPE(data_path+"Cs_137_Weak_090716_141039.Spe");
	UnpackSPE(data_path+"Na_22_Weak_090716_131442.Spe");

	return 0;
}
