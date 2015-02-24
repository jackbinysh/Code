clear;
% A script to analyse the data from the ising mode
Size = 40;
N = Size^2;
fileID = fopen(strcat('Size',int2str(Size),'.txt'));
NumRuns = 10^6;
formatSpec = '%f %f %f';
while ~feof(fileID)
    data = textscan(fileID, formatSpec,NumRuns,'Delimiter','\t');
    % We now have our block of data for a single temperature.
    % compute the autocorrelation for the magnetisation
    T = data{1}(1);
    m = data{2};
    e = data{3};
    % TAKING THE ABS OF m HERE
    m = abs(m);
    Tau = IntegratedAutoCorrelation(m);
    TauArray = cat(1,TauArray,[T,Tau]);
    % to get average of m and e, we take independent samples, spaced at
    % 2tau, and compute their averages.
    m = m(1:2*ceil(Tau):end);
    avgm = mean(m);
    sigmam = sqrt((1/(length(m)-1))*var(m));
    e = e(1:2*ceil(Tau):end);
    avge = mean(e);
    sigmae = sqrt((1/(length(e)-1))*var(e));
    % compute chi 
    [x,sigmaxsq] = jackknife(m);
    x = x*N/T;
    sigmax = (N/T)*sqrt(sigmaxsq);
    % compute c
    [c,sigmacsq] = jackknife(e);
    c = c*(N/(T^2));
    sigmac = (N/(T^2))* sqrt(sigmacsq);

    %REMEMBER ITS 2SIGMA
    figure(1);
    errorbar(T,avge,2*sigmae,'x');
    hold on
    figure(2);
    errorbar(T,abs(avgm),2*sigmam,'x');
    hold on
    figure(3);
    errorbar(T,c,2*sigmac,'x');  
    hold on
    figure(4);
    errorbar(T,x,2*sigmax,'x');  
    hold on
    figure(5);
    plot(T,Tau,'x');  
    hold on
end
fclose(fileID);