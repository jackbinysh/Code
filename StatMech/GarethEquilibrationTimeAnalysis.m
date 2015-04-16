clear;
Temp = 40;

filepath = strcat(pwd,'\EquilibrationTimeData\FixedSpins\');
fileID = strcat(filepath,'Size80Temp',int2str(Temp),'Equilibration.txt');
FixedSpinData = importdata(fileID);
T = FixedSpinData(1,1);
FixedSpinData = abs(FixedSpinData(2:end,1));

filepath = strcat(pwd,'\EquilibrationTimeData\RandomSpins\');
fileID = strcat(filepath,'Size80Temp',int2str(Temp),'Equilibration.txt');
RandomSpinData = importdata(fileID);
RandomSpinData = abs(RandomSpinData(2:end,1));

plot(FixedSpinData);
hold on
plot(RandomSpinData);

legend('all spins up','random spins'); 
title('Plot of m vs Time for two intial configuration, T = 2')
xlabel('Time')
ylabel('m')
