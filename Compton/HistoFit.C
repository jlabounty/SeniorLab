int HistoFit()
{
	TFile *file = new TFile("./data/Cs_137_Weak_090716_141039.root");
	TH1D *his = file->Get("h");
	TF1 *fSignal = new TF1("fSignal","gaus",650.,2000.);
	TF1 *fBackground = new TF1("fBackground","pol0+expo(1)",650.,2000.);
	TF1 *fSpectrum = new TF1("fSpectrum","gaus+pol0(3)+expo(4)",650.,2000.);
	fSpectrum->SetParNames("Strength","Mean","Sigma","Back1","Back2","Back3");
	fSpectrum->SetParameters(100, 1000, 2, 50, 0, 0);
	his->Fit("fSpectrum", "", "", 650., 2000.);
	Double_t param[6];
	fSpectrum->GetParameters(param);
	fSignal->SetParameters(&param[0]);
	fBackground->SetParameters(&param[3]);
	TH1D *hisSignal = new TH1D(*his);
	hisSignal->Sumw2();
	hisSignal->Add(fBackground, -1);
	his->Draw("e"); hisSignal->Draw("SAME");
	fSignal->Draw("SAME"); fBackground->Draw("SAME");

	TCanvas *c2 = new TCanvas ();
	hisSignal->Draw();
	fSignal->Draw("SAME");

	TF1 *fitResult = his->GetFunction("fSpectrum");
	cout << fitResult->GetChisquare() << endl;
	cout << fitResult->GetNDF() << endl;

	return 0;

}
