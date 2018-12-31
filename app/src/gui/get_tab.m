function tab = get_tab(app,tab_name)
% Get the tab from the main application
    if(strcmp(tab_name,"Home"))
        tab = app.HomeTab;
    elseif(strcmp(tab_name,"General"))
        tab = app.GeneralTab;

    elseif(strcmp(tab_name,"OSC Receivers"))
        tab = app.OSCReceiversTab;

    elseif(strcmp(tab_name,"Spectral Power Ratio"))
        tab = app.SpectralPowerRatioTab;

    elseif(strcmp(tab_name,"Topographic Distribution"))
        tab = app.TopographicDistributionTab;

    elseif(strcmp(tab_name,"Phase Amplitude Coupling"))
        tab = app.PhaseAmplitudeCouplingTab;

    elseif(strcmp(tab_name,"Frontoparietal wPLI"))
        tab = app.FrontoparietalwPLITab;

    elseif(strcmp(tab_name,"Frontoparietal dPLI"))
        tab = app.FrontoparietaldPLITab;

    elseif(strcmp(tab_name,"Hub Location"))
        tab = app.HubLocationTab;

    elseif(strcmp(tab_name,"Permutation Entropy"))
        tab = app.PermutationEntropyTab;

    end
end