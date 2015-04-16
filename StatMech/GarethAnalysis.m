% A script to analyse the data from the ising model
% for co904
clear all;
for Size = [20,40,80]
    % initial paramters
    N = Size^2;
    % initialize arrays
    mArray = [];
    absmArray = [];
    eArray = [];
    chiArray = [];
    cArray = [];
    BCArray = [];

    list = 40:60;
    for i = list
        fileID = strcat('Size',int2str(Size),'Temp',int2str(i),'.txt');
        data = importdata(fileID,'\t',1);
        T = data.textdata;
        T = str2num(T{1});
        data = data.data;

        % We now have our block of data for a single temperature.
        m = data(:,1);
        e = data(:,2);
        absm = abs(m);

        % averages of m and e, and their deviations
        avgm = mean(m);
        avgabsm = mean(absm);
        avge = mean(e);

        % compute chi 
        x = var(absm);
        x = x*N/T;
        % compute c
        c= var(e);
        c = c*(N/(T^2));
        
        %compute the Binder Cumulant
        BC = 1 -  ((mean(m.^4))/ (3*mean(m.^2)^2));
        
        % now add these into overall arrays storing everything

        mArray = cat(1,mArray,[T,avgm]);
        absmArray = cat(1,absmArray,[T,avgabsm]);
        eArray = cat(1,eArray,[T,avge]);
        chiArray = cat(1,chiArray,[T,x]);
        cArray = cat(1,cArray,[T,c]);
        BCArray = cat(1,BCArray,[T,BC]);
    end
    
        figure(1);    
        plot(absmArray(:,1),absmArray(:,2),'-+')
        hold on
        figure(2);
        plot(eArray(:,1),eArray(:,2),'-+')
        hold on
        figure(3);
        plot(chiArray(:,1),chiArray(:,2),'-+')  
        hold on
        figure(4);
        plot(cArray(:,1),cArray(:,2),'-+')  
        hold on
        figure(5);
        plot(mArray(:,1),mArray(:,2),'-+')  
        hold on
        figure(6);
        plot(BCArray(:,1),BCArray(:,2),'-+')  
        hold on
end

% some output formatting
figure(1);
legend('Size 20','Size 40','Size 80');   
title('Absolute magnetisation per spin')
xlabel('Temp')
ylabel('abs m')
figure(2);
legend('Size 20','Size 40','Size 80'); 
title('Energy per spin')
xlabel('Temp')
ylabel('e')
figure(3);
legend('Size 20','Size 40','Size 80'); 
title('Susceptiblity per spin')
xlabel('Temp')
ylabel('x')
figure(4);
legend('Size 20','Size 40','Size 80'); 
title('Specific heat per spin')
xlabel('Temp')
ylabel('c')
figure(5);
legend('Size 20','Size 40','Size 80'); 
title('Magnetisation per spin')
xlabel('Temp')
ylabel('m')
figure(6);
legend('Size 20','Size 40','Size 80'); 
title('Binders Cumulant')
xlabel('Temp')
ylabel('Binders Cumulant')
