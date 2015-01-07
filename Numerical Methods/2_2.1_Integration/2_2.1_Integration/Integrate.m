function I = Integrate(LeftEdge,RightEdge,NumPoints,IntegrationMethod)
    
    if(LeftEdge > RightEdge)
        disp('Jack, the bounds are wrong way round - terminating!')
        return;
    end

    StepSize = ((RightEdge-LeftEdge) / NumPoints);
    
    switch(IntegrationMethod)
        
        case( Method.Trapezium )
            RunningSum = 0;
            for i = (1:(NumPoints-1))
                RunningSum = RunningSum + f(LeftEdge + i*StepSize);
            end
            I = StepSize * (0.5*f(LeftEdge) + RunningSum + 0.5*f(RightEdge));

        case ( Method.Simpsons )
            RunningSumOne = 0;
            for i = (1:((NumPoints/2)-1))
                RunningSumOne = RunningSumOne + f(LeftEdge + 2*i*StepSize);
            end
            RunningSumTwo = 0;
            for i = (1:(NumPoints/2))
                RunningSumTwo = RunningSumTwo + f(LeftEdge + (2*i-1)*StepSize);
            end
            I = StepSize * (1/3) * (f(LeftEdge) + 2*RunningSumOne + 4*RunningSumTwo + f(RightEdge));
    end      
end

function f = f(x)
     f = 1.5*cos(x^(3/2));
end
