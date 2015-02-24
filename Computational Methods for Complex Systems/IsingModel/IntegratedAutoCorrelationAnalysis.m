clear;
% A script to analyse the data from the ising model, 
% in order to get the integrated autocorrelation times
Size = 20;
fileID = fopen(strcat('Size',int2str(Size),'.txt'));
N = 10^6;
TauArray = [];
formatSpec = '%f %f %f';
while ~feof(fileID)
    data = textscan(fileID, formatSpec,N,'Delimiter','\t');
    % We now have our block of data for a single temperature.
    % compute the autocorrelation for the magnetisation
    T = data{1}(1);
    m = data{2};
    e = data{3};
    % TAKING THE ABS OF m HERE
    m = abs(m);
    Tau = IntegratedAutoCorrelation(m);
    TauArray = cat(1,TauArray,[T,Tau]);
    plot(T,Tau,'x');  
    hold on
end
fclose(fileID);