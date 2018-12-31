function tick_value = is_ticked(app,tag)
% Check if a given analysis technique is ticked 
    switch tag
        case 'spr'
            tick_value = app.SpectralPowerRatioCheckBox.Value;
        case 'td'
            tick_value = app.TopographicDistributionCheckBox.Value;
        case 'pac'
            tick_value = app.PhaseAmplitudeCouplingCheckBox.Value;
        case 'fp_wpli'
            tick_value = app.FrontoparietalwPLICheckBox.Value;
        case 'fp_dpli'
            tick_value = app.FrontoparietaldPLICheckBox.Value;
        case 'hl'
            tick_value = app.HubLocationCheckBox.Value;
        case 'pe'
            tick_value = app.PermutationEntropyCheckBox.Value;
    end            
end