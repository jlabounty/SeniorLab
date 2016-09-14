int GetBaPeaks(
	       TString infile = "data/Ba_133_Weak_091216_133430.root"
)
{
  TFile *baFile = TFile::Open(infile);
  TH1D *baHraw = new TH1D();
  baHraw = (TH1D*)baFile->Get("h");
  TCanvas *c1 = new TCanvas();
  baHraw->Draw();

  vector<double> mean, stdev, energy;

  /*========Ba-133 302/356 keV Peak=========*/
  
  TH1D *baHist_300 = (TH1D*)h->Clone("baHraw");
  TF1 *fSpec_300 = new TF1("fSpec_300", "gaus+gaus(3)+pol0(6)+expo(7)", 375., 800.);
  fSpec_300->SetParameters(100, 400, 2, 100 , 550, 2,  50, 0, 0);
  TCanvas *c2 = new TCanvas();
  baHist_300->Fit("fSpec_300", "Q", "", 375., 800.);

  TF1 *fGausStat_300 = baHist_300->GetFunction("fSpec_300");

  double Chi_300 = fGausStat_300->GetChisquare();
  double NDF_300 = fGausStat_300->GetNDF();
  double Red_300 = Chi_300/NDF_300;

  cout << "=======================" << endl;
  cout << "!                     !" << endl;
  cout << "!       Ba-133        !" << endl;
  cout << "!                     !" << endl;
  cout << "=======================" << endl;

  cout << "=======================" << endl;
  cout << "!Finding 302 keV Peak!" << endl;
  cout << "-----------------------" << endl;
  double Peak_302 = fGausStat_300->GetParameter(1);
  double Stdv_302 = fGausStat_300->GetParameter(2);
  cout << "Peak Occurs at: " << endl;
  cout << Peak_302 << " +/- " << Stdv_302 << endl;
  cout << "-----------------------" << endl;
  cout << "-----Fit Statistics----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Sq     |  " << Chi_300 << endl;
  cout << "DoF        |  " << NDF_300 << endl;
  cout << "Red Chi-Sq |  " << Red_300 << endl;
  cout << "=======================" << endl;
  cout << "=======================" << endl;
  cout << "!Finding 356 keV Peak!" << endl;
  cout << "-----------------------" << endl;
  double Peak_356 = fGausStat_300->GetParameter(4);
  double Stdv_356 = fGausStat_300->GetParameter(5);
  cout << "Peak Occurs at: " << endl;
  cout << Peak_356 << " +/- " << Stdv_356 << endl;
  cout << "-----------------------" << endl;
  cout << "-----Fit Statistics----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Sq     |  " << Chi_300 << endl;
  cout << "DoF        |  " << NDF_300 << endl;
  cout << "Red Chi-Sq |  " << Red_300 << endl;
  cout << "=======================" << endl;


  TF1 *fGaussOne = new TF1("fGaussOne", "gaus", 375., 800.);
  fGaussOne->SetLineColor(kBlue);
  TF1 *fGaussTwo = new TF1("fGaussTwo", "gaus", 375., 800.);
  fGaussTwo->SetLineColor(kGreen);

  Double_t param[9];
  fGausStat_300->GetParameters(param);
  fGaussOne->SetParameters(&param[0]);
  fGaussTwo->SetParameters(&param[3]);
  fGaussOne->Draw("SAME");
  fGaussTwo->Draw("SAME");



  /*===================================*/

  energy.push_back(302.);
  mean.push_back(Peak_302);
  stdev.push_back(Stdv_302);
  energy.push_back(356.);
  mean.push_back(Peak_356);
  stdev.push_back(Stdv_356);

  //Output the data to a root file                                                   
  //Create a root file to store the data taken from the files                        
  std::string file_root = "OutputFile.root";
  TFile f(("./"+file_root).c_str(),"UPDATE");
	TTree *t = (TTree*)f.Get("t");
  double mean_i, stdev_i, energy_i;


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
