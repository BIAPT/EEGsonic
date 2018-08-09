function unconscious_network_properties

%   This function is based on find_network_properties3.m
%   It finds the network properties of the unconscious period in the MDF
%   study

samp_freq = 500;
network_thresh = 0.3;
win = 10;   % number of seconds of EEG window

for bp = 4
    switch bp
        case 1
            bpname = ' all';
            lp = 1;
            hp = 25;
        case 2
            bpname = ' delta';
            lp = 1;
            hp = 4;
        case 3
            bpname = ' theta';
            lp = 4;
            hp = 8;
        case 4
            bpname = ' alpha';
            lp = 8;
            hp = 13;
        case 5
            bpname = ' beta';
            lp = 13;
            hp = 25;
    end
    
    EEG = load('D:\Documents\McDonnell Foundation\MDFA03\MDFA03 scouts part 1.txt');
    new_EEG = scout_reorg(EEG);
    total_length = length(new_EEG);
    
    filt_data = bpfilter(lp,hp,samp_freq,new_EEG);
    
    % Initialize window-dependent variables
    b_charpath = zeros(1,floor(total_length/(win*samp_freq)));
    b_clustering = zeros(1,floor(total_length/(win*samp_freq)));
    b_geff = zeros(1,floor(total_length/(win*samp_freq)));
    bsw = zeros(1,floor(total_length/(win*samp_freq)));
    Q = zeros(1,floor(total_length/(win*samp_freq)));
            
    for i = 1:(floor((length(filt_data))/(win*samp_freq)))

        i
        EEG_seg = filt_data(:,(i-1)*win*samp_freq + 1:i*win*samp_freq);      
        EEG_seg = EEG_seg';

        % Generate PLI network of significant connections
        
        PLI = w_PhaseLagIndex(EEG_seg);
        [corr_PLI,conn_ratio] = test_PLI_stats(PLI,EEG_seg); % Only keep connections that are not random
        total_conn(i) = conn_ratio;
        figure; imagesc(corr_PLI); caxis([0 0.8]); colormap jet; colorbar;
        filename = strcat('D:\Documents\McDonnell Foundation\MDFA03\PLI ',num2str(i), '.jpg');
        saveas(gcf, filename);
        
        %hgsave(strcat('PLI ',num2str(i)));
        
        % Now create dPLI network based on the PLI connections that are
        % significant
        
        corr_dPLI = create_sig_dPLI(corr_PLI,EEG_seg);
        figure; imagesc(corr_dPLI); caxis([0.1 0.9]); colormap jet; colorbar;
        filename = strcat('D:\Documents\McDonnell Foundation\MDFA03\dPLI ',num2str(i), '.jpg');
        saveas(gcf, filename);
        
        %hgsave(strcat('dPLI ',num2str(i)));
       
        % Now create a binary correlation matrix of top 30% of PLI
        % connections
        
        A = sort(corr_PLI);
        B = sort(A(:));
        C = B(1:length(B)-length(corr_PLI));
        
        index = floor(length(C)*(1-network_thresh));
        thresh = C(index);
        
        for m = 1:length(corr_PLI)
            for n = 1:length(corr_PLI)
                if (m == n)
                    b_mat(m,n) = 0;
                else
                    if (corr_PLI(m,n) > thresh)
                        b_mat(m,n) = 1;
                    else
                        b_mat(m,n) = 0;
                    end
                end
            end
        end
               
        % Find average path length

        D = distance_bin(b_mat);
        [b_lambda,geff,~,~,~] = charpath(D);   % binary charpath
        [W0,R] = null_model_und_sign(b_mat,10,0.1);    % generate random matrix

          % Find clustering coefficient

        C = clustering_coef_bu(b_mat);  

        % Find properties for random network

        [rlambda,rgeff,~,~,~] = charpath(distance_bin(W0));   % charpath for random network
        rC = clustering_coef_bu(W0); % cc for random network

        b_clustering(i) = nanmean(C)/nanmean(rC); % binary clustering coefficient
        b_charpath(i) = b_lambda/rlambda;  % charpath
        b_geff(i) = geff/rgeff; % global efficiency

        bsw(i) = b_clustering/b_charpath; % binary smallworldness

        [M,modular] = community_louvain(b_mat,1); % community, modularity
        Q(i) = modular;

    end
            
    dlmwrite(['D:\Documents\McDonnell Foundation\MDFA03\MDFA03 scouts ' bpname '_clustering.txt'], b_clustering);
    dlmwrite(['D:\Documents\McDonnell Foundation\MDFA03\MDFA03 scouts ' bpname '_lambda.txt'], b_charpath);
    dlmwrite(['D:\Documents\McDonnell Foundation\MDFA03\MDFA03 scouts ' bpname '_geff.txt'], b_geff);
    dlmwrite(['D:\Documents\McDonnell Foundation\MDFA03\MDFA03 scouts ' bpname '_bsw.txt'], bsw);
    dlmwrite(['D:\Documents\McDonnell Foundation\MDFA03\MDFA03 scouts ' bpname '_Q.txt'], Q);

end


avg_conn = mean(total_conn)