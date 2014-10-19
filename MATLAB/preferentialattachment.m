%
% INITIALISATION
%

N = 1000; % total number of nodes
m0 = 2; % number of nodes to begin with
k0 = 0; % an initial offset in the probabilities
totalcounts = zeros(N-1,1)';
NumRealisations = 100;
sumgrads = 0;
alllambda = [];


for k0 = [0]
    for realisations = 1:NumRealisations

        e = []; % initiailising the empty edge list
        A = zeros(N); % intiailisng the adjacncy matrix which will define the graph

        % initialisng the list to be sampled from 
        for i = 1:m0
            % each node is connted to m0-1 other nodes at the begining, ie they all have degree ki=m0 -1 to which we
            % add k0, the offset.
            e = horzcat(e,repmat(i,m0+k0-1,1)');
        end

        % initialisng the adjacency matrix
        A(1:m0,1:m0) =1;
        A = triu(A) - diag(diag(A));


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
        % completing the matrix
        A = A + A';
        
        % after each realisation, compute the degree distribution and plot
        % it
        d = sum(A'); % the degree of each node, found from the row sums
        countsthisrealization = hist(d, unique(d)); % creating the distribution (crappily)
         
        % update the total number of counts.
       

        p = polyfit(unique(d),countsthisrealization,1);
        sumgrads = sumgrads + p(1);
        totalcounts(int64(unique(d))) = totalcounts(int64(unique(d))) + countsthisrealization;
        %plotting
        %loglog(unique(d),countsthisrealization)
        hold all
        
        % computing the graph laplacian
        Q = A - diag(sum(A'));
        lambda = eig(Q);
        alllambda = vertcat(alllambda,lambda);
      
    end
    
    averagecounts = totalcounts/NumRealisations;
    averagegrad = sumgrads/NumRealisations
    
    
end

 plot(ksdensity(alllambda));
