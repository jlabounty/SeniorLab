int GetCdPeaks(
	       TString infile = "data/Scattering_Cd_101216_143714.root"
)
{
  TFile *cdFile = TFile::Open(infile); 
  TH1D *cdHraw = new TH1D();
  cdHraw = (TH1D*)cdFile->Get("h");
  TCanvas *c_Cd = new TCanvas();
  cdHraw->Draw();
  vector<double> mean, stdev, energy, Z;

  cout << "=======================" << endl;
  cout << "!                     !" << endl;
  cout << "!        Cd-48        !" << endl;
  cout << "!                     !" << endl;
  cout << "=======================" << endl;

  /*==============Cd-48 K1 Peak===============*/
  /*Clone Histogram of Spectrum from Data File*/
  TH1D *cdHist_K1 = (TH1D*)h->Clone("cdHraw");
  /*Define Spectrum Fit Function*/
  TF1 *fSpec_K1 = new TF1("fSpec_K1", "gaus", 930., 955.);
  /*Estimate Parameters of Fit*/
  fSpec_K1->SetParameters(940, 10, 2);
  TCanvas *c_CdK1 = new TCanvas();
  /*Fit Pre-Defined Function to Spectrum*/
  cdHist_K1->Fit("fSpec_K1", "Q", "", 930., 955.);

  /*Obtain Fit Function from Histogram*/
  TF1 *fStat_K1 = cdHist_K1->GetFunction("fSpec_K1");

  /*Assign Fit Parameters to Variables*/
  double Peak_K1 = fStat_K1->GetParameter(1);
  double Stdv_K1 = fStat_K1->GetParameter(2);
  /*Assign Fit Statistics to Variables*/
  double Chi_K1 = fStat_K1->GetChisquare();
  double NDF_K1 = fStat_K1->GetNDF();
  double Red_K1 = Chi_K1/NDF_K1;

  /*Output Results to Terminal*/
  cout << "=======================" << endl;
  cout << "!   Finding K1 Peak   !" << endl;
  cout << "-----------------------" << endl;
  cout << "Peak Occurs at: " << endl;
  cout << Peak_K1 << " +/- " << Stdv_K1 << endl;
  cout << "-----------------------" << endl;
  cout << "-----Fit Statistics----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Sq     |  " << Chi_K1 << endl;
  cout << "DoF        |  " << NDF_K1 << endl;
  cout << "Red Chi-Sq |  " << Red_K1 << endl;
  cout << "=======================" << endl;

  /*Append Values to Vectors*/
  energy.push_back(23.17);
  Z.push_back(48.);
  mean.push_back(Peak_K1);
  stdev.push_back(Stdv_K1);

  /*===================================*/

  /*==============Cd-48 K2 Peak===============*/
  /*Clone Histogram of Spectrum from Data File*/
  TH1D *cdHist_K2 = (TH1D*)h->Clone("cdHraw");
  /*Define Spectrum Fit*/
  TF1 *fSpec_K2 = new TF1("fSpec_K2", "gaus", 1050., 1080);
  /*Estimate Parameters of Fit Function*/
  // fSpec_K2->SetParNames("Strength", "Mean","Sigma", "Back1", "Back2", "Back3"); 
  fSpec_K2->SetParameters(1065., 1000, 2);
  TCanvas *c_CdK2 = new TCanvas();
  /*Fit Pre-Defined Function to Spectrum*/
  cdHist_K2->Fit("fSpec_K2", "Q", "", 1050., 1080.);

  /*Obtain Fit Function from Histogram*/
  TF1 *fStat_K2 = cdHist_K2->GetFunction("fSpec_K2");

  /*Assign Fit Parameters to Variables*/
  double Peak_K2 = fStat_K2->GetParameter(1);
  double Stdv_K2 = fStat_K2->GetParameter(2);
  /*Assign Fit Statistics to Variables*/
  double Chi_K2 = fStat_K2->GetChisquare();
  double NDF_K2 = fStat_K2->GetNDF();
  double Red_K2 = Chi_K2/NDF_K2;

  /*Output Results to Terminal*/
  cout << "=======================" << endl;
  cout << "!   Finding K2 Peak   !" << endl;
  cout << "-----------------------" << endl;
  cout << "Peak Occurs at: " << endl;
  cout << Peak_K2 << " +/- " << Stdv_K2 << endl;
  cout << "-----------------------" << endl;
  cout << "-----Fit Statistics----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Sq     |  " << Chi_K2 << endl;
  cout << "DoF        |  " << NDF_K2 << endl;
  cout << "Red Chi-Sq |  " << Red_K2 << endl;
  cout << "=======================" << endl;
  
  /*Append Values to Vectors*/
  energy.push_back(26.09);
  Z.push_back(48.);
  mean.push_back(Peak_K2);
  stdev.push_back(Stdv_K2);

  /*===================================*/

  /*==============Cd-48 L1 Peak==============*/
  // /*Clone Histogram of Spectrum from Data File*/
  // TH1D *cdHist_L1 = (TH1D*)h->Clone("cdHraw");
  // /*Define Spectrum Fit Function*/
  // TF1 *fSpec_L1 = new TF1("fSpec_L1", "landau", 9., 15.);
  // /*Estimate Parameters of Fit*/
  // fSpec_L1->SetParameters(12, 75);
  // TCanvas *c_CdL1 = new TCanvas();
  // /*Fit Pre-Defined Function to Spectrum*/
  // cdHist_L1->Fit("fSpec_L1", "Q", "", 9., 15.);

  // /*Obtain Fit Function from Histogram*/
  // TF1 *fStat_L1 = cdHist_L1->GetFunction("fSpec_L1");

  // /*Assign Fit Parameters to Variables*/
  // double Peak_L1 = fStat_L1->GetParameter(1);
  // double Stdv_L1 = fStat_L1->GetParameter(2);
  // /*Assign Fit Statistics to Variables*/
  // double Chi_L1 = fStat_L1->GetChisquare();
  // double NDF_L1 = fStat_L1->GetNDF();
  // double Red_L1 = Chi_L1/NDF_L1;

  // /*Output Results to Terminal*/
  // cout << "=======================" << endl;
  // cout << "!   Finding L1 Peak   !" << endl;
  // cout << "-----------------------" << endl;
  // cout << "Peak Occurs at: " << endl;
  // cout << Peak_L1 << " +/- " << Stdv_L1 << endl;
  // cout << "-----------------------" << endl;
  // cout << "-----Fit Statistics----" << endl;
  // cout << "-----------------------" << endl;
  // cout << "Chi-Sq     |  " << Chi_L1 << endl;
  // cout << "DoF        |  " << NDF_L1 << endl;
  // cout << "Red Chi-Sq |  " << Red_L1 << endl;
  // cout << "=======================" << endl;

  // /*Append Values to Vectors*/
  // // energy.push_back(3.13);
  // Z.push_back(48.);
  // // mean.push_back(Peak_L1);
  // // stdev.push_back(Stdv_L1);

  // /*===================================*/

  // /*==============Cd-48 L2 Peak==============*/
  // /*Clone Histogram of Spectrum from Data File*/
  // TH1D *cdHist_L2 = (TH1D*)h->Clone("cdHraw");
  // /*Define Spectrum Fit Function*/
  // TF1 *fSpec_L2 = new TF1("fSpec_L2", "gaus", 700., 720.);
  // /*Estimate Parameters of Fit*/
  // fSpec_L2->SetParameters(710, 75, 2);
  // TCanvas *c_CdL2 = new TCanvas();
  // /*Fit Pre-Defined Function to Spectrum*/
  // cdHist_L2->Fit("fSpec_L2", "Q", "", 700., 720.);

  // /*Obtain Fit Function from Histogram*/
  // TF1 *fStat_L2 = cdHist_L2->GetFunction("fSpec_L2");

  // /*Assign Fit Parameters to Variables*/
  // double Peak_L2 = fStat_L2->GetParameter(1);
  // double Stdv_L2 = fStat_L2->GetParameter(2);
  // /*Assign Fit Statistics to Variables*/
  // double Chi_L2 = fStat_L2->GetChisquare();
  // double NDF_L2 = fStat_L2->GetNDF();
  // double Red_L2 = Chi_L2/NDF_L2;

  // /*Output Results to Terminal*/
  // cout << "=======================" << endl;
  // cout << "!   Finding L2 Peak   !" << endl;
  // cout << "-----------------------" << endl;
  // cout << "Peak Occurs at: " << endl;
  // cout << Peak_L2 << " +/- " << Stdv_L2 << endl;
  // cout << "-----------------------" << endl;
  // cout << "-----Fit Statistics----" << endl;
  // cout << "-----------------------" << endl;
  // cout << "Chi-Sq     |  " << Chi_L2 << endl;
  // cout << "DoF        |  " << NDF_L2 << endl;
  // cout << "Red Chi-Sq |  " << Red_L2 << endl;
  // cout << "=======================" << endl;

  /*Append Values to Vectors*/
  // energy.push_back(3.32);
  // Z.push_back(48.);
  // mean.push_back(Peak_L2);
  // stdev.push_back(Stdv_L2);

  /*===================================*/

  // /*==============Cd-48 L3 Peak==============*/
  // /*Clone Histogram of Spectrum from Data File*/
  // TH1D *cdHist_L3 = (TH1D*)h->Clone("cdHraw");
  // /*Define Spectrum Fit Function*/
  // TF1 *fSpec_L3 = new TF1("fSpec_L3", "gaus", 700., 720.);
  // /*Estimate Parameters of Fit*/
  // fSpec_L3->SetParameters(710, 75, 2);
  // TCanvas *c_CdL3 = new TCanvas();
  // /*Fit Pre-Defined Function to Spectrum*/
  // cdHist_L3->Fit("fSpec_L3", "Q", "", 700., 720.);

  // /*Obtain Fit Function from Histogram*/
  // TF1 *fStat_L3 = cdHist_L3->GetFunction("fSpec_L3");

  // /*Assign Fit Parameters to Variables*/
  // double Peak_L3 = fStat_L3->GetParameter(1);
  // double Stdv_L3 = fStat_L3->GetParameter(2);
  // /*Assign Fit Statistics to Variables*/
  // double Chi_L3 = fStat_L3->GetChisquare();
  // double NDF_L3 = fStat_L3->GetNDF();
  // double Red_L3 = Chi_L3/NDF_L3;

  // /*Output Results to Terminal*/
  // cout << "=======================" << endl;
  // cout << "!   Finding L3 Peak   !" << endl;
  // cout << "-----------------------" << endl;
  // cout << "Peak Occurs at: " << endl;
  // cout << Peak_L3 << " +/- " << Stdv_L3 << endl;
  // cout << "-----------------------" << endl;
  // cout << "-----Fit Statistics----" << endl;
  // cout << "-----------------------" << endl;
  // cout << "Chi-Sq     |  " << Chi_L3 << endl;
  // cout << "DoF        |  " << NDF_L3 << endl;
  // cout << "Red Chi-Sq |  " << Red_L3 << endl;
  // cout << "=======================" << endl;

  // /*Append Values to Vectors*/
  // // energy.push_back(13.6);
  // Z.push_back(48.);
  // // mean.push_back(Peak_L3);
  // // stdev.push_back(Stdv_L3);

  // /*===================================*/


  /*Output the data to a root file*/
  /*Create a root file to store the data taken from the files*/
  std::string file_root = "OutputFile.root";
  TFile f(("./"+file_root).c_str(),"UPDATE");
  TTree *t = (TTree*)f.Get("t");
  double mean_i, stdev_i, energy_i, Z_i; 

  t->SetBranchAddress("mean",&mean_i);
  t->SetBranchAddress("stdev",&stdev_i);
  t->SetBranchAddress("energy",&energy_i);
  t->SetBranchAddress("Z",&Z_i);

  /*Fill the output file branches with the data from the file*/
  for(int i = 0; i < mean.size(); i++)
    {
      mean_i = mean[i];
      Z_i = Z[i];
      energy_i = energy[i];
      stdev_i = stdev[i];
      t->Fill();
    }

  f.Write();
  f.Close();


	gStyle->SetOptStat(0);
	std::string title = "^{48}Cd Uncalibrated Spectrum";

	TCanvas *c_CdSpec = new TCanvas("c_CdSpec",title.c_str(),750,750);     //Makes canvas large enough for png printing.
		c_CdSpec->cd();
		c_CdSpec->SetGridx(1);
		c_CdSpec->SetGridy(1);
	//Use blank histogram to set the parameters of the canvas
	TH1F *blankCd = new TH1F("blankCd",title.c_str(),10, 0, 2048);
		blankCd->GetYaxis()->SetRangeUser(0, 600);
		blankCd->GetXaxis()->SetTitle("Bin Number");
		blankCd->GetYaxis()->SetTitle("Photon Count");
		blankCd->GetYaxis()->SetTitleOffset(1.65);
		blankCd->GetXaxis()->SetNdivisions(505);
		blankCd->GetYaxis()->SetNdivisions(505);
		blankCd->SetLineColor(0);
	blankCd->Draw();

	TH1D *hist = new TH1D();
	hist = (TH1D*)cdFile->Get("h");
	hist->Draw("SAME");
	fStat_K1->SetLineColor(kRed);
	fStat_K1->Draw("SAME");
	fStat_K2->SetLineColor(kOrange+10);
	fStat_K2->Draw("SAME");
	// fStat_L1->SetLineColor(kGreen+3);
	// fStat_L1->Draw("SAME");
	// fStat_L2->SetLineColor(kBlue);
	// fStat_L2->Draw("SAME");
	// fStat_L3->SetLineColor(kViolet);
	// fStat_L3->Draw("SAME");

	// c_CdSpec->Print("./plots/CdBinnedSpectrum.png");

	c_Cd->Close();
	c_CdK1->Close();
	c_CdK2->Close();
	// c_CdL1->Close();
	// c_CdL2->Close();
	// c_CdL3->Close();
	c_CdSpec->Close();

  return 0;
}
