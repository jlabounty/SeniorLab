int makePlot_VvT_BaTiO3(
			TString infile1 = "data/mV_vs_T111416_Run2.txt",
			TString infile2 = "data/BaTiO3_CurieWeiss.txt"
)
{

  TTree *TData = new TTree();
  TData->ReadFile(infile1, "T/D:V:null");
  int n = TData->Draw("V:T", "", "goff");

  vector<double> V, T, C1, C2, k;
  for(int i = 0; i<n; i++)
    {
      V.push_back(TData->GetV1()[i]);
      T.push_back(TData->GetV2()[i]);

      C1.push_back(TMath::Abs(V[i]/1.99) / (2*TMath::Pi()*25000.*1029));
      C2.push_back(1.99*(1 - sqrt(1 - 4*(V[i]/1.99)**2. )) / (2*TMath::Pi()*25000.*1029*2*TMath::Abs(V[i])));

      // k.push_back( C2[i]/ (8.854*(10**(-12.)) ));

      k.push_back( C2[i] / (3.2384*10**(-13.)));

    }

  TTree *TDataCW = new TTree();
  TDataCW->ReadFile(infile2, "TCW/D:VCW:nullCW");
  int nCW = TDataCW->Draw("VCW:TCW", "", "goff");
  vector<double> VCW, TCW, C1CW, C2CW, kCW;
  for(int iCW = 0; iCW<n; iCW++)
    {
      VCW.push_back(TDataCW->GetV1()[iCW]);
      TCW.push_back(TDataCW->GetV2()[iCW]);

      C1CW.push_back(TMath::Abs(VCW[iCW]/1.99) / (2*TMath::Pi()*25000.*1029));
      C2CW.push_back(1.99*(1 - sqrt(1 - 4*(VCW[iCW]/1.99)**2. )) / (2*TMath::Pi()*25000.*1029*2*TMath::Abs(VCW[iCW])));

      // k.push_back( C2[i]/ (8.854*(10**(-12.)) ));

      kCW.push_back( C2CW[iCW] / (3.2384*10**(-13.)));

    }


  TCanvas *c1 = new TCanvas();  
  TGraph *g_VvT = new TGraph(n, &T[0], &V[0]);
  g_VvT->SetTitle("");
  g_VvT->GetXaxis()->SetTitle("T ( ^{#circ}C)");
  g_VvT->Draw("AP");

  TGraph *g_VvT_CW = new TGraph(nCW, &TCW[0], &VCW[0]);
  g_VvT_CW->SetLineColor(kRed);
  g_VvT_CW->Draw("same");

  // TCanvas *c2 = new TCanvas();
  // TGraph *g_C1vT = new TGraph(n, &T[0], &C1[0]);
  // g_C1vT->Draw("AP");

  TCanvas *c3 = new TCanvas();  
  TGraph *g_C2vT = new TGraph(n, &T[0], &C2[0]);
  g_C2vT->SetTitle("");
  g_C2vT->GetXaxis()->SetTitle("T ( ^{#circ}C)");
  g_C2vT->Draw("AP");
  TGraph *g_C2vT_CW = new TGraph(nCW, &TCW[0], &C2CW[0]);
  g_C2vT_CW->SetLineColor(kRed);
  g_C2vT_CW->Draw("same");


  TCanvas *c4 = new TCanvas();  
  TGraph *g_kvT = new TGraph(n, &T[0], &k[0]);
  g_kvT->SetTitle("");
  g_kvT->GetXaxis()->SetTitle("T ( ^{#circ}C)");
  g_kvT->Draw("AP");
  TGraph *g_kvT_CW = new TGraph(nCW, &TCW[0], &kCW[0]);
  g_kvT_CW->SetLineColor(kRed);
  g_kvT_CW->Draw("same");

  TF1* fit = new TF1("fit", "[0]/(x-[1])", 120., 150.);
  g_kvT_CW->Fit("fit");

  return 0;
}
