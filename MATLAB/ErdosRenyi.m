% some code to generate Erdos Renyi random graphs

for N = [1000]
    A = zeros(N);
    
    for z = [1000]/10
        alllambda = [];
        sumlargest = 0;
        sumsecondlargest = 0;
        averagelargest = [];
        averagesecondlargest = [];
        sumclustercoeff=0;
        
        for realisations = 1:20
            p = z/N; % the probability of an ede being chosen.
            % using the MIT graph theory toolbox
            A = random_graph(N,p);
%             listofcomponents = find_conn_comp(A);
            
%             largest = 0;
%             %find the largest components
%             for i=1:length(listofcomponents)
%                 if length(listofcomponents{i})> largest
%                     largestindex = i;
%                     largest = length(listofcomponents{i});  
%                 end
%             end
            
%             secondlargest = 0;
%             % find the second largest
%             for i=1:length(listofcomponents)
%                 if (i ~= largestindex) &(length(listofcomponents{i})> secondlargest)
%                     secondlargestindex = i;
%                     secondlargest = length(listofcomponents{i});
%                 end
%             end
            
%             sumlargest = sumlargest + largest;
%             sumsecondlargest = sumsecondlargest + secondlargest
%         [C1,C2,C]=clust_coeff(A);
%         sumclustercoeff=sumclustercoeff+C2;

            lambda = eig(A);
            alllambda = vertcat(alllambda,lambda);

        end
%         averageclustercoeff=sumclustercoeff/realisations;
%         averagelargest(10*z) = sumlargest/realisations;
%         averagesecondlargest(10*z) = sumsecondlargest/realisations;

%         computing the wigner semicircle
          var = p*(1-p);
          syms lambda;


           [x,f] = ksdensity(alllambda, 'bandwidth', 0.1);
           plot(f,x, 'o')
           hold on
           ezplot((1/(2*pi*var*N))*sqrt(4*var*N - lambda^2),[-sqrt(4*var*N),sqrt(4*var*N)])
           hold off
           
           

        

% 
%         hold all
%         figure(1);
%         plot(z,averagelargest(10*z),'x');
%         figure(2);
%         plot(z,averagesecondlargest(10*z), 'o');
%         figure(3)
%         plot(z,averageclustercoeff,'o')
    end
end