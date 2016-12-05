int makePlot_VvT_BaTiO3(
			TString infile1 = "data/mV_vs_T111416_Run2.txt",
			TString infile2 = "data/BaTiO3_CurieWeiss.txt",
			// TString infile3 = "data/BaTiO3_CurieWeiss_LowT.txt",
			TString infile3 = "data/BaTiO3_CurieWeiss_LowT2.txt"
)
{

  TTree *TData = new TTree();
  TData->ReadFile(infile1, "T/D:V:null");
  int n = TData->Draw("V:T", "", "goff");

  vector<double> V, T, C1, C2, k;
  for(int i = 0; i<n; i++)
    {
      if(TData->GetV2()[i] > 50.)
	{
      V.push_back(TData->GetV1()[i]);
      T.push_back(TData->GetV2()[i]);

      C1.push_back(TMath::Abs(TData->GetV1()[i]/1.99) / (2*TMath::Pi()*25000.*1029));
      // C2.push_back((10**12.)*1.99*(1 - sqrt(1 - 4*(V[i]/1.99)**2. )) / (2*TMath::Pi()*25000.*1029*2*TMath::Abs(V[i])));
      C2.push_back((10**12.)*1.99*(1 - sqrt(1 - 4*(TData->GetV1()[i]/1.99)**2. )) / (2*TMath::Pi()*25000.*1029*2*TMath::Abs(TData->GetV1()[i])));

      // k.push_back( C2[i] / (3.2384*10**(-13.)));

      k.push_back((10**12.)*1.99*(1 - sqrt(1 - 4*(TData->GetV1()[i]/1.99)**2. )) / (2*TMath::Pi()*25000.*1029*2*TMath::Abs(TData->GetV1()[i])) / (3.2384*10**(-13.)));

	}
    }

  TTree *TDataCW = new TTree();
  TDataCW->ReadFile(infile2, "TCW/D:VCW:nullCW");
  int nCW = TDataCW->Draw("VCW:TCW", "", "goff");
  vector<double> VCW, TCW, C1CW, C2CW, kCW;
  for(int iCW = 0; iCW<nCW; iCW++)
    {
      if(TDataCW->GetV2()[iCW] > 50.)
	{
      VCW.push_back(TDataCW->GetV1()[iCW]);
      TCW.push_back(TDataCW->GetV2()[iCW]);

      C1CW.push_back(TMath::Abs(TDataCW->GetV1()[iCW]/1.99) / (2*TMath::Pi()*25000.*1029));
      C2CW.push_back((10**12.)*1.99*(1 - sqrt(1 - 4*(TDataCW->GetV1()[iCW]/1.99)**2. )) / (2*TMath::Pi()*25000.*1029*2*TMath::Abs(TDataCW->GetV1()[iCW])));


      // kCW.push_back( C2CW[iCW] / (3.2384*10**(-13.)));
      kCW.push_back((10**12.)*1.99*(1 - sqrt(1 - 4*(TDataCW->GetV1()[iCW]/1.99)**2. )) / (2*TMath::Pi()*25000.*1029*2*TMath::Abs(TDataCW->GetV1()[iCW])) / (3.2384*10**(-13.)));

	}
    }

  TTree *TDataLow = new TTree();
  TDataLow->ReadFile(infile3, "TLow/D:VLow:nullLow");
  int nLow = TDataLow->Draw("VLow:TLow", "", "goff");
  vector<double> VLow, TLow, C1Low, C2Low, kLow;
  for(int iLow = 0; iLow<nLow; iLow++)
    {
      if(TDataLow->GetV2()[iLow] > 50.)
	{
      VLow.push_back(TDataLow->GetV1()[iLow]);
      TLow.push_back(TDataLow->GetV2()[iLow]);

      C1Low.push_back(TMath::Abs(TDataLow->GetV1()[iLow]/1.99) / (2*TMath::Pi()*25000.*1029));
      C2Low.push_back((10**12.)*1.99*(1 - sqrt(1 - 4*(TDataLow->GetV1()[iLow]/1.99)**2. )) / (2*TMath::Pi()*25000.*1029*2*TMath::Abs(TDataLow->GetV1()[iLow])));


      // kLow.push_back( C2Low[iLow] / (3.2384*10**(-13.)));
      kLow.push_back((10**12.)*1.99*(1 - sqrt(1 - 4*(TDataLow->GetV1()[iLow]/1.99)**2. )) / (2*TMath::Pi()*25000.*1029*2*TMath::Abs(TDataLow->GetV1()[iLow])) / (3.2384*10**(-13.)));

	}
    }


  TCanvas *c1 = new TCanvas();  
  TGraph *g_VvT = new TGraph(T.size(), &T[0], &V[0]);
  g_VvT->SetTitle("");
  g_VvT->GetXaxis()->SetTitle("T (#circC)");
  g_VvT->Draw("AP");

  // TGraph *g_VvT_CW = new TGraph(TCW.size(), &TCW[0], &VCW[0]);
  // g_VvT_CW->SetLineColor(kRed);
  // g_VvT_CW->Draw("same");

  // TCanvas *c2 = new TCanvas();
  // TGraph *g_C1vT = new TGraph(n, &T[0], &C1[0]);
  // g_C1vT->Draw("AP");

  TCanvas *c3 = new TCanvas();  
  TGraph *g_C2vT = new TGraph(T.size(), &T[0], &C2[0]);
  g_C2vT->SetTitle("");
  g_C2vT->GetXaxis()->SetTitle("T (#circC)");
  g_C2vT->GetYaxis()->SetTitle("C (pF)");
  // double Cb = g_C2vT->Eval(126.2394);
  double Cb = g_C2vT->Eval(126.2394);
  cout << Cb << endl;

  g_C2vT->Draw("AP");

  TLine *Tc = new TLine(126.2, 340., 126.2, 540.);
  Tc->SetLineStyle(2);
  Tc->SetLineColor(kRed);
  Tc->Draw();

  TLegend *leg = new TLegend(0.2, 0.6, 0.5, 0.7);
  leg->SetNColumns(1);
  leg->AddEntry(g_C2vT, "BaTiO_{3} C vs T", "p");
  leg->AddEntry(Tc, "T_{C} = 126.2 #circC", "l");
  leg->Draw();

  TGraph *g_C2vT_CW = new TGraph(TCW.size(), &TCW[0], &C2CW[0]);
  // g_C2vT_CW->SetLineColor(kRed);
  // g_C2vT_CW->Draw("same");
  TGraph *g_C2vT_Low = new TGraph(TLow.size(), &TLow[0], &C2Low[0]);
  // g_C2vT_Low->SetLineColor(kRed);
  // g_C2vT_Low->Draw("same");


  TCanvas *c4 = new TCanvas();
  TH1 *h4 = c4->DrawFrame(30., 0., 150., 5000.);
  h4->SetTitle("");   
  h4->GetXaxis()->SetTitle("T (#circC)");
  h4->GetYaxis()->SetTitle("k");
  h4->GetYaxis()->SetTitleOffset(1.8);
  TGraph *g_kvT = new TGraph(T.size(), &T[0], &k[0]);

  for(int iG = 0; iG < g_C2vT->GetN(); iG++)
    {
      g_kvT->SetPoint(iG, g_C2vT->GetX()[iG], (g_C2vT->GetY()[iG]*Cb / (Cb - g_C2vT->GetY()[iG])) / (3.2384*10**(-13)));
    }

  g_kvT->Draw("P");
  TGraph *g_kvT_CW = new TGraph(TCW.size(), &TCW[0], &kCW[0]);
  for(int iGCW = 0; iGCW < g_C2vT_CW->GetN(); iGCW++)
    {
      g_kvT_CW->SetPoint(iGCW, g_C2vT_CW->GetX()[iGCW], (g_C2vT_CW->GetY()[iGCW]*Cb / (Cb - g_C2vT_CW->GetY()[iGCW])) / (3.2384*10**(-13)));
    }
  g_kvT_CW->SetMarkerColor(kRed);
  g_kvT_CW->Draw("same, P");

  TGraph *g_kvT_Low = new TGraph(TLow.size(), &TLow[0], &kLow[0]);
  for(int iGLow = 0; iGLow < g_C2vT_Low->GetN(); iGLow++)
    {
      g_kvT_Low->SetPoint(iGLow, g_C2vT_Low->GetX()[iGLow], (g_C2vT_Low->GetY()[iGLow]*Cb / (Cb - g_C2vT_Low->GetY()[iGLow])) / (3.2384*10**(-13)));
    }
  g_kvT_Low->SetMarkerColor(kBlue);
  g_kvT_Low->Draw("same, P");

  TF1* fit = new TF1("fit", "[0]/(x-[1])", 126., 150.);
  // fit->SetParameters(500., 126.2);
  g_kvT_CW->Fit("fit", "","", 130., 142.);

  double ccw = (fit->GetParameter(0));
  double p = sqrt( (8.85*10**(-12.))*1.38*10**(-23.)*(fit->GetParameter(0))*(0.4*10**(-9.))**3. );

  cout << ccw << endl;
  cout << "p = " << p << endl;
  cout << "x = " << p  / (9.6*10**(-19.)) << endl;

  // cout << "p = " << sqrt( 8.85*10**(-12.)*1.38*10**(-23.)*(fit->GetParameter(0))*(0.4*10**(-9.))**3. ) << endl;


  TF1* fit2 = new TF1("fit2", "[0]/([1]-x)", 90., 115.);
  fit2->SetParameters(500., 122.);
  g_kvT_Low->Fit("fit2", "","", 90., 115.);
  g_kvT_Low->GetFunction("fit2")->SetLineColor(kBlue);

  TLegend *leg2 = new TLegend(0.2, 0.6, 0.55, 0.8);
  leg2->SetNColumns(1);
  leg2->AddEntry(g_kvT, "BaTiO_{3} k vs T", "p");
  leg2->AddEntry(fit, "#splitline{Curie-Weiss Law for T > T_{C}}{C_{CW} = 10523 #pm 24}", "l");
  leg2->AddEntry(g_kvT_Low->GetFunction("fit2"), "#splitline{Curie-Weiss Law for T < T_{C}}{C_{CW} = 19677 #pm 250}", "l");
  leg2->Draw();


  c3->Print("report/plots/BaTiO3_CvT_withTC.png");
  c4->Print("report/plots/BaTiO3_kvT.png");

  return 0;
}
