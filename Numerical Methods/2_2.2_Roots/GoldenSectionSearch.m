function Brackets = GoldenSectionSearch( InitialBracket )
    
    tolerance = 10^(-15);
    w = (5^(1/2) - 1)/2;
    %note, if you write w another way, the results you get are slightly
    %uneven. not sure why"!
    Brackets = [];
    
    a = InitialBracket(1);
    b = InitialBracket(2);
    c = InitialBracket(3);
    
    % check its a valid starting bracket
    if ~(f(b) < f(a) && f(b) < f(c))
        error('the bracketing interval does not bracket a minimum');      
    end
    
    while c-a > tolerance
        
        if abs(c-b) > abs(b-a)
            x = b+(1-w)*(c-b);
            if f(b) < f(x)
                c = x;
            else
                %watch the order here!
                a = b;
                b = x;
            end
        else
            x = b-(1-w)*(b-a);
            if f(b)<f(x)
                a = x;
            else 
                c = b;
                b = x;
            end
        end
        Brackets(end+1,:) = [a,b,c];
    end
end

