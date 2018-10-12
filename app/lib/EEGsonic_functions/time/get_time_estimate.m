function [time] = get_time_estimate(type,information,parameters)
%GET_TIME_ESTIMATE return an estimate of the time it will take to run this
%analysis technique with the specific set of parameters
    %Input:
    %   type:
    %   information: static data of the app
    %   parameters: inputed data by the user
    %Output:
    %   time: time it took to run the analysis and to generate the outputs
    %         in seconds

   
    %% Calling the right timer function 
    if(strcmp(type,"spr"))
        time = time_spectral_power_ratio(information,parameters);
    elseif(strcmp(type,"td"))
        time = time_topographic_distribution(information,parameters);
    elseif(strcmp(type,"pac"))
        time = time_phase_amplitude_coupling(information,parameters);
    elseif(strcmp(type,"fp_wpli"))
        time = time_fp_wpli(information,parameters);
    elseif(strcmp(type,"fp_dpli"))
        time = time_fp_dpli(information,parameters);
    elseif(strcmp(type,"hl"))
        time = time_hub_location(information,parameters);
    elseif(strcmp(type,"pe"))
        time = time_permutation_entropy(information,parmeters);
    end
end

