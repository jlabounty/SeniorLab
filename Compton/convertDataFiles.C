#include "headers/UnpackSPE.C"

int convertDataFiles()
{

	std::string data_path = "/home/josh/github/SeniorLab/Compton/data/";

	//Measurement Files from 9/7
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


	//Files from 9/12
	UnpackSPE(data_path+"Co_57_Weak_091216_140228.Spe");
	UnpackSPE(data_path+"Co_57_Weak_091216_135650.Spe");
	UnpackSPE(data_path+"Co_57_Weak_091216_134953.Spe");
	UnpackSPE(data_path+"Ba_133_Weak_091216_134204.Spe");
	UnpackSPE(data_path+"Ba_133_Weak_091216_133430.Spe");
	UnpackSPE(data_path+"Ba_133_Weak_091216_132314.Spe");
	UnpackSPE(data_path+"Co_60_Weak_091216_131604.Spe");
	UnpackSPE(data_path+"Co_60_Weak_091216_131036.Spe");
	UnpackSPE(data_path+"Co_60_Weak_091216_130411.Spe");
	UnpackSPE(data_path+"Cs_137_Weak_091216_124935.Spe");
	UnpackSPE(data_path+"Cs_137_Weak_091216_124114.Spe");
	UnpackSPE(data_path+"Cs_137_Weak_091216_123452.Spe");
	UnpackSPE(data_path+"Cs_137_Weak_091216_122728.Spe");
	UnpackSPE(data_path+"Cs_137_Weak_091216_122105.Spe");
	UnpackSPE(data_path+"Background_091216_120951.Spe");
	UnpackSPE(data_path+"Background_091216_120413.Spe");
	UnpackSPE(data_path+"Background_091216_115701.Spe");
	UnpackSPE(data_path+"Na_22_Weak_091216_142051.Spe");
	UnpackSPE(data_path+"Na_22_Weak_091216_142706.Spe");
	UnpackSPE(data_path+"Na_22_Weak_091216_143229.Spe");

	return 0;
}
