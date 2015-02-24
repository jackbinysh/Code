% clear;
% x = importdata('Size40Temp2.200000_fixed.txt');
% figure(1)
% plot(abs(x));
% hold on
% x = importdata('Size40Temp2.200000_random.txt');
% plot(abs(x));
% 
% 
% x = importdata('Size40Temp2.300000_fixed.txt');
% figure(2)
% plot(abs(x));
% hold on
% x = importdata('Size40Temp2.300000_random.txt');
% plot(abs(x));

x = importdata('Size40Temp2.400000_fixed.txt');
plot(abs(x(:,2)));
hold on
x = importdata('Size40Temp2.400000_random.txt');
plot(abs(x(:,2)));