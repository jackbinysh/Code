T = 500;
L = 100;
X = zeros(T,2*L);
N = 10; 

FitnessMatrix = zeros(N,N);
FitnessMatrix(:) = 0.5;


%intialising

for i = 1:L
    X(1,(2*i)-1) = randi(N);
end
   
for t = 1:T-1
    for j = 1:2*L
        % do it for the zeros too, no harm, avoids iritating cases
        
        if j == 1
            leftparent = X(t,2*L);
        else
            leftparent = X(t,j-1);
        end
         
        
        if j == 2*L
            rightparent = X(t,1);
        else 
            rightparent = X(t,j+1);
        end
        
        if leftparent ~= 0
            p = FitnessMatrix(leftparent,rightparent);
        end
        
        if(leftparent == rightparent)
            X(t+1,j) = leftparent;
        elseif rand <= p
            X(t+1,j) = leftparent;
        else
           X(t+1,j) = rightparent;
        end
    end
end


%INSERT HAX HERE
for i = 1:T
    for j = 1:2*L
        if X(i,j) ~= 0
            X(i,j) = X(i,j)+2;
            %for the stupid color spacing
            % shifting the numbers away from 0
        end
    end
end

%the imaging
imagesc(X);




            
            
        
        


