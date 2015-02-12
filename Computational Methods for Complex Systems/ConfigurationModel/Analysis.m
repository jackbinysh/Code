data  = importdata('Size10NumRuns1000000');
hold on
plot(data(:,1),data(:,2))
data  = importdata('Size100NumRuns1000000');
plot(data(:,1),data(:,2))
data  = importdata('Size1000NumRuns1000000');
plot(data(:,1),data(:,2))
data  = importdata('Size10000NumRuns5000');
plot(data(:,1),data(:,2))
hold 1off