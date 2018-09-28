function [corrected_dpli] = dpli(eeg_data,eeg_info,parameters)
%DPLI Summary of this function goes here
%   Detailed explanation goes here

%% Seting up variables
%% NOTE: Do we need the p_value? Seems like no from the information in the documentation
    number_surrogates = parameters.number_surrogates;
    number_channels = size(eeg_data,1);
   
    surrogates_dpli = zeros(number_surrogates,number_channels,number_channels);
    eeg_data = eeg_data';
    %% Calculate wPLI
    uncorrected_dpli = d_PhaseLagIndex(eeg_data); % uncorrected
    for index = 1:number_surrogates
        disp(index);
        surrogates_dpli(index,:,:) = d_PhaseLagIndex_surrogate(eeg_data);
    end
    type = "substraction"; %TODO need to put that into the GUI
    parameters.correction_type = type;
    uncorrected_dpli(isnan(uncorrected_dpli)) = 0.5; %Have to do this otherwise NaN break the code
    corrected_dpli = get_corrected_dpli(uncorrected_dpli,surrogates_dpli,parameters);

end

function [corrected_dpli] = get_corrected_dpli(uncorrected_dpli,surrogates_dpli,parameters)
    correction_type = parameters.correction_type;
    if(strcmp(correction_type,"substraction"))
        corrected_dpli = uncorrected_dpli - squeeze(mean(surrogates_dpli,1));
        corrected_dpli(corrected_dpli<0) = 0;
    elseif(strcmp(correction_type,"p value"))
        p_value = parameters.p_value;
        corrected_dpli = zeros(size(uncorrected_dpli));
        %Here we compare the calculated dPLI versus the surrogate
            %and test for significance
            
            %if the result is significant then 4 conditions are possible
            %1.dPLI value is greater than 0.5 and the median of the surrogate
            %is greater than 0.5
            %2.dPLI value is smaller than 0.5 and the median of the surrogate
            %is smaller than 0.5
            %3.dPLI is greater than 0.5 and median of surrogate is smaller
            %than 0.5
            %4.dPLI is smaller than 0.5 and median of surrogate is greater
            %than 0.5
            for m = 1:length(uncorrected_dpli)
                for n = 1:length(uncorrected_dpli)
                    test = surrogates_dpli(:,m,n);
                    p = signrank(test, uncorrected_dpli(m,n)); 
                    disp(p);
                    if p < p_value % 4 Conditions 
                        if uncorrected_dpli(m,n) > 0.5 && median(test) > 0.5
                            gap = uncorrected_dpli(m,n) - median(test);
                                if(gap < 0)
                                    corrected_dpli(m,n) = 0.5; 
                                else
                                    corrected_dpli(m,n) = gap + 0.5; %Gap is positive here
                                end  
                        elseif uncorrected_dpli(m,n) < 0.5 && median(test) < 0.5 % CASE 2
                            gap = uncorrected_dpli(m,n) - median(test);
                            if(gap > 0)
                                corrected_dpli(m,n) = 0.5; 
                            else
                                corrected_dpli(m,n) = gap + 0.5; %Gap is negative here
                            end
                        elseif uncorrected_dpli(m,n) > 0.5 && median(test) < 0.5 %CASE 3
                            extra = 0.5 - median(test);
                            corrected_dpli(m,n) = uncorrected_dpli(m,n) + extra;
                        elseif uncorrected_dpli(m,n) < 0.5 && median(test) > 0.5 %CASE 4
                            extra = median(test) - 0.5;
                            corrected_dpli(m,n) = uncorrected_dpli(m,n) - extra;
                        end
                    else
                        corrected_dpli(m,n) = 0.5;
                    end
                end
            end 
    end
end
