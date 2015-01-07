
% filepaths
filepath = 'C:\Users\Jack Binysh\Google Drive\Warwick\Numerical Methods\Homework 1\2.3_Binary_Search\';
filepath = strcat(filepath,'Results_SearchTimes2.txt');


% data import
Data = importdata(char(filepath));

%plots
figure(1);
hold on
plot(Data(:,1),Data(:,2),'o');
hold off
