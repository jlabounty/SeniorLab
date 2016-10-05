int GetCsPeaks(
	       TString infile = "data/Cs_137_Weak_090716_141039.root"
)
{
  TFile *feFile = TFile::Open(infile); 
  TH1D *feHraw = new TH1D();
  feHraw = (TH1D*)feFile->Get("h");
  TCanvas *c1 = new TCanvas();
  feHraw->Draw();
  vector<double> mean, stdev, energy;

  /*========Fe-55 5.9 keV Peak=========*/
  /*Clone Histogram of Spectrum from Data File*/
  TH1D *feHist_005 = (TH1D*)h->Clone("feHraw");
  /*Define Spectrum Fit Function*/
  TF1 *fSpec_005 = new TF1("fSpec_005", "gaus+pol2(3)", 20., 100.);
  /*Estimate Parameters of Fit*/
  fSpec_005->SetParameters(100, 75, 2, 200, 1);
  TCanvas *c2 = new TCanvas();
  /*Fit Pre-Defined Function to Spectrum*/
  feHist_032->Fit("fSpec_005", "Q", "", 20., 100.);

  /*Obtain Fit Function from Histogram*/
  TF1 *fStat_005 = feHist_005->GetFunction("fSpec_005");

  /*Assign Fit Parameters to Variables*/
  double Peak_005 = fStat_005->GetParameter(1);
  double Stdv_005 = fStat_005->GetParameter(2);
  /*Assign Fit Statistics to Variables*/
  double Chi_005 = fStat_005->GetChisquare();
  double NDF_005 = fStat_005->GetNDF();
  double Red_005 = Chi_005/NDF_005;

  /*Output Results to Terminal*/
  cout << "=======================" << endl;
  cout << "!                     !" << endl;
  cout << "!        Fe-55        !" << endl;
  cout << "!                     !" << endl;
  cout << "=======================" << endl;

  cout << "=======================" << endl;
  cout << "!Finding  5.9 keV Peak!" << endl;
  cout << "-----------------------" << endl;
  cout << "Peak Occurs at: " << endl;
  cout << Peak_005 << " +/- " << Stdv_005 << endl;
  cout << "-----------------------" << endl;
  cout << "-----Fit Statistics----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Sq     |  " << Chi_005 << endl;
  cout << "DoF        |  " << NDF_005 << endl;
  cout << "Red Chi-Sq |  " << Red_005 << endl;
  cout << "=======================" << endl;

  /*Append Values to Vectors*/
  energy.push_back(5.9);
  mean.push_back(Peak_005);
  stdev.push_back(Stdv_005);

  /*===================================*/

  /*========Fe-55 6.49 keV Peak========*/
  /*Clone Histogram of Spectrum from Data File*/
  TH1D *feHist_006 = (TH1D*)h->Clone("feHraw");
  /*Define Spectrum Fit*/
  TF1 *fSpec_006 = new TF1("fSpec_006", "gaus+pol0(3)+expo(4)", 650., 2000.);
  /*Estimate Parameters of Fit Function*/
  fSpec_006->SetParNames("Strength", "Mean","Sigma", "Back1", "Back2", "Back3"); 
  fSpec_006->SetParameters(100, 1000, 2, 50, 0, 0);
  TCanvas *c3 = new TCanvas();
  /*Fit Pre-Defined Function to Spectrum*/
  feHist_006->Fit("fSpec_006", "Q", "", 650., 2000.);

  /*Obtain Fit Function from Histogram*/
  TF1 *fStat_006 = feHist_006->GetFunction("fSpec_006");

  /*Assign Fit Parameters to Variables*/
  double Peak_006 = fStat_006->GetParameter(1);
  double Stdv_006 = fStat_006->GetParameter(2);
  /*Assign Fit Statistics to Variables*/
  double Chi_006 = fStat_006->GetChisquare();
  double NDF_006 = fStat_006->GetNDF();
  double Red_006 = Chi_006/NDF_006;

  /*Output Results to Terminal*/
  cout << "=======================" << endl;
  cout << "!Finding 6.49 keV Peak!" << endl;
  cout << "-----------------------" << endl;
  cout << "Peak Occurs at: " << endl;
  cout << Peak_006 << " +/- " << Stdv_006 << endl;
  cout << "-----------------------" << endl;
  cout << "-----Fit Statistics----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Sq     |  " << Chi_006 << endl;
  cout << "DoF        |  " << NDF_006 << endl;
  cout << "Red Chi-Sq |  " << Red_006 << endl;
  cout << "=======================" << endl;
  
  /*Append Values to Vectors*/
  energy.push_back(6.49);
  mean.push_back(Peak_006);
  stdev.push_back(Stdv_006);

  /*===================================*/

  /*Output the data to a root file*/
  /*Create a root file to store the data taken from the files*/
  std::string file_root = "OutputFile.root";
  TFile f(("./"+file_root).c_str(),"UPDATE");
  TTree *t = (TTree*)f.Get("t");
  double mean_i, stdev_i, energy_i; 

  t->SetBranchAddress("mean",&mean_i);
  t->SetBranchAddress("stdev",&stdev_i);
  t->SetBranchAddress("energy",&energy_i);

  /*Fill the output file branches with the data from the file*/
  for(int i = 0; i < mean.size(); i++)
    {
      mean_i = mean[i];
      energy_i = energy[i];
      stdev_i = stdev[i];
      t->Fill();
    }

  f.Write();
  f.Close();


	gStyle->SetOptStat(0);
	std::string title = "^{55}Fe Uncalibrated Spectrum";

	TCanvas *c22 = new TCanvas("c22",title.c_str(),750,750);     //Makes canvas large enough for png printing.
		c22->cd();
		c22->SetGridx(1);
		c22->SetGridy(1);
//		c->SetFixedAspectRatio();
	//Use blank histogram to set the parameters of the canvas
	TH1F *blank3 = new TH1F("blank",title.c_str(),10, 0, 2048);
		blank3->GetYaxis()->SetRangeUser(0, 2600);
		blank3->GetXaxis()->SetTitle("Bin Number");
		blank3->GetYaxis()->SetTitle("Photon Count");
		blank3->GetYaxis()->SetTitleOffset(1.65);
		blank3->GetXaxis()->SetNdivisions(505);
		blank3->GetYaxis()->SetNdivisions(505);
		blank3->SetLineColor(0);
	blank3->Draw();

	TH1D *hist = new TH1D();
	hist = (TH1D*)feFile->Get("h");
	hist->Draw("SAME");
	fStat_006->SetLineColor(kBlue);
	fStat_006->Draw("SAME");
	fStat_005->SetLineColor(kRed);
	fStat_005->Draw("SAME");

//	c22->Print("./plots/CsBinnedSpectrum.png");

  c1->Close();
  c2->Close();
  c3->Close();
  c22->Close();



  return 0;
}
