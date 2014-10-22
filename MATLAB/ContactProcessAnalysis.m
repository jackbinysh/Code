% script for analysing data from contact process
n=['128']
d=[];
NumSteps = 200;
Legend = cell(1);
 for lambda = cellfun(@num2str, num2cell((161:169)/10) , 'UniformOutput', false) %{'16.1','16.2','16.3','16.4','16.5','16.6','16.7','16.8','16.9'}
        fileextension = strcat('C:\Users\Jack Binysh\Google Drive\Warwick\Networks and Random Processes\Homework2\1.3\Finer data\contact_n',n,'_lambda',lambda,'.dat');
        A = importdata(char(fileextension));
        B(1:NumSteps,1) = A(1:NumSteps,2);
        for i = 0:9
            B(1:NumSteps, i+2) = A(((i*NumSteps + 1) : ((i+1)*NumSteps)), 1);
        end
% constuct a matrix of times and average values
c(:,1) = B(:,1);
c(:,2) = transpose(mean(transpose(B(:,2:end))));

% plot
loglog(c(:,1),c(:,2))
hold all
ax = get(gca);
set(gca,'ColorOrder', hsv(8))
Legend(end+1) = strcat('lambda = ', lambda)
 end
 % fiddling with the graph to make it look nice
 %legend
Legend = Legend(2:end); 
legend(Legend)
%axes labels and title
title(strcat('L =',n));
xlabel('Time')
ylabel('N')

clear

        
            
    

