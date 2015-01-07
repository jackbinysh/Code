function Root = NewtonRaphson(Initialz)

    z = Initialz;
    NumIterations = 500;
    tolerance = 0.01;

    for k = (1:NumIterations)
        Nextz = z - (f(z)/Df(z));
        
        error = Nextz - z;
        z = Nextz;
        
        % after some number of iterations, if we are not converging, set the
        % result to inf, indicating no convergence
        if ((k > 0.5 * NumIterations) && (abs(error) > tolerance))
            z = Inf;
            break;
        end
       
    end 
    Root = z;
end
    