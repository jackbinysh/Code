N = 5; % total number of nodes
m0 = 2 % number of nodes to begin with
m = 2; % number of nodes each newly added node randomly connects to
k0 = 2; % an initial offset in the probabilities

e = zeros(1000000,1); % edge list
length = 0;

% initialisng the list to be sampled from 
for i = 1:m0
    % each node is connted to m0-1 other nodes at the begining, ie they all have degree ki=m0 -1 to which we
    % add k0, the offset.
    for j=1:(k0+m0-1)
        e(j+length) = i;
    end
    length = length + (k0+m0-1);
end

A = zeros(N);

A(1,2) = 1;
A(1,3) = 2;
A(2,3) = 3;

for i=m0+1:N
    x = e(randi(length));
    y = e(randi(length));
    while x == y 
        y = e(randi(length));
    end
    
    e(length+1) = x;
    e(length+2) = y;
    e(length+3:length+2+m0+k0) = i;
    
    length = length +2 +k0+m;
    
end

A = A + A'

d= vertcat(d, sum(A)');


