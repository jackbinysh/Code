% A script to analyse the data from the ising mode
clear all;
for Size = [10,20,40]
    % initial paramters
    %Size = 20;
    N = Size^2;
    % initialize arrays
    TauArray = [] ;
    mArray = [];
    absmArray = [];
    eArray = [];
    chiArray = [];
    cArray = [];

    list = 10:40;
    for i = list
        fileID = strcat('Size',int2str(Size),'Temp',int2str(i),'.txt');
        data = importdata(fileID);
        Tau = data(1,1);
        T = data(1,2);
        data(1,:) = [];

        % We now have our block of data for a single temperature.
        % compute the autocorrelation for the magnetisation
        m = data(:,1);
        e = data(:,2);
        absm = abs(m);

        % averages of m and e, and their deviations
        avgm = mean(m);
        avgabsm = mean(absm);
        sigmam = sqrt((1/(length(m)-1))*var(absm));
        avge = mean(e);
        sigmae = sqrt((1/(length(e)-1))*var(e));

        % compute chi 
        [x,sigmaxsq] = jackknife(absm);
        x = x*N/T;
        sigmax = (N/T)*sqrt(sigmaxsq);
        % compute c
        [c,sigmacsq] = jackknife(e);
        c = c*(N/(T^2));
        sigmac = (N/(T^2))* sqrt(sigmacsq);

        % now add these into overall arrays storing everything

        TauArray = cat(1,TauArray,[T,Tau]);
        mArray = cat(1,mArray,[T,avgm]);
        absmArray = cat(1,absmArray,[T,avgabsm,sigmam]);
        eArray = cat(1,eArray,[T,avge,sigmae]);
        chiArray = cat(1,chiArray,[T,x,sigmax]);
        cArray = cat(1,cArray,[T,c,sigmac]);
    end

        %REMEMBER ITS 2SIGMA
        figure(1);    
        errorbar(absmArray(:,1),absmArray(:,2),2*absmArray(:,3),'x')
        hold on
        figure(2);
        errorbar(eArray(:,1),eArray(:,2),2*eArray(:,3),'x')
        hold on
        figure(3);
        errorbar(chiArray(:,1),chiArray(:,2),2*chiArray(:,3),'x')  
        hold on
        figure(4);
        errorbar(cArray(:,1),cArray(:,2),2*cArray(:,3),'x')  
        hold on
        figure(5);
        plot(TauArray(:,1),TauArray(:,2),'x')  
        hold on
        figure(6);
        plot(mArray(:,1),mArray(:,2),'x')  
        hold on
end

% some output formatting
figure(1);
legend('Size 10','Size 20','Size 40');   
title('Absolute magnetisation per spin')
xlabel('Temp')
ylabel('abs m')
figure(2);
legend('Size 10','Size 20','Size 40'); 
title('Energy per spin')
xlabel('Temp')
ylabel('e')
figure(3);
legend('Size 10','Size 20','Size 40'); 
title('Susceptiblity per spin')
xlabel('Temp')
ylabel('x')
figure(4);
legend('Size 10','Size 20','Size 40'); 
title('Specific heat per spin')
xlabel('Temp')
ylabel('c')
figure(5);
legend('Size 10','Size 20','Size 40'); 
title('Integrated Autocorrelation times')
xlabel('Temp')
ylabel('Tau')
figure(6);
legend('Size 10','Size 20','Size 40'); 
title('Magnetisation per spin')
xlabel('Temp')
ylabel('m')
