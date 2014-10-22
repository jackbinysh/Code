% some code to generate Erdos Renyi random graphs

for N = [1000]
    A = zeros(N);
    
    for z = (1:30)/10
        
        sumlargest = 0;
        sumsecondlargest = 0;
        averagelargest = [];
        averagesecondlargest = [];
        
        for realisations = 1:30
            p = z/N; % the probability of an egde being chosen.
            % using the MIT graph theory toolbox
            A = random_graph(N,p);
            listofcomponents = find_conn_comp(A);
            
            largest = 0;
            % find the largest components
            for i=1:length(listofcomponents)
                if length(listofcomponents{i})> largest
                    largestindex = i;
                    largest = length(listofcomponents{i});  
                end
            end
            
            secondlargest = 0;
            % find the second largest
            for i=1:length(listofcomponents)
                if (i ~= largestindex) &(length(listofcomponents{i})> secondlargest)
                    secondlargestindex = i;
                    secondlargest = length(listofcomponents{i});
                end
            end
            
            sumlargest = sumlargest + largest;
            sumsecondlargest = sumsecondlargest + secondlargest
                   
        end
        
        averagelargest(10*z) = sumlargest/realisations;
        averagesecondlargest(10*z) = sumsecondlargest/realisations;
        
        hold all
        figure(1);
        plot(z,averagelargest(10*z),'x');
        figure(2);
        plot(z,averagesecondlargest(10*z), 'o');
    end
end