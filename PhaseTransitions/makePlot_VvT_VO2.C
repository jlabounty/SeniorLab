int makePlot_VvT_VO2(
		     TString infile = "data/VO2_V_vs_T_111616.txt",
		     TString infile2 = "data/VO2_EnergyGap.txt"
)
{

  TTree *TData = new TTree();
  TData->ReadFile(infile, "T/D:V:null");
  int n = TData->Draw("V:T", "", "goff");

  vector<double> V, T, R, pLOG, TInv;
  for(int i = 0; i<n; i++)
    {
      V.push_back(TData->GetV1()[i]);
      T.push_back(TData->GetV2()[i]);

      // R.push_back(V[i]*(9970000. + 1029) / (1.99 - V[i]));
      R.push_back(V[i]*(997000. + 1029) / (1.99 - V[i]));

      pLOG.push_back(TMath::Log(R[i]));
      TInv.push_back(1 / T[i]);

    }

  TTree *TDataEGap = new TTree();
  TDataEGap->ReadFile(infile2, "TEGap/D:VEGap:nullEGap");
  int nEGap = TDataEGap->Draw("VEGap:TEGap", "", "goff");

  vector<double> VEGap, TEGap, REGap, pLOGEGap, TInvEGap;
  for(int iEGap = 0; iEGap<nEGap; iEGap++)
    {
      VEGap.push_back(TDataEGap->GetV1()[iEGap]);
      TEGap.push_back(TDataEGap->GetV2()[iEGap]);

      // REGap.push_back(VEGap[iEGap]*(9970000. + 1029) / (1.99 - VEGap[iEGap]));
      REGap.push_back(VEGap[iEGap]*(997000. + 1029) / (1.99 - VEGap[iEGap]));

      pLOGEGap.push_back(TMath::Log(REGap[iEGap]));
      TInvEGap.push_back(1 / TEGap[iEGap]);

    }


  TCanvas *c1 = new TCanvas();  
  TGraph *g_VvT = new TGraph(n, &T[0], &V[0]);
  g_VvT->Draw("AP");

  // TCanvas *c2 = new TCanvas();
  // TGraph *g_C1vT = new TGraph(n, &T[0], &C1[0]);
  // g_C1vT->Draw("AP");

  // TCanvas *c3 = new TCanvas();  
  // TGraph *g_C2vT = new TGraph(n, &T[0], &C2[0]);
  // g_C2vT->Draw("AP");

  TCanvas *c3 = new TCanvas();  
  TGraph *g_RvT = new TGraph(n, &T[0], &R[0]);
  c3->SetLogy();
  g_RvT->SetTitle("");
  g_RvT->GetXaxis()->SetTitle("T ( ^{#circ}C)");
  g_RvT->GetYaxis()->SetTitle("R (#Omega)");
  g_RvT->Draw("AP");

  TLine *TcLO = new TLine(66.5, 4*10**3., 66.5, 2*10**6.);
  TcLO->SetLineStyle(2);
  TcLO->SetLineColor(kBlue);
  TcLO->Draw();

  TLine *TcUP = new TLine(82.5, 4*10**3., 82.5, 2*10**6.);
  TcUP->SetLineStyle(2);
  TcUP->SetLineColor(kBlue);
  TcUP->Draw();

  TLine *Tc = new TLine(74.5, 4*10**3., 74.5, 2*10**6.);
  Tc->SetLineStyle(2);
  Tc->SetLineColor(kRed);
  Tc->Draw();

  TLegend *leg = new TLegend(0.2, 0.2, 0.44, 0.43);
  leg->SetNColumns(1);
  leg->AddEntry(g_RvT, "VO_{2} R vs T", "p");
  leg->AddEntry(Tc, "T_{C} = 74.5^{#circ}C", "l");
  leg->AddEntry(TcUP, "T_{C} #pm T*", "l");
  leg->Draw();

  /*=====================*/
  TCanvas *c4 = new TCanvas();
  // c4->SetLogy();
  TGraph *g_RvT2 = new TGraph(n, &TInv[0], &pLOG[0]);
  g_RvT2->SetTitle("");
  g_RvT2->Draw("AP");
  TGraph *g_RvTEGap2 = new TGraph(nEGap, &TInvEGap[0], &pLOGEGap[0]);
  g_RvTEGap2->SetMarkerColor(kRed);
  g_RvTEGap2->Draw("SAME, P");

  g_RvTEGap2->Fit("pol1");


  TLegend *leg2 = new TLegend(0.55, 0.2, 0.8, 0.35);
  leg2->SetNColumns(1);
  leg2->AddEntry(g_RvT, "VO_{2} R vs T", "p");
  leg2->AddEntry(g_RvTEGap2->GetFunction("pol1"), "#splitline{Semiconductor}{Resistivity Law}", "l");
  leg2->AddEntry((TObject*)0 ,"E_{G} = ", "");
  leg2->Draw();
  /*=====================*/

  TCanvas *c5 = new TCanvas();
  c5->SetLogy();
  g_RvT->Draw("AP");
  TGraph *g_RvTEGap = new TGraph(nEGap, &TEGap[0], &REGap[0]);
  g_RvTEGap->SetMarkerColor(kRed);
  g_RvTEGap->Draw("SAME, P");

  // g_RvTEGap->Fit("expo");


  // TLegend *leg2 = new TLegend(0.2, 0.2, 0.45, 0.35);
  // leg2->SetNColumns(1);
  // leg2->AddEntry(g_RvT, "VO_{2} R vs T", "p");
  // leg2->AddEntry(g_RvTEGap->GetFunction("expo"), "#splitline{Semiconductor}{Resistivity Law}", "l");
  // leg2->AddEntry((TObject*)0 ,"E_{G}", "");
  // leg2->Draw();



  // c3->Print("report/plots/VO2_RvT_withTC.png");

  return 0;
}
