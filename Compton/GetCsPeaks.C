int GetCsPeaks()
{
  TFile *csFile = new TFile("data/Cs_137_Weak_090716_141039.root"); 
  TH1D *csHraw = new TH1D();
  csHraw = (TH1D*)csFile->Get("h");
  TCanvas *c1 = new TCanvas();
  csHraw->Draw();

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
  cout << "Peak Occurs at: " << Peak_032 << " +/- " << Stdv_032 << endl;

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
  
  /*===================================*/


  return 0;
}
