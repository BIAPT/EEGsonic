function warm_up(information,parameters)
%WARM_UP This function will call all the analysis techniques one by one to
%prevent them from being to slow during the first round of the pipeline
%   Input: 
    %   parameters: inputed data by the user
    
    %% Check which analysis techniques were choosen and run these
    %  We call the timing functions without collecting the results
    % Spectral Power Ratio
    if(parameters.spr.is_selected)
        time_spectral_power_ratio(information,parameters);
    end
    
    % Topographic Distribution
    if(parameters.td.is_selected)  
        time_topographic_distribution(information,parameters);
    end
    

    % Phase Amplitude Coupling
    if(parameters.pac.is_selected)   
        time_phase_amplitude_coupling(information,parameters);
    end
    
    % Fronto-parietal weighted Phase Lag Index
    if(parameters.fp_wpli.is_selected)    
        time_fp_wpli(information,parameters);
    end
    
    
    % Fronto-Parietal directed Phase Lag Index
    if(parameters.fp_dpli.is_selected)
        time_fp_dpli(information,parameters);
    end
    
    % Hub Location
    if(parameters.hl.is_selected)  
        time_hub_location(information,parameters);
    end
    
    % Permutation Entropy
    if(parameters.pe.is_selected)    
        time_permutation_entropy(information,parameters);
    end
end

