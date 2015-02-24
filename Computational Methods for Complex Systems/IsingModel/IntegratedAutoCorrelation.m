function [ Tau ] = IntegratedAutoCorrelation( m )
    Tau = 0;
    x= 1;
    t = 0;
    while(x>(10^-3))
        x = (AutoCorrelation(t,abs(m)));
        if (t == 0)
            x0=x;
        end
        x = x/x0;
        Tau = Tau + x;
        t = t+1;
    end
end
    
% takes in a vector m, and an index m up to which to compute the
% autocorrelation.
function [xt] = AutoCorrelation(t,m)
    tmax = 50000;
    firstpart = (1/(tmax-t))*sum(m(1:tmax-t).*m((1+t):tmax));
    secondpart = (1/(tmax-t))*sum(m(1:tmax-t))*(1/(tmax-t))*sum(m(t+1:tmax));
    xt = firstpart - secondpart;
end
    

