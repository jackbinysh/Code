%
% INITIALISATION
%

N = 5; % total number of nodes
m0 = 2 % number of nodes to begin with
k0 = 2; % an initial offset in the probabilities

e = []; % initiailising the empty edge list
A = zeros(N); % intiailisng the adjacncy matrix which will define the graph

% initialisng the list to be sampled from 
for i = 1:m0
    % each node is connted to m0-1 other nodes at the begining, ie they all have degree ki=m0 -1 to which we
    % add k0, the offset.
    e = horzcat(e,repmat(i,m0+k0-1,1)');
end

% initialisng the adjacency matrix
A(1:m0,1:m0) =1
A = triu(A) - diag(diag(A))


% okay we are all set up, now we can begin adding nodes

for i=m0+1:N % adding node m0+1 up to node N
    % choosing our two nodes
    x = e(randi(length(e)));
    y = e(randi(length(e)));
    % if we choose the same node twice, keep rechoosing until we don't
    while x == y 
        y = e(randi(length(e)));
    end
    
    % update the adjacency matrix, we know i is greater than x or y
    % so these are going in the upper triangle
    A(x,i) = 1;
    A(y,i) =1 ;
    
    % add in 1 entry for x and y each, since their degrees have just
    % increase by 1
    e(end+1) = x;
    e(end+1) = y;
    % add in 2 i's, since it has degree two, and k0 i's for free 
    %e(length+3:length+2+m0+k0) = i;
    e(end+1:(end+1) + k0 + 2) = i;
end

A = A + A'

d= vertcat(d, sum(A)');


