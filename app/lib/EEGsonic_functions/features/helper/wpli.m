function [corrected_wpli] = wpli(eeg_data,eeg_info,parameters)
%WPLI Summary of this function goes here
%   Detailed explanation goes here

%% Seting up variables
%% NOTE: Do we need the p_value? Seems like no from the information in the documentation
    number_surrogates = parameters.number_surrogates;
    number_channels = size(eeg_data,1);
   
    surrogates_wpli = zeros(number_surrogates,number_channels,number_channels);
    eeg_data = eeg_data'; % TODO CHECK IF THIS IS LEGIT
    %% Calculate wPLI
    uncorrected_wpli = w_PhaseLagIndex(eeg_data); % uncorrected
    for index = 1:number_surrogates
        disp(index);
        surrogates_wpli(index,:,:) = w_PhaseLagIndex_surrogate(eeg_data);
    end
    
    %% Correct the wPLI (either by substracting or doing a p test)
    uncorrected_wpli(isnan(uncorrected_wpli)) = 0; %Have to do this otherwise NaN break the code
    corrected_wpli = get_corrected_wpli(uncorrected_wpli,surrogates_wpli,parameters);
end

function [corrected_wpli] = get_corrected_wpli(uncorrected_wpli,surrogates_wpli,parameters)
    is_surrogates = parameters.is_surrogates;
    if(is_surrogates)
            p_value = parameters.p_value;
            %Here we compare the calculated dPLI versus the surrogate
            %and test for significance
            corrected_wpli = zeros(size(uncorrected_wpli));
            for m = 1:length(uncorrected_wpli)
                for n = 1:length(uncorrected_wpli)
                    test = surrogates_wpli(:,m,n);
                    p = signrank(test, uncorrected_wpli(m,n));       
                    if p < p_value
                        if uncorrected_wpli(m,n) - median(test) > 0 %Special case to make sure no PLI is below 0
                            corrected_wpli(m,n) = uncorrected_wpli(m,n) - median(test);
                        end
                    end          
                end
            end
    else
        corrected_wpli = uncorrected_wpli - squeeze(mean(surrogates_wpli,1));
        corrected_wpli(corrected_wpli<0) = 0;
    end

end
