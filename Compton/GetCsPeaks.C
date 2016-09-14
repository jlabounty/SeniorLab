int GetCsPeaks(
	       TString infile = "data/Cs_137_Weak_090716_141039.root"
)
{
  TFile *csFile = TFile::Open(infile); 
  TH1D *csHraw = new TH1D();
  csHraw = (TH1D*)csFile->Get("h");
  TCanvas *c1 = new TCanvas();
  csHraw->Draw();

  vector<double> mean, stdev, energy;

  /*========Cs-137 32 keV Peak=========*/

  TH1D *csHist_032 = (TH1D*)h->Clone("csHraw");
  TF1 *fSpec_032 = new TF1("fSpec_032", "gaus+pol2(3)", 20., 100.);
  fSpec_032->SetParameters(100, 75, 2, 200, 1);
  TCanvas *c2 = new TCanvas();
  csHist_032->Fit("fSpec_032", "Q", "", 20., 100.);

  TF1 *fGausStat_032 = csHist_032->GetFunction("fSpec_032");

  double Chi_032 = fGausStat_032->GetChisquare();
  double NDF_032 = fGausStat_032->GetNDF();
  double Red_032 = Chi_032/NDF_032;
  cout << "Fit Statistics..." << endl;
  cout << "Chi-Squared: " << Chi_032 << endl;
  cout << "Degrees of Freedom: " << NDF_032 << endl;
  cout << "Reduced Chi-Squared: " << Red_032 << endl;

  double Peak_032 = fGausStat_032->GetParameter(1);
  double Stdv_032 = fGausStat_032->GetParameter(2);
  // cout << fGausStat_032->GetChisquare() << endl;
  // cout << fGausStat_032->GetNDF() << endl;
  cout << "Peak Occurs at: " << Peak_032 << " +/- " << Stdv_032 << endl << endl;

  energy.push_back(32.0);
  mean.push_back(Peak_032);
  stdev.push_back(Stdv_032);

  /*===================================*/

  /*======Cs-137 661.6 keV Peak======*/
  TH1D *csHist_662 = (TH1D*)h->Clone("csHraw");
  TF1 *fSpec_662 = new TF1("fSpec_662", "gaus+pol0(3)+expo(4)", 650., 2000.);
  fSpec_662->SetParNames("Strength", "Mean","Sigma", "Back1", "Back2", "Back3"); 
  fSpec_662->SetParameters(100, 1000, 2, 50, 0, 0);
  TCanvas *c3 = new TCanvas();
  csHist_662->Fit("fSpec_662", "Q", "", 650., 2000.);

  TF1 *fGausStat_662 = csHist_662->GetFunction("fSpec_662");
  double Chi_662 = fGausStat_662->GetChisquare();
  double NDF_662 = fGausStat_662->GetNDF();
  double Red_662 = Chi_662/NDF_662;
  cout << "Fit Statistics..." << endl;
  cout << "Chi-Squared: " << Chi_662 << endl;
  cout << "Degrees of Freedom: " << NDF_662 << endl;
  cout << "Reduced Chi-Squared: " << Red_662 << endl;

  double Peak_662 = fGausStat_662->GetParameter(1);
  double Stdv_662 = fGausStat_662->GetParameter(2);
  cout << "Peak Occurs at: " << Peak_662 << " +/- " << Stdv_662 << endl;
  
  energy.push_back(661.6);
  mean.push_back(Peak_662);
  stdev.push_back(Stdv_662);

  /*===================================*/

	//Output the data to a root file
	//Create a root file to store the data taken from the files
	std::string file_root = "OutputFile.root";
	TFile f(("./"+file_root).c_str(),"UPDATE");
//	TTree *t = new TTree("t","Peaks of Functions and their Standard Deviations");
	TTree *t = (TTree*)f.Get("t");
	double mean_i, stdev_i, energy_i; 

//	TBranch *b_mean = t->Branch("mean",&mean_i,"Mean bin of the energy peak/D");
//	TBranch *b_stdev = t->Branch("stdev",&stdev_i,"Standard deviation of gaussian fit to the energy peak/D");
//	TBranch *b_energy = t->Branch("energy",&energy_i,"Known energy of the peak/D");
	t->SetBranchAddress("mean",&mean_i);
	t->SetBranchAddress("stdev",&stdev_i);
	t->SetBranchAddress("energy",&energy_i);


	//Fill the output file branches with the data from the file 
	for(int i = 0; i < mean.size(); i++)
	{
		mean_i = mean[i];
		energy_i = energy[i];
		stdev_i = stdev[i];
		t->Fill();
	}

	f.Write();
	f.Close();


  return 0;
}
