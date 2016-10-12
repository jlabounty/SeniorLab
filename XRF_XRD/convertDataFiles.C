#include "headers/UnpackSPE.C"

int convertDataFiles()
{

	std::string data_path = "data/";

	/*Data from 10/05*/
 	// UnpackSPE(data_path+"Rh_045_100516_125309.Spe");
	// UnpackSPE(data_path+"Co_057_100516_130227.Spe");
	// UnpackSPE(data_path+"Am_241_100516_132724.Spe");
	// UnpackSPE(data_path+"Fe_055_100516_135010.Spe");
	// UnpackSPE(data_path+"Am_241_100516_140641.Spe");
	// UnpackSPE(data_path+"Fe_055_100516_140912.Spe");
	// UnpackSPE(data_path+"Co_057_100516_141254.Spe");

 	// UnpackSPE(data_path+"Scattering_Ag_100516_143056.Spe");
 	// UnpackSPE(data_path+"Scattering_Au_100516_141827.Spe");
 	// UnpackSPE(data_path+"Scattering_Co_100516_144646.Spe");
 	// UnpackSPE(data_path+"Scattering_Cu_100516_144030.Spe");

	/*Data from 10/10*/
 	UnpackSPE(data_path+"Scattering_Fe_101016_122756.Spe");
 	UnpackSPE(data_path+"Scattering_Mo_101016_142121.Spe");
 	UnpackSPE(data_path+"Scattering_Ni_101016_125209.Spe");
 	UnpackSPE(data_path+"Scattering_Ni_101016_132653.Spe");
 	UnpackSPE(data_path+"Scattering_Pb_101016_143318.Spe");
 	UnpackSPE(data_path+"Scattering_Sn_101016_143908.Spe");
 	UnpackSPE(data_path+"Scattering_Ti_101016_115929.Spe");
 	UnpackSPE(data_path+"Scattering_UX_101016_134602.Spe");
 	UnpackSPE(data_path+"Scattering_VX_101016_120945.Spe");
 	UnpackSPE(data_path+"Scattering_WX_101016_142917.Spe");
 	UnpackSPE(data_path+"Scattering_YX_101016_133927.Spe");
 	UnpackSPE(data_path+"Scattering_Zn_101016_133330.Spe");



	return 0;
}
