% some code to generate Erdos Renyi random graphs

for N = [100]
    A = zeros(N);
    
    for z = (1:30)/10
        
        sumlargest = 0;
        sumsecondlargest = 0;
        averagelargest = [];
        averagesecondlargest = [];
        sumclustercoeff=0;
        
        for realisations = 1:200
            p = z/N; % the probability of an egde being chosen.
            % using the MIT graph theory toolbox
            A = random_graph(N,p);
            listofcomponents = find_conn_comp(A);
            
            largest = 0;
            % find the largest components
%             for i=1:length(listofcomponents)
%                 if length(listofcomponents{i})> largest
%                     largestindex = i;
%                     largest = length(listofcomponents{i});  
%                 end
%             end
            
            secondlargest = 0;
            % find the second largest
%             for i=1:length(listofcomponents)
%                 if (i ~= largestindex) &(length(listofcomponents{i})> secondlargest)
%                     secondlargestindex = i;
%                     secondlargest = length(listofcomponents{i});
%                 end
%             end
            
%             sumlargest = sumlargest + largest;
%             sumsecondlargest = sumsecondlargest + secondlargest
        [C1,C2,C]=clust_coeff(A);
        sumclustercoeff=sumclustercoeff+C2;
        end
        averageclustercoeff=sumclustercoeff/realisations;
%         averagelargest(10*z) = sumlargest/realisations;
%         averagesecondlargest(10*z) = sumsecondlargest/realisations;
        
        hold all
%         figure(1);
%         plot(z,averagelargest(10*z),'x');
%         figure(2);
%         plot(z,averagesecondlargest(10*z), 'o');
        figure(3)
        plot(z,averageclustercoeff,'o')
    end
end