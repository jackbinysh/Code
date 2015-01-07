%% First Part analysis
clear
imax = 10;
for i = (1:imax)
    
    NumPoints = 2^i;
    TrapeziumResults(1,i) = NumPoints; %the number of points being used
    TrapeziumResults(2,i) = 1/NumPoints; % the step size
    TrapeziumResults(3,i) = Integrate(0,1,NumPoints,Method.Trapezium);
    
    SimpsonsResults(1,i) = NumPoints; %the number of points being used
    SimpsonsResults(2,i) = 1/NumPoints; % the step size
    SimpsonsResults(3,i) = Integrate(0,1,NumPoints,Method.Simpsons);

end

% plotting data and lines of best fit

%Trapezium
p1 = polyfit(log(TrapeziumResults(2,:)),log(TrapeziumResults(3,:) - 2.4),1);
syms x;
f1 = p1(1)*x + p1(2);

figure(1)
hold on
ezplot(f1);
plot(log(TrapeziumResults(2,:)),log(TrapeziumResults(3,:) - 2.4),'x');
hold off

%Simpsons
p2 = polyfit(log(SimpsonsResults(2,:)),log(SimpsonsResults(3,:) - 2.4),1);
syms y;
f2 = p2(1)*y + p2(2);

figure(2)
hold on
ezplot(f2);
plot(log(SimpsonsResults(2,:)),log(SimpsonsResults(3,:) - 2.4),'x');
hold off


%% Second Part analysis
% REMEMBER TO CHANGE TO DEFINITIION OF INTEGRATE BETWEEN THESE SECTIONS
clear
imax = 8;
for i = (1:imax)
    
    NumPoints = 2^i;
    TrapeziumResults(1,i) = NumPoints; %the number of points being used
    TrapeziumResults(2,i) = ((2*pi)^(2/3))/NumPoints; % the step size
    TrapeziumResults(3,i) = Integrate(0,(2*pi)^(2/3),NumPoints,Method.Trapezium);
    TrapeziumResults(4,i) = Integrate(0,(2*pi)^(2/3),2*(NumPoints),Method.Trapezium);
    
    SimpsonsResults(1,i) = NumPoints; %the number of points being used
    SimpsonsResults(2,i) = ((2*pi)^(2/3))/(NumPoints); % the step size
    SimpsonsResults(3,i) = Integrate(0,(2*pi)^(2/3),NumPoints,Method.Simpsons);
    SimpsonsResults(4,i) = Integrate(0,(2*pi)^(2/3),2*(NumPoints),Method.Simpsons);
end

% plotting data and lines of best fit

%Trapezium
p1 = polyfit(log(TrapeziumResults(2,:)),log(TrapeziumResults(3,:) - TrapeziumResults(4,:)),1);
syms x;
f1 = p1(1)*x + p1(2);

figure(1)
hold on
ezplot(f1);
plot(log(TrapeziumResults(2,:)),log(TrapeziumResults(3,:) - TrapeziumResults(4,:)),'x');
hold off

%Simpsons
p2 = polyfit(log(SimpsonsResults(2,:)),log(SimpsonsResults(3,:) - SimpsonsResults(4,:)),1);
syms y;
f2 = p2(1)*y + p2(2);

%figure(2)
hold on
%ezplot(f2);
plot(log(SimpsonsResults(2,:)),log(SimpsonsResults(3,:) - SimpsonsResults(4,:)),'x');
hold off

