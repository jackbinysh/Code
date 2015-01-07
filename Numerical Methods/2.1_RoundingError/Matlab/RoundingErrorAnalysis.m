
% filepaths
filepath = 'C:\Users\Jack Binysh\Google Drive\Warwick\Numerical Methods\Homework 1\2.1_loss_of_significance\';
Floatfilepath = strcat(filepath,'FloatResults.txt');
Doublefilepath = strcat(filepath,'DoubleResults.txt');

% data import
FloatData = importdata(char(Floatfilepath));
DoubleData = importdata(char(Doublefilepath));

% relative errors
Delta = abs(FloatData - DoubleData)./DoubleData

%plots

Epsiloni = ((2/3).^(1:40))'

figure(1);
hold on
plot(Epsiloni,Delta(:,1), 'o');
plot(Epsiloni,Delta(:,2), 'o');
hold off

figure(2);
hold on
plot(Epsiloni,Delta(:,3), 'o');
plot(Epsiloni,Delta(:,4), 'o');
hold off



 