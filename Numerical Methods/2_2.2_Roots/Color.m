function ColoredResult = Color( A )

    % run through the array. at each element, find which of the unqiue
    % elements it corresponds to, and assign it the number of this unique
    % value.
    
    uniqueresults = unique(A);
    Size = size(A);
    
    for i = 1:Size(1)
        for j = 1:Size(2)
            ColoredResult(i,j) = color(A(i,j),uniqueresults);
        end
    end
end

function ColoredElement = color(element, uniqueresults)
    ColoredElement = find((element == uniqueresults)==1);
end

