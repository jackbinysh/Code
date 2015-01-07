clear;

%% Part 2
syms z;
f = z^3 - 2*z + 2;
ezplot(f);
% from the plot we can see the real root lies around -1.7. if we begin from here
RealRoot = NewtonRaphson(-1.7);
%% part 3
% define the area we will create the grid over, and the number of
% subdivisions we want
clear;clc;
ReZBounds = [-2,2];
ImZBounds = [-2,2];
NumPoints = 1000;
ReZCoords = linspace(ReZBounds(1),ReZBounds(2), NumPoints);
ImZCoords = linspace(ImZBounds(1),ImZBounds(2), NumPoints) *1i;
% create a nice grid over the complex plane
for k = 1:length(ImZCoords)
    for l = 1:length(ReZCoords)
        Grid(l,k) = ReZCoords(k) + ImZCoords( length(ImZCoords)+1- l );
    end
end
% apply newton Raphson to every point in the grid
Result = arrayfun(@NewtonRaphson,Grid);

% run through the matrix, coloring it
ColoredResult = Color(Result);

colormap(prism);
image(ColoredResult);
labels = {'0.8846 - 0.5897i','0.8846 + 0.5897i','-1.7693','No Convergence'};


