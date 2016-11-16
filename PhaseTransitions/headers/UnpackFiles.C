#include "exist_test.h"

int UnpackFiles(std::string file_name_V_vs_T, std::string file_name_T_vs_t)
{

	if(!exists_test(file_name_V_vs_T))
	{
		cerr << "ERROR: File " << file_name_V_vs_T << " not found. Aborting." << endl;
		return -1;
	}
	if(!exists_test(file_name_T_vs_t))
	{
		cerr << "ERROR: File " << file_name_T_vs_t << " not found. Aborting." << endl;
		return -1;
	}

	std::ifstream file(file_name_V_vs_T.c_str());
	std::string str;
	vector<double> voltage, temp;
	double voltage_i, temp_i;
	double garbage_i;

	while (std::getline(file, str))
	{
		if(file >> temp_i >> voltage_i >> garbage_i)
		{
			temp.push_back(temp_i);
			voltage.push_back(voltage_i);
		}
	}

	std::ifstream file2(file_name_T_vs_t.c_str());
	vector<double> time, temp2;
	double time_i, temp2_i;

	while (std::getline(file2, str))
	{
		if(file2 >> time_i >> temp2_i)
		{
			time.push_back(time_i);
			temp2.push_back(temp2_i);
		}
	}


	std::string data_file_root = (file_name_V_vs_T.erase(file_name_V_vs_T.size()-3,3)).append("root");
	TFile f((data_file_root).c_str(),"RECREATE");
	TTree *t = new TTree("tVoltage","Lock-In Measurement from LabView");
	TBranch *b_voltage = t->Branch("Voltage",&voltage_i,"Voltage from Lock In/D");
	TBranch *b_tempVoltage = t->Branch("TempVoltage",&temp_i,"Temperature from Temp Sensor corr. to Voltage Measurement/D");


	TTree *t2 = new TTree("tTime","Lock-In Measurement from LabView");
	TBranch *b_time = t2->Branch("Time",&time_i,"Time/D");
	TBranch *b_tempTime = t2->Branch("TempTime",&temp2_i,"Temperature from Temp Sensor corr. to Time measurement/D");

	for(int i = 0; i< temp.size(); i++)
	{
		temp_i = temp[i];
		voltage_i = voltage[i];
		t->Fill();
	}
	for(int i = 0; i< temp2.size(); i++)
	{
		temp2_i = temp2[i];
		time_i = time[i];
		t2->Fill();
	}
	
	f.Write();
	f.Close();

	cout << "File: " << (file_name_V_vs_T.erase(file_name_V_vs_T.size()-5,5)).append(".txt") << " and " << file_name_T_vs_t << " converted to " << data_file_root << endl;

	return 0;

}
