int GetSnPeaks(
	       TString infile = "data/Scattering_Sn_101016_143908.root"
)
{
  TFile *snFile = TFile::Open(infile); 
  TH1D *snHraw = new TH1D();
  snHraw = (TH1D*)snFile->Get("h");
  TCanvas *c_Sn = new TCanvas();
  snHraw->Draw();
  vector<double> mean, stdev, energy, Z;
  vector<int> line;

  cout << "=======================" << endl;
  cout << "!                     !" << endl;
  cout << "!       Sn-50        !" << endl;
  cout << "!                     !" << endl;
  cout << "=======================" << endl;

  /*==============Sn-50 K1 Peak==============*/
  /*Clone Histogram of Spectrum from Data File*/
  TH1D *snHist_K1 = (TH1D*)h->Clone("snHraw");
  /*Define Spectrum Fit Function*/
  TF1 *fSpec_K1 = new TF1("fSpec_K1", "gaus", 1025., 1040.);
  /*Estimate Parameters of Fit*/
  fSpec_K1->SetParameters(1030, 10, 2);
  TCanvas *c_SnK1 = new TCanvas();
  /*Fit Pre-Defined Function to Spectrum*/
  snHist_K1->Fit("fSpec_K1", "Q", "", 1025., 1040.);

  /*Obtain Fit Function from Histogram*/
  TF1 *fStat_K1 = snHist_K1->GetFunction("fSpec_K1");

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
  energy.push_back(25.27);
  Z.push_back(50.);
  mean.push_back(Peak_K1);
  stdev.push_back(Stdv_K1);
  line.push_back(1);

  /*===================================*/

  /*===========Sn-50 K2 Peak==========*/
  /*Clone Histogram of Spectrum from Data File*/
  TH1D *snHist_K2 = (TH1D*)h->Clone("snHraw");
  /*Define Spectrum Fit*/
  TF1 *fSpec_K2 = new TF1("fSpec_K2", "gaus", 1155., 1170.);
  /*Estimate Parameters of Fit Function*/
  // fSpec_K2->SetParNames("Strength", "Mean","Sigma", "Back1", "Back2", "Back3"); 
  fSpec_K2->SetParameters(1160., 1000, 2);
  TCanvas *c_SnK2 = new TCanvas();
  /*Fit Pre-Defined Function to Spectrum*/
  snHist_K2->Fit("fSpec_K2", "Q", "", 1155., 1170.);

  /*Obtain Fit Function from Histogram*/
  TF1 *fStat_K2 = snHist_K2->GetFunction("fSpec_K2");

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
  energy.push_back(28.48);
  Z.push_back(50.);
  mean.push_back(Peak_K2);
  stdev.push_back(Stdv_K2);
  line.push_back(2);

  /*===================================*/

  /*==============Sn-50 L1 Peak==============*/
  /*Clone Histogram of Spectrum from Data File*/
  TH1D *snHist_L1 = (TH1D*)h->Clone("snHraw");
  /*Define Spectrum Fit Function*/
  TF1 *fSpec_L1 = new TF1("fSpec_L1", "gaus", 137., 147.);
  /*Estimate Parameters of Fit*/
  fSpec_L1->SetParameters(142, 75, 2);
  TCanvas *c_SnL1 = new TCanvas();
  /*Fit Pre-Defined Function to Spectrum*/
  snHist_L1->Fit("fSpec_L1", "Q", "", 137., 147.);

  /*Obtain Fit Function from Histogram*/
  TF1 *fStat_L1 = snHist_L1->GetFunction("fSpec_L1");

  /*Assign Fit Parameters to Variables*/
  double Peak_L1 = fStat_L1->GetParameter(1);
  double Stdv_L1 = fStat_L1->GetParameter(2);
  /*Assign Fit Statistics to Variables*/
  double Chi_L1 = fStat_L1->GetChisquare();
  double NDF_L1 = fStat_L1->GetNDF();
  double Red_L1 = Chi_L1/NDF_L1;

  /*Output Results to Terminal*/
  cout << "=======================" << endl;
  cout << "!   Finding L1 Peak   !" << endl;
  cout << "-----------------------" << endl;
  cout << "Peak Occurs at: " << endl;
  cout << Peak_L1 << " +/- " << Stdv_L1 << endl;
  cout << "-----------------------" << endl;
  cout << "-----Fit Statistics----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Sq     |  " << Chi_L1 << endl;
  cout << "DoF        |  " << NDF_L1 << endl;
  cout << "Red Chi-Sq |  " << Red_L1 << endl;
  cout << "=======================" << endl;

  /*Append Values to Vectors*/
  energy.push_back(3.44);
  Z.push_back(50.);
  mean.push_back(Peak_L1);
  stdev.push_back(Stdv_L1);
  line.push_back(11);

  /*===================================*/

  /*==============Sn-50 L2 Peak==============*/
  /*Clone Histogram of Spectrum from Data File*/
  TH1D *snHist_L2 = (TH1D*)h->Clone("snHraw");
  /*Define Spectrum Fit Function*/
  TF1 *fSpec_L2 = new TF1("fSpec_L2", "gaus", 149., 157.);
  /*Estimate Parameters of Fit*/
  fSpec_L2->SetParameters(153, 75, 2);
  TCanvas *c_SnL2 = new TCanvas();
  /*Fit Pre-Defined Function to Spectrum*/
  snHist_L2->Fit("fSpec_L2", "Q", "", 149., 157.);

  /*Obtain Fit Function from Histogram*/
  TF1 *fStat_L2 = snHist_L2->GetFunction("fSpec_L2");

  /*Assign Fit Parameters to Variables*/
  double Peak_L2 = fStat_L2->GetParameter(1);
  double Stdv_L2 = fStat_L2->GetParameter(2);
  /*Assign Fit Statistics to Variables*/
  double Chi_L2 = fStat_L2->GetChisquare();
  double NDF_L2 = fStat_L2->GetNDF();
  double Red_L2 = Chi_L2/NDF_L2;

  /*Output Results to Terminal*/
  cout << "=======================" << endl;
  cout << "!   Finding L2 Peak   !" << endl;
  cout << "-----------------------" << endl;
  cout << "Peak Occurs at: " << endl;
  cout << Peak_L2 << " +/- " << Stdv_L2 << endl;
  cout << "-----------------------" << endl;
  cout << "-----Fit Statistics----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Sq     |  " << Chi_L2 << endl;
  cout << "DoF        |  " << NDF_L2 << endl;
  cout << "Red Chi-Sq |  " << Red_L2 << endl;
  cout << "=======================" << endl;

  /*Append Values to Vectors*/
  energy.push_back(3.66);
  Z.push_back(50.);
  mean.push_back(Peak_L2);
  stdev.push_back(Stdv_L2);
  line.push_back(12);

  /*=========================================*/

  // /*==============Sn-50 L3 Peak==============*/
  // /*Clone Histogram of Spectrum from Data File*/
  // TH1D *snHist_L3 = (TH1D*)h->Clone("snHraw");
  // /*Define Spectrum Fit Function*/
  // TF1 *fSpec_L3 = new TF1("fSpec_L3", "gaus", 595., 610.);
  // /*Estimate Parameters of Fit*/
  // fSpec_L3->SetParameters(600, 75, 2);
  // TCanvas *c_SnL3 = new TCanvas();
  // /*Fit Pre-Defined Function to Spectrum*/
  // snHist_L3->Fit("fSpec_L3", "Q", "", 595., 610.);

  // /*Obtain Fit Function from Histogram*/
  // TF1 *fStat_L3 = snHist_L3->GetFunction("fSpec_L3");

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
  // energy.push_back(14.76);
  // Z.push_back(50.);
  // mean.push_back(Peak_L3);
  // stdev.push_back(Stdv_L3);
  // line.push_back(13);

  // /*===================================*/


  /*Output the data to a root file*/
  /*Create a root file to store the data taken from the files*/
  std::string file_root = "OutputFile.root";
  TFile f(("./"+file_root).c_str(),"UPDATE");
  TTree *t = (TTree*)f.Get("t");
  double mean_i, stdev_i, energy_i, Z_i; 
  int line_i;

  t->SetBranchAddress("mean",&mean_i);
  t->SetBranchAddress("stdev",&stdev_i);
  t->SetBranchAddress("energy",&energy_i);
  t->SetBranchAddress("Z",&Z_i);
  t->SetBranchAddress("Ident",&line_i);

  /*Fill the output file branches with the data from the file*/
  for(int i = 0; i < mean.size(); i++)
    {
      mean_i = mean[i];
      Z_i = Z[i];
      energy_i = energy[i];
      stdev_i = stdev[i];
      line_i = line[i];
      t->Fill();
    }

  f.Write();
  f.Close();


	gStyle->SetOptStat(0);
	std::string title = "^{50}Sn Uncalibrated Spectrum";

	TCanvas *c_SnSpec = new TCanvas("c_SnSpec",title.c_str(),750,750);     //Makes canvas large enough for png printing.
		c_SnSpec->cd();
		c_SnSpec->SetGridx(1);
		c_SnSpec->SetGridy(1);
	//Use blank histogram to set the parameters of the canvas
	TH1F *blankSn = new TH1F("blankSn",title.c_str(),10, 0, 2048);
		blankSn->GetYaxis()->SetRangeUser(0, 600);
		blankSn->GetXaxis()->SetTitle("Bin Number");
		blankSn->GetYaxis()->SetTitle("Photon Count");
		blankSn->GetYaxis()->SetTitleOffset(1.65);
		blankSn->GetXaxis()->SetNdivisions(505);
		blankSn->GetYaxis()->SetNdivisions(505);
		blankSn->SetLineColor(0);
	blankSn->Draw();

	TH1D *hist = new TH1D();
	hist = (TH1D*)snFile->Get("h");
	hist->Draw("SAME");
	fStat_K1->SetLineColor(kRed);
	fStat_K1->Draw("SAME");
	fStat_K2->SetLineColor(kOrange+10);
	fStat_K2->Draw("SAME");
	fStat_L1->SetLineColor(kGreen+3);
	fStat_L1->Draw("SAME");
	fStat_L2->SetLineColor(kBlue);
	fStat_L2->Draw("SAME");
	// fStat_L3->SetLineColor(kViolet);
	// fStat_L3->Draw("SAME");

	// c_SnSpec->Print("./plots/SnBinnedSpectrum.png");

  c_Sn->Close();
  c_SnK1->Close();
  c_SnK2->Close();
  c_SnL1->Close();
  c_SnL2->Close();
  // c_SnL3->Close();
  c_SnSpec->Close();

  return 0;
}
