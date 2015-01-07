clear;clc;

InitialBracket = [0,1,2];

Brackets = GoldenSectionSearch(InitialBracket);

%plotting the bracket sizes againt number of iterations
dim = size(Brackets);
length = dim(1);
BracketSizes = Brackets(:,3) - Brackets(:,1);
hold on
plot(1:length, (BracketSizes),'x');
p1 = polyfit((1:length)',log(BracketSizes),1);

% plotting the theoretical convergence
w = (5^(1/2) - 1)/2;
plot( 1:length,(InitialBracket(3) - InitialBracket(1))*(w.^(1:length)) );
hold off;



